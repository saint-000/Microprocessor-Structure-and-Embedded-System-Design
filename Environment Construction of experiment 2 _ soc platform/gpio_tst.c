/*
 * gpio_tst.c
 *
 *  Created on: 2018年1月25日
 *      Author: Administrator
 *      Function:8个LED实现流水灯，向上拨动任意一个拨码开关时，流水灯运行到最后一个LD7时停止
 */



#include"xparameters.h"
#include"xgpio.h"
#include"xil_printf.h"//有输出语句就要用到
#include"xil_cache.h"

#define GPIO_BITWIDTH 8
#define GPIO_LED_DEVICE_ID 0
#define GPIO_SW_DEVICE_ID 1
#define LED_DELAY 10000000  //简单的延时参数宏定义
#define LED_MAX_BLINK 0x1 //闪烁次数
#define LED_CHANNEL 1
#define printf xil_printf

XGpio GpioOutput;
XGpio GpioInput;
u32 flag=0;
u32 DataRead;

int Gpio_led(u16 Deviceid,u32 Gpio_Width)
{
	volatile int delay;
	u32 Ledbit;
	u32 Ledloop;
	int status;
	status=XGpio_Initialize(&GpioOutput,Deviceid);
	if(status !=XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	XGpio_SetDataDirection(&GpioOutput,LED_CHANNEL,0x0);
	for(Ledbit =0x0;Ledbit < Gpio_Width;Ledbit++)
	{
		for(Ledloop=0x0;Ledloop<LED_MAX_BLINK;Ledloop++)
		{
			XGpio_DiscreteWrite(&GpioOutput,LED_CHANNEL,1<<Ledbit);
			for(delay=0;delay<LED_DELAY;delay++);
			XGpio_DiscreteClear(&GpioOutput,LED_CHANNEL,0x00);
			for(delay=0;delay<LED_DELAY;delay++);
		}
	}
	return XST_SUCCESS;
}

u32 Gpio_sw(u16 Deviceid,u32 *DataRead)
{
	int Status;
    Status = XGpio_Initialize(&GpioInput, Deviceid);
	if (Status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	XGpio_SetDataDirection(&GpioInput, LED_CHANNEL, 0xFFFFFFFF);
	*DataRead = XGpio_DiscreteRead(&GpioInput, LED_CHANNEL);

	u32 data;
	data=*DataRead;
    return data;
}

int main()
{
	while(1)
	{
		flag =Gpio_sw(GPIO_SW_DEVICE_ID, &DataRead);
	    if(flag == 0)
	    {
			u32 status;
		    status = Gpio_led(GPIO_LED_DEVICE_ID,GPIO_BITWIDTH);
		    if(status==0)
		    {
		    	printf("SUCCESS.\r\n");
		    }
		    else
			    printf("FAIL.\r\n");
	    }
	    else
	    {
	    	u32 Ledbit;
		    for(Ledbit =0x0;Ledbit < GPIO_BITWIDTH;Ledbit++)
		    	XGpio_DiscreteClear(&GpioOutput,LED_CHANNEL,0x00);
	    }
	}
}

