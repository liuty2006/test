// point_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	//
/*	unsigned int i = 0;
	char** pP = NULL;
	
	//
	pP = (char**)calloc(128, sizeof(char*));
	for (i = 0; i < 128; ++i)
	{
		pP[i] = (char*)calloc(128, sizeof(char));
		memset()
	}
	
	// 这种初始化方法，好像不存在越界。
	pP[1000] = "ddd";
	cout << pP[1000] << endl;
*/

	unsigned int i = 0;
	char** pp = NULL;
	
	//
	pp = (char**)calloc(128, sizeof(char*));
	for (i = 0; i < 128; ++i)
	{
		pp[i] = (char*)calloc(128, sizeof(char));
		//memset(pp[i], 0, 128);
	}

	//
	//char* p = pp[0];
	
	//
	vector<char *> vecValue;
	vecValue.push_back("hello");
	
	//
	//char p[128];
	//strcpy_s(p, 6, "hello");
	//strcpy_s(p, 5, vecValue[0]);
	strcpy_s(pp[0],6, vecValue[0]);

	printf("%s", pp[0]);


	//
	//char *szVal;
	//vecValue.push_back("hello");
    return 0;
}

