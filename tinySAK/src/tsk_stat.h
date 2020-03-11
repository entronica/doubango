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
#ifndef _STAT_H_
#define _STAT_H_

#include "tinysak_config.h"
#include "tsk_object.h"
#include "tsk_timer.h"

TSK_BEGIN_DECLS

typedef enum TSK_STAT_NAME
{
    TSK_STAT_RECEIVED_MESSAGE = 0,
    TSK_STAT_SENT_MESSAGE,

    TSK_STAT_SIP_SENT,
    TSK_STAT_SIP_RECV,

    TSK_STAT_WEBSOCKET_SENT,
    TSK_STAT_WEBSOCKET_RECV,

    TSK_STAT_CONNECTION,
    TSK_STAT_ERROR_SENDING,
    TSK_STAT_ERROR_RECEIVING,

    TSK_STAT_SIP_REQUEST_INVITE,
    TSK_STAT_SIP_REQUEST_UPDATE,
    TSK_STAT_SIP_REQUEST_PRACK,
    TSK_STAT_SIP_REQUEST_ACK,
    TSK_STAT_SIP_REQUEST_OPTIONS,
    TSK_STAT_SIP_REQUEST_BYE,
    TSK_STAT_SIP_REQUEST_CANCEL,
    TSK_STAT_SIP_REQUEST_INFO,
    TSK_STAT_SIP_REQUEST_NOTIFY,
    TSK_STAT_SIP_REQUEST_REFER,

    TSK_STAT_LAST
} TSK_STAT_NAME;

static const char *TSK_STR_STAT[TSK_STAT_LAST] = {
    "RECEIVED_MESSAGE",
    "SENT_MESSAGE",

    "SIP_SENT",
    "SIP_RECV",

    "WEBSOCKET_SENT",
    "WEBSOCKET_RECV",

    "CONNECTION",

    "ERROR_SENDING",
    "ERROR_RECEIVING",

    "SIP_REQUEST_INVITE",
    "SIP_REQUEST_UPDATE",
    "SIP_REQUEST_PRACK",
    "SIP_REQUEST_ACK",
    "SIP_REQUEST_OPTIONS",
    "SIP_REQUEST_BYE",
    "SIP_REQUEST_CANCEL",
    "SIP_REQUEST_INFO",
    "SIP_REQUEST_NOTIFY",
    "SIP_REQUEST_REFER",
};

typedef struct stat_s
{
    TSK_DECLARE_OBJECT; /* Mandatory */
    int stats[TSK_STAT_LAST];
    int interval;
    int timer_id;
} stat_t;

// (constructor)
static tsk_object_t *stat_ctor(tsk_object_t *self, va_list *app);

// (destructor)
static tsk_object_t *stat_dtor(tsk_object_t *self);

// (comparator)
static int stat_cmp(const tsk_object_t *_p1, const tsk_object_t *_p2);

static const tsk_object_def_t stat_def_t =
    {
        sizeof(stat_t),
        stat_ctor,
        stat_dtor,
        stat_cmp};



static stat_t *STAT = NULL;
static char STAT_FILE[256] = "webrtc2sip.stat";
static char STAT_PATH[256] = "./";
static char STAT_PATH_FILE[512] = "./webrtc2sip.stat";
static char STAT_TIMESTAMP[128] = "";
static int STAT_INTERVAL = 10;  //10 seconds
static int STAT_RESET = 1; //enable resetting on next day

#define TSK_STAT_INIT(timeout) STAT = (stat_t *)TSK_STAT_CREATE(timeout)
#define TSK_STAT_CREATE() tsk_object_new(&stat_def_t)

TINYSAK_API int tsk_stat_init(int interval);
TINYSAK_API void tsk_stat_increase(TSK_STAT_NAME name);
TINYSAK_API void tsk_stat_reset();
TINYSAK_API void tsk_stat_set_path_file(const char* path, const char* filename);
TINYSAK_API const char* tsk_stat_path_file();
TINYSAK_API int tsk_stat_count(TSK_STAT_NAME name);
TINYSAK_API const char* tsk_stat_to_string();
TINYSAK_API void tsk_stat_set_filename(const char *file);
TINYSAK_API void tsk_stat_set_path(const char *path);
TINYSAK_API void tsk_stat_set_interval(int interval);
TINYSAK_API void tsk_stat_reset_enable(int is_reset);
TINYSAK_API const char* tsk_stat_get_filename();
TINYSAK_API const char* tsk_stat_get_path();
TINYSAK_API int tsk_stat_get_interval();
TINYSAK_API int tsk_stat_is_reset();
TINYSAK_API static int _tsk_stat_writer_cb(const void* arg, tsk_timer_id_t timer_id);
TINYSAK_API int tsk_stat_start();

TSK_END_DECLS

#endif //_STAT_H_