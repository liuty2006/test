// async_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <future>
#include <iostream>
#include <windows.h>
//#include <stout/stringify.hpp>

bool is_prime(int x)
{
	for (int i = 1; i<x; i++)
	{
		//
		::Sleep(1000);
		std::cout << "*";
		//if (x % i == 0)
		if (i == 5)
			return false;
	}
	return true;
}

//
void async_test()
{
	//auto f = std::async(std::launch::async, is_prime, 700020007);
	std::future<bool> fut = std::async(std::launch::async, is_prime, 700020007);
	std::cout << "please wait";
	std::chrono::milliseconds span(10);
	//while (fut.wait_for(span) != std::future_status::ready)
	//	std::cout << ".";
	std::cout << std::endl;

	if (fut.wait_for(span) != std::future_status::ready) {
		return;
	}

	bool ret = fut.get();
	std::cout << "final result: " << ret << std::endl;
	//std::cout << "final result: " << stringify(ret) << std::endl;
}

int main()
{
	async_test();

	//
	std::cout << "over."<< std::endl;

	getchar();
    return 0;
}

