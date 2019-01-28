		AREA	Example,CODE,READONLY	  	;声明代码段Example1 
		ENTRY				  				;标识程序入口 
		CODE32				  				;声明32位ARM指令
START 	MOV		SP,#0x300000
		MOV		R1,#0x11
		MOV		R2,#0x22
		MOV		R3,#0x33
		MOV		R4,#0x44
		MOV		R5,#0x55
		STMFA	R13!,{R2-R5}        		;将寄存器R2～R5内容存入堆栈
		MOV		R2,#0X77
		LDMFA	R13!,{R2-R5}
		MOV		SP,#0x400000
		STMEA	R13!,{R1-R5}        		;将寄存器R1～R5内容存入堆栈
		
		MOV		SP,#0x5400000
		STMFD	R13!,{R2-R5}        		;将寄存器R2～R5内容存入堆栈
		
		MOV		SP,#0x600000
		STMED	R13!,{R2-R4}        		;将寄存器R2～R4内容存入堆栈	   
		MOV		R0,#0  
		B			START   					
		END			     					;文件结束
