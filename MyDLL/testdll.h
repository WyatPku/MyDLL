#pragma once
#ifndef TestDll_H_
#define TestDll_H_
#ifdef MYLIBDLL
#define MYLIBDLL extern "C" _declspec(dllimport)
#else
#define MYLIBDLL extern "C" _declspec(dllexport)
#endif // MYLIBDLL
//MYLIBDLL int __stdcall ADD(int plus1, int plus2, Info* infop);
#endif // !TestDll_H_