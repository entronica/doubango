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

    /* DONOT CHANGE THE SEQUENCE OF STAT, 
    IT IS DUE TO MATCH WITH DESCRIPTION */

    TSK_STAT_WS_IN_ACK,
    TSK_STAT_WS_IN_BYE,
    TSK_STAT_WS_IN_CANCEL,
    TSK_STAT_WS_IN_INVITE,
    TSK_STAT_WS_IN_OPTIONS,
    TSK_STAT_WS_IN_REGISTER,
    TSK_STAT_WS_IN_SUBSCRIBE,
    TSK_STAT_WS_IN_NOTIFY,
    TSK_STAT_WS_IN_REFER,
    TSK_STAT_WS_IN_INFO,
    TSK_STAT_WS_IN_UPDATE,
    TSK_STAT_WS_IN_MESSAGE,
    TSK_STAT_WS_IN_PUBLISH,
    TSK_STAT_WS_IN_PRACK,
    TSK_STAT_WS_IN_1XX,
    TSK_STAT_WS_IN_2XX,
    TSK_STAT_WS_IN_3XX,
    TSK_STAT_WS_IN_4XX,
    TSK_STAT_WS_IN_5XX,
    TSK_STAT_WS_IN_6XX,

    TSK_STAT_WS_OUT_ACK,
    TSK_STAT_WS_OUT_BYE,
    TSK_STAT_WS_OUT_CANCEL,
    TSK_STAT_WS_OUT_INVITE,
    TSK_STAT_WS_OUT_OPTIONS,
    TSK_STAT_WS_OUT_REGISTER,
    TSK_STAT_WS_OUT_SUBSCRIBE,
    TSK_STAT_WS_OUT_NOTIFY,
    TSK_STAT_WS_OUT_REFER,
    TSK_STAT_WS_OUT_INFO,
    TSK_STAT_WS_OUT_UPDATE,
    TSK_STAT_WS_OUT_MESSAGE,
    TSK_STAT_WS_OUT_PUBLISH,
    TSK_STAT_WS_OUT_PRACK,
    TSK_STAT_WS_OUT_1XX,
    TSK_STAT_WS_OUT_2XX,
    TSK_STAT_WS_OUT_3XX,
    TSK_STAT_WS_OUT_4XX,
    TSK_STAT_WS_OUT_5XX,
    TSK_STAT_WS_OUT_6XX,

    TSK_STAT_SIP_IN_ACK,
    TSK_STAT_SIP_IN_BYE,
    TSK_STAT_SIP_IN_CANCEL,
    TSK_STAT_SIP_IN_INVITE,
    TSK_STAT_SIP_IN_OPTIONS,
    TSK_STAT_SIP_IN_REGISTER,
    TSK_STAT_SIP_IN_SUBSCRIBE,
    TSK_STAT_SIP_IN_NOTIFY,
    TSK_STAT_SIP_IN_REFER,
    TSK_STAT_SIP_IN_INFO,
    TSK_STAT_SIP_IN_UPDATE,
    TSK_STAT_SIP_IN_MESSAGE,
    TSK_STAT_SIP_IN_PUBLISH,
    TSK_STAT_SIP_IN_PRACK,
    TSK_STAT_SIP_IN_1XX,
    TSK_STAT_SIP_IN_2XX,
    TSK_STAT_SIP_IN_3XX,
    TSK_STAT_SIP_IN_4XX,
    TSK_STAT_SIP_IN_5XX,
    TSK_STAT_SIP_IN_6XX,

    TSK_STAT_SIP_OUT_ACK,
    TSK_STAT_SIP_OUT_BYE,
    TSK_STAT_SIP_OUT_CANCEL,
    TSK_STAT_SIP_OUT_INVITE,
    TSK_STAT_SIP_OUT_OPTIONS,
    TSK_STAT_SIP_OUT_REGISTER,
    TSK_STAT_SIP_OUT_SUBSCRIBE,
    TSK_STAT_SIP_OUT_NOTIFY,
    TSK_STAT_SIP_OUT_REFER,
    TSK_STAT_SIP_OUT_INFO,
    TSK_STAT_SIP_OUT_UPDATE,
    TSK_STAT_SIP_OUT_MESSAGE,
    TSK_STAT_SIP_OUT_PUBLISH,
    TSK_STAT_SIP_OUT_PRACK,
    TSK_STAT_SIP_OUT_1XX,
    TSK_STAT_SIP_OUT_2XX,
    TSK_STAT_SIP_OUT_3XX,
    TSK_STAT_SIP_OUT_4XX,
    TSK_STAT_SIP_OUT_5XX,
    TSK_STAT_SIP_OUT_6XX,

    TSK_STAT_LAST
} TSK_STAT_NAME;

static const char *TSK_STR_STAT[TSK_STAT_LAST] = {
    "RECEIVED_MESSAGE",
    "SENT_MESSAGE",

    "SIP_SENT",
    "SIP_RECV",

    "WEBSOCKET_SENT",
    "WEBSOCKET_RECV",

 /* DONOT CHANGE THE SEQUENCE OF STAT, 
    IT IS DUE TO MATCH WITH DESCRIPTION */
    "WS_IN_ACK",
    "WS_IN_BYE",
    "WS_IN_CANCEL",
    "WS_IN_INVITE",
    "WS_IN_OPTIONS",
    "WS_IN_REGISTER",
    "WS_IN_SUBSCRIBE",
    "WS_IN_NOTIFY",
    "WS_IN_REFER",
    "WS_IN_INFO",
    "WS_IN_UPDATE",
    "WS_IN_MESSAGE",
    "WS_IN_PUBLISH",
    "WS_IN_PRACK",
    "WS_IN_1XX",
    "WS_IN_2XX",
    "WS_IN_3XX",
    "WS_IN_4XX",
    "WS_IN_5XX",
    "WS_IN_6XX",

    "WS_OUT_ACK",
    "WS_OUT_BYE",
    "WS_OUT_CANCEL",
    "WS_OUT_INVITE",
    "WS_OUT_OPTIONS",
    "WS_OUT_REGISTER",
    "WS_OUT_SUBSCRIBE",
    "WS_OUT_NOTIFY",
    "WS_OUT_REFER",
    "WS_OUT_INFO",
    "WS_OUT_UPDATE",
    "WS_OUT_MESSAGE",
    "WS_OUT_PUBLISH",
    "WS_OUT_PRACK",
    "WS_OUT_1XX",
    "WS_OUT_2XX",
    "WS_OUT_3XX",
    "WS_OUT_4XX",
    "WS_OUT_5XX",
    "WS_OUT_6XX",

    "SIP_IN_ACK",
    "SIP_IN_BYE",
    "SIP_IN_CANCEL",
    "SIP_IN_INVITE",
    "SIP_IN_OPTIONS",
    "SIP_IN_REGISTER",
    "SIP_IN_SUBSCRIBE",
    "SIP_IN_NOTIFY",
    "SIP_IN_REFER",
    "SIP_IN_INFO",
    "SIP_IN_UPDATE",
    "SIP_IN_MESSAGE",
    "SIP_IN_PUBLISH",
    "SIP_IN_PRACK",
    "SIP_IN_1XX",
    "SIP_IN_2XX",
    "SIP_IN_3XX",
    "SIP_IN_4XX",
    "SIP_IN_5XX",
    "SIP_IN_6XX",

    "SIP_OUT_ACK",
    "SIP_OUT_BYE",
    "SIP_OUT_CANCEL",
    "SIP_OUT_INVITE",
    "SIP_OUT_OPTIONS",
    "SIP_OUT_REGISTER",
    "SIP_OUT_SUBSCRIBE",
    "SIP_OUT_NOTIFY",
    "SIP_OUT_REFER",
    "SIP_OUT_INFO",
    "SIP_OUT_UPDATE",
    "SIP_OUT_MESSAGE",
    "SIP_OUT_PUBLISH",
    "SIP_OUT_PRACK",
    "SIP_OUT_1XX",
    "SIP_OUT_2XX",
    "SIP_OUT_3XX",
    "SIP_OUT_4XX",
    "SIP_OUT_5XX",
    "SIP_OUT_6XX"
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
static int STAT_INTERVAL = 10; //10 seconds
static int STAT_RESET = 1;     //enable resetting on next day

#define TSK_STAT_INIT(timeout) STAT = (stat_t *)TSK_STAT_CREATE(timeout)
#define TSK_STAT_CREATE() tsk_object_new(&stat_def_t)

TINYSAK_API int tsk_stat_init(int interval);
TINYSAK_API void tsk_stat_increase(TSK_STAT_NAME name);
TINYSAK_API void tsk_stat_reset();
TINYSAK_API void tsk_stat_set_path_file(const char *path, const char *filename);
TINYSAK_API const char *tsk_stat_path_file();
TINYSAK_API int tsk_stat_count(TSK_STAT_NAME name);
TINYSAK_API const char *tsk_stat_to_string();
TINYSAK_API void tsk_stat_set_filename(const char *file);
TINYSAK_API void tsk_stat_set_path(const char *path);
TINYSAK_API void tsk_stat_set_interval(int interval);
TINYSAK_API void tsk_stat_reset_enable(int is_reset);
TINYSAK_API const char *tsk_stat_get_filename();
TINYSAK_API const char *tsk_stat_get_path();
TINYSAK_API int tsk_stat_get_interval();
TINYSAK_API int tsk_stat_is_reset();
TINYSAK_API static int _tsk_stat_writer_cb(const void *arg, tsk_timer_id_t timer_id);
TINYSAK_API int tsk_stat_start();
TINYSAK_API int tsk_stat_response_code_to_group(int response_code);

TSK_END_DECLS

#endif //_STAT_H_