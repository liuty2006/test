// callback_test.cpp : �������̨Ӧ�ó������ڵ㡣
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

//��������_stdcall����Ҫ�� 
void _stdcall Test(int n)   //���������ȫ�ֱ����������������� ������� ��̬��Ա����
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
	call.SetFun((MyFun)Test);    //���ص������Ľӿڣ�������һ��������Ϊ����
	call.LetRun(10);
	
    return 0;
}

