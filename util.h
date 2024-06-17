/*
QMM (beta) - Q3 MultiMod
Copyright 2004-2024
https://github.com/thecybermind/qmm-beta/
3-clause BSD license: https://opensource.org/license/bsd-3-clause

Created By:
    Kevin Masterson < cybermind@gmail.com >

*/

#ifndef __UTIL_H__
#define __UTIL_H__

//Format a string
char* vaf(char*, ...);
//find CPlugin with given id, return ptr
CPlugin* findplugin(int);

//return a string name for the int
const char* modfuncname(int);
//return a string name for the int
const char* engfuncname(int);

#endif //__UTIL_H__
