		AREA	Example,CODE,READONLY	  	;声明代码段Example1 
		ENTRY				  				;标识程序入口 
		CODE32				  				;声明32位ARM指令
START 	MOV		R1,#0x01		  			; 
		MOV		R2,#0x04
		MOV		R3,#0x03
		MOV		R4,#0x04
		MOV		R5,#0x05
			    			
		LDR		R6,[R2]		    			;寄存器间接寻址
		LDR		R6,[R2,#4]
		STR		R3,[R7]
		LDR		R7,[R2,#0x0C]	    		;基址＋变址寻址 注意字节对齐R2的值要是4的整数倍
			  	    						
		LDR		R0,=0x100000
		STMIA	R0,{R1-R3}					;多寄存器寻址
		LDR		R0,=0x100000
		STMIB	R0,{R1-R3}					;多寄存器寻址
		LDR		R0,=0x200008
		STMDA	R0,{R1-R3,R5}				;块拷贝寻址
		LDR		R0,=0x210000
		LDMIA	R0,{R1-R5,R7}		
		MOV		R0,#0x0						;非跳转的指令最后一条无法运行
		B		START			
		END			     					;文件结束
