// callback_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Callback.h"

int g_i;

class Win
{
public:
	//Win1();
	//~Win1();

	int n;

	void updateView() {
		n = g_i;
	};
};

//
Win *g_Win;

//下面的这个_stdcall很重要的 
void _stdcall Test(int n)   //如果不定义全局变量，而定义在类中 则必须是 静态成员函数
{
	printf("%d", n);

	//
	g_Win->updateView();
}

int main()
{
	g_Win = new Win;

	//
	Callback call;
	call.SetFun((MyFun)Test);    //调回调函数的接口，并传入一个函数作为参数
	call.LetRun(10);
	
    return 0;
}

