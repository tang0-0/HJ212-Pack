/**
 * @File Name: hj212.h
 * @Brief : HJ212-2017 协议的实现
 * @Author : ty (tangt_t@foxmail.com)
 * @Version : 1.0
 * @Creat Date : 2021-01-15
 * 
 */

#ifndef __HJ212_H__
#define __HJ212_H__


// HJ212相关参数
typedef struct{
    unsigned char monitor_num; //监测因子个数
    unsigned long monitor_time; //上传时间间隔，单位秒
    signed char ST[4]; // ST
    signed char PW[8]; // PW
    signed char MN[24]; // MN
    unsigned char hex_data[50]; // Modbus收集的hex数据
    unsigned char ascii_data[255]; // 转化为ASCII形式的数据

}E212_ARGS;

// 监测因子参数
typedef struct{
    unsigned short hex_data;
    signed char name[10];
    signed char ascii_data[10];
    
}E212_FACTORS;


// 请求命令返回表
typedef enum{
    QnRtn_ready = '1',
    QnRtn_rejected = '2',
    QnRtn_err_pw = '3',
    QnRtn_err_mn = '4',
    QnRtn_err_st = '5',
    QnRtn_err_flag = '6',
    QnRtn_err_qn = '7',
    QnRtn_err_cn = '8',
    QnRtn_err_crc = '9',
    QnRtn_err_unknow = 100 // 注意这里是数值100

}QnRtn_code;

// 执行结果定义表
typedef enum{
    ExeRtn_success = '1',
    ExeRtn_err_unknow = '2',
    ExeRtn_err_condition = '3',
    ExeRtn_err_timeout = '4',
    ExeRtn_err_busy = '5',
    ExeRtn_err_fault = '6',
    ExeRtn_err_nodata = 100 // 注意这里是数值100

}ExeRtn_code;


// 函数声明ver
unsigned short hj212_crc16(signed char *puchMsg, unsigned short usDataLen);
signed char  hj212_check_mn(const signed char* pkt,const signed char* mn);
signed char  hj212_check_pw(const signed char* pkt,const signed char* pw);
signed char  hj212_check_crc(const signed char* pkt,const signed short crc);
signed short hj212_ver_cn(const signed char* pkt);
QnRtn_code  hj212_ver_QnRtn(signed char* pkt,E212_ARGS* args);

signed char  hj212_pkt_getadress(const signed char* pkt, unsigned short* address);
signed char  hj212_pkt_getvalue(const signed char* pkt, unsigned short* value);

unsigned short ascii16_to_u16(char *str);


#endif 