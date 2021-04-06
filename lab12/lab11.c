#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lab12.h"

//
// Do a DFS to check whether a starting point can reach only the correct
// kind of termination, HALT or RET.  These aspects are recorded in the
// flags field of each instruction.  This function returns the bitwise OR
// of flags for all instructions visited by the DFS.
//

inst_flag_t
do_search (code_stat_t* cs, int32_t first)
{
    // flags found in the search so far
    inst_flag_t    search_val = INST_FLAG_NO_FLAGS;

    int32_t        i;		// used to loop over all instructions

    instruction_t* stack;	// the stack
    instruction_t* current;	// the instruction being explored

    // FILL IN THE CODE FOR EACH BLOCK OF COMMENTS

    // First, mark all of the instructions in the code_stat_t pointed to
    // by cs as not found by removing the INST_FLAG_FOUND bit from their 
    // flags.
    for(i = 0; i < cs->len; i++){
        cs->inst[i].flags &= ~INST_FLAG_FOUND;
    }
    // Next, initialize a "stack" by putting the first instruction onto
    // the stack (a singly-linked list of instructions).  Also mark the
    // first instruction as found by setting its INST_FLAG_FOUND flag.
    stack = &cs->inst[first];
    stack->flags |= INST_FLAG_FOUND;
    // Loop until the stack is empty.
    //
    // Inside the loop...
    // - pop the top of the stack into current
    // - OR the current instruction's flags into the search result
    // - if the current instructions has a next instruction that
    //   has yet to have been found (check its flags), mark the 
    //   next instruction as found and push it onto the stack.
    // - if the current instructions has a branch target that
    //   has yet to have been found (check its flags), mark the 
    //   branch target as found and push it onto the stack.
    // - if the current instruction has a JSR target, mark the
    //   first instruction of the subroutine (the target instruction)
    //   as having been called by setting its INST_FLAG_SUB_CALLED flag.
    while(stack != NULL){
        current = stack;
        search_val |= current->flags;
        stack = stack->next;
        if( current->next_inst != NULL && current->next-inst->flags & INST_FLAG_FOUND == 0){
            current->next_inst->flag |= INST_FLAG_FOUND;
            current->next_inst->next = stack;
            stack = current->next_inst;
        }
        if( current->branch_tgt != NULL && current->branch_tgt->flags & INST_FLAG_FOUND == 0){
            current->branch_tgt->flag |= INST_FLAG_FOUND;
            current->branch_tgt->next = stack;
            stack = current->branch_tgt;
        }
        if( current->jsr_tgt != NULL && current->jsr_tgt->flags & INST_FLAG_FOUND == 0){
            current->jsr_tgt->flag |= INST_FLAG_SUB_CALLED;
        }
    }
    // Return the flags of all instructions visited in the DFS, OR'd
    // together.
    return search_val;
}

