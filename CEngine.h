/*
QMM (beta) - Q3 MultiMod
Copyright 2004-2024
https://github.com/thecybermind/qmm-beta/
3-clause BSD license: https://opensource.org/license/bsd-3-clause

Created By:
    Kevin Masterson < cybermind@gmail.com >

*/

#ifndef __CENGINE_H__
#define __CENGINE_H__

#include "qmm.h"

class CEngine {
	public:
		CEngine();
		~CEngine();

		eng_syscall_t get_syscall() { return this->syscall; }
		void set_syscall(eng_syscall_t psyscall) { this->syscall = psyscall; }
	private:
		eng_syscall_t syscall;
};

#endif //__CENGINE_H__
