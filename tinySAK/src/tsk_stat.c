#include "tsk_stat.h"
#include "tsk_debug.h"
#include "tsk_memory.h"
#include "tsk_string.h"
#include "tsk_runnable.h"

#include <sys/time.h>
#include <stdio.h> /* puts, printf */
#include <time.h>  /* time_t, struct tm, time, localtime */
#include <errno.h>

static void *stat_timer;

// (constructor)
static tsk_object_t *stat_ctor(tsk_object_t *self, va_list *app)
{
    stat_t *stat = self;
    if (stat)
    {
    }
    return self;
}

// (destructor)
static tsk_object_t *stat_dtor(tsk_object_t *self)
{
    stat_t *stat = self;
    if (stat)
    {
    }
    return self;
}

// (comparator)
static int stat_cmp(const tsk_object_t *_p1, const tsk_object_t *_p2)
{
    const stat_t *p1 = _p1;
    const stat_t *p2 = _p2;
    int ret = 0;

    return ret;
}

int tsk_stat_init(int interval)
{
    stat_t *s = (stat_t *)TSK_STAT_CREATE();
    if (s != tsk_null)
    {
        s->interval = interval;
        s->timer_id = TSK_INVALID_TIMER_ID;
    }
    else
    {
        return -1;
    }

    STAT = s;

    return 0;
}

void tsk_stat_increase(TSK_STAT_NAME name)
{
    if (STAT != NULL)
    {
        STAT->stats[name]++;
    }
}

void tsk_stat_reset()
{
    if (STAT)
    {
        memset(STAT->stats, 0, TSK_STAT_LAST * sizeof(int));
    }
}

void tsk_stat_set_path_file(const char *path, const char *filename)
{
    sprintf(STAT_PATH_FILE, "%s/%s", path, filename);
}

const char *tsk_stat_path_file()
{
    return (const char *)STAT_PATH_FILE;
}

int tsk_stat_count(TSK_STAT_NAME name)
{

    if (name > TSK_STAT_LAST)
    {
        return -1;
    }

    return STAT->stats[name];
}

const char *tsk_stat_to_string(TSK_STAT_NAME name)
{
    return TSK_STR_STAT[name];
}

void tsk_stat_set_filename(const char *file)
{
    if (file != tsk_null)
        strcpy(STAT_FILE, file);
}

void tsk_stat_set_path(const char *path)
{
    if (path != tsk_null)
        strcpy(STAT_PATH, path);
}

/* 
    interval is second unit 
*/
void tsk_stat_set_interval(int interval)
{
    if (interval > 0)
        STAT_INTERVAL = interval;
}

void tsk_stat_reset_enable(int is_reset)
{
    if (is_reset > 0)
        STAT_RESET = 1;
}

const char *tsk_stat_get_filename()
{
    return (const char *)STAT_FILE;
}

const char *tsk_stat_get_path()
{
    return (const char *)STAT_PATH;
}

int tsk_stat_get_interval()
{
    return STAT_INTERVAL;
}

int tsk_stat_is_reset()
{
    return STAT_RESET;
}

static int _tsk_stat_writer_cb(const void *arg, tsk_timer_id_t timer_id)
{
    stat_t *stat = (stat_t *)tsk_object_ref(TSK_OBJECT(arg));

    if (stat && stat->timer_id == timer_id)
    {
        TSK_DEBUG_INFO("appending stat file");
        const char *filepath = tsk_stat_path_file();
        FILE *file = fopen(filepath, "a+"); // do not forget to close the file using fclose().
        if (file == NULL)
        {
            fprintf(stderr, "Error opening file: %s\n", strerror(errno));
            return -1;
        }
        struct tm tm;
        struct timeval curTime;
        gettimeofday(&curTime, NULL);

        //Time alignment
        curTime.tv_sec = stat->interval * (long)(curTime.tv_sec / stat->interval);
        tm = *localtime(&curTime.tv_sec);

        //31-10-2019 23:50:00
        char *b = tsk_null;
        tsk_sprintf(&b, "%02d-%02d-%04d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, 1900 + tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec);
        fputs(b, file);

        int i;

        for (i = 0; i < TSK_STAT_LAST; i++)
        {
            tsk_sprintf(&b, "%s|%d\n", tsk_stat_to_string(i), tsk_stat_count(i));
            fputs(b, file);
        }

        fputs("\n\n", file);
        TSK_FREE(b);
        fclose(file);
        
        STAT->timer_id = tsk_timer_manager_schedule(stat_timer, STAT->interval * 1000, _tsk_stat_writer_cb, STAT);
        TSK_DEBUG_INFO("reschedule stat timer id : %d", STAT->timer_id);
    }

    tsk_object_unref(TSK_OBJECT(stat));

    return 0;
}

int tsk_stat_start()
{
    TSK_DEBUG_INFO("start stat timer with interval %d s", STAT->interval);

    if( !stat_timer ){
        tsk_timer_manager_destroy(&stat_timer);
    }

    if (!(stat_timer = tsk_timer_manager_create()))
    {
        TSK_DEBUG_ERROR("Failed to create timer manager");
        return -1;
    }

    if ((tsk_timer_manager_start(stat_timer)) == 0)
    {
        STAT->timer_id = tsk_timer_manager_schedule(stat_timer, STAT->interval * 1000, _tsk_stat_writer_cb, STAT);
        TSK_DEBUG_INFO("stat timer id : %d", STAT->timer_id);
    }
    else
    {
        TSK_DEBUG_ERROR("Failed to start stat timer");
        return -1;
    }
    return 0;
}