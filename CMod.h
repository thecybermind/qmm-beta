/*
QMM (beta) - Q3 MultiMod
Copyright 2004-2024
https://github.com/thecybermind/qmm/
3-clause BSD license: https://opensource.org/license/bsd-3-clause

Created By:
    Kevin Masterson < cybermind@gmail.com >

*/

#ifndef __CMOD_H__
#define __CMOD_H__

#include "CDLL.h"
#include "qmm.h"

class CMod {
	public:
		CMod();
		~CMod();
		bool LoadMod(const char*, eng_syscall_t);
		void UnloadMod();

		mod_vmMain_t get_vmMain() { return this->vmMain; }
		char* get_filename() { return this->filename; }
	private:
		mod_dllEntry_t dllEntry;
		mod_vmMain_t vmMain;
		char* filename;
		CDLL dll;
};

#endif //__CMOD_H__
