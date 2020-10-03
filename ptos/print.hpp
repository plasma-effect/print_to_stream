#pragma once
#include"ptos/impl/type_traits.hpp"
#include<string>
#include<ostream>

namespace ptos
{
	namespace detail
	{
		template<class Stream, class T, std::size_t... Is>void write_tuple(Stream&, T const&, std::index_sequence<Is...>);
		template<class Stream, class T>void write_iterate(Stream&, T const& rng, char manip);

		template<class Stream>void write(Stream& stream, char const* str)
		{
			stream << str;
		}
		template<class Stream>void write(Stream& stream, wchar_t const* str)
		{
			stream << str;
		}
		template<class Stream, class T>void write(Stream& stream, T const& v)
		{
			if constexpr (std::is_same_v<T, std::string>)
			{
				stream << v;
			}
			else if constexpr (type_traits::is_range_v<T>)
			{
				write_iterate(stream, v, ' ');
			}
			else if constexpr (type_traits::is_tuple_v<T>)
			{
				write_tuple(stream, v, std::make_index_sequence<std::tuple_size_v<T>>());
			}
			else if constexpr (type_traits::is_optional_v<T>)
			{
				if (v)
				{
					write(stream, *v);
				}
				else
				{
					stream << "[ ]";
				}
			}
			else
			{
				stream << v;
			}
		}
		template<class Stream, class T, class... Ts>auto write(Stream& stream, T const& v, Ts const&... vs)
			->std::enable_if_t<sizeof...(Ts) != 0>
		{
			write(stream, v);
			write(stream, " ");
			write(stream, vs...);
		}
		template<class Stream, class T, std::size_t... Is>void write_tuple(Stream& stream, T const& v, std::index_sequence<Is...>)
		{
			write(stream, std::get<Is>(v)...);
		}
		template<class Stream, class T>void write_iterate(Stream& stream, T const& rng, char manip)
		{
			auto ite = std::begin(rng);
			auto end = std::end(rng);
			if (ite != end)
			{
				write(stream, *ite);
				for (++ite; ite != end; ++ite)
				{
					stream << manip;
					write(stream, *ite);
				}
			}
		}
		template<class Stream>void write(Stream& stream)
		{

		}
	}
	template<class Stream, class... Ts>void print(Stream& stream, Ts const&... vs)
	{
		detail::write(stream, vs...);
	}
	template<class Stream, class... Ts>void println(Stream& stream, Ts const&... vs)
	{
		detail::write(stream, vs...);
		stream << std::endl;
	}
	template<class Stream, class T>void print_range(Stream& stream, T const& rng)
	{
		if constexpr (!type_traits::is_range_v<T>)
		{
			static_assert(type_traits::is_range_v<T>, "The argument of this function must be range");
		}
		else
		{
			for (auto&& v : rng)
			{
				println(stream, v);
			}
		}
	}
}