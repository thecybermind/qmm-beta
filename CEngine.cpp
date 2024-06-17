/*
QMM (beta) - Q3 MultiMod
Copyright 2004-2024
https://github.com/thecybermind/qmm-beta/
3-clause BSD license: https://opensource.org/license/bsd-3-clause

Created By:
    Kevin Masterson < cybermind@gmail.com >

*/

#include "version.h"
#include <q_shared.h>
#include "qmm.h"
#include "CEngine.h"

CEngine::CEngine() {
	this->syscall = NULL;
}

CEngine::~CEngine() {
	this->syscall = NULL;
}
