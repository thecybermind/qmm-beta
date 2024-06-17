/*
QMM (beta) - Q3 MultiMod
Copyright 2004-2024
https://github.com/thecybermind/qmm-beta/
3-clause BSD license: https://opensource.org/license/bsd-3-clause

Created By:
    Kevin Masterson < cybermind@gmail.com >

*/

#ifndef __CPLUGIN_H__
#define __CPLUGIN_H__

#include "CDLL.h"
#include "qmm.h"

class CPlugin {
	public:
		CPlugin();
		~CPlugin();
		bool LoadQuery(const char*, int);
		int Attach(eng_syscall_t, mod_vmMain_t, int);
		bool Pause();
		void Unpause();
		bool Unload(int);
		
		plugin_vmmain get_QMM_vmMain() { return this->QMM_vmMain; }
		plugin_vmmain get_QMM_vmMain_Post() { return this->QMM_vmMain_Post; }
		plugin_syscall get_QMM_syscall() { return this->QMM_syscall; }
		plugin_syscall get_QMM_syscall_Post() { return this->QMM_syscall_Post; }
		plugininfo_t* get_plugininfo() { return this->plugininfo; }
		char* get_filename() { return this->filename; }
		bool get_paused() { return this->paused; }
		pluginres_t get_result() { return this->result; }
		void set_result(pluginres_t res) { this->result = res; }
		int get_iscmd() { return this->iscmd; }
	private:
		plugin_query QMM_Query;
		plugin_attach QMM_Attach;
		plugin_detach QMM_Detach;
		plugin_vmmain QMM_vmMain;
		plugin_vmmain QMM_vmMain_Post;
		plugin_syscall QMM_syscall;
		plugin_syscall QMM_syscall_Post;
		plugininfo_t* plugininfo;
		char* filename;
		bool paused;
		static pluginres_t result;
		int iscmd;
		CDLL dll;
};
#endif //__CPLUGIN_H__
