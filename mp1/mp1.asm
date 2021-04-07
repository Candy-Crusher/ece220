		.ORIG X3000		
;PRINT_SLOT:
;A number from 0 to 14 is passed to this subroutine in R1. 
;The subroutine prints the time corresponding to the specified slot.(R1+6)
;If R1=0, for example, your subroutine must print “0600”
;preceded by three spaces (ASCII x20) and followed by two trailing spaces.

PRINT_SLOT	
		;store R0-R7
		ST R0,STORE_REGISTER0
		ST R1,STORE_REGISTER1
		ST R2,STORE_REGISTER2
		ST R3,STORE_REGISTER3
		ST R4,STORE_REGISTER4
		ST R5,STORE_REGISTER5
		ST R6,STORE_REGISTER6
		ST R7,STORE_REGISTER7

		;print preceded spaces
		LD R0,SPACE
		OUT
		OUT
		OUT

		;print numbers

		;test if R1<=3
		ADD R2,R1,#-3
		BRp FIRSTN_NOT_ZERO
		;if R1<=3, first digit should be 0,print
		LD R0,ZERO
		OUT
		;if R1<=3,second digit should be R1+6;print
		LD R2,START_TIME
		ADD R0,R1,R2
		OUT
		BRnzp LATTER
		;go to print followed zeros and spaces

FIRSTN_NOT_ZERO ;test if R1=14
		ADD R2,R1,#-14
		BRn FIRSTN_1
		;if R1=14,the first digit should be 2,print
		LD R0,ZERO
		ADD R0,R0,#2
		OUT
		;if R1=14,the second digit should be 0,print
		LD R0,ZERO
		OUT
		BRnzp LATTER
		;go to print followed zeros and spaces
FIRSTN_1	;if 3<=R1<14,the first digit should be 1
		LD R0,ZERO
		ADD R0,R0,#1
		OUT
		;if 3<=R1<14,the second digit should be R1-4
		LD R0,ZERO
		ADD R2,R1,#-4
		ADD R0,R0,R2
		OUT
		
		;print followed zeros and spaces
LATTER		LD R0,ZERO
		OUT
		OUT
		LD R0,SPACE
		OUT
		OUT
		;load back
		LD R0,STORE_REGISTER0
		LD R1,STORE_REGISTER1
		LD R2,STORE_REGISTER2
		LD R3,STORE_REGISTER3
		LD R4,STORE_REGISTER4
		LD R5,STORE_REGISTER5
		LD R6,STORE_REGISTER6
		LD R7,STORE_REGISTER7
		RET

;The second subroutine is PRINT_CENTERED. 
;A string (the address of the first ASCII character 
;in sequence terminated by an ASCII NUL, x00) is passed to your subroutine in R1. 
;Your subroutine must print exactly nine characters. 
;If the string is longer than nine characters, 
;your subroutine must print the first nine characters. 
;If the string is shorter than nine characters, 
;your subroutine must print additional spaces 
;around the string to bring the total length to nine characters. 
;If the number of spaces needed is odd, 
;the subroutine must use one more leading space than trailing space.




PRINT_CENTERED	;store R0-R7
		ST R0,STORE_REGISTER0
		ST R1,STORE_REGISTER1
		ST R2,STORE_REGISTER2
		ST R3,STORE_REGISTER3
		ST R4,STORE_REGISTER4
		ST R5,STORE_REGISTER5
		ST R6,STORE_REGISTER6
		ST R7,STORE_REGISTER7
		;initialize
		AND R2,R2,#0
		ADD R4,R1,#0;copy R1 to R4
		;count the length of the string
	COUNT_LENGTH
		LDR R3,R1,#0;load first character to R3
		BRz COMPARE
		; check if the string ends
		ADD R2,R2,#1;the length of the string is stored in R2
		ADD R1,R1,#1
		BRnzp COUNT_LENGTH
		;go to check next character
		;compare the length of the string with 9
	COMPARE
		ADD R1,R4,#0;copy the address of the first character to R1
		ADD R4,R2,#-9;R4 <- R2-9
		BRzp NOT_SMALLER_THAN_9
	SMALLER_TAHN_9
		NOT R4,R4;R4 <- 9-R2-1
		ADD R4,R4,#1;R4 <- 9-R2
		AND R5,R5,#0
		AND R3,R3,#0
		ADD R3,R4,#0;R3 is 9-R2

	CULCULATE_SPACE	
		ADD R5,R5,#1;R5 as former spaces counter
		ADD R4,R4,#-2;R4/2
		BRp CULCULATE_SPACE
		AND R6,R6,#0
		ADD R6,R5,R6
		;print former spaces
	FORMER_SPACE
		BRz PRINT_STRING
		LD R0,SPACE
		OUT
		ADD R5,R5,#-1
		BRnzp FORMER_SPACE
		;print string
	PRINT_STRING
		ADD R2,R2,#0
		BRz LATTER_SPACE1
		LDR R0,R1,#0
		OUT
		ADD R1,R1,#1
		ADD R2,R2,#-1
		BRnzp PRINT_STRING
		;print latter spaces
	LATTER_SPACE1
		NOT R6,R6;R6 was the number of former spaces
		ADD R6,R6,#1
		ADD R5,R3,R6;R5 is 9-string length-former spaces length=latter spaces length
	LATTER_SPACE2
		BRz DONE
		LD R0,SPACE
		OUT
		ADD R5,R5,#-1
		BRnzp LATTER_SPACE2
	NOT_SMALLER_THAN_9
		AND R4,R4,#0
		ADD R4,R4,#9;R4 as a counter of 9
		;print first 9 characters
	FIRST_9
		BRz DONE
		LDR R0,R1,#0
		ADD R1,R1,#1
		OUT
		ADD R4,R4,#-1
		BRnzp FIRST_9

	DONE	;load back
		LD R0,STORE_REGISTER0
		LD R1,STORE_REGISTER1
		LD R2,STORE_REGISTER2
		LD R3,STORE_REGISTER3
		LD R4,STORE_REGISTER4
		LD R5,STORE_REGISTER5
		LD R6,STORE_REGISTER6
		LD R7,STORE_REGISTER7
		RET

SPACE		.FILL X20
START_TIME	.FILL X36
ZERO		.FILL X30
STORE_REGISTER0 .BLKW #1
STORE_REGISTER1 .BLKW #1
STORE_REGISTER2 .BLKW #1
STORE_REGISTER3 .BLKW #1
STORE_REGISTER4 .BLKW #1
STORE_REGISTER5 .BLKW #1
STORE_REGISTER6 .BLKW #1
STORE_REGISTER7 .BLKW #1
		.END
