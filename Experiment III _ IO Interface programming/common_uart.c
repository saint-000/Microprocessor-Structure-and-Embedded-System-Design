/*
 * common.c
 *
 *  Created on: 2017年8月17日
 *      Author: EES_AE_02
 */

#include "xparameters.h"
#include "xil_printf.h"
#include "sleep.h"
#include <stdio.h>
#include "xil_io.h"

#define uart_bas_addr  0x42c00000
#define uart_rxd_addr  0x42c00000//接收数据输入地址
#define uart_txd_addr  0x42c00004//发送数据输出地址
#define uart_stat_addr 0x42c00008 // 串口状态寄存器
#define uart_ctrl_addr 0x42c0000c


int main()
{
	while(1)
    {	 /*补全代码，接收字符并回传，当接收到字符x时退出程序*/						
	static int a;
	if((Xil_In8(uart_stst_addr))&0x01==1)//判断串口状态寄存器的最低位是否为1
{
	a=Xil_In8(uart_txd_addr, a);//若为1，接收串口数据，并赋给一个变量
	if(a=='x')//将接收到的数据回传
        {
	    break;//判断接收到的数据是否位‘x’，若是，跳出while循环
        }
}						
											                          

    }
    return 0;
}




