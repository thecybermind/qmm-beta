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
#include <g_public.h>
#include "qmm.h"
#include "main.h"
#include "CMod.h"
#include "CDLL.h"
#include "util.h"

CMod::CMod() {
	this->dllEntry = NULL;
	this->vmMain = NULL;
	this->filename = NULL;
}

CMod::~CMod() {
	this->UnloadMod();
}

//load the given file as the mod, pass the given syscall pointer to the dllEntry() function
bool CMod::LoadMod(const char* file, eng_syscall_t psyscall) {
	//since the filename is made with vaf(), we should copy it to avoid recursive vaf() problems
	char tempfile[MAX_QPATH];
	memcpy(tempfile, file, strlen(file) + 1);
	file = (const char*)tempfile;

	//load DLL, or fail
	if (!this->dll.Load(file)) {
		ENGFUNC(G_PRINT, vaf("[QMM] ERROR: CDLL::Load(\"%s\") failed\n", file));
		return 0;
	}

	//find dllEntry() func, or fail
	if ((this->dllEntry = (mod_dllEntry_t)this->dll.GetFunc("dllEntry")) == NULL) {
		ENGFUNC(G_PRINT, vaf("[QMM] ERROR: Unable to find \"dllEntry\" function in mod file \"%s\"\n", file));
		return 0;
	}

	//find vmMain() func, or fail
	if ((this->vmMain = (mod_vmMain_t)this->dll.GetFunc("vmMain")) == NULL) {
		ENGFUNC(G_PRINT, vaf("[QMM] ERROR: Unable to find \"vmMain\" function in mod file \"%s\"\n", file));
		return 0;
	}

	//give our local syscall to the mod's dllEntry() func
	(this->dllEntry)(psyscall);

	//store filename
	int slen = strlen(file) + 1;
	this->filename = (char*)new char[slen];
	memcpy(this->filename, file, slen);

	return 1;
}

//unload mod file
void CMod::UnloadMod() {
	this->dllEntry = NULL;
	this->vmMain = NULL;
	if (this->filename)
		delete [] this->filename;
	this->filename = NULL;
	this->dll.Unload();
}
