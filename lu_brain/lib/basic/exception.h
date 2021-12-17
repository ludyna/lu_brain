/**
	Copyright © 2022 Oleh Ihorovych Novosad
*/
#ifndef _LU_EXCEPTION_H
#define _LU_EXCEPTION_H

#include "debug.h"

#define lu_exception CEXCEPTION_T
#define lu_try Try 
#define lu_catch Catch

// entity NULL
#define LU__ENT_NULL 0

// Exceptions list
enum lu_e {
	LU_E__FIRST = 6000, 
	
	// Lu_Mem 
	LU_E__MEM_ALLOC_FAIL, 

	// Brain
	LU_E__BRAIN_OPTS_REQUIRED, 
	LU_E__BRAIN_RECS_REQUIRED, 

	LU_E__LAST
};

#ifndef LU__USER_ASSERT_DEFAULT
#define LU__USER_ASSERT_DEFAULT 1
#endif 

extern lu_bool g_user_assert;

static inline void lu__user_assert_on() { g_user_assert = 1; }
static inline void lu__user_assert_off() { g_user_assert = 0; }

void lu__throw_internal(enum lu_e e, const char* file, int line);
void lu__throw_with_message_internal(enum lu_e e, const char* file, int line, const char* fmt, ...);

#define lu__throw(e) lu__throw_internal(e, __FILE__, __LINE__);
#define lu__throw_with_message(e, msg, ...) lu__throw_with_message_internal(e, __FILE__, __LINE__, msg, __VA_ARGS__)

void* lu__user_debug_internal(const char* func, const char* file, int line, const char* fmt);
void* lu__user_debug_args_internal(const char* func, const char* file, int line, const char* fmt, ...);

#define lu__user_debug(msg) lu__user_debug_internal(__func__, __FILE__, __LINE__, msg)
#define lu__user_debug_args(msg, ...) lu__user_debug_args_internal	(__func__, __FILE__, __LINE__, msg, __VA_ARGS__)

#define lu__user_assert(exp, msg) if(!(exp)) return g_user_assert ? lu__user_debug(msg) : NULL;
#define lu__user_assert_void(exp, msg) if(!(exp)) { if (g_user_assert) lu__user_debug(msg); return; }
#define lu__user_assert_ent(exp, msg) if(!(exp)) { if (g_user_assert) lu__user_debug(msg); return LU__ENT_NULL; }
#define lu__user_assert_ext(exp, msg, func, file, line) if(!(exp)) return g_user_assert ? lu__user_debug_internal(func, file, line, msg) : NULL;
#define lu__user_assert_void_ext(exp, msg, func, file, line) if(!(exp)) { if (g_user_assert) lu__user_debug_internal(func, file, line, msg); return; }
#define lu__user_assert_ent_ext(exp, msg, func, file, line) if(!(exp)) { if (g_user_assert) lu__user_debug_internal(func, file, line, msg); return EXT_NULL; }


#endif // _LU_EXCEPTION_H

