

.ORIG X3000
; Add this test code to the start of your file (just after .ORIG).
; I'd put it in another file, but we can't use the PRINT_SLOT and 
; PRINT_CENTERED labels outside of the mp1.asm file (at least, not 
; easily).

; Read the comments in this file to understand what it's doing and
; for ways that you can use this test code.  You can also just run
; it and diff the output with the output produced by our 'gold'
; (bug-free!) version.
;
; After assembling mp1 with lc3as, execute the test script by typing
;    lc3sim -s script1 > your_output
; (look at the script--it just loads mp1 with a file command, then
; continues execution; when the LC-3 halts, the script is finished,
; so the simulator halts).
;
; You can then type
;    diff your_output out1
; to compare your code's output with ours.
;

	; feeling lazy, so I'm going to set all of the bits to the same value
	LD	R0,BITS
	ADD	R2,R0,#0
	ADD	R3,R0,#0
	ADD	R4,R0,#0
	ADD	R5,R0,#0
	ADD	R6,R0,#0

	; let's try PRINT_SLOT ... "   1100  "
	AND	R1,R1,#0
	LEA	R1,WORDS

	; set a breakpoint here in the debugger, then use 'next' to
	; execute your subroutine and see what happens to the registers;
	; they're not supposed to change (except for R7)...
	JSR	PRINT_CENTERED

	; we're short on human time to test your code, so we'll do 
	; something like the following instead (feel free to replicate)...
	LD	R7,BITS
	NOT	R7,R7
	ADD	R7,R7,#1
	ADD	R0,R0,R7
	BRz	R0_OK
	LEA	R0,R0_BAD
	PUTS
R0_OK	

	; this trap changes register values, so it's not sufficient
	; to check that all of the registers are unchanged; HALT may
	; also lead to confusion because the register values differ
	; for other reasons (R7 differences, for example).
	HALT
WORDS	
.FILL x0049  ; TEST_STRING[0]
.FILL x004c  ; TEST_STRING[1]
.FILL x004f  ; TEST_STRING[2]
.FILL x0056  ; TEST_STRING[3]
.FILL x0045  ; TEST_STRING[4]
.FILL x0059  ; TEST_STRING[5]
.FILL x004f  ; TEST_STRING[6]
.FILL x0055  ; TEST_STRING[7]
.FILL x0000  ; TEST_STRING[8]
.FILL x0041  ; TEST_STRING[9]
.FILL x0041  ; TEST_STRING[10]
.FILL x0041  ; TEST_STRING[11]
.FILL x0041  ; TEST_STRING[12]
.FILL x0041  ; TEST_STRING[13]
.FILL x0041  ; TEST_STRING[14]
.FILL x0000  ; TEST_STRING[15]
BITS	.FILL	xABCD	; something unusual
R0_BAD	.STRINGZ "PRINT_SLOT changes R0!\n"

; your code should go here ... don't forget .ORIG and .END		
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
