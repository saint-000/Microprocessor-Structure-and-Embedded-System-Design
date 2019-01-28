/*
 * seg_test.c
 *
 *  Created on: 2018年1月29日
 *      Author: Administrator
 */


#include"xparameters.h"
#include"xgpio.h"
#include"xil_cache.h"

//设备ID
#define GPIO_SEG_W_DEVICE_ID 1
#define GPIO_SW_DEVICE_ID 2
#define GPIO_SEG_D_DEVICE_ID 0
//通道号
#define SEG_CHANNEL 1

//指向设备的指针
XGpio GpioOutput0; //位选对应寄存器
XGpio GpioOutput1; //段选对应寄存器
XGpio GpioInput;//按键对应寄存器

u32 flag=0;
u32 DataRead;

int Gpio_w_seg(u16 Deviceid)位选
{
	int w;
	int status;
	/*请补全代码，给w赋值*/
	w=0x00          ;将要写入InstancePtr指向寄存器的值
	status=XGpio_Initialize(&GpioOutput0,Deviceid);实现X_GPIO设备的初始化
		if(status !=XST_SUCCESS)	;如果不成功，提示失败
		{
			return XST_FAILURE;
		}
	XGpio_SetDataDirection(&GpioOutput0,SEG_CHANNEL,0x0);通道的数据方向的设定（1orO）
    XGpio_DiscreteWrite(&GpioOutput0,SEG_CHANNEL,w);读取GPIO的值

	return XST_SUCCESS;
}

int Gpio_d_seg(u16 Deviceid,u32 data)左边四个数码管的段选
{

	u32 a;
	int status;
	status=XGpio_Initialize(&GpioOutput1,Deviceid);
		if(status !=XST_SUCCESS)
		{
			return XST_FAILURE;
		}
	/*设置GPIO为输出*/

XGpio_SetDataDirection(&GpioOutput0,SEG_CHANNEL,0x0);

	switch(data)
	{
	    case 0 :a=0x3f;
	            break;
	    /*补全余下代码，定义data为1~9时对应的数码管值*/
	    case 1 :a=0x06;
	            break;
	    case 2 :a=0x5b;
	            break;
	    case 3 :a=0x4f;
	            break;
	    case 4 :a=0x66;
	            break;
	    case 5 :a=0x6d;
	            break;
	    case 6 :a=0x7d;
	            break;
	    case 7 :a=0x07;
	            break;
	    case 8 :a=0x7f;
	            break;
	    case 9 :a=0x6f;
	            break;
	  

	}
    /*向数码管寄存器中写入值*/

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
	/*补全代码，读取并返回按键的值*/
DataRead=XGpio_DiscreteWrite(&GpioOutput,SEG_CHANNEL);读取InstancePtr指针指向的寄存器的值返回读取的数值
u32 data;
data=DataRead;
return data;

}

void main()
{
	while(1)
	{
		flag =Gpio_sw(GPIO_SW_DEVICE_ID,&DataRead);
		Gpio_w_seg(GPIO_SEG_W_DEVICE_ID);
	    if(flag < 10)
	    {
		     Gpio_d_seg(GPIO_SEG_D_DEVICE_ID,flag);

	   }
	   else
	   {
		   /*补全代码，使数码管不显示*/
XGpio_Initialize(&GpioOutput0,GPIO_SEG_W_DEVICE_ID);
XGpio_SetDataDirection(&GpioOutput0,SEG_CHANNEL,0x0);
XGpio_DiscreteWrite(&GpioOutput0,SEG_CHANNEL,0x0000);
	    }
	}
}

