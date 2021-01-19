#include"hj212.h"
#include <string.h>


// 数据类型重定义
typedef signed long    s32;
typedef signed short   s16;
typedef signed char     s8;
typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char   u8;


/***************************** 内部函数 开始 *********************************/
/**
 * @Brief : 将ACSII形式的数字转化为数值形式的数字   "1256"->value:1256
 * @param  str
 * @return s16
 */
static u16 ascii_to_u16(char *str)
{
    u16 res = 0;  //结果
    while (*str >= '0' && *str <= '9' && *str != 0)
    {
        res = res * 10 + (*str - '0');
        *str++;
    }
    return res;
}

/**
 * @Brief : 将ASCII形式的16进制字符转化为数字   'A'->10,'b'->11,'9'->9
 * @param  str
 * @return u8  para err:0
 */
 u8 char_to_num(char ch)
{
    if (ch >= '0' && ch <= '9')
        return (ch - '0');
    else if (ch >= 'a' && ch <= 'f')
        return (ch - 'a' + 10);
    else if (ch >= 'A' && ch <= 'F')
        return (ch - 'A' + 10);

    return '!';
}

/**
 * @Brief : 将ACSII形式的16进制数字转化为数值形式的数字    "078A"->value:1930
 * @param  str
 * @return u16
 */
 u16 ascii16_to_u16(char *str)
{
    u16 res = 0;  //结果
    char *p=str;

    for (p = str; char_to_num(*p) != '!'; p++)
    {
        res = res * 16 + char_to_num(*p);
    }
    return res;

}

/**
 * @Brief :将无符号16位数字转化位ASCII
 * @param  num
 * @param  asc
 * @return  s8  :null err:-1   ok: 1
 */
static s8 u16_to_ascii(u16 num_u16, char *asc)
{
    u8 temp[8];
    u8 i = 0, j = 0;

    if (asc == NULL)
        return -1;

    while (num_u16)
    {
        temp[i] = num_u16 % 10 + 0x30;
        i++;
        num_u16 /= 10;
    }
    j = i;

    for (i = 0; i < j; i++)
    {
        asc[i] = temp[j - i - 1];
    }

    if (!i)
    {
        asc[i] = '0'; //如果num_u16=0
    }
    else
    {
        asc[i] = '\0'; // 字符串末尾加0
    }
    return 1;

}

/**
 * @Brief : 将有符号16位数字转化位ASCII
 * @param  num_s16
 * @param  asc
 * @return s8   :null err:-1   ok: 1
 */
static s8 s16_to_ascii(s16 num_s16, char *asc)
{
    u8 temp[8];
    u8 i = 0, j = 0, type = 0;

    if (asc == NULL)
        return -1;

    if (num_s16 & 0x8000) //<0 负数以补码形式存储，这里要将负数转化为正数
    {
        type = 1;
        num_s16 = ~num_s16;
        num_s16 = num_s16 + 1;
        // num_s16 = num_s16 << 16;
        // num_s16 = num_s16 >> 16;
    }

    while (num_s16)
    {
        temp[i] = num_s16 % 10 + 0x30;
        i++;
        num_s16 /= 10;
    }
    j = i;

    if (type == 1)
    {
        temp[j] = '-';
        j = j + 1;
    }

    for (i = 0; i < j; i++)
    {
        asc[i] = temp[j - i - 1];
    }

    if (!i)
    {
        asc[i] = '0';
    }
    else
    {
        asc[i] = 0;
    }
    return 1;
}

/***************************** 内部函数 结束 *********************************/

/***************************** 外部函数 开始 *********************************/
/**
 * @Brief : CRC校验算法
 * @param  puchMsg
 * @param  usDataLen
 * @return u16 
 */
u16 hj212_crc16(s8 *puchMsg, u16 usDataLen)
{

    u16 i, j, crc_reg, check;
    crc_reg = 0xFFFF;
    for (i = 0; i < usDataLen; i++)
    {
        crc_reg = (crc_reg >> 8) ^ puchMsg[i];
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


/**
 * @Brief : 检查服务器下发数据包的MN字段
 * @param  pkt
 * @return s8 para err:-1,mach err:-2,len err:-3,compare err:-4 ; ok:1
 */
s8 hj212_check_mn(const s8 *pkt, const s8 *mn)
{
    char *point = NULL;
    u8 i = 0, len = 0;

    if (pkt == NULL || mn == NULL)
        return -1;

    len = strlen(mn);

    point = strstr(pkt, "MN=");
    if (point == NULL)
    {
        return -2;
    }
    else
    {
        point += 3;
    }

    for (i = 0; i < len; i++)
    {
        if (*point == mn[i])
        {
            point++;
        }
        else
        {
            return -4;
        }

    }
    if (*point == ';')
        return 1;
    else
        return -3;

}

/**
 * @Brief : 检查服务器下发数据包的PW字段
 * @param  pkt
 * @returnerr: para err:-1,mach err:-2,len err:-3,compare err:-4 ; ok:1
 */
s8 hj212_check_pw(const s8 *pkt, const s8 *pw)
{
    char *point = NULL;
    u8 i = 0, len = 0;

    if (pkt == NULL || pw == NULL)
        return -1;

    len = strlen(pw);

    point = strstr(pkt, "PW=");
    if (point == NULL)
    {
        return -2;
    }
    else
    {
        point += 3;
    }

    for (i = 0; i < len; i++)
    {
        if (*point == pw[i])
        {
            point++;
        }
        else
        {
            return -4;
        }

    }

    if (*point == ';')
        return 1;
    else
        return -3;

}

/**
 * @Brief : 检查服务器下发数据包的CRC校验
 * @param  pkt
 * @param  crc
 * @return s8   para err:-1,mach err:-2,compare err:-3  ok:1
 */
s8  hj212_check_crc(const s8 *pkt, const s16 crc)
{
    char *point = NULL;
    u16 tem = 0;

    if (pkt == NULL)
        return -1;

    point = strstr(pkt, "&&");
    if (point == NULL)
    {
        return -2;
    }
    else
    {
        point = strstr((point + 2), "&&");
        if (point == NULL)
        {
            return -2;
        }
        else
        {
            point += 2;
        }
    }

    tem = ascii16_to_u16(point);
    if (tem == crc)
    {
        return 1;
    }
    else
    {
        return -3;
    }


}

/**
 * @Brief : 解析服务器下发的反控命令数据包
 * @param  pkt
 * @return 返回命令字段CN
 * err return: para err:-1, mach err:-2, len err:-3
 */
s16 hj212_ver_cn(const s8 *pkt)
{
    char *point = NULL;
    s16 tem = 0;
    u8 i = 0;

    if (pkt == NULL)
        return -1;

    point = strstr(pkt, "CN=");
    if (point == NULL)
    {
        return -2;
    }
    else
    {
        point += 3;
    }

    tem = 1000 * (*point - '0') + 100 * (*(point + 1) - '0') + 10 * (*(point + 2) - '0') + (*
            (point + 3) - '0');

    if (*(point + 4) == ';')
        return tem;
    else
        return -3;

}

/**
 * @Brief : 判断QnRtn字段要返回的内容
 * @param  pkt
 * @param  args
 * @return s8 '1':准备执行请求, '3':PW错误, '4':MN错误, '8':CN错误, '9':CRC错误
 */
QnRtn_code hj212_ver_QnRtn(s8 *pkt, E212_ARGS *args)
{
    char Qn = 0;
    u16 crc = 0;

    crc  = hj212_crc16(&pkt[6], strlen(pkt) - 12);

    if(1 != hj212_check_crc(pkt, crc))//检查crc
        return QnRtn_err_crc;
    
    if(1 != hj212_check_mn(pkt, args->device_code))//检查MN
        return QnRtn_err_mn;

    if(1 != hj212_check_pw(pkt, args->password))//检查PW
        return QnRtn_err_pw;
    
    return QnRtn_ready;

}


/**
 * @Brief : 获取下发命令中的寄存器地址字段
 * @param  pkt
 * @param  address
 * @return s8 para err:-1, mach err:-2; ok:1
 */
s8 hj212_pkt_getadress(const s8 *pkt, u16 *address)
{
    char *point = NULL;

    if (pkt == NULL)
        return -1;

    point = strstr(pkt, "MB_BgnAddr=");
    if (point == NULL)
    {
        return -2;
    }
    else
    {
        point += 11;
    }

    *address = ascii_to_u16(point);
    return 1;

}

/**
 * @Brief : 获取下发命令中的改变的值
 * 字段
 * @param  pkt
 * @param  value
 * @return s8 para err:-1, mach err:-2; ok:1
 */
s8 hj212_pkt_getvalue(const s8 *pkt, u16 *value)
{
    char *point = NULL;

    if (pkt == NULL)
        return -1;

    point = strstr(pkt, "MB_Wrt=");
    if (point == NULL)
    {
        return -2;
    }
    else
    {
        point += 7;
    }

    *value = ascii_to_u16(point);
    return 1;

}

/***************************** 外部函数 结束 *********************************/