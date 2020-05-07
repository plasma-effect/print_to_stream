#include"ptos/print.hpp"
#include<iostream>
#include<optional>
#include<vector>

template<class... Ts>void print(Ts const... vs)
{
	ptos::println(std::cout, vs...);
}

int main()
{
	std::vector vec = { 4,5,6 };
	std::string str = "hoge";
	std::optional<int> opt0 = 10, opt1;
	print(1);
	print(2, 3);
	print(vec);
	print(std::make_tuple(7, 8, 9));
	print("test");
	print(str);
	print(opt0);
	print(opt1);
}