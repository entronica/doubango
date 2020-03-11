/* Copyright (C) 2019-Present Narongsak Mala <narongsak.mala@gmail.com>
* Copyright (C) 2019-Present Narongsak Mala <narongsak.mala@gmail.com>
* This file is part of Open Source Doubango Framework.
*
* DOUBANGO is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* DOUBANGO is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with DOUBANGO.
*
*/

#ifndef _MY_DEBUG_H_
#define _MY_DEBUG_H_

#include "tinysak_config.h"


TSK_BEGIN_DECLS

#if !defined(DEBUG_LEVEL)
#define DEBUG_LEVEL DEBUG_LEVEL_INFO
#endif

#ifndef DEBUG_LEVEL_INFO
#define DEBUG_LEVEL_INFO 4
#endif
#ifndef DEBUG_LEVEL_WARN
#define DEBUG_LEVEL_WARN 3
#endif
#ifndef DEBUG_LEVEL_ERROR
#define DEBUG_LEVEL_ERROR 2
#endif
#ifndef DEBUG_LEVEL_FATAL
#define DEBUG_LEVEL_FATAL 1
#endif

static char LOG_FILE[128] = "webrtc2sip.log";
static char LOG_PATH[128] = "./";
static char LOG_PATH_FILE[256] = "./webrtc2sip.log";
static char LOG_TIMESTAMP[128] = "";

typedef int (*tsk_debug_f)(const void* arg, const char* fmt, ...);

TINYSAK_API void tsk_debug_set_arg_data(const void*);
TINYSAK_API const void* tsk_debug_get_arg_data();
TINYSAK_API void tsk_debug_set_info_cb(tsk_debug_f );
TINYSAK_API tsk_debug_f tsk_debug_get_info_cb();
TINYSAK_API void tsk_debug_set_warn_cb(tsk_debug_f );
TINYSAK_API tsk_debug_f tsk_debug_get_warn_cb();
TINYSAK_API void tsk_debug_set_error_cb(tsk_debug_f );
TINYSAK_API tsk_debug_f tsk_debug_get_error_cb( );
TINYSAK_API void tsk_debug_set_fatal_cb(tsk_debug_f );
TINYSAK_API tsk_debug_f tsk_debug_get_fatal_cb( );
TINYSAK_API int tsk_debug_get_level( );
TINYSAK_API void tsk_debug_set_level(int );
TINYSAK_API void tsk_debug_set_log_file( const char* );
TINYSAK_API const char* tsk_debug_get_log_file( );
TINYSAK_API void tsk_debug_set_log_path( const char* );
TINYSAK_API const char* tsk_debug_get_log_path( );
TINYSAK_API void tsk_debug_set_log_file_path( const char* , const char*);
TINYSAK_API const char* tsk_debug_get_log_file_path( );
TINYSAK_API const char* tsk_debug_get_current_time( );
TINYSAK_API int tsk_debug_writer(const void* arg, const char* fmt, ...);

/* INFO */
#define TSK_DEBUG_INFO(FMT, ...)		\
	if(tsk_debug_get_level() >= DEBUG_LEVEL_INFO){ \
		if(tsk_debug_get_info_cb()) \
			tsk_debug_get_info_cb()(tsk_debug_get_arg_data(), "|INFO|%s|%s()|%u|" FMT "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
		else \
			fprintf(stderr, "%s|INFO|%s|%s()|%u|" FMT "\n", tsk_debug_get_current_time(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
	}


/* WARN */
#define TSK_DEBUG_WARN(FMT, ...)		\
	if(tsk_debug_get_level() >= DEBUG_LEVEL_WARN){ \
		if(tsk_debug_get_warn_cb()) \
			tsk_debug_get_warn_cb()(tsk_debug_get_arg_data(), "|WARN|%s|%s()|%u|" FMT "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
		else \
			fprintf(stderr, "%s|WARN|%s|%s()|%u|" FMT "\n", tsk_debug_get_current_time(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
	}

/* ERROR */
#define TSK_DEBUG_ERROR(FMT, ...) 		\
	if(tsk_debug_get_level() >= DEBUG_LEVEL_ERROR){ \
		if(tsk_debug_get_error_cb()) \
			tsk_debug_get_error_cb()(tsk_debug_get_arg_data(), "|ERROR|%s|%s()|%u|" FMT "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
		else \
			fprintf(stderr, "%s|ERROR|%s|%s()|%u|" FMT "\n", tsk_debug_get_current_time(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
	}


/* FATAL */
#define TSK_DEBUG_FATAL(FMT, ...) 		\
	if(tsk_debug_get_level() >= DEBUG_LEVEL_FATAL){ \
		if(tsk_debug_get_fatal_cb()) \
			tsk_debug_get_fatal_cb()(tsk_debug_get_arg_data(), "|FATAl|%s|%s()|%u|" FMT "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
		else \
			fprintf(stderr, "%s|FATAl|%s|%s()|%u|" FMT "\n", tsk_debug_get_current_time(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
	}
	
/* INIT DEBUG */
#define INIT_DEBUG_WRITER() tsk_debug_set_info_cb(tsk_debug_writer);\
tsk_debug_set_warn_cb(tsk_debug_writer);\
tsk_debug_set_error_cb(tsk_debug_writer);\
tsk_debug_set_fatal_cb(tsk_debug_writer)

TSK_END_DECLS

#endif