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

#include "app_log.h"
#include "tsk_memory.h"

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h> /* puts, printf */
#include <time.h>  /* time_t, struct tm, time, localtime */
#include <errno.h>

static int tsk_app_level = DEBUG_LEVEL;

void tsk_app_set_log_file(const char *logfile)
{
    strcpy(APP_FILE, logfile);
}

const char *tsk_app_get_log_file()
{
    return APP_FILE;
}

void tsk_app_set_log_path(const char *pathfile)
{
    strcpy(APP_PATH, pathfile);
}

const char *tsk_app_get_log_path()
{
    return APP_PATH;
}


void tsk_app_set_log_file_path(const char *path, const char *file)
{
    sprintf(APP_PATH_FILE, "%s/%s", path, file);
}

const char *tsk_app_get_log_file_path()
{
    return APP_PATH_FILE;
}

const char *tsk_app_get_current_time()
{

    struct tm tm;
    struct timeval curTime;
    gettimeofday(&curTime, NULL);
    tm = *localtime(&curTime.tv_sec);
    int micro = curTime.tv_usec / 1000;
    sprintf(APP_TIMESTAMP, "%02d%02d%04d %02d:%02d:%02d.%03d|%d", tm.tm_mday, tm.tm_mon + 1, 1900 + tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec, micro, getpid());

    return APP_TIMESTAMP;
}

int tsk_app_writer(const void *arg, const char *fmt, ...)
{
    const char *filepath = tsk_app_get_log_file_path();
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

    va_list ap;
    const void *_this = (void *)arg; // value passed to the framework using tsk_app_set_arg_data()
    va_start(ap, fmt);
    tsk_sprintf_2(&b, fmt, &ap);
    fputs(b, file);

    TSK_FREE(b);
    va_end(ap);
    fclose(file);
    return 0;
}

static const void *tsk_app_arg_data = tsk_null;
static tsk_app_f tsk_app_info_cb = tsk_null;
static tsk_app_f tsk_app_warn_cb = tsk_null;
static tsk_app_f tsk_app_error_cb = tsk_null;
static tsk_app_f tsk_app_fatal_cb = tsk_null;

/**@ingroup tsk_app_group
* Defines the callback data. Will be the @a arg parameter for the callback function.
* @param arg_data The callback data.
* @sa @ref tsk_app_get_arg_data()
*/
void tsk_app_set_arg_data(const void *arg_data)
{
    tsk_app_arg_data = arg_data;
}
/**@ingroup tsk_app_group
* Gets the callback data passed to the framework using @ref tsk_app_set_arg_data().
* @retval The callback data.
* @sa @ref tsk_app_set_arg_data()
*/
const void *tsk_app_get_arg_data()
{
    return tsk_app_arg_data;
}
/**@ingroup tsk_app_group
* Sets the callback function to call when @ref TSK_DEBUG_INFO() is internally used.
* @param cb A pointer to the callback function.
* @sa @ref tsk_app_set_warn_cb() @ref tsk_app_set_error_cb() @ref tsk_app_set_fatal_cb().
*/
void tsk_app_set_info_cb(tsk_app_f cb)
{
    tsk_app_info_cb = cb;
}
/**@ingroup tsk_app_group
* Gets the callback function defined using @ref tsk_app_set_info_cb().
* @retval A pointer to the callback function.
*/
tsk_app_f tsk_app_get_info_cb()
{
    return tsk_app_info_cb;
}
/**@ingroup tsk_app_group
* Sets the callback function to call when @ref TSK_DEBUG_WARN() is internally used.
* @param cb A pointer to the callback function.
* @sa @ref tsk_app_set_info_cb() @ref tsk_app_set_error_cb() @ref tsk_app_set_fatal_cb().
*/
void tsk_app_set_warn_cb(tsk_app_f cb)
{
    tsk_app_warn_cb = cb;
}
/**@ingroup tsk_app_group
* Gets the callback function defined using @ref tsk_app_set_warn_cb().
* @retval A pointer to the callback function.
*/
tsk_app_f tsk_app_get_warn_cb()
{
    return tsk_app_warn_cb;
}
/**@ingroup tsk_app_group
* Sets the callback function to call when @ref TSK_DEBUG_ERROR() is internally used.
* @param cb A pointer to the callback function.
* @sa @ref tsk_app_set_info_cb() @ref tsk_app_set_warn_cb() @ref tsk_app_set_fatal_cb().
*/
void tsk_app_set_error_cb(tsk_app_f cb)
{
    tsk_app_error_cb = cb;
}
/**@ingroup tsk_app_group
* Gets the callback function defined using @ref tsk_app_set_error_cb().
* @retval A pointer to the callback function.
*/
tsk_app_f tsk_app_get_error_cb()
{
    return tsk_app_error_cb;
}
/**@ingroup tsk_app_group
* Sets the callback function to call when @ref TSK_DEBUG_FATAL() is internally used.
* @param cb A pointer to the callback function.
* @sa @ref tsk_app_set_info_cb() @ref tsk_app_set_warn_cb() @ref tsk_app_set_error_cb().
*/
void tsk_app_set_fatal_cb(tsk_app_f cb)
{
    tsk_app_fatal_cb = cb;
}
/**@ingroup tsk_app_group
* Gets the callback function defined using @ref tsk_app_set_fatal_cb().
* @retval A pointer to the callback function.
*/
tsk_app_f tsk_app_get_fatal_cb()
{
    return tsk_app_fatal_cb;
}
/**@ingroup tsk_app_group
* Gets the debug level defined using @ref tsk_app_set_level.
* @retval The debug level. <b>Must be</b>: @ref DEBUG_LEVEL_INFO, @ref DEBUG_LEVEL_WARN, @ref DEBUG_LEVEL_ERROR or @ref DEBUG_LEVEL_FATAL.
* @sa @ref tsk_app_set_level()
*/
int tsk_app_get_level()
{
    return tsk_app_level;
}
/**@ingroup tsk_app_group
* Sets the debug level.
* @param level The debug level. <b>Must be</b>: @ref DEBUG_LEVEL_INFO, @ref DEBUG_LEVEL_WARN, @ref DEBUG_LEVEL_ERROR or @ref DEBUG_LEVEL_FATAL.
* @sa @ref tsk_app_get_level()
*/
void tsk_app_set_level(int level)
{
    tsk_app_level = level;
}