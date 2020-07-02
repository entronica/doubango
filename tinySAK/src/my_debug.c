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

#include "my_debug.h"
#include "tsk_memory.h"
#include "tsk_string.h"
#include "tsk_mutex.h"

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h> /* puts, printf */
#include <time.h>  /* time_t, struct tm, time, localtime */
#include <errno.h>

static int tsk_debug_level = DEBUG_LEVEL;
static tsk_mutex_handle_t* debug_mutex;

void tsk_debug_init() {
    debug_mutex = tsk_mutex_create();
}

void tsk_debug_set_log_file(const char *logfile)
{
    strcpy(LOG_FILE, logfile);
}

const char *tsk_debug_get_log_file()
{
    return LOG_FILE;
}

void tsk_debug_set_log_path(const char *pathfile)
{
    strcpy(LOG_PATH, pathfile);
}

const char *tsk_debug_get_log_path()
{
    return LOG_PATH;
}

void tsk_debug_set_log_file_path(const char *path, const char *file)
{
    sprintf(LOG_PATH_FILE, "%s/%s", path, file);
}

const char *tsk_debug_get_log_file_path()
{
    return LOG_PATH_FILE;
}

const char *tsk_debug_get_current_time()
{

    struct tm tm;
    struct timeval curTime;
    gettimeofday(&curTime, NULL);
    tm = *localtime(&curTime.tv_sec);
    int micro = curTime.tv_usec / 1000;
    sprintf(LOG_TIMESTAMP, "%02d%02d%04d %02d:%02d:%02d.%03d|%d", tm.tm_mday, tm.tm_mon + 1, 1900 + tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec, micro, getpid());

    return LOG_TIMESTAMP;
}

int tsk_debug_writer(const void *arg, const char *fmt, ...)
{
    tsk_mutex_lock(debug_mutex);

    const char *filepath = tsk_debug_get_log_file_path();
    FILE *file = fopen(filepath, "a+"); // do not forget to close the file using fclose().
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return -1;
    }

    struct tm tm;
    struct timeval curTime;
    gettimeofday(&curTime, NULL);
    tm = *localtime(&curTime.tv_sec);
    int micro = curTime.tv_usec / 1000;

    //31012020 21:11:59.000|
    char *b = tsk_null;
    tsk_sprintf(&b, "%02d%02d%04d %02d:%02d:%02d.%03d|%d", tm.tm_mday, tm.tm_mon + 1, 1900 + tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec, micro, getpid());
    fputs(b, file);
    TSK_FREE(b);

    b = tsk_null;
    va_list ap;
    const void *_this = (void *)arg; // value passed to the framework using tsk_debug_set_arg_data()
    va_start(ap, fmt);
    tsk_sprintf_2(&b, fmt, &ap);
    fputs(b, file);
    TSK_FREE(b);
    

    va_end(ap);
    fclose(file);
    tsk_mutex_unlock(debug_mutex);
    return 0;
}