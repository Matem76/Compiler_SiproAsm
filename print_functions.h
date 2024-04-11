#ifndef PRINT_FUNCTIONS_H
#define PRINT_FUNCTIONS_H

#include "types.h"

//Generates assembly code for printing a value.

void print_affiche();

//Generates assembly code for the start of the program 

void debut();

//Generates assembly code for the end of the program

void fin();

//Generates assembly code for calling a function identified by id, there is one for recursive calls and one for regular calls.

void print_call(char* id);

void print_callrec(char* id);

//Generates assembly code for the beginning of a program.

void print_debut();

//Generates assembly code for handling a return value.

void print_retvalue();

//Generate assembly code for arithmetic operations: addition, subtraction, multiplication, and division, respectively.

void print_add();

void print_sub();

void print_mul();

void print_div();

//Generate assembly code for comparison operations: equal, not equal, greater than, less than, greater than or equal to, and less than or equal to, respectively.

void print_equal();

void print_diff();

void print_sup();

void print_inf();

void print_supe();

void print_infe();

//Generate assembly code for logical operations: AND, OR, and NOT, respectively.

void print_and();

void print_or();

void print_not();

//Generate assembly code for pushing a number, true, or false onto the stack.

void print_num(int i);

void print_true();

void print_false();

//Generates assembly code for handling an identifier id.

void print_id(char* id, int d);

//Generates assembly code for setting the value of an identifier

void print_setid(char* id, int d);

////Generates assembly code for the start of an algorithm/function identified by id.

void print_algo(char* id);

// //Generates assembly code for handling a return statement.

void print_return(int d);

//Generate assembly code for handling if, if-else, else, and end-if constructs.

void print_ifelse();

void print_else();

void print_fi();

//Generate assembly code for handling loops and jumps: unconditional jump, do-while loop start, do-while loop condition check, jump back to loop start, and loop end.

void print_jmp();

void print_do();

void print_dowhile();


void print_jmpwhile();

void print_od();

//This function generates the assembly code marking the start of a for loop.
//It prints a label that will be used as the entry point of the loop. The label includes a unique identifier ind_dofori to ensure that each loop has a distinct label.

void print_dofori();

//This function generates the assembly code for an unconditional jump back to the start of the for loop. It uses the ind_dofori identifier to reference the correct loop start
// label, effectively creating the loop's iteration mechanism.

void print_jmpfor();

//This function generates the assembly code for incrementing a variable by one. It first calculates the stack offset for the variable to be incremented (identified by id) and then performs the increment operation.
// The arg_ind variable is used to manage the stack offset, and it's reset to its initial value at the end to ensure correct offsets for subsequent variables.

void print_incr(char * id, int d);

//This function generates the assembly code for the loop condition check in a for loop. It pops the top value from the stack (which should be the result of the condition expression), compares it with the current value of the loop variable (identified by id), and jumps out of the loop if the condition is false.
// The ind_od identifier is used to reference the correct label for exiting the loop.

void print_dofor(char * id , int d);

void print_returnrec();

void print_all(tcell *t);

#endif