		AREA	Example,CODE,READONLY	  	;声明代码段Example1 
		ENTRY				  				;标识程序入口 
		CODE32				  				
START 	MOV		R1,#0x04		  			 
		MOV		R2,R1
		MOV		R3,R2,LSL #4	    		
		    		    					 
		LDR		R3,[R2]		    			
		MOV		R0,PC            	    				 
		MOV		R3,#0x10
		LDR		R4,[R3,#0x0C]	    		
			  	    						 
		LDMIA	R1!,{R4-R7,R12}     		
			    	     					
		MOV		SP,#0x30
		
		MOV		R2,#0x22
		MOV		R3,#0x33
		MOV		R4,#0x44
		MOV		R5,#0x55
		STMFA	R13!,{R2-R5}        		
			    	     					
		LDMFA	SP!,{R2-R5}         		
LOOP	BL		ADD_SUB	    	     		 
		B		LOOP		     			
		
ADD_SUB	 
		ADDS	R0,R0,R1	     			
		MOV		PC,LR	     	     		 
		END			     					
