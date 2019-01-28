;文件名：TESTFILE.S 
;功能：从汇编语言中调用C语言

		IMPORT g
		
		AREA	Example1,CODE,READONLY	  	;声明代码段Example1 
		CODE32				  	;声明32位ARM指令
		ENTRY

START	
	;------------------------------------------
;通过调用c函数g（）实现1+2+3+10，结果存在R8中
	
		MOV		R0,#1	
		MOV		R1,#2
		MOV		R3,#10
		BL		g
		MOV		R8,R0	
		B		START
	
	
	
	;------------------------------------------

		END			     					;文件结束

