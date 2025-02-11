#pragma once
#ifndef S7_H_
#define S7_H_

/*
#ifdef S7LIBDLL
#define S7LIBDLL extern "C" _declspec(dllimport) 
#else
#define S7LIBDLL extern "C" _declspec(dllexport) 
#endif

void hello();
int Add(int plus1, int plus2);
*/
//You can also write like this:

extern "C" {
        _declspec(dllexport) void hello();
        _declspec(dllexport) int Add(int plus1, int plus2);
};
#endif
