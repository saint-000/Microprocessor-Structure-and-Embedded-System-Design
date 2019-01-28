	AREA	Example,CODE,READONLY	  	;声明代码段Example1 
	ENTRY				  				;标识程序入口 
	CODE32				  				;声明32位ARM指令
START 	
	MOVS		R0,#0x04					;立即寻址
	MOVS		R1,#0x100
	MOVS		R2,#0x0
		
	LDR			R0,=0x12345678
		
	MOV		R5,R2						;寄存器寻址
	ADD		R7,R1,R2
	CMP		R1,R2

	MOV		R4,R0,ROR #1				;寄存器移位寻址		
	ADD		R3,R1,R0,LSL #2	  			 
	MOV		R3,R2,LSL #4	    		;寄存器移位寻址
	SUB		R6,R5,R2,LSL #3				;寄存器移位寻址
	B		START
	END			     					;文件结束

