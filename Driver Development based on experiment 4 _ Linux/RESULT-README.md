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


