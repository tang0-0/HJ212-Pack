#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hj212_pack.h"


static int get_datatime(char *string, unsigned int string_size)
{
    time_t timestamp = 0;
    struct tm *tm_t = NULL;

    timestamp = time(NULL);
    tm_t = localtime(&timestamp);
    if (NULL == tm_t) return -1;

    return  snprintf(string, string_size, "%04d%02d%02d%02d%02d%02d",
                     tm_t->tm_year + 1900, tm_t->tm_mon + 1, tm_t->tm_mday,
                     tm_t->tm_hour, tm_t->tm_min, tm_t->tm_sec);
}

int main(int argc, char *argv[])
{
    /* 1. 创建一个hj212对象 */
    hj212p_obj *hj212 = hj212p_create_object();

    /* 2. 添加头字段 */
    hj212p_add_head(hj212, "T1", "2011", "123456", "mn1234567890", "4");

    /* 3. 添加DataTime */
    char value_string[16] = {0};
    get_datatime(value_string, sizeof(value_string));
    hj212p_add_instance(hj212, "DataTime", value_string, HJ212_SUFFIX_NONE, HJ212_DEL_SEMICOLON);

    /* 4. 添加监测因子字段 */
    hj212p_add_factor_rtd(hj212, "w0102", "1.234", 1, "N");
    hj212p_add_factor_rtd(hj212, "w0105", "1.234", 0, "N");

    /* 5. 添加数据段结束标记 */
    hj212p_add_tail(hj212);

    /* 6. 生成string类型报文 */
    char *text = NULL;
    text = hj212p_generate_packet(hj212);
    printf("Packet:%s", text);

    /* 7. 释放报文内存 */
    hj212p_free_packet(text);

    /* 8. 释放HJ212对象 */
    hj212p_free_object(hj212);

    return 0;
}
