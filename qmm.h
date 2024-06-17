/*
QMM (beta) - Q3 MultiMod
Copyright 2004-2024
https://github.com/thecybermind/qmm/
3-clause BSD license: https://opensource.org/license/bsd-3-clause

Created By:
    Kevin Masterson < cybermind@gmail.com >

*/

#ifndef __QMM_H__
#define __QMM_H__

#ifdef WIN32
 #define DLLEXPORT __declspec(dllexport)
 #ifdef linux
  #undef linux
 #endif
#else
 #define DLLEXPORT /* */
#endif
#define C_DLLEXPORT extern "C" DLLEXPORT

typedef int (QDECL *eng_syscall_t)(int, ...);
typedef int (*mod_vmMain_t)(int, int, int, int, int, int, int, int, int, int, int, int, int);
typedef void (*mod_dllEntry_t)(eng_syscall_t);

//plugins and internal use
typedef struct plugininfo_s {
	char* name;		//name of plugin
	char* version;		//version of plugin
	char* desc;		//description of plugin
	char* author;		//author of plugin
	char* url;		//website of plugin
	int canpause;		//can this plugin be paused?
	int loadcmd;		//can this plugin be loaded via cmd
	int unloadcmd;		//can this plugin be unloaded via cmd
} plugininfo_t;

typedef enum pluginres_e {
	QMM_UNUSED = -2,
	QMM_ERROR = -1,
	QMM_IGNORED = 0,
	QMM_OVERRIDE,
	QMM_SUPERCEDE
} pluginres_t;

//QMM_Query(plugininfo_t** pinfo);
typedef void (*plugin_query)(plugininfo_t**);
//QMM_Attach(eng_syscall_t syscall, mod_vmMain_t vmMain, pluginres_t* result, int iscmd)
typedef int (*plugin_attach)(eng_syscall_t, mod_vmMain_t, pluginres_t*, int);
//QMM_Detach(int iscmd)
typedef void (*plugin_detach)(int);
//QMM_syscall(int cmd, int, int, int, int, int, int, int, int, int, int, int, int)
typedef int (*plugin_syscall)(int, int, int, int, int, int, int, int, int, int, int, int, int);
//QMM_vmMain(int cmd, int, int, int, int, int, int, int, int, int, int, int, int)
typedef int (*plugin_vmmain)(int, int, int, int, int, int, int, int, int, int, int, int, int);

//plugin use only
extern pluginres_t* g_result;		//set to 'result' in QMM_Attach
extern plugininfo_t g_plugininfo;	//set '*pinfo' to &g_plugininfo in QMM_Query
extern eng_syscall_t g_syscall;		//set to 'engfunc' in QMM_Attach
extern mod_vmMain_t g_vmMain;		//set to 'modfunc' in QMM_Attach
extern int g_vmbase;			//set to g_syscall(G_CVAR_VARIABLE_INTEGER_VALUE, "qmmvm_vmbase") in QMM_Attach
C_DLLEXPORT void QMM_Query(plugininfo_t** pinfo);
C_DLLEXPORT int QMM_Attach(eng_syscall_t engfunc, mod_vmMain_t modfunc, pluginres_t* presult, int iscmd);
C_DLLEXPORT void QMM_Detach(int iscmd);
C_DLLEXPORT int QMM_vmMain(int cmd, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11);
C_DLLEXPORT int QMM_syscall(int cmd, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11);
C_DLLEXPORT int QMM_vmMain_Post(int cmd, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11);
C_DLLEXPORT int QMM_syscall_Post(int cmd, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11);

#define QMM_RETURN(x, y)	return (*g_result = (pluginres_t)(x), (y))
//do { *g_result = (pluginres_t)(x); return (y); } while(0);
#define QMM_RET_ERROR(x)	QMM_RETURN(QMM_ERROR, (x))
#define QMM_RET_IGNORED(x)	QMM_RETURN(QMM_IGNORED, (x))
#define QMM_RET_OVERRIDE(x)	QMM_RETURN(QMM_OVERRIDE, (x))
#define QMM_RET_SUPERCEDE(x)	QMM_RETURN(QMM_SUPERCEDE, (x))

//modified to not add/subtract g_vmbase if x is NULL
#define GETPTR(x,y)		(x ? (y)((int)(x) + g_vmbase) : NULL)
#define SETPTR(x,y)		(x ? (y)((int)(x) - g_vmbase) : NULL)

//for non-API function hooking
#define SETVMHOOK_VOID(x) do { if (g_vmbase) { g_vmMain(-1,(int)x,0,0,0,0,0,0,0,0,0,0,0); return; } } while(0)
#define SETVMHOOK(x) do { if (g_vmbase) { g_vmMain(-1,(int)x,0,0,0,0,0,0,0,0,0,0,0); return 0; } } while(0)

#endif //__QMM_H__
