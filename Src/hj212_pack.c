#include "hj212_pack.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>


hj212p_obj *hj212p_create_object(void)
{
    hj212p_obj *obj = malloc(sizeof(hj212p_obj));
    if (obj)
    {
        memset(obj, 0, sizeof(hj212p_obj));
    }
    return obj;
}

void hj212p_free_object(hj212p_obj *obj)
{
    hj212p_obj *next = NULL;
    hj212p_obj *first = obj;
    while (obj != NULL)
    {
        next = obj->next;

        if (obj->name != NULL)
        {
            free(obj->name);
        }
        if (obj->value != NULL)
        {
            free(obj->value);
        }

        free(obj);
        obj = next;

        if (obj == first) break;
    }
}

static int hj212p_add_object(hj212p_obj *object, hj212p_obj *next_obj)
{
    if (NULL == object || NULL == next_obj || object == next_obj)
    {
        return -1;
    }

    if (NULL == object->next)
    {
        object->next = next_obj;
        object->prev = next_obj;
        next_obj->prev = object;
        next_obj->next = object;
    }
    else
    {
        if (object->prev)
        {
            object->prev->next = next_obj;
            next_obj->prev = object->prev;
            object->prev = next_obj;
            next_obj->next = object;
        }
        else
        {
            return -2;
        }
    }
    return 0;
}

static hj212p_obj *hj212p_create_instance(const char *name, const char *value, int suffix, int delimiter)
{
    if (NULL == name) return NULL;

    unsigned int name_len = strlen(name);
    if (0 == name_len) return NULL;

    char *name_buff = calloc(1, name_len + 1);
    if (NULL == name_buff) return NULL;
    strncpy(name_buff, name, name_len);

    char *value_buff = NULL;
    unsigned int value_len = 0;
    if (value && (value_len = strlen(value)) > 0)
    {
        value_buff = calloc(1, value_len + 1);
        if (NULL == value_buff)
        {
            free(name_buff);
            return NULL;
        }
        strncpy(value_buff, value, value_len);
    }

    hj212p_obj *obj = calloc(1, sizeof(hj212p_obj));
    if (obj)
    {
        obj->suffix = suffix;
        obj->delimiter = delimiter;
        obj->name = name_buff;
        obj->value = value_buff;
    }

    return obj;
}

int hj212p_add_instance(hj212p_obj *obj, const char *name, const char *value, int suffix, int delimiter)
{
    if (NULL == obj) return -1;

    hj212p_obj *ins = hj212p_create_instance(name, value, suffix, delimiter);
    if (NULL == ins)
    {
        return -2;
    }

    if (hj212p_add_object(obj, ins) < 0)
    {
        hj212p_free_object(ins);
        return -3;
    }

    return 0;
}

static int hj212p_get_qn(char *qn, unsigned int qn_size)
{
    struct timeval time_ms = {0};
    struct tm *tm_t = NULL;

    gettimeofday(&time_ms, NULL);
    time_t seconds = time_ms.tv_sec;
    tm_t = localtime(&seconds);
    if (NULL == tm_t) return -2;

    snprintf(qn, qn_size, "%04d%02d%02d%02d%02d%02d%03ld",
             tm_t->tm_year + 1900, tm_t->tm_mon + 1, tm_t->tm_mday,
             tm_t->tm_hour, tm_t->tm_min, tm_t->tm_sec, (time_ms.tv_usec / 1000));

    return 0;
}

int hj212p_add_head(hj212p_obj *obj, const char *st, const char *cn,
                    const char *pw, const char *mn, const char *flag)
{
    if (NULL == obj) return -1;

    char str_buff[20] = {0};
    hj212p_get_qn(str_buff, sizeof(str_buff));
    hj212p_add_instance(obj, "QN", str_buff, HJ212_SUFFIX_NONE, HJ212_DEL_SEMICOLON);
    hj212p_add_instance(obj, "ST", st, HJ212_SUFFIX_NONE, HJ212_DEL_SEMICOLON);
    hj212p_add_instance(obj, "CN", cn, HJ212_SUFFIX_NONE, HJ212_DEL_SEMICOLON);
    hj212p_add_instance(obj, "PW", pw, HJ212_SUFFIX_NONE, HJ212_DEL_SEMICOLON);
    hj212p_add_instance(obj, "MN", mn, HJ212_SUFFIX_NONE, HJ212_DEL_SEMICOLON);
    hj212p_add_instance(obj, "Flag", flag, HJ212_SUFFIX_NONE, HJ212_DEL_SEMICOLON);
    hj212p_add_instance(obj, "CP", "&&", HJ212_SUFFIX_NONE, HJ212_DEL_NONE);

    return 0;
}

int hj212p_add_tail(hj212p_obj *obj)
{
    if (NULL == obj) return -1;

    if (obj->prev)
    {
        obj->prev->delimiter = HJ212_DEL_NONE;
    }

    return hj212p_add_instance(obj, "&&", NULL, HJ212_SUFFIX_NONE, HJ212_DEL_NONE);
}

int hj212p_add_factor_rtd(hj212p_obj *obj, const char *name, const char *value, int has_flag, const char *flag)
{
    if (NULL == obj) return -1;

    int ret = -1;
    if (has_flag)
    {
        ret = hj212p_add_instance(obj, name, value, HJ212_SUFFIX_RTD, HJ212_DEL_COMMA);
        if (ret < 0) return -2;
        ret = hj212p_add_instance(obj, name, flag, HJ212_SUFFIX_FLAG, HJ212_DEL_SEMICOLON);
        if (ret < 0) return -3;
    }
    else
    {
        ret = hj212p_add_instance(obj, name, value, HJ212_SUFFIX_RTD, HJ212_DEL_SEMICOLON);
        if (ret < 0) return -2;
    }

    return 0;
}

static int strbuff_add_string(hj212p_strbuff *strbuff, const char *str, unsigned int length)
{
    if (NULL == str || 0 == length) return 0;

    if (length >= (strbuff->size - strbuff->length))
    {
        unsigned int new_size = 0;
        char *new_value = NULL;

        new_size = strbuff->length + length + 1;
        new_value = realloc(strbuff->value, new_size);
        if (!new_value) return -1;

        strbuff->value = new_value;
        strbuff->size = new_size;
    }

    memcpy(&strbuff->value[strbuff->length], str, length);
    strbuff->length += length;
    strbuff->value[strbuff->length] = '\0';

    return length;
}

static void strbuff_free(hj212p_strbuff *strbuff)
{
    if (!strbuff) return;

    if (strbuff->value)
    {
        free(strbuff->value);
    }

    strbuff->length = 0;
    strbuff->size = 0;
    strbuff->value = NULL;
}

static char *get_suffix_string(int suffix)
{
    switch (suffix)
    {
    case HJ212_SUFFIX_NONE:
    {
        return NULL;
    }
    break;
    case HJ212_SUFFIX_RTD:
    {
        return "-Rtd";
    }
    break;
    case HJ212_SUFFIX_FLAG:
    {
        return "-Flag";
    }
    break;
    }

    return NULL;
}

static char *get_del_string(int del)
{
    switch (del)
    {
    case HJ212_DEL_NONE:
    {
        return NULL;
    }
    break;
    case HJ212_DEL_COMMA:
    {
        return ",";
    }
    break;
    case HJ212_DEL_SEMICOLON:
    {
        return ";";
    }
    break;
    }

    return NULL;
}

static unsigned short hj212p_crc16(char *data, unsigned int length)
{
    if (NULL == data || 0 == length) return 0;

    unsigned short j, check;
    unsigned short crc_reg = 0xFFFF;
    unsigned int i;

    for (i = 0; i < length; i++)
    {
        crc_reg = (crc_reg >> 8) ^ data[i];
        for (j = 0; j < 8; j++)
        {
            check = crc_reg & 0x0001;
            crc_reg >>= 1;
            if (check == 0x0001)
            {
                crc_reg ^= 0xA001;
            }
        }
    }

    return crc_reg;
}

char *hj212p_generate_packet(hj212p_obj *obj)
{
    if (NULL == obj) return NULL;

    hj212p_obj *now = NULL;
    hj212p_strbuff strbuff = {0};

    for (now = obj->next; (now != NULL) && (now != obj); now = now->next)
    {
        if (now->name)
        {
            strbuff_add_string(&strbuff, now->name, strlen(now->name));
        }

        if (now->suffix)
        {
            strbuff_add_string(&strbuff, get_suffix_string(now->suffix), strlen(get_suffix_string(now->suffix)));
        }

        if (now->value)
        {
            strbuff_add_string(&strbuff, "=", 1);
            strbuff_add_string(&strbuff, now->value, strlen(now->value));
        }

        if (now->delimiter)
        {
            strbuff_add_string(&strbuff, get_del_string(now->delimiter), 1);
        }
    }

    char head[7] = {0}, tail[7] = {0};
    unsigned short crc16 = hj212p_crc16(strbuff.value, strbuff.length);
    snprintf(head, sizeof(head), "##%04u", strbuff.length);
    snprintf(tail, sizeof(tail), "%02X%02X\r\n", (crc16 >> 8), (crc16 & 0x00FF));

    unsigned int total_len = strbuff.length + 12;
    char *total_packet = malloc(total_len + 1);
    if (total_packet)
    {
        memcpy(total_packet, head, 6);
        memcpy(total_packet + 6, strbuff.value, strbuff.length);
        memcpy(total_packet + 6 + strbuff.length, tail, 6);
        total_packet[total_len] = '\0';
    }

    strbuff_free(&strbuff);
    return total_packet;
}

void hj212p_free_packet(char *packet)
{
    free(packet);
}

