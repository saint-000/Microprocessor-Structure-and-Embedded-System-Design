/****************************************
文件名：main.c
功能：完成字符串的拷贝

****************************************/
#include <stdio.h>

extern void strcopy(char *d ,char *s);

int main(void)
{
	char *srcstr = "aaaa";
	char dststr[] = "bbbb";
	
	//printf("Before copying:\n");				仿真调试时禁用printf语句
	//printf(" %s %s\n",srcstr,dststr);
	
	strcopy(dststr,srcstr);
	
	//printf("After copying: \n");
	//printf(" %s\n  %s\n",srcstr,dststr);
	
	return (0);

}

