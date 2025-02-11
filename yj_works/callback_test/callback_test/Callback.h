#pragma once

typedef void(_stdcall *MyFun)(int n);

class Callback
{
public:
	Callback();
	~Callback();

private:
	MyFun myFun;
public:
	void SetFun(MyFun _myFun)
	{
		myFun = _myFun;
	}

	void LetRun(int n)
	{
		myFun(n);
	}
};

