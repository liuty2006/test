// s7.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "stdio.h"
#include "s7.h"

//
int Add(int plus1, int plus2)
{
	return plus1 + plus2;
}

void hello() 
{
	printf("hello");
}