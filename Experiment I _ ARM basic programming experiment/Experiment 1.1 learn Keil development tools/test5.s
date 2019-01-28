		AREA	Example,CODE,READONLY	  	;声明代码段Example1 
		ENTRY				  				;标识程序入口 
		CODE32				  				;声明32位ARM指令
START 	MOV		R1,#0x04		  			 
		MOV		R2,#0x04
		SUBS	R3,R2,R1	    			
		
		MOVNE	R5,#0x200						
		ADDS	R7,R5,R2,LSL #0x4
		MOVS	R6,#8
		CMP		R1,R2
		
		MOV		R2,R2,ROR #4	    		
		SUB		R6,R5,R2,LSL #3				
		B			.
		END			     					;文件结束
