1.掌握Linux系统下设备驱动程序的作用与编写技巧

2.掌握Linux驱动程序模块加载和卸载的方法

3.了解串口驱动的原理和工作方式

4.了解串口驱动的原理和工作方式

具体内容：

1.基于ees331开发板编写led驱动程序。

2.编写led驱动，修改makefile，并将led驱动动态加载入linux内核中。

3.编写关于led的测试程序，交叉编译后运行，控制led灯的亮灭。

4.修改uart驱动，修改makefile，修改设备树，并将uart驱动动态加载入linux内核中。

5.编写关于uart的测试程序，交叉编译后运行，进行串口通信。

需要了解：

1.linux 设备驱动程序
以 Linux 为代表的自由操作系统的优点之一, 是它们的内部是开放给所有人看的。Linux 内核保留有大量的复杂的代码, 但是, 那些想要成为内核 hacker 的人需要一个入口点, 这样他们可以进入代码中,不会被代码的复杂性压倒。通常,设备驱动就是提供了这样的一个入口点。

驱动程序在 Linux 内核里扮演着特殊的角色。它们是截然不同的"黑盒子", 使不同的硬件来响应相同的系统上层定义好的内部编程接口。它们完全隐藏了设备工作的细节。上层的用户无须知道硬件的具体情况以及它们的工作原理，他们只需要调用系统提供的一套标准化的调用来进行, 这些调用与特别的驱动是独立的。设备驱动的角色就是将这些调用映射到作用于实际硬件的和设备相关的操作上。

Linux 系统将设备分为三种基本的设备类型，每一种类型的设备对应着不同形式的驱动，这三种设备分别为字符设备，块设备和网络设备。
字符设备：一个字符( char ) 设备是一种可以当作一个字节流来存取的设备(如同一个文件)；一个字符驱动负责实现这种行为。这样的驱动常常至少实现 open, close,read, 和 write 系统调用。文本控制台( /dev/console )和串口( /dev/ttyS0 及类似的设备)就是两个典型的字符设备, 因为它们很好地展现了流的抽象。字符设备通过文件系统节点来存取, 例如 /dev/tty1 和 /dev/lp0。

在一个字符设备和一个普通文件之间唯一的不同就是, 对普通文件的访问可以前后移动访问位置, 但是大部分字符设备仅仅是一个只能顺序访问的数据通道, 不能随意改变访问位置。然而, 也存在具有数据区特性的字符设备, 访问它们的时候可前后移动访问位置。例如,帧抓取器就是这样一个设备, 应用程序可以使用 mmap 或者 lseek 存取整个要求的图像。本实验所要设计的 led 驱动实验就是一种字符设备驱动。

块设备：和字符设备类似, 块设备也是通过位于/dev 目录的文件系统结点来访问。块设备(例如一个磁盘)上能够容纳文件系统。在大部分的 Unix 系统中, 一个块设备只能处理这样的 I/O 操作, 传送一个或多个长度是 512 字节( 或一个更大的 2 的幂的数)的块. 但是 Linux 却允许应用程序象字符设备一样读写一个块设备，允许一次传送任意多字节的数据。因而，块和字符设备的区别仅仅在内核在内部管理数据的方式上, 也就是在内核和驱动的软件接口上有所不同。但是它们之间的区别对用户是透明的。

如同一个字符设备, 每个块设备都通过一个文件系统节点被访问读写。在内核中，和字符驱动相比, 块设备驱动与内核的接口完全不同。
网络设备：任何网络事务都通过一个接口来进行, 就是说, 一个能够与其他主机交换数据的设备。通常, 一个接口是一个硬件设备, 但是它也可能是一个纯粹的软件设备, 比如回环（loopback）接口。

网络接口由内核中的网络子系统的驱动,负责发送和接收数据包，但它不必知道单个事务是如何映射到实际的被发送的数据包上的。很多网络连接( 特别那些使用 TCP 协议的连接)是面向流的, 但是网络设备却围绕数据包的发送和接收进行设计。一个网络驱动对单个连接一无所知，它只负责处理数据包。由于不是面向流的设备，因而将网络接口映射到文件系统中的节点（比如/dev/tty1）比较困难。

Linux 操作系统访问网络接口的方法仍然是给他们分配一个唯一的名字（比如 eth0），但这个名字在文件系统中不存在对应的节点。内核和网络设备驱动程序间的通信，完全不同于内核和字符以及块设备驱动程序之间的通信。内核调用一套和数据包传输相关的函数而不是标准调用函数 read，write 等。

设计驱动时，我们需要在所需要的编程时间以及驱动程序的灵活性之间选择一个可以接受的折衷。换句话来说就是我们要强调设备驱动程序的功能在于提供机制而不是提供策略。区分机制和策略是 unix 设计背后隐藏的一种思想。

机制指的是需要提供什么功能，策略指的是如何使用这些功能。在编写驱动程序时, 程序员应当特别注意这个基础的概念: 编写访问硬件的内核代码时,不要强加特别的策略给用户, 因为不同的用户有不同的需求。驱动应当处理如何使硬件可用的问题, 将所有关于如何使用硬件的事情留给应用程序。一个驱动如果它只提供了访问硬件的功能而没有附加任何限制的时候，这个驱动程序就比较灵活。然而, 我们有时也必须在驱动程序中作出一些策略的实现。

例如, 一个数字 I/O 驱动也许只提供以字节为单位访问硬件的方法, 以便避免编写额外的代码处理单个数据位的麻烦。你也可以从不同的角度看驱动程序: 它是一个存在于应用程序和实际设备间的软件层. 驱动的这种特权的角色允许驱动程序员选择如何展现设备特性: 即使对于相同的设备，不同的驱动也可以提供不同的功能。实际的驱动设计应当是在许多不同考虑中的平衡。

例如, 一个单个设备可能由不同的程序并发使用, 驱动程序员有完全的自由来决定如何处理并发性。你能在设备上实现独立于硬件能力的内存映射或者你能提供一个用户库来帮助应用程序员在可用的原语之上实现新策略, 等等。总得来说，驱动程序设计主要还是综合考虑下面三个因素：展现给用户尽可能多的选项,编写驱动要占有的时间以及尽量保持程序简单以避免错误丛生。

2.驱动的模块式加载和卸载
Linux 操作系统的众多优良特性之一就是内核提供的特性可以在运行时进行扩展。这意
味着你可以在系统正在运行着的时候增加内核的功能(当然也可以移除功能)。
模块简介
可以在运行时添加到内核的代码, 被称为“模块”。 Linux 内核提供了对许多模块类型的支持, 包括但不限于设备驱动程序。每个模块由目标代码组成( 没有连接成一个完整可执行文件 ), 可以通过 insmod 程序动态连接到运行中的内核中,以及通过 rmmod 程序去从内核中移除模块。
下面是一个最简单的内核模块的例子。

#include <linux/init.h> //包含对初始化函数和清除函数的定义
#include <linux/module.h> //包含可装载模块需要的大量符号和函数的定义
MODULE_LICENSE("Dual BSD/GPL"); //指定代码所使用的许可证，本例使用 BSD/GPL
双重许可证
static int __init hello_init(void) //模块初始化函数，加载时被调用
{
printk(KERN_ALERT "Hello, world\n");
return 0;
}
static void __exit hello_exit(void) //模块清除函数，卸载时被调用
{
printk(KERN_ALERT "Goodbye, cruel world\n");
}
module_init(hello_init); // module_init 用于声明模块初始化函数，没有
这个定义，初始化函数无法被调用
module_exit(hello_exit); // module_exit 用于声明模块清除函数
这个模块是最基本的内核模块，只包含模块所必备的一些功能，并没有实现实质性的功能。

这个模块定义了两个函数, 一个在模块加载到内核时被调用( hello_init )以及一个在模块被移除时被调用( hello_exit ). moudle_init 和 module_exit 这几行使用了特别的内核宏来指出这两个函数的角色. 另一个特别的宏 (MODULE_LICENSE) 是用来告知内核, 该模块带有一个自由的许可证; 没有这样的说明, 在模块加载时内核会产生警告。函数printk 是在 Linux 内核中定义的打印输出函数，功能和标准 C 库中的函数 printf 类似。由这段程序可以看出, 编写一个模块并不是如你想象的困难，至少, 当模块没有要求做任何有价值的工作时。真正的困难在于理解你的设备并最大化其性能。

在进行 linux 模块编程之前, 先强调一下内核模块和应用程序之间的各种不同。不同于大部分的应用程序从头至尾处理一个单个任务, 每个内核模块只是预先注册自己以便服务于将来的某个请求, 然后它的初始化函数就立刻结束。换句话说, 模块初始化函数的任务是为以后调用模块的函数做准备。

这就好像是模块说： " 我在这里, 这是我能做的."模块的退出函数( 例子里是 hello_exit )就在模块被卸载时调用。它好像告诉内核： "我不再在那里了, 不要要求我做任何事了."这种编程的方法类似于应用程序中的事件驱动的编程, 但是并不是所有的应用程序都是事件驱动的, 而每个内核模块都是。

事件驱动的应用程序和内核代码之间另外一个主要的不同是退出函数: 一个终止的应用程序可以不管资源的释放以及其他的一些清理工作,但是模块的退出函数必须小心恢复每个由初始化函数建立的东西, 否则会保留一些东西直到系统重启。另外内核的模块编程仅仅能调用那些内核导出的那些函数，而不存在任何可以链接的函数库。内核模块不能包含应用程序所包含的那些通常的头文件，只能包含作为内核一部分的头文件。

编译模块
在编译模块之前首先要有正确版本的交叉编译器，本实验用的是 arm-linux-gnueabihf-gcc 交叉编译器。在Makefile文件指定了编译器目录和内核源码树中，在编译执行时，将 led 驱动作为模块编译，编译出可装载的目标文件.ko 文件。
装载和卸载模块
模块建立之后, 下一步是加载到内核。insmod 将为你完成这个工作。这个程序加载模块的代码段和数据段到内核, 接着, 执行一个类似 ld 的函数, 它连接模块中任何未解决的符号连接到内核的符号表上. 但是不象链接器, 内核不修改模块的磁盘文件, 仅仅修改内存中的副本。

insmod 有许多命令行选项,它能够在连接到当前内核之前安排值给你模块中的参数。因此, 如果一个模块正确设计了, 它能够在加载时配置。加载时配置比编译时配置给了用户更多的灵活性。模块可以用 rmmod 工具从内核去除. 但是如果内核认为模块还在用( 就是说, 一个程序仍然有一个打开文件对应模块输出的设备 ), 或者内核被配置成不允许模块去除, 模块去除会失败。

可以配置内核允许"强行"去除模块, 甚至在它们看来是忙的。lsmod 程序生成一个内核中当前加载的模块的列表, 也提供了一些其他信息, 例如使用了一个特定模块的其他模块。lsmod 通过读取 /proc/modules 虚拟文件工作. 当前加载的模块的信息也可在位于 /sys/module 的 sysfs 虚拟文件系统找到。

3.led 驱动的原理

在本开发板上有八个 led 指示灯，从下往上分别为 LED0-LED7。这八个 led 灯都是接的PL上的管脚口。在本实验的开发板硬件设计中，当 led 灯对应的管脚口的电平为高时，led 灯被点亮；当 led 灯对应的管脚口的电平为低时，led 灯灭。

本驱动的作用就是通过设置对应管脚口的电平来控制 led 的亮灭。
在硬件工程中，PL上的管脚口要与PS通信，就要通过axi总线来实现通信，选择的axi_gpio模块需要将引脚数设置为8，设置为输出模式。在硬件工程里的address editor中可以查看和修改PL中各个模块的地址。
为了方便访问，在内核中需要对IO地址地址进行映射:
ioremap(ees331_led_PHY_ADDR, 32)
将一个IO地址空间映射到内核的虚拟地址空间上去，便于访问。
led端口操作函数：iowrite32(arg, GPIO_Regs)
arg:写入的值；
GPIO_Regs:写入的地址；

4.设备树
	设备树保留着存在于系统中的设备信息。当机器引导时，OS通过使用驱动程序和其他组件获得的信息建立此树，并且当添加或删除设备时更新此树。设备树是分级的，总线上的设备代表着总线适配器或驱动控制器的“子集”。设备树的每一个节点是一个设备节点（devnode），一个devnode包括设备驱动程序的设备对象加上有OS所保留的内部信息。
	DTS文件.dts是一种ASCII文本格式的设备树描述，人性化适合阅读.dts的基本元素为节点和属性ARM Linux中，一个.dts文件对应一个ARM的设备，一般放置在内核的arch/arm/boot/dts目录中。
	
	如下是uartlite的设备树部分，其中“uartlite_0@42C00000”前面部分表示的是uartlite的名称，后部分表示的是uartlite的地址。“compatible”属性表示uartlite设备与驱动连接建立的的名称，为“xlnx,axi-uartlite-1.02.a”；
	
	“reg”属性表示uartlite的起始地址和寄存器大小；“interrupts”表示uartlite的中断信息，第一个参数是中断类型，第二个是中断号，第三个是中断触发条件。“clock”表示uartlite的时钟频率。
       
       uartlite_0@42C00000 {
            compatible = "xlnx,axi-uartlite-1.02.a";
            reg = <0x42C00000 0x10000>;
            interrupt-parent = <0x3>;
            interrupts = <0 29 4>;
            clock = <100000000>;
        };
	DTC
	
	DTC是将.dts编译为.dtb的工具。DTC的源代码位于内核的scripts/dtc目录中，在Linux内核使能了Device Tree的情况下，编译内核的时候主机工具dtc会被编译出来，对应scripts/dtc/Makefile中的“hostprogs-y := dtc”这一hostprogs编译target在Linux内核的arch/arm/boot/dts/Makefile中，描述了当某种SOC被选中后，哪些.dtb文件会被编译出来，如与VEXPRESS对应的.dtb如下：在Linux下可以单独编译设备树文件，当在Linux内核下运行make dtbs时，若之前选择了ARCH_VEXPRESS，上述.dtb都会有对应的.dts编译出来，因为arch/arm/Makefile中包含有一个.dtbs编译目标项目。

将dts文件编译成dtb文件的命令为：
	dtc -I dts -O dtb -o devicetree.dtb devicetree.dts
其中devicetree.dts为输入的dts文件，devicetree.dtb为输出的dtb文件。
	DTB
	文件.dtb是.dts被DTC编译后的二进制格式的Device Tree描述，可由Linux内核解析。
	
	通常在我们为电路板制作NAND、SD启动image时，会为.dtb文件单独留下一个很小的区域以存放之，之后bootloader在引导kernel的过程中，会先读取该.dtb到内存。

5.Uartlite驱动接口函数

打开设备：
在linux下编程实现对具体设备的操作，首先要做的就是打开要操作的设备文件，uartlite设备的设备文件是”/dev/ttyUL1”,具体实现函数是：
fd = open(uart,O_RDWR | O_NOCTTY)

配置串口设备：
这个函数是一个重要的函数，在使用串口设备时，需要对其进行配置，若需要配置的参数是波特率为9600、8位数据位宽、无停止位、奇校验，配置的函数为：
ret = set_opt(fd,9600,8,'N',1)

向设备写数据：
向串口设备写数据，先定一个数组，再写入串口设备
char buffer_out[] = "hello world!\n";            需要输出的字符串
ret = write(fd,buffer_out,strlen(buffer_out));   将字符串输出到串口设备

从设备读数据：
从串口读数据，同样定义一个数组作为缓存区，再读取串口设备
char buffer_in[512]; 			接收数组
ret = read(fd,buffer_in,10);	接收10个字符

关闭设备：
close(fd);

实验步骤：

Led驱动

1.在vivado里搭建好硬件工程，包括：led、sw和uart模块。（详见实验2）

2.搭建好后生成比特流文件，利用SDK软件将fsbl文件、比特流文件、u-boot文件生成boot.bin启动文件。(详见实验2)

3.在driver_code/led目录下找到ees331_led.c源文件，双击打开源文件，也可以通过终端命令gedit 打开:
编写led驱动源代码，修改三个部分：

添加led的地址：
/*   Modify the address to your peripheral   */
#define ees331_led_PHY_ADDR    
/*   Modify the address to your peripheral   */

led驱动的初始化函数为如下：
int __init ees331_led_init(void)
{
	int ret;
	GPIO_Regs = ioremap(ees331_led_PHY_ADDR, 32); 
	ret = misc_register(&ees331_led_dev);
	 if (ret)
	 {
    printk("ees331_led:[ERROR] Misc device register failed\n");
    return ret;
  }，
  printk("ees331_led: success! Module init complete\n");
  iowrite32(255, GPIO_Regs);
  return 0; /* Success */
}

添加控制函数的代码，如下：
static int ees331_led_ioctl(struct file *filp, unsigned int reg_num, unsigned long arg)
{
/*   Add your code here   */
  //通过led地址给led寄存器赋值
/*   Add your code here   */
  return 0;
}

在驱动的文件操作结构体添加代码，如下
static const struct file_operations ees331_led_fops =
{
	
  .owner = THIS_MODULE,
/*   Add your code here   */
  .open =,
  .release =,
  .read =,
  .unlocked_ioctl =,  
/*   Add your code here   */
};

4.打开Makefile 文件，修改其中部分，加入交叉编译器和内核源码树目录，如下。
ifneq ($(KERNELRELEASE),)
obj-m	:= ees331_led.o

else
ifeq ($(TARGET),)
TARGET := $(shell uname -r)
endif
PWD := $(shell pwd)
/*   Add your code here   */

CC = 
KDIR ?= 

/*   Add your code here   */

default:
		@echo $(TARGET) > module.target
		$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
		@rm -f *.ko *.o modules.order Module.symvers *.mod.? .ees331_led*.* *~
		@rm -rf .tmp_versions module.target

install: ees331_led.ko
install --mode 0644 ees331_led.ko /lib/modules/$(shell cat module.target)/kernel/drivers/char/
		/sbin/depmod -a $(shell cat module.target)
ees331_led.ko:
		$(MAKE)
endif

在需要添加部分加入交叉编译器和内核源码树目录$(CROSS_COMPILE)gcc、/home/zynq/Downloads/2016.3/linux-xlnx-xilinx-v2016.3

5.虚拟机中打开一个终端，在led目录下执行make命令，生成.ko驱动模块文件。
	make 

6．将测试文件ledtest.c进行交叉编译，（或者在开发板上执行gcc命令），生成可执行文件ledtest。
	arm-linux-gnueabihf-gcc ledtest.c -o ledtest

7.在win7系统里打开putty软件，选择对应的com口，波特率选择为115200。

8.putty的窗口里，进入到arm-linux系统里，将ees331_led.ko和 ledtest文件拷贝到SD卡根文件系统的root目录下。
scp zynq@192.168.1.12:/home/zynq/driver_code/led/ledtest    /root
scp zynq@192.168.1.12:/home/zynq/driver_code/led/ees331_led.ko /root

9.putty的窗口里，在/root(~)目录下执行insmod 命令，将驱动模块动态加载到内核中。
insmod ees331_led.ko
驱动加载成功后，在/dev/目录中用ls命令可以查看到相应的设备。
ls   /dev/

10.putty的窗口里，返回到/root目录，在/root(~)目录下运行测试程序ledtest，putty的ARM-linux 操作系统的命令行输入：	
./ledtest

11.putty的窗口里，程序会提示：please enter the led status,输入与希望显示的led 状态对应的ledstatus 值（输入十进制值即可），观察led 的显示情况。

12.putty的窗口里，卸载led驱动模块：
rmmod ees331_led

UART驱动

1.在vivado里搭建好硬件工程，包括：led、sw和uart模块。

2.搭建好后生成比特流文件，利用SDK软件将fsbl文件、比特流文件、u-boot文件生成boot.bin启动文件。

3.在driver_code/BOOT相应目录下找到devicetree.dts源文件，打开源文件（图中的目录是devicetree目录，实际是BOOT），修改设备树文件，如下：
		ees331_uart@42c00000 {
			clock-names = "ref_clk";
			clocks = "clkc 0";
			compatible = "xlnx,xps-uartlite-1.00.a";
			current-speed = <0x2580>;
			device_type = "serial";
			port-number = <0x1>;

		/*   Add your code here   */

			reg = <>;				//寄存器的起始地址 和偏移量
			xlnx,baudrate = <>;		//波特率
			xlnx,data-bits = <>;	//数据位宽
			xlnx,odd-parity = <>;	//奇偶校验位
			interrupt-parent=<>;	//中断节点数
			interrupts=<>;			//中断信息

	/*   Add your code here   */
			xlnx,s-axi-aclk-freq-hz-d = "100.0";
			xlnx,use-parity = <0x0>;

		};	
在注释部分增加设备树信息。


4.在虚拟机终端中，将设备树文件dts转换成dtb格式，并通过读卡器将devicetree.dtb拷贝到SD里的BOOT分区里：
	dtc -I dts -O dtb -o devicetree.dtb devicetree.dts

5.在driver_code/uartlite目录下修改测试程序uart.c。
int main(void)  
{  
    int fd,ret;  

	/*  Add your code here  */
	//1.加入设备名称；2.填写自己的学号

    char *uart = "";  
    char buffer_out[] = "";  

	/*  Add your code here  */

    char buffer_in[512];       
    memset(buffer_in,0,512);  
    fd = open(uart,O_RDWR | O_NOCTTY);  
    if(fd == -1)  
    {  
        printf("%s open failed\n",uart); 
	return -1; 
    }   

    printf("%s open success\n",uart);  
    ret = set_opt(fd,9600,8,'N',1);  
    if(ret == -1)  
    {  
        exit(-1);  
    }  
    ret = write(fd,buffer_out,strlen(buffer_out));
    printf("your number sent  %d\n",ret); 
    while(1)  
    {  
	/*  Add your code here  */
	//1.主程序实现接收字符，并把接收到的字符在发送出去
	
	
	
	
	
	/*  Add your code here  */
    }  
    close(fd);  
}  

6.对提供的测试程序uart.c 进行交叉编译，生成可执行文件uart，在终端下输入以下命令：
cd /home/zynq/driver_code/uartlite
sudo su        （密码：1） 
source zynq-env.sh  
arm-linux-gnueabihf-gcc uart.c -o uart

7.对驱动文件进行编译，生成驱动模块uartlite.ko，在同一个终端下继续输入命令：
make

8.在win7系统里打开putty软件，选择对应的com口，波特率选择为115200。

9.putty的窗口里，将uartlite.ko和uart文件拷贝到SD卡的root目录下。
scp zynq@192.168.1.12:~/driver_code/uartlite/uart   /root
scp zynq@192.168.1.12:~/driver_code/uartlite/uartlite.ko  /root

10.putty的窗口里，进入到arm-linux系统里，在/root(~)目录下执行insmod 命令，将驱动模块动态加载到内核中。
insmod uartlite.ko
驱动加载成功后，在/dev/目录中用ls命令可以查看到相应的设备。
ls  /dev/

11.用双头usb线将开发板上PL的串口（5上）与上位机连接，打开串口助手，选择对应的com口与波特率9600。

12..putty的窗口里，在/root（~）目录下运行测试程序uart，putty的ARM-linux 操作系统的命令行输入：
./uartlite

实验截图：
