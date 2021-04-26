.ORIG x3000

;This program translates a student’s daily
;schedule from a list to a two-dimensional
;matrix of pointers (memory addresses, in this
;case to names of events), then prints the
;schedule. 
;First we initialize the content of new schedule to 0.
;Then we translate the old schedule to new schedule.
;Finally we print the new schedule.
			
			LD R6,EVENT_LIST 
			AND R5,R5,#0
			AND R1,R1,#0
			AND R0,R0,#0
			LD R2,START
;1.Initialize
;Register
;R5:temporery counter of 75
;R2:temporery pointer of shedule to 0 initialize shedule
;R1:0
			ADD R5,R5,#15
			ADD R5,R5,R5
			ADD R5,R5,R5
			ADD R5,R5,#15
INITIALIZE		STR R1,R2,#0
			ADD R2,R2,#1
			ADD R5,R5,#-1
			BRp INITIALIZE			

;2.Translating
;Register
;R6:event list pointer
;R5:present day filed content of event list
;R4:1/2/4/8/16
;R3:counter of 5
;R2:first address of string
;R1:shedule address calculator
;R0:temporery copy of time_n/temporery check if in the day
;/temporery as x3000/temporery check if conflict	
	
EACH_WORDS		AND R4,R4,#0
			ADD R4,R4,#1
			AND R3,R3,#0
			ADD R3,R3,#4
			LDR R5,R6,#0
			ADD R5,R5,#1
			BRz CALL
			ADD R5,R5,#-1
			ADD R6,R6,#1			;R6 points at the first char
			ADD R2,R6,#0			;R2 as the first address of words
			LDR R1,R6,#0
			BRz DAY_FIELD			;check if the strings end
			ADD R6,R6,#1			
			BRnp #-4			
DAY_FIELD		ADD R6,R6,#1			;R6 as the address of day field
			LDR R1,R6,#0
			BRn WARNING1
			ADD R1,R1,#-14
			BRp WARNING1			;check if in range 0-14
			ADD R1,R1,#14
			ADD R0,R1,#0			;copy R1 to R0
			ADD R1,R1,R1
			ADD R1,R1,R1
			ADD R1,R1,R0			;R1=R1*5,R0 is free now	
			ADD R1,R1,#4			;R1=R1+day_n
			LD R0,START
			ADD R1,R1,R0

DAY_CHECK		AND R0,R5,R4			;R0 temporery check day
			BRz #3				;if in the day,check time
			LDR R0,R1,#0
			BRnp WARNING2
			STR R2,R1,#0			;store address of strings to shedule
			ADD R4,R4,R4			;if in the day,check next day
			ADD R1,R1,#-1
			ADD R3,R3,#-1
			BRzp DAY_CHECK
			ADD R6,R6,#1
			BRnzp EACH_WORDS
	
CALL			JSR MP3
			BRz #1
			JSR PRINT_SCHEDULE

END_MAIN		HALT

WARNING1		ADD R0,R2,#0
			PUTS
			LEA R0,INVALID_SLOT
			PUTS
			BRnzp END_MAIN		
WARNING2		ADD R0,R2,#0
			PUTS
			LEA R0,CONFLICTS
			PUTS
			BRnzp END_MAIN
EVENT_LIST	.FILL x4000
INVALID_SLOT	.STRINGZ " has an invalid slot number.\n"
CONFLICTS	.STRINGZ " conflicts with an earlier event.\n"


PRINT_SCHEDULE
			ST R0,STORE_0
			ST R1,STORE_1
			ST R2,STORE_2
			ST R3,STORE_3
			ST R4,STORE_4
			ST R5,STORE_5
			ST R6,STORE_6
			ST R7,STORE_7
;3.Printing
;First line
;Register
;R3:counter of 5
;R2:date
;R1:Address of date
;R0:|
			LEA R1,NONE
			JSR PRINT_CENTERED
			LD R0,VER
			LEA R1,MON
			AND R3,R3,#0
			ADD R3,R3,#4
FIRST_LINE		OUT
			JSR PRINT_CENTERED
			ADD R1,R1,#1
			LDR R2,R1,#0
			BRnp #-3
			ADD R1,R1,#1
			ADD R3,R3,#-1
			BRzp FIRST_LINE
			LD R0,LINE_FEED
			OUT
			
;Latter lines
;Register
;R6:counter of 14
;R5:counter of 5
;R4:shedule address counter
;R3:copy of temporery R1
;R2:x3000
;R1:things to print
;R0:|/line feed			
			LD R4,START
			AND R3,R3,#0
			AND R1,R1,#0
			AND R6,R6,#0
			ADD R6,R6,#15
			
			
EACH_LINE		BRz DONE1
			AND R5,R5,#0
			ADD R5,R5,#4
			LD R0,VER
			JSR PRINT_SLOT
			ADD R3,R1,#0	       		;copy R1 to R3,as date_n	
		
EACH_DAY		OUT
			LDR R1,R4,#0			;R1 as address of first char to print
			BRnp #1
			LEA R1,NONE
			JSR PRINT_CENTERED
			ADD R4,R4,#1
			ADD R5,R5,#-1
			BRzp EACH_DAY
			LD R0,LINE_FEED
			OUT
			ADD R1,R3,#0
			ADD R1,R1,#1
			ADD R6,R6,#-1
			BRnzp EACH_LINE
					


DONE1			;load back
			LD R0,STORE_0
			LD R1,STORE_1
			LD R2,STORE_2
			LD R3,STORE_3
			LD R4,STORE_4
			LD R5,STORE_5
			LD R6,STORE_6
			LD R7,STORE_7
			RET



STORE_0		.BLKW #1
STORE_1		.BLKW #1
STORE_2		.BLKW #1
STORE_3		.BLKW #1
STORE_4		.BLKW #1
STORE_5		.BLKW #1
STORE_6		.BLKW #1
STORE_7		.BLKW #1
NONE 		.FILL x00
MON		.STRINGZ "MONDAY"
TUE		.STRINGZ "TUESDAY"
WED		.STRINGZ "WEDNESDAY"
THU		.STRINGZ "THURSDAY"
FRI		.STRINGZ "FRIDAY"
VER		.FILL x7C
LINE_FEED	.FILL x0A
START		.FILL x3800

MP3
;DESCRIPTION
;This subroutine attempts to find a compatible combination of times at which events can be
;inserted into an existing weekly schedule. Given a list of extra events, each of which can
;occur at one or more hours, this program uses a stack to perform a depth-first search
;(DFS) of possible time combinations until a compatible combination is discovered (or until
;all possible combinations are eliminated as incompatible).

;REGISTERS
;R0:(STORE)now_slot_n/(CONFLICT)now_p_slot
;R1:(STORE)possible days
;R2:(STACK PUSH)now_slot checker/(DAY_CHECK)day chekcer/
;(STORE)day chekcer/;(CONFLICT)now_slot checker
;R3:(STACK PUSH)now_slot_n counter/(DAY_CHECK)day counter/(STORE)day counter
;R4:(DAY_CHECK)sched pointer/(POP)0
;R5:always extra list pointer
;R6:always stack pointer
			
			ST R1,S_MP3_1
			ST R2,S_MP3_2
			ST R3,S_MP3_3
			ST R4,S_MP3_4
			ST R5,S_MP3_5
			ST R6,S_MP3_6
			ST R7,S_MP3_7
			;initialize
			
			LD R6,STACK
			ADD R6,R6,#-1			;R6 as top of stack
			LD R5,EXTRA_LIST		;R5 as start of extra list

			
MP3_STACK_PUSH		;stack structure
			;now_slot
			;now_slot_number(now_slot_n)
			LDR R0,R5,#0		;(R0 temporary)
			BRn MP3_DONE_S		;check if extra list ends,if end ->success
			LDR R0,R5,#2		;R0 as now_possible_slot(now_p_slot)
			AND R2,R2,#0
			ADD R2,R2,#1		;R2 as now_slot checker
			AND R3,R3,#0		;R3 as now_slot_n counter
			AND R1,R2,R0		;(R1 temporary check T/F)
			BRp #5			;Check if the now_slot found,if found,push
			ADD R3,R3,#1		;if no found,loop increase
			ADD R2,R2,R2
			ADD R1,R3,#-15		;(R1 temporary check if finish all 15 slots)
			BRzp MP3_DONE_F		;no possible slot in all 15 slots ->fail
			BRn #-7			;go check if this slot fits

			STR R2,R6,#-1		;store now_slot in stack
			STR R3,R6,#0		;store now_slot_n in stack

MP3_CHECK_DAY		AND R2,R2,#0
			ADD R2,R2,#1		;R2 as now_day checker
			AND R3,R3,#0		
			ADD R3,R3,#4		;R3 as now_day counter
			LD R4,MP3_START		;R4 as sched pointer
			LDR R1,R6,#0		;(R1 temporary as now_slot_n)
			ADD R4,R4,R1
			ADD R1,R1,R1
			ADD R1,R1,R1
			ADD R4,R4,R1
			ADD R4,R4,#4			;R4 as addr of friday in that slot
			LDR R1,R5,#0			;R1 as possible days(p_day)
			BRnzp #4
MP3_CHECK_DAY_LOOP	ADD R2,R2,R2
			ADD R4,R4,#-1
			ADD R3,R3,#-1
			BRn MP3_STORE_EXTRA_SCHED	
			AND R0,R2,R1			;(R0 temporary check if day fits)
			BRz MP3_CHECK_DAY_LOOP		;if not fit,check next day
MP3_CF_DAY_CHECK	;if fits,check if this day conflicts with sched
			LDR R0,R4,#0			;(R0 temporary check if sched empty)
			BRz MP3_CHECK_DAY_LOOP		;if not conflicts,check next day
			;if conflicts,check another time
MP3_NEW_CHECK			LDR R0,R5,#2			;R0 as now_p_slot
			LDR R2,R6,#-1			;R2 as now_slot checker
			LDR R3,R6,#0
			ADD R3,R3,#1			;try to find another possible slot
			ADD R2,R2,R2			
			BRn MP3_POP	;if no other possible slot,pop
			AND R1,R0,R2			;(R1 temporary check if this slot p)
			BRz #-5				;if this one not psb,check next one
			STR R2,R6,#-1			;store new no2_slot in stack
			STR R3,R6,#0			;store new now_slot_n in stack
			BRnzp MP3_CHECK_DAY		;check each day for this slot	

MP3_STORE_EXTRA_SCHED   ;If not conficts,store in schedule			
			AND R2,R2,#0				;R2 as day checker
			ADD R2,R2,#1
			AND R3,R3,#0				;R3 as day counter
			ADD R3,R3,#4
STORE_E_DAY_LOOP	LDR R1,R5,#0				;R1 as p_day
			AND R0,R2,R1		;(R0 temporary check if day fits)
			BRz #9			;if not fit,don't store
			LDR R0,R6,#0		;R0 as now_slot_n
			LD R4,MP3_START		;R4 as sched pointer
			ADD R4,R0,R4
			ADD R0,R0,R0
			ADD R0,R0,R0
			ADD R4,R0,R4
			ADD R4,R4,R3
			LDR R1,R5,#1		;(R1 temporary as string addr)
			STR R1,R4,#0		;store in sched
			ADD R2,R2,R2
			ADD R3,R3,#-1
			BRzp STORE_E_DAY_LOOP	;check if store all day,if not,loop
			ADD R5,R5,#3		;if so,increase R5,R6 and go store next group
			ADD R6,R6,#-2	
			BRnzp MP3_STACK_PUSH



					
MP3_POP		AND R4,R4,#0
			STR R4,R6,#0
			STR R4,R6,#-1		;pop this group stack
			ADD R5,R5,#-3		;go to previous group
			ADD R6,R6,#2
			LD R1,STACK
			ADD R1,R1,#-1
			NOT R1,R1
			ADD R1,R1,#1
			ADD R1,R1,R6
			BRp MP3_DONE_F		;reach the top of stack,so fail
			;if not reach top of stack,delete
MP3_DELETE_EXTRA_SCHED  ;If not conficts,store in schedule			
			AND R2,R2,#0				;R2 as day checker
			ADD R2,R2,#1
			AND R3,R3,#0				;R3 as day counter
			ADD R3,R3,#4
DELETE_E_DAY_LOOP	LDR R1,R5,#0				;R1 as p_day
			AND R0,R2,R1		;(R0 temporary check if day fits)
			BRz #9			;if not fit,don't delete
			LDR R0,R6,#0		;R0 as now_slot_n
			LD R4,MP3_START		;R4 as sched pointer
			ADD R4,R0,R4
			ADD R0,R0,R0
			ADD R0,R0,R0
			ADD R4,R0,R4
			ADD R4,R4,R3
			AND R1,R1,#0		;(R1 temporary as 0)
			STR R1,R4,#0		;store in sched
			ADD R2,R2,R2
			ADD R3,R3,#-1
			BRzp DELETE_E_DAY_LOOP	;check if delete all day,if not,loop
			BRnzp MP3_NEW_CHECK
			
MP3_DONE_F		LEA R0,MP3_FAIL
			PUTS
			AND R0,R0,#0
			BRnzp MP3_DONE							
MP3_DONE_S		AND R0,R0,#0
			ADD R0,R0,#1
MP3_DONE		;load back
			LD R1,S_MP3_1
			LD R2,S_MP3_2
			LD R3,S_MP3_3
			LD R4,S_MP3_4
			LD R5,S_MP3_5
			LD R6,S_MP3_6
			LD R7,S_MP3_7
			ADD R0,R0,#0
			RET
S_MP3_1		.BLKW #1
S_MP3_2		.BLKW #1
S_MP3_3		.BLKW #1
S_MP3_4		.BLKW #1
S_MP3_5		.BLKW #1
S_MP3_6		.BLKW #1
S_MP3_7		.BLKW #1
MP3_START	.FILL x3800
EXTRA_LIST	.FILL x4800
STACK		.FILL x8000
MP3_FAIL	.STRINGZ "Could not fit all events into schedule.\n"





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















