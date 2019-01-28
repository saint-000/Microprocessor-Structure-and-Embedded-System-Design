1.基于ARM的模块方式驱动程序实验.在Linux虚拟机下编写实验程序。

设置IP

1.sudo  du   （取得用户权限）

2.ifconfig    （查看ip）

3.ifconfig  ens33 192.168.1.12    （配置ip）

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/7.png)



对测试程序ledtest.c 进行交叉编译，生成可执行文件ledtest，在终端下输入以下命令：
cd /home/zynq/driver_code/led
进入到led目录下
sudo su        （密码：1） 
source zynq-env.sh  
arm-linux-gnueabihf-gcc ledtest.c -o ledtest
对驱动文件进行编译，生成驱动模块ees331_led.ko，在同一个终端下继续输入命令：make
![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/8.png)

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/9.png)


![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/10.png)

putty的窗口里，进入到arm-linux系统里，将ees331_led.ko和 ledtest文件拷贝到SD卡根文件系统的root目录下。在/root(~)目录下执行insmod 命令，将驱动模块动态加载到内核中。实验截图如下：

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/28.png)

驱动加载成功后，在/dev/目录中用ls命令可以查看到相应的设备：

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/29.png)

./ledtest运行LED程序文件，实验截图如下：
![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/30.png)

键入1对应硬件上LD0亮灯

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/31.png)

键入2，硬件上LD1亮灯对应10

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/32.png)

键入5，硬件上LD0和LD1亮灯对应101

2.基于ARM的串口驱动实验 

在driver_code/BOOT相应目录下找到devicetree.dts源文件，打开源文件.将设备树文件dts转换成dtb格式，并通过读卡器将devicetree.dtb拷贝到SD里的BOOT分区里，在driver_code/uartlite目录下编写测试程序uart.c.

实验截图：
![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/33.png)

对提供的测试程序uart.c 进行交叉编译，生成可执行文件uart，在终端下输入以下命令：
<pre>
cd /home/zynq/driver_code/uartlite
sudo su        （密码：1） 
source zynq-env.sh  
arm-linux-gnueabihf-gcc uart.c -o uart
</pre>

对驱动文件进行编译，生成驱动模块uartlite.ko，在同一个终端下继续输入命令：make在win7系统里打开putty软件，选择对应的com口，波特率选择为115200；将uartlite.ko和uart文件拷贝到SD卡的root目录下。
<pre>
scp zynq@192.168.1.12:~/driver_code/uartlite/uart   /root
scp zynq@192.168.1.12:~/driver_code/uartlite/uartlite.ko  /root
insmod uartlite.ko
</pre>
![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/34.png)

用双头usb线将开发板上PL的串口（5上）与上位机连接，打开串口助手，选择对应的com口与波特率9600。./uart执行程序截图如下：
![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/35.png)
我们在串口点击发送，发现显示区出现2016031002009我的学号号码，然后在数值输入窗口输入1，putty的窗口里显示反馈1，实验截图如下：
![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/36.png)

我们在输入区输入1，点击发送发现串口调试助手显示区显示2，实验截图如下：
![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/37.png)

