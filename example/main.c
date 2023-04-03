#include <stdio.h>
#include "hj212_pack.h"


int main(int argc, char *argv[])
{
	/* 1. 创建一个hj212对象 */
	hj212p_obj *hj212 = hj212p_create_object();
	
	/* 2. 添加头字段 */
	hj212p_add_head(hj212, "T1", "2011", "123456","mn1234567890", "4");
	
	/* 3. 添加监测因子字段 */
	hj212p_add_factor_rtd(hj212, "w0102", "1.234", 1, 'N');
	hj212p_add_factor_rtd(hj212, "w0105", "1.234", 0, 'N');
	
	/* 4. 添加数据段结束标记 */
	hj212p_add_tail(hj212);
	
	/* 5. 生成string类型报文 */
	char *text = hj212p_generate_packet(hj212);
	printf("Packet:%s",text);

	/* 6. 释放报文内存 */
	hj212p_free_packet(text);

	/* 7. 释放HJ212对象 */
	hj212p_free_object(hj212);
	
	return 0;
}
