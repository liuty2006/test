// s7_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "s7.h"
#pragma comment(lib,"s7.lib")

int main()
{
	hello();
	int n = Add(1,2);
	getchar();
    return 0;
}

