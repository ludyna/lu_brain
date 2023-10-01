/**
	Copyright © 2022 Oleh Ihorovych Novosad 
	Defines library fundamentals.
*/
#ifndef _LU_BASIC_H
#define _LU_BASIC_H

#if defined(__linux__)
	#define LU_LINUX
#endif 

#if defined (_WIN64)
	#define LU_WIN64
#endif

#include <limits.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdarg.h>

#ifdef LU_LINUX
	#include <unistd.h>  
	#include <pthread.h>
#endif 

#include <string.h>

#include "../vendor/CException.h"

#include "_module_head.h"
#include "types.h"
#include "debug.h"
#include "version.h"
#include "exception.h"
#include "util.h"
#include "macro.h"

#endif // _LU_BASIC_H
