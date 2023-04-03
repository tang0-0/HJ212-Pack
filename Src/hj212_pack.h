/**
 * @brief : HJ212-2017报文组包接口实现
 *
 * @Author : ty (tangt_t@foxmail.com)
 * @CreateTime : 2023-04-01
 * @Version : V1.0.0
 * @Change Logs:
 * Date       Author        Notes
 *
 */
#ifndef __HJ212_PACK_H__
#define __HJ212_PACK_H__


#define HJ212_SUFFIX_MAX_SIZE 16

typedef enum
{
    HJ212_SUFFIX_NONE = 0,
    HJ212_SUFFIX_RTD,
    HJ212_SUFFIX_FLAG,
} hj212p_suffix_type;

typedef enum
{
    HJ212_DEL_NONE = 0,
    HJ212_DEL_COMMA,
    HJ212_DEL_SEMICOLON,
} hj212p_delimiter_type;

typedef struct hj212p_obj
{
    struct hj212p_obj *prev;
    struct hj212p_obj *next;
    int suffix;             /* 后缀类型 */
    int delimiter;          /* 分隔符类型 */
    char *name;             /* 参数名 */
    char *value;            /* 参数值 */
} hj212p_obj;

typedef struct
{
    char *value;
    unsigned int length;
    unsigned int size;
} hj212p_strbuff;


hj212p_obj *hj212p_create_object(void);
void hj212p_free_object(hj212p_obj *obj);

int hj212p_add_instance(hj212p_obj *obj, const char *name, const char *value, int suffix, int delimiter);
int hj212p_add_head(hj212p_obj *obj, const char *st, const char *cn, const char *pw, const char *mn, const char *flag);
int hj212p_add_tail(hj212p_obj *obj);
int hj212p_add_factor_rtd(hj212p_obj *obj, const char *name, const char *value, int has_flag, char flag);

char *hj212p_generate_packet(hj212p_obj *obj);
void hj212p_free_packet(char *packet);

#endif
