1.掌握ARM的GPIO，UART接口工作原理。

2.学习编程实现GPIO接口的控制及ARM和PC机的UART通信。

3.掌握ARM裸机下C语言编程方法。

需要了解：

1.数码管
1.18段数码管
八段数码管主要由“位选”和“段选”两块电路驱动。
位选中每一位对应一个数码管，从左至右为7—0号数码管，对应位选的低位到高位。
段选每个寄存器对应数码管的a,b,c,d,e,f,g,dp 段，从高到低依次对应dp-a，1为亮，0为灭。例如0的字型数据为0x3f。

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/1.PNG)

1.2引脚约束
该实验板上1-8引脚对应0-3号数码管段选，13-10号引脚对应4—7号数码管的段选。9—12,21—24为位选，对应控制0—7号数码管

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/2.PNG)

1.3工程相关内容
硬件工程：
硬件工程里有三个8位的GPIO，两个输出的：SEG_W和SEG_D，一个输入的：SW。
SEG_W和SEG_D分别对应位选和左边四个数码管的段选。为三个GPIO分配的地址可在address_editor中查看。
硬件工程已经搭建，比特流生成完毕。
软件程序：
用到的接口函数有：

1.intXGpio_Initialize(XGpio * InstancePtr, u16 DeviceId)：
功能：初始化GPIO
参数：InstancePtr：指向设备的指针
DeviceId：设备id，可在,xparameters.h中找到

2.voidXGpio_SetDataDirection(XGpio *InstancePtr, unsigned Channel,u32 DirectionMask)：
功能：设置GPIO为输入/输出
参数：InstancePtr：指向设备的指针
Channel：通道（1或2）
DirectionMask：标志设备输入输出（0xffffffff为输入，0x0为输出）

3.voidXGpio_DiscreteWrite(XGpio * InstancePtr, unsigned Channel, u32 Data)：
功能：读取GPIO的值
参数：InstancePtr：指向设备的指针
Channel：通道（1或2）
Data：将要写入InstancePtr指向寄存器的值

4.u32XGpio_DiscreteRead(XGpio * InstancePtr, unsigned Channel)：
功能：读取InstancePtr指向的寄存器的值，返回读取的数值
参数：InstancePtr：指向设备的指针
Channel：通道（1或2）
注：指向设备的指针，设备ID，通道号已在程序中定义完成

2.UART串口

2.1异步串行I／O
异步串行方式是将传输数据的每个字符一位接一位(例如先低位、后高位)地传送。数据的各不同位可以分时使用同一传输通道，因此串行I／O 可以减少信号连线，最少用一对线即可进行。接收方对于同一根线上一连串的数字信号，首先要分割成位，再按位组成字符。
为了恢复发送的信息，双方必须协调工作。在微型计算机中大量使用异步串行I／O 方式，双方使用各自的时钟信号，而且允许时钟频率有一定误差，因此实现较容易。但是由于每个字符都要独立确定起始和结束(即每个字符都要重新同步)，字符和字符间还可能有长度不定的空闲时间，因此效率较低。

2.2串行接口的物理层标准
通用的串行I／O 接口有许多种，现仅就最常见的一种标准作简单介绍。
EIA RS—232C：
这是美国电子工业协会推荐的一种标准(Electronic industries AssociationRecoilmendedStandard)。它在一种25针接插件(DB—25)上定义了串行通信的有关信号。这个标准后来被世界各国所接受并使用到计算机的I／O接口中。
信号连线：
在实际异步串行通信中，并不要求用全部的RS—232C信号，许多PC／XT兼容机仅用15针接插件(DB—15)来引出其异步串行I／O信号，而PC中更是大量采用9针接插件(DB—9)来担当此任，因此这里也不打算就RS—232C 的全部信号作详细解释。
TXD／RXD：是一对数据线，TXD 称发送数据输出，RXD 称接收数据输入。当两台微机以全双工方式直接通信(无MODEM 方式)时，双方的这两根线应交叉联接(扭接)。
信号地：所有的信号都要通过信号地线构成耦合回路。
通信线有以上三条(TXD、RXD 和信号地)就能工作了。其余信号主要用于双方设备通信过程中的联络(握手信号)，而且有些信号仅用于和MODEM的联络。若采取微型机对微型机直接通信，且双方可直接对异步串行通信电路芯片编程，若设置成不要任何联络信号，则其它线都可不接。有时在通信线的同一端将相关信号短接以“自握手”方式满足联络要求。

2.3. UART串口管脚约束
EES331在PL端设计了一路UART模块电路，方便学习使用串口功能。该UART经CP2103芯片转换成USB通信方式经过J8的USB2.0母口与外部通信。

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/3.PNG)

EES331上有8个八段数码管，可以方便设计各种数值显示电路。八段数码管本身采用的是共阴极驱动的主要由“位选”和“段选”两块电路驱动。但具体的驱动电平需要根据如下原理图来确定。因为位选电路采用了三极管2N5551进行了反向驱动，所以这里需要特别提醒一下。
2.4. 工程相关内容
硬件工程：
搭建了一个UART接口，地址可在address editor处查看
硬件工程已经搭建，比特流生成完毕。
软件程序：
1.static INLINEu8 Xil_In8(UINTPTR Addr)：
功能：通过从指定地址读取并返回从该地址读取的8位值，对存储器位置执行输入操作。
参数：Addr：地址

2.static INLINEvoidXil_Out8(UINTPTR Addr, u8 Value)：
  功能：通过将8位值写入指定地址来执行内存位置的输出操作。
   参数：Addr：地址
         Value：要写入的值
注：UART串口相关地址已经定义

六、实验步骤

1.数码管实验

1.双击打开对应工程文件夹下的vivado project file

2.在File菜单下选择Export，点击包括比特流，点击OK 

3.在File菜单下选择luanch SDK，打开SDK软件

4.新建工程并命名，类型选择Empty Application

5.在新建的工程中添加源文件，新建Source File

6.为文件命名，注意要跟上文件类型.c，点击Finish

7.使用开关控制右四位数码管显示数字0~9，当值大于9时，数码管无显示
  其中开关从右至左为低位至高位，开关开状态为1，关状态为0，开关组成的2进制值对 应数码管上显示的十进制数值

8.点击保存,软件自动编译程序

9.用USB数据线将开发板2处接口与电脑主机连接，打开板子电源开关7，开发板1处拨码开关全部打到”on”

10.在vivado中点击左下角Open Hardware Manager，选择open target， 再选择Auto Connection 

11.点击Program device，在弹出的窗口中找到工程的比特流，比特流文件在工程中的路径为：project_name/project_name.runs/impl_1/system_wrapper.bit，如下图，点击Program下载比特流到板子

12.运行程序

13.拨动开关，观察数码管上的显示

14.可使用debug调试程序


2.UART串口实验

1.双击打开对应工程文件夹下的vivado project file

2.在File菜单下选择Export，点击包括比特流，点击OK 

3.在File菜单下选择luanch SDK，打开SDK软件

4.新建工程并命名，类型选择Empty Application

5.在新建的工程中添加源文件，新建Source File

6.为文件命名，注意要跟上文件类型.c，点击Finish

7.通过PL上的UART串口发送单个字符，接收后向串口回传该字符，若收到的字符为“x”，则退出程序

8.点击保存,软件会自动编译程序

9.用USB数据线将开发板2处UART接口与电脑主机连接，将5上方的USB口用双头USB线连接至主机，打开板子电源开关7

10.在vivado中点击左下角Open Hardware Manager，选择open target， 再选择Auto Connection 

11.点击Program device，在弹出的窗口中找到工程的比特流，比特流文件在工程中的路径为：project_name/project_name.runs/impl_1/system_wrapper.bit，如下图，点击Program下载比特流到板子

12.计算机→管理，在设备管理器→端口里查看Silicon Labs CP210x USB to UART Bridge对应的端口号

13.打开串口调试助手，将串口设置为该端口号，将波特率设为9600，其余配置不改变，然后打开串口

14.运行程序

15.在串口助手里，输入字符，点击TX发送，在左上方的框里看是否有接受到正确的字符

实验截图：

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/4.png)

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/5.png)

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/6.png)
