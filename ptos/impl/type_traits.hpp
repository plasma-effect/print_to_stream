#pragma once
#include<iterator>
#include<utility>
#include<type_traits>
#include<tuple>
#include<optional>

namespace ptos
{
	namespace type_traits
	{
#pragma region is_range
		namespace impl
		{
			template<class T>auto has_iterator(T const& v)
				->decltype(std::begin(v), std::end(v), std::true_type());
			std::false_type has_iterator(...);

			template<class T, class U>auto are_iterators_i(T v, U u)
				->decltype(++v, v != u, *v, std::true_type());
			std::false_type are_iterator_i(...);

			template<class T, class U>struct are_iterator
				: decltype(are_iterators_i(std::declval<T>(), std::declval<U>())){};

			template<class T,class = decltype(has_iterator(std::declval<T>()))>struct is_range_i
				: std::false_type{};
			template<class T>struct is_range_i<T, std::true_type>
				: decltype(are_iterators_i(std::begin(std::declval<T>()), std::end(std::declval<T>()))){};
		}
		template<class T>struct is_range :impl::is_range_i<T>
		{

		};
		template<class T>constexpr auto is_range_v = is_range<T>::value;
#pragma endregion
#pragma region is_tuple
		template<class T>struct is_tuple :std::false_type
		{

		};
		template<class... Ts>struct is_tuple<std::tuple<Ts...>> :std::true_type
		{

		};
		template<class T0, class T1>struct is_tuple<std::pair<T0, T1>> :std::true_type
		{

		};
		template<class T>constexpr bool is_tuple_v = is_tuple<T>::value;
#pragma endregion
#pragma region is_optional
		template<class T>struct is_optional :std::false_type
		{

		};
		template<class T>struct is_optional<std::optional<T>> :std::true_type
		{

		};
		template<class T>constexpr auto is_optional_v = is_optional<T>::value;
#pragma endregion
	}
}