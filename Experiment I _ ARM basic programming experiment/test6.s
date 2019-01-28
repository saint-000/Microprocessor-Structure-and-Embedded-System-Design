
		AREA	Example,CODE,READONLY	  	;声明代码段Example1 
		ENTRY				  				;标识程序入口 
		CODE32				  				;声明32位ARM指令
START 	;into system mode
    	MRS		R0,CPSR
    	BIC 	R0,R0,#0x1F
    	ORR 	R0,R0,#0x1F
    	MSR 	CPSR_cxsf,R0
    	MOV 	R0,#0
    	MOV 	R1,#1
    	MOV 	R2,#2 
    	MOV 	R3,#3
    	MOV 	R4,#4
    	MOV 	R5,#5 
    	MOV 	R6,#6
    	MOV 	R7,#7
    	MOV 	R8,#8 
    	MOV 	R9,#9
    	MOV 	R10,#0x0A
    	MOV 	R11,#0x0B
    	MOV 	R12,#0x0C
    	MOV 	R13,#0x0D
    	MOV 	R14,#0x0E

		;into FIQ mode
    	MRS 	R0,CPSR
    	BIC 	R0,R0,#0x1F
    	ORR 	R0,R0,#0x11
    	MSR 	CPSR_cxsf,R0
    	MOV 	R8,#0x18 
    	MOV 	R9,#0x19
    	MOV 	R10,#0x1A
    	MOV 	R11,#0x1B
    	MOV 	R12,#0x1C
    	MOV 	R13,#0x1D
    	MOV 	R14,#0x1E

		;into SVC mode
   	 	MRS 	R0,CPSR
    	BIC 	R0,R0,#0x1F
    	ORR 	R0,R0,#0x13
    	MSR 	CPSR_cxsf,R0
    	MOV 	R13,#0x2D
    	MOV 	R14,#0x2E

		;into Abort mode
    	MRS 	R0,CPSR
    	BIC 	R0,R0,#0x1F
    	ORR 	R0,R0,#0x17
    	MSR 	CPSR_cxsf,R0
    	MOV 	R13,#0x3D
    	MOV 	R14,#0x3E

		;into IRQ mode
    	MRS 	R0,CPSR
    	BIC 	R0,R0,#0x1F
    	ORR 	R0,R0,#0x12
    	MSR 	CPSR_cxsf,R0
    	MOV 	R13,#0x4D
    	MOV 	R14,#0x4E

		;into UND mode
    	MRS 	R0,CPSR
    	BIC 	R0,R0,#0x1F
    	ORR 	R0,R0,#0x1b
    	MSR 	CPSR_cxsf,R0
    	MOV 	R13,#0x5D
    	MOV 	R14,#0x5E

    	B 		START

    	END
