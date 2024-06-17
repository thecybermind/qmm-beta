/*
QMM (beta) - Q3 MultiMod
Copyright 2004-2024
https://github.com/thecybermind/qmm/
3-clause BSD license: https://opensource.org/license/bsd-3-clause

Created By:
    Kevin Masterson < cybermind@gmail.com >

*/

#include "version.h"
#include <stdlib.h>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include "CDLL.h"

CDLL::CDLL() {
	this->hDLL = NULL;
}

CDLL::~CDLL() {
	this->Unload();

	this->hDLL = NULL;
}

//load lib with given filename
bool CDLL::Load(const char* file) {
#ifdef WIN32
	//don't bother with the fugly win32 types
	this->hDLL = (void*)LoadLibrary(file);
#else
	this->hDLL = dlopen(file, RTLD_NOW);
#endif
	return (this->hDLL ? 1 : 0);
}

void* CDLL::GetFunc(const char* func) {
#ifdef WIN32
	return (void*)GetProcAddress((HINSTANCE)this->hDLL, func);
#else
	return dlsym(this->hDLL, func);
#endif
}

void CDLL::Unload() {
	if (this->hDLL)
#ifdef WIN32
		FreeLibrary((HINSTANCE)this->hDLL);
#else
		dlclose(this->hDLL);
#endif
}
