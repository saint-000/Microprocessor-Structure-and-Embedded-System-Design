;文件名：TESTFILE.S 
;功能：从C语言中调用汇编语言
 
		AREA	Example1,CODE,READONLY	  ;声明代码段Example1 
		CODE32				  ;声明32位ARM指令

		IMPORT __main

		
		EXPORT strcopy
strcopy	
	;------------------------------------------
;用汇编实现字符串拷贝
	
	LDRB  R2,[R1],#1	     ;拷贝源字符串的一个字节
	STRB  R2,[R0],#1              ;将拷贝的字节复制到目标空间
	
	CMP   R2,#0
	BNE   strcopy
	
	MOV   PC,LR
	;------------------------------------------
		
	END			     	   ;文件结束
