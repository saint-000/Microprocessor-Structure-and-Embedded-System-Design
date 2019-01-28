;功能：计算1+2+3+4+...+N
;说明；N>=0,当N=0时结果为0，当N=1时结果为1

N EQU 100   ;定义N的值100
	AREA Examples,CODE,READONLY   ;声明代码断Examples3
	ENTRY   ;标识程序入口 
	
	CODE32
ARM_CODE

	LDR SP,=0X30003F00    ;设置堆栈指针
	ADR R0,THUMB_CODE+1    ;
	BX R0       ;跳转并切换处理器状态
	LTORG       ;声明文字池

	CODE16
THUMB_CODE

	LDR R0,=N      ;设置子程序SUM_N的入口参数
	BL SUM_N      ;调用子程序SUM_N
	B THUMB_CODE 

;SUM_N
;功能：计算1+2+3+......+N
;入口参数：R0 N的值
;出口参数：R0 运行结果 
;占用资源：R0
;说明：当N=0时结果为0，当N=1时结果为1
;若运算溢出，结果为0

SUM_N
	PUSH {R1-R7,LR}    ;寄存器入栈保护
	MOVS R2,R0     ;将n的值复制到R2,并影响相应条件标志
	BEQ SUM_END     ;若N=0,则返回
	CMP R2,#1
	BEQ SUM_END     ;若N=1,则返回
	MOV R1,#1     ;初始化计数器R1=1
	MOV R0,#0     ;初始化计数器R0=1
SUN_L1
	;------------------------------------------
;用汇编实现算法核心部分
	ADD R0,R1
	BVS SUM_END
	ADD R1,#1
	B SUN_L1
SUM_ERR
	MOV R0,#0
	
	
	
	
	;------------------------------------------

SUM_END 
	MOV R8,R0		 ;将结果保存在R8中
	POP {R1-R7,PC}   ;寄存器出栈，返回
        
	END
