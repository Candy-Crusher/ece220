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
;R0
;R1
;R2
;R3
;R4
;R5
;R6
			
			ST R1,S_MP3_1
			ST R2,S_MP3_2
			ST R3,S_MP3_3
			ST R4,S_MP3_4
			ST R5,S_MP3_5
			ST R6,S_MP3_6
			ST R7,S_MP3_7
			;initialize
			AND R0,R0,#0
			AND R2,R2,#0
			ADD R2,R2,#15
			ADD R2,R2,R2
			ADD R2,R2,R2
			ADD R2,R2,#15
			LEA R1,MP3_MON
MP3_INITIALIZE		STR R0,R1,#0
			ADD R1,R1,#1
			ADD R2,R2,#-1
			BRp MP3_INITIALIZE			
			
			LD R6,STACK
			ADD R6,R6,#-1
			ST R6,N_STACK
			LD R5,EXTRA_LIST
			ST R5,N_EXTRA_LIST
			BRnzp #6

			
MP3_EACH_GROUP		LD R5,N_EXTRA_LIST
			ADD R5,R5,#3
			ST R5,N_EXTRA_LIST
			LD R6,N_STACK
			ADD R6,R6,#-5
			ST R6,N_STACK
			LDR R1,R5,#0
			BRn MP3_DONE_S		;Check if extra list ends
			LDR R1,R5,#2		;Find initial now_p_slot
			ST R1,NOW_P_SLOT
			LDR R2,R5,#0		;R2 as event days(N)
			AND R4,R4,#0
			ADD R4,R4,#4		;R4 as counter of day(-1)
			AND R3,R3,#0
			ADD R3,R3,#1		;R3 as day checker(*2)
MP3_DAY_CHECK		LDR R1,R5,#2		;Find initial now_p_slot
			ST R4,MP3_DAY_COUNTER
			ST R3,MP3_DAY_CHECKER
			AND R0,R3,R2		;R0 Y/N day fits
			BRp MP3_EACH_DAY	;If fits,go check time
MP3_DAY_LOOP		LD R4,MP3_DAY_COUNTER
			LD R3,MP3_DAY_CHECKER
			ADD R3,R3,R3		;R3 goes to next day
			ADD R4,R4,#-1		;R4 goes to next day
			BRzp MP3_DAY_CHECK	;If R4>=0,loop
			BRn MP3_STACK_PUSH
MP3_EACH_DAY		LD R1,NOW_P_SLOT	;R0 as event possible times
			AND R4,R4,#0
			ADD R4,R4,#14		;R4 as counter of times(-1)
			AND R3,R3,#0
			ADD R3,R3,#1		;R3 as time checker(*2)
MP3_TIME_CHECK		LD R1,NOW_P_SLOT	;R0 as event possible times
			ST R4,MP3_TIME_COUNTER
			ST R3,MP3_TIME_CHECKER
			AND R0,R3,R1		;R0 Y/N time fits
			BRp MP3_POSSIBLE	;If fits,go check possible
MP3_TIME_LOOP		LD R4,MP3_TIME_COUNTER
			LD R3,MP3_TIME_CHECKER
			ADD R3,R3,R3		;R3 goes to next time
			ADD R4,R4,#-1		;R4 goes to next time
			BRzp MP3_TIME_CHECK	;If R4>=0,loop
			BRn MP3_DAY_CHECK			
MP3_POSSIBLE		LD R1,MP3_START
			NOT R4,R4
			ADD R4,R4,#1
			ADD R4,R4,#14
			ADD R1,R1,R4
			ADD R4,R4,R4
			ADD R4,R4,R4
			ADD R1,R1,R4
			LD R4,MP3_DAY_COUNTER
			ADD R1,R1,R4		;R1 as address of schedule
			LDR R1,R1,#0		;R1 as content of schedule
			BRz #5
			LD R4,NOW_P_SLOT
			NOT R3,R3
			ADD R3,R3,#1
			ADD R4,R3,R4
			ST R4,NOW_P_SLOT
			BRnzp MP3_TIME_LOOP 
		
MP3_STACK_PUSH		ST R5,N_EXTRA_LIST
			ST R6,N_STACK
			;stack structure
			;day
			;strings address
			;now_p_slot
			;now_slot
			;now_slot_n
			LD R1,NOW_P_SLOT
			BRz MP3_DONE_F		;check if this event conflicts with old sched
			STR R1,R6,#-2		;store now_p_slot in stack
			AND R2,R2,#0
			ADD R2,R2,#1		;R2 as now_slot checker
			AND R3,R3,#0		;R3 as now_slot counter
			AND R0,R2,R1
			BRp #4			;Check if the now_slot found
			ADD R3,R3,#1
			ADD R2,R2,R2
			ADD R4,R3,#-15
			BRn #-6 		;Check if counter of 15 ends
			ST R2,NOW_SLOT		;R2 AS NOW_SLOT
			STR R2,R6,#-1		;store now_slot in stack
			ST R3,NOW_SLOT_N	;R3 as now_slot_number
			STR R3,R6,#0		;store now_slot_n in stack
			LDR R1,R5,#0
			STR R1,R6,#-4		;store event days in stack
			LDR R1,R5,#1
			STR R1,R6,#-3		;store event string address in stack
			


MP3_CFE			AND R2,R2,#0
			ADD R2,R2,#1		;R2 as now_day checker
			AND R3,R3,#0		
			ADD R3,R3,#4		;R3 as now_day counter
			LEA R4,MP3_FRI		;R4 as day pointer
			BRnzp #4
MP3_CF_E_DAY_LOOP	ADD R2,R2,R2
			ADD R4,R4,#-15
			ADD R3,R3,#-1
			BRn MP3_STORE_EXTRA_SCHED
			LDR R1,R5,#0
			AND R0,R2,R1
			BRz MP3_CF_E_DAY_LOOP
MP3_CF_E_CHECK		LD R1,NOW_SLOT_N
			ADD R1,R4,R1
			LDR R0,R1,#0
			BRz MP3_CF_E_DAY_LOOP
			LD R6,N_STACK
			LDR R4,R6,#-1
			NOT R4,R4
			ADD R4,R4,#1
			LD R1,NOW_P_SLOT
			ADD R1,R1,R4
			BRz MP3_CF_EXTRA 
			ST R1,NOW_P_SLOT
			BRnzp MP3_STACK_PUSH

MP3_STORE_EXTRA_SCHED   ;If not conficts with extra schedule,store in extra schedule
			LD R6,N_STACK			
			LDR R0,R6,#-4
			LEA R2,MP3_FRI
			AND R1,R1,#0
			ADD R1,R1,#1
			AND R4,R4,#0
			ADD R4,R4,#4
STORE_E_DAY_LOOP	AND R3,R1,R0
			BRz #5
			LDR R5,R6,#0
			ADD R6,R5,R2
			LD R3,N_STACK
			LDR R3,R3,#-3
			STR R3,R6,#0
			LD R6,N_STACK
			LDR R0,R6,#-4
			ADD R1,R1,R1
			ADD R2,R2,#-15
			ADD R4,R4,#-1
			BRzp STORE_E_DAY_LOOP			
			BRnzp MP3_EACH_GROUP
MP3_CF_EXTRA    	AND R0,R0,#0
			STR R0,R6,#-4
			STR R0,R6,#-3
			STR R0,R6,#-2
			STR R0,R6,#-1
			STR R0,R6,#0
			LD R5,N_EXTRA_LIST
			LD R6,N_STACK
			ADD R6,R6,#5
			LD R0,STACK
			ADD R0,R0,#-1
			NOT R0,R0
			ADD R0,R0,#1
			ADD R0,R0,R6
			BRp MP3_DONE_F
			ADD R5,R5,#-3
			ST R6,N_STACK
			ST R5,N_EXTRA_LIST
			LDR R1,R6,#-2
			LDR R0,R6,#-1
			LDR R5,R6,#0		;R5 changes
			NOT R0,R0
			ADD R0,R0,#1
			ADD R1,R0,R1
			ADD R5,R5,#1
			ADD R0,R0,R0
			BRn MP3_NO_ALTER
			AND R6,R1,R0		;R6 changes
			BRz #-5
			LD R6,N_STACK
			STR R0,R6,#-1
			STR R5,R6,#0
			LDR R0,R6,#-4
			LEA R2,FRI
			AND R1,R1,#0
			ADD R1,R1,#1
			AND R4,R4,#0
			ADD R4,R4,#4
S_STORE_E_DAY_CHECK	AND R3,R1,R0
			BRz #4
			ADD R6,R5,R2
			LD R3,N_STACK
			LDR R3,R3,#-3
			STR R3,R6,#0
			LD R6,N_STACK
			LDR R0,R6,#-4
			ADD R1,R1,R1
			ADD R2,R2,#-15
			ADD R4,R4,#-1
			BRzp S_STORE_E_DAY_CHECK			
			BRnzp MP3_STACK_PUSH
MP3_NO_ALTER		LD R6,N_STACK
			LDR R0,R6,#-2
			ST R0,NOW_P_SLOT
			LDR R0,R6,#-4
			LEA R2,FRI
			AND R1,R1,#0
			ADD R1,R1,#1
			AND R4,R4,#0
			ADD R4,R4,#4
F_STORE_E_DAY_CHECK	AND R3,R1,R0
			BRz #4
			ADD R6,R5,R2
			AND R3,R3,#0
			STR R3,R6,#0
			LD R6,N_STACK
			LDR R0,R6,#-4
			ADD R1,R1,R1
			ADD R2,R2,#-15
			ADD R4,R4,#-1
			BRzp F_STORE_E_DAY_CHECK
			LDR R0,R6,#-2
			ST R0,NOW_P_SLOT			
			BRnzp MP3_CF_EXTRA


S_MP3_1		.BLKW #1
S_MP3_2		.BLKW #1
S_MP3_3		.BLKW #1
S_MP3_4		.BLKW #1
S_MP3_5		.BLKW #1
S_MP3_6		.BLKW #1
S_MP3_7		.BLKW #1
N_EXTRA_LIST	.BLKW #1
N_STACK		.BLKW #1
MP3_START	.FILL x3800
EXTRA_LIST	.FILL x4800
STACK		.FILL x8000
MP3_NEW_SCHEDULE .BLKW #1
MP3_DAY_COUNTER	.BLKW #1
MP3_DAY_CHECKER	.BLKW #1
MP3_TIME_COUNTER	.BLKW #1
MP3_TIME_CHECKER	.BLKW #1
NOW_SLOT_N	.BLKW #1
NOW_SLOT	.BLKW #1
NOW_P_SLOT	.BLKW #1
MP3_EXTRA_LIST_POINTER .BLKW #1
MP3_MON		.BLKW #15						
MP3_DONE_F		LEA R0,MP3_FAIL
			PUTS
			AND R0,R0,#0
			BRnzp MP3_DONE							
MP3_DONE_S		LEA R1,MP3_MON
			AND R5,R5,#0
			ADD R5,R5,#-1
			ADD R5,R5,#1
			ADD R4,R5,#-4
			BRp #10 
			LD R0,MP3_START
			ADD R0,R5,R0
			AND R6,R6,#0
			ADD R6,R6,#15
			LDR R2,R1,#0
			STR R2,R0,#0
			ADD R1,R1,#1
			ADD R0,R0,#5
			ADD R6,R6,#-1
			BRzp #-10
		
			AND R0,R0,#0
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

MP3_TUE		.BLKW #15
MP3_WED		.BLKW #15
MP3_THU		.BLKW #15
MP3_FRI		.BLKW #15
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














