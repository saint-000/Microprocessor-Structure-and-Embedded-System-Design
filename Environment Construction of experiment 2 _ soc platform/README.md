以PS与PL协同设计实现GPIO为例，自行搭建SoC平台环境。
将FPGA当做一个PS处理器的外设，通过寄存器地址映射到PS的寻址空间。在处理器中使用C程序访问这些寄存器，来实现软件和逻辑结合的协同设计的效果。
具体步骤是先在VIVADO中配置ZYNQ处理器，做好FPGA的外设，互联完成之后生成BIT流文件下载到板子。在SDK环境下开发好软件之后，进行在线调试运行。

需要了解：
当前嵌入式设计发展迅猛，有很多需求无法被现有的产品满足。现有的产品包括单个处理器、单个ASIC、ASSP或者单纯的FPGA方案，甚至这些方案的组合也都无法满足需求。深入了解下一代嵌入式处理器的需要，会发现提高性能、减少成本、降低功耗、缩小外形、增加灵活性是主要需要。现有方案的局限性也是相当明显的，例如有的微处理器缺乏足够的信号处理能力，需要多芯片方案来搭建下一代的处理器系统。

多芯片方案成本较高，功耗大，占用更多的空间，不利于缩小外形。
ZYNQ-7000是Xilinx推出的一款全可编程片上系统（All Programmable SoC），该芯片集成了ARM Cortex A9双核与FPGA，是一款SoPC芯片。其架构如下图，图中的Processing System（PS）即为处理器（ARM Cortex A9 MPCore）部分，里面资源非常的丰富。Programmable Logic（PL）即可编程部分（FPGA），该部分的资源随SoC芯片级别高低不同而不同。

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/19.PNG)


![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/20.PNG)
Zynq-7000系列的亮点在于它包含了完整的ARM处理子系统，每一颗Zynq-7000系列的处理器都包含了双核的CortexTM-A9处理器，整个处理器的搭建都以处理器为中心，而且处理器子系统中集成了内存控制器和大量的外设，使CortexTM-A9的核在Zynq-7000中完全独立于可编程逻辑单元，也就是说如果暂时没有用到FPGA的部分，ARM处理器的子系统也可以独立工作。

在ZYNQ中，可以把PL看成是PS的另一个具有可重配置特点的“外设”，它可以作为PS部分的一个从设备，受ARM处理器控制，比如ARM（PS）的串口数量不够时，以太网接口不够时，或者需要视频接口时都可以用PL部分扩展。FPGA的部分用于扩展子系统，其有丰富的扩展能力，有超过3000个内部互连，连接资源非常丰富。此外在I/O接口方面，FPGA的优点是I/O可以充分自定义，并在FPGA部分集成高速串行口（Multi Gigabit Transceiver）。
Xilinx为ZYNQ的开发提供了软件：Xilinx Vivado、Xilinx Software Development Kit（SDK）。关于这两个软件的定位以及作用，Xilinx官网都有详细的说明。

Vivado
主要用来搭建整个硬件环境，完成系统集成，提供了一个IP核图形界面，让用户可以创建集成了PL和PS的系统的结构图。
专注于集成的组件——为解决集成的瓶颈，Vivado 设计套件采用了用于快速综合和验证C 语言算法IP 的ESL 设计，实现重用的标准算法和RTL IP封装技术，标准IP 封装和各类系统构建模块的系统集成，模块和系统验证的仿真速度提高了3倍，与此同时，硬件协仿真性能提升了100倍。

专注于实现的组件——为解决实现的瓶颈，Vivado工具采用层次化器件编辑器和布局规划器、速度提升了3至15倍，且为SystemVerilog 提供了支持的逻辑综合工具、速度提升4倍且确定性更高的布局布线引擎，以及通过分析技术可最小化时序、线长、路由拥堵等多个变量的“成本”函数。此外，增量式流程能让工程变更通知单(ECO) 的任何修改只需对设计的一小部分进行重新实现就能快速处理，同时确保性能不受影响。

最后，Vivado 工具通过利用最新共享的可扩展数据模型，能够估算设计流程各个阶段的功耗、时序和占用面积，从而达到预先分析，进而优化自动化时钟门等集成功能。

SDK
是Xilinx对Eclipse的改装，主要用于软件部分的设计，在SDK中可以创建全功能的软件应用、编译然后调试。SDK 包括基于 GNU 的编译工具链（GCC 编译器、GDB 调试器、工具和库）、JTAG 调试器、闪存编程器、Xilinx IP 的驱动和裸机 BSP 及应用领域函数的中间件库。这个 SDK 的功能包括：
• 项目管理
• 错误导航
• C/C++ 代码编辑和编译环境
• 应用构建配置和自动产生 makefile
• 调试和剖析嵌入式目标的集成环境
• 通过第三方插件的额外功能，比如源代码和版本控制
• 第一级引导装载程序（FSBL）的应用模板，以及构建引导映像的图形界面

本实验选用依元素EES331开发板，EES-331是依元素科技基于Xilinx ZYNQ-7000 FPGA 研发的基础教学平台。其配备的 FPGA (xc7z020clg484-1)具有ARM-A9 双核处理器和丰富 PL 逻辑资源等特点，结合SoC设计的概念能实现较复杂的数字逻辑设计和复杂的控制逻辑设计。该平台拥有丰富的外设，以及灵活的通用扩展接口。EES331硬件实物如下图所示，开发板的详细信息参见EES331用户手册。


![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/21.PNG)

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/22.PNG)

具体步骤：

1.打开桌面VIVADO 2017.3，点击Create Project创建新工程。为新工程命名，选择工程保存路径，点击Next。选择芯片xc7z020clg484-1，点击Next → Finish。点击Create Block Design，创建块设计，并命名

2.在右侧Diagram窗口空白处右击 → Add IP。搜索zynq，双击ZYNQ7 Processing System，添加zynq处理器，并点击Run Block Automation，勾选处理器→ 点击OK，会自动进行一些配置

3.再添加两个GPIO核，在Diagram窗口空白处右击 → Add IP → 搜索gpio → 双击。操作两次，添加两个AXI GPIO核，点击Run Connection Automation，勾选All Automation，点击OK，进行自动配置。自动连接之后在空白处右击选择Regenerate Layout，重新布局

4.双击ZYNQ处理器核，进行配置，更改DDR型号为MT41K256M16 RE-15E，将Bank1 I/O电平设为1.8V，勾选Uart1，用于通过串口查看程序打印信息

5.将GPIO IP核的名字和端口名称修改为LED和SW。双击LED IP核，配置LED为输出，GPIO Width设置为8，对应8个LED灯，点击OK。双击SW IP核，配置SW为输入，GPIO Width设置为8，对应8个拨码开关，点击OK

6.新建约束文件：右击Constraints → Add Sources → 点击Next---Create File，为文件命名，点击OK → Finish。根据EES331用户手册中LED和SW的管脚约束表，在PINS_SET.xdc中添加引脚与电平约束并保存

7.生成顶层文件：先右击system → Generate Output Products → Generate，再右击system → Create HDL Wrapper → OK。Vivado会为IP子系统生成一个顶层文件，以便对该系统进行综合、实现并生成比特流

8.工程配置完成，点击左下侧Generate Bitstream生成比特流，点击Yes → OK，等待比特流生成。若没有其他错误，比特流生成完成后直接关闭弹出的窗口或选择查看报告

9.硬件工程设计好之后，可在以下窗口中看到系统分配给外设的地址。接下来将硬件工程导出到SDK，在SDK中进行软件编译与运行（注：不要单独打开SDK，是在VIVADO中导出）。VIVADO -> File → Export Hardware Design to SDK，导出硬件到SDK，打钩，包括比特流，点击OK

10.打开SDK：File → Launch SDK → OK，进入SDK界面。在SDK中新建工程对LED和SW进行编程，实现相应功能。为新工程命名，并产生相应的BSP →  注意选Next → 选择空工程 →  Finish

11.在新建的工程中添加源文件，新建Source File或者Header File，为文件命名，注意要跟上文件类型.c或.h，点击Finish，在源文件中添加代码

12.硬件和软件设计好之后，保存工程，接下来调试和运行程序，运行之前先把板子的上所有拨码开关拨到下面。使用USB线连接PC机和开发板J3端口（JTAG/PS_UART），打开板子开关，在Vivado中点击左下角Open Hardware Manager → Open target → Auto Connection

若连接不上板子

1. 重启板子或电脑：开关断开或按下板子上的复位按钮（LED和数码管旁边S3/POR(B5)）

2. 杀进程：打开任务管理器——进程——hw_server.exe

13.下载比特流：点击Program device，在弹出的窗口中找到工程的比特流，比特流文件在工程中的路径为：project_name/project_name.runs/impl_1/system_wrapper.bit，如下图，点击Program下载比特流到板子。

14.若运行程序，则右击工程——Run As  ——Launch on Hardware（GDB）
若调试程序，则右击工程——Debug As——Launch on Hardware（GDB）

15.查看串口打印：使用桌面串口工具Putty，设置波特率和端口号。
端口号查看方式：右击桌面电脑/计算机 → 管理 → 设备管理器 → 端口

16.若工程正确，可看到8个LED灯循环闪烁，向上拨动任意一个拨码开关时，流水灯运行到最后一个LD7时停止。

实验截图:

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/23.png)

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/24.png)

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/25.png)

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/26.png)

![image](https://github.com/saint-000/Microprocessor-Structure-and-Embedded-System-Design/blob/master/image/27.png)

