#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "types.h"
#include "variables.h"
#include "print_functions.h"

//Initializes the program by setting up initial jump addresses and printing messages for program start, division by zero error, and boolean values.

void debut(){ 
    printf("\tconst ax,debut\n");
    printf("\tjmp ax\n");
    printf(":result\n");
    printf("@string \"RESULT : \"\n");
    printf(":endMsg\n");
    printf("@string \"END OF PROGRAM\"\n");
    printf(":nl\n");
    printf("@string \"\\n\"\n");
    printf(":msgErrorDiv\n");
    printf("@string \"Division by zero\"\n");
    printf(":false\n");
    printf("@string \"false\"\n");
    printf(":true\n");
    printf("@string \"true\"\n");
    printf(":booleen\n");
    printf("@string \"bool:\"\n");
    printf(":entier\n");
    printf("@string \"int:\"\n");
    printf(":errDiv0\n");
    printf("\tconst ax,msgErrorDiv\n");
    printf("\tcallprintfs ax\n");
    printf("\tconst ax,nl\n");
    printf("\tcallprintfs ax\n");
    printf("\tend\n");
    
}

//Prints the end program message and finalizes the program execution.

void fin(){ 
    printf("\tconst ax,endMsg\n");
    printf("\tcallprintfs ax\n");
    printf("\tconst ax,nl\n");
    printf("\tcallprintfs ax\n");
    printf("\tend\n");
    printf(":pile\n");
    printf("@int 0\n");
}

//Generates assembly code for printing a value.

void print_affiche(){ 
    printf(";AFFICHE\n");
    printf("\tconst ax,result\n");
    printf("\tcallprintfs ax\n");
    printf("\tcp ax,bp\n");
    printf("\tcallprintfd ax\n");
    printf("\tconst ax,nl\n");
    printf("\tcallprintfs ax\n");
}

//Generates assembly code for calling a function identified by id, there is one for recursive calls and one for regular calls.

void print_call(char* id){ 
    printf(";CALL\n");
    printf("\tconst ax,algo:%s\n", id);
    printf("\tcall ax\n");
    int i = search_tab_ind(id);
    if(i == -1){
        fprintf(stderr, "Indice error\n");
        exit(EXIT_FAILURE);
    }
    while (tab_lid[i]->size > 0) {
        printf("\tpop ax\n");
        tab_lid[i]->size--;
    }
}

void print_callrec(char* id){
    printf(";CALLREC\n");
    printf("\tconst ax,algo:%s\n", id);
    printf("\tcall ax\n");
    int i = search_tab_ind(id);
    if(i == -1){
        fprintf(stderr,"Indice error\n");
        exit(EXIT_FAILURE);
    }
    int k = tab_lid[i]->size;
    while (k > 0) {
        printf("\tpop ax\n");
        k--;
    }
}

//Generates assembly code for the beginning of a program.

void print_debut(){ 
    printf(";DEBUT\n");
    printf(":debut\n");
    printf("\tconst bp,pile\n");
    printf("\tconst sp,pile\n");
    printf("\tconst ax,2\n");
    printf("\tsub sp,ax\n");
}

//Generates assembly code for handling a return value.

void print_retvalue(){ 
    printf(";RETVALUE\n");
    printf("\tconst ax,0\n");
    printf("\tpush ax\n");
}


//Generate assembly code for arithmetic operations: addition, subtraction, multiplication, and division, respectively.

void print_add(){
    printf(";ADD\n");
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tadd ax,bx\n");
    printf("\tpush ax\n");
}

void print_sub(){
    printf(";SUB\n");
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tsub bx,ax\n");
    printf("\tpush bx\n");
}

void print_mul(){
    printf(";MUL\n");
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tmul ax,bx\n");
    printf("\tpush ax\n");
}

void print_div(){
    printf(";DIV\n");
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tconst dx,errDiv0\n");
    printf("\tdiv bx,ax\n");
    printf("\tjmpe dx\n");
    printf("\tpush bx\n");
}

//Generate assembly code for comparison operations: equal, not equal, greater than, less than, greater than or equal to, and less than or equal to, respectively.

void print_equal(){
    printf(";EQUAL\n");
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tconst dx,istrue%d\n", incr);
    printf("\tconst cx,end%d\n", incr);
    printf("\tcmp ax,bx\n");
    printf("\tjmpc dx\n");
    printf("\tconst dx,0\n");
    printf("\tpush dx\n");
    printf("\tjmp cx\n");
    printf(":istrue%d\n", incr);
    printf("\tconst dx,1\n");
    printf("\tpush dx\n");
    printf(":end%d\n", incr);
    incr++;
}

void print_diff(){
    printf(";DIFF\n");
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tconst dx,isfalse%d\n", incr);
    printf("\tconst cx,end%d\n", incr);
    printf("\tcmp ax,bx\n");
    printf("\tjmpc dx\n");
    printf("\tconst dx,1\n");
    printf("\tpush dx\n");
    printf("\tjmp cx\n");
    printf(":isfalse%d\n", incr);
    printf("\tconst dx,0\n");
    printf("\tpush dx\n");
    printf(":end%d\n", incr);
    incr++;
}

void print_sup(){
    printf(";SUP\n");
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tconst dx,istrue%d\n", incr);
    printf("\tconst cx,end%d\n", incr);
    printf("\tsless ax,bx\n");
    printf("\tjmpc dx\n");
    printf("\tconst dx,0\n");
    printf("\tpush dx\n");
    printf("\tjmp cx\n");
    printf(":istrue%d\n", incr);
    printf("\tconst dx,1\n");
    printf("\tpush dx\n");
    printf(":end%d\n", incr);
    incr++;
}

void print_inf(){
    printf(";INF\n");
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tconst dx,istrue%d\n", incr);
    printf("\tconst cx,end%d\n", incr);
    printf("\tsless bx,ax\n");
    printf("\tjmpc dx\n");
    printf("\tconst dx,0\n");
    printf("\tpush dx\n");
    printf("\tjmp cx\n");
    printf(":istrue%d\n", incr);
    printf("\tconst dx,1\n");
    printf("\tpush dx\n");
    printf(":end%d\n", incr);
    incr++;
}

void print_supe(){
    printf(";SUPE\n");
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tconst dx,istrue%d\n", incr);
    printf("\tconst cx,end%d\n", incr);
    printf("\tcmp ax,bx\n");
    printf("\tjmpc dx\n");
    printf("\tsless ax,bx\n");
    printf("\tjmpc dx\n");
    printf("\tconst dx,0\n");
    printf("\tpush dx\n");
    printf("\tjmp cx\n");
    printf(":istrue%d\n", incr);
    printf("\tconst dx,1\n");
    printf("\tpush dx\n");
    printf(":end%d\n", incr);
    incr++;
}

void print_infe(){
    printf(";INFE\n");
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tconst dx,istrue%d\n", incr);
    printf("\tconst cx,end%d\n", incr);
    printf("\tcmp ax,bx\n");
    printf("\tjmpc dx\n");
    printf("\tsless bx,ax\n");
    printf("\tjmpc dx\n");
    printf("\tconst dx,0\n");
    printf("\tpush dx\n");
    printf("\tjmp cx\n");
    printf(":istrue%d\n", incr);
    printf("\tconst dx,1\n");
    printf("\tpush dx\n");
    printf(":end%d\n", incr);
    incr++;
}

//Generate assembly code for logical operations: AND, OR, and NOT, respectively.

void print_and(){
    printf(";AND\n");
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tand ax,bx\n");
    printf("\tpush ax\n");
}

void print_or(){
    printf(";OR\n");
    printf("\tpop ax\n");
    printf("\tpop bx\n");
    printf("\tor ax,bx\n");
    printf("\tpush ax\n");
}

void print_not(){
    printf(";NOT\n");
    printf("\tpop ax\n");
    printf("\tconst bx,0\n");
    printf("\tconst dx,istrue%d\n", incr);
    printf("\tconst cx,end%d\n", incr);
    printf("\tcmp ax,bx\n");
    printf("\tjmpc dx\n");
    printf("\tconst dx,0\n");
    printf("\tpush dx\n");
    printf("\tjmp cx\n");
    printf(":istrue%d\n", incr);
    printf("\tconst dx,1\n");
    printf("\tpush dx\n");
    printf(":end%d\n", incr);
    incr++;
}

//Generate assembly code for pushing a number, true, or false onto the stack.

void print_num(int i){
    printf(";NUM\n");
    printf("\tconst ax,%d\n"
            "\tpush ax\n", i);
}

void print_true(){
    printf(";TRUE\n");
    printf("\tconst ax,1\n"
            "\tpush ax\n");
}

void print_false(){
    printf(";FALSE\n");
    printf("\tconst ax,0\n"
            "\tpush ax\n");
}

//Generates assembly code for handling an identifier id.

void print_id(char* id, int d){ 
    int ind = indice_id(id, tab_lid[d]);
    if(ind == -1){
        fprintf(stderr, "Identification error%d\n", d);
        exit(EXIT_FAILURE);
    }
    while(ind >= 0){
        arg_ind += 2;
        ind--;
    }
    printf(";ID\n");
    printf("\tconst ax,%d\n"
            "\tcp bx,bp\n"
            "\tsub bx,ax\n"
            "\tloadw ax,bx\n"
            "\tpush ax\n",arg_ind);
    arg_ind = 2;
}

//Generates assembly code for setting the value of an identifier

void print_setid(char* id, int d){ 
    int ind = indice_id(id, tab_lid[d]);
    if(ind == -1){
        fprintf(stderr, "Identification error\n");
        exit(EXIT_FAILURE);
    }
    while(ind >= 0){
        arg_ind += 2;
        ind--;
    }
    printf(";SETID\n");
    printf("\tconst ax,%d\n", arg_ind);
    printf("\tcp bx,bp\n");
    printf("\tsub bx,ax\n");
    printf("\tpop ax\n");
    printf("\tstorew ax,bx\n");
    arg_ind = 2;
}

////Generates assembly code for the start of an algorithm/function identified by id.

void print_algo(char* id){ 
    printf(";ALGO\n");
    printf(":algo:%s\n", id);
    printf("\tpush bp\n");
    printf("\tcp bp,sp\n");
}

// //Generates assembly code for handling a return statement.

void print_return(int d){
    int ind = tab_lid[d]->size * 2 + 2;
    arg_ind += ind;
    printf(";RETURN\n");
    printf("\tconst ax,%d\n", arg_ind);
    printf("\tcp bx,bp\n");
    printf("\tsub bx,ax\n");
    printf("\tpop ax\n");
    printf("\tstorew ax,bx\n");
    printf("\tpop bp\n");
    printf("\tret\n");
    arg_ind = 2;
}

//Generate assembly code for handling if, if-else, else, and end-if constructs.

void print_if(){
    printf(";IF\n");
    printf("\tpop ax\n");
    printf("\tconst bx,0\n");
    printf("\tconst cx,finif%d\n",ind_if);
    printf("\tcmp ax,bx\n");
    printf("\tjmpc cx\n");
}

void print_ifelse(){
    printf(";IFELSE\n");
    printf("\tpop ax\n");
    printf("\tconst bx,0\n");
    printf("\tconst cx,else%d\n",ind_else);
    printf("\tcmp ax,bx\n");
    printf("\tjmpc cx\n");
}

void print_else(){
    printf(";ELSE\n");
    printf(":else%d\n",ind_else);
    ind_else++;
}

void print_fi(){
    printf(";FI\n");
    printf(":finif%d\n",ind_if);
    ind_if++;
}

//Generate assembly code for handling loops and jumps: unconditional jump, do-while loop start, do-while loop condition check, jump back to loop start, and loop end.

void print_jmp(){
    printf(";JMP\n");
    printf("\tconst cx,finif%d\n",ind_if);
    printf("\tjmp cx\n");
}

void print_do(){
    printf(";DO\n");
    printf("\tpop ax\n");
    printf("\tconst bx,0\n");
    printf("\tconst cx,od%d\n",ind_od);
    printf("\tcmp ax,bx\n");
    printf("\tjmpc cx\n");

}

void print_dowhile(){
    printf(";DOWHILE\n");
    printf(":dowhile%d\n",ind_dowhile);
    

}

void print_jmpwhile(){
    printf(";JMPWHILE\n");
    printf("\tconst cx,dowhile%d\n",ind_dowhile);
    printf("\tjmp cx\n");
}

void print_od(){
    printf(";OD\n");
    printf(":od%d\n",ind_od);
    ind_od++;
    ind_dowhile++;
    ind_dofori++;

}

//This function generates the assembly code marking the start of a for loop.
//It prints a label that will be used as the entry point of the loop. The label includes a unique identifier ind_dofori to ensure that each loop has a distinct label.

void print_dofori(){
    printf(";DOFORI\n");
    printf(":dofori%d\n",ind_dofori);
}

//This function generates the assembly code for an unconditional jump back to the start of the for loop. It uses the ind_dofori identifier to reference the correct loop start
// label, effectively creating the loop's iteration mechanism.

void print_jmpfor(){
    printf(";JMPFOR\n");
    printf("\tconst cx,dofori%d\n",ind_dofori);
    printf("\tjmp cx\n");
}

//This function generates the assembly code for incrementing a variable by one. It first calculates the stack offset for the variable to be incremented (identified by id) and then performs the increment operation.
// The arg_ind variable is used to manage the stack offset, and it's reset to its initial value at the end to ensure correct offsets for subsequent variables.

void print_incr(char * id, int d){
    printf(";INCR\n");
     int ind = indice_id(id, tab_lid[d]);
     if(ind == -1){
        fprintf(stderr, "Identification error\n");
        exit(EXIT_FAILURE);
    }
    while(ind >= 0){
        arg_ind += 2;
        ind--;
    }
    printf("\tconst cx,%d\n"
            "\tcp bx,bp\n"
            "\tsub bx,cx\n"
            "\tloadw cx,bx\n",arg_ind);
    printf("\tconst dx,1\n");
    printf("\tadd cx,dx\n");
    printf("\tconst ax,%d\n", arg_ind);
    printf("\tcp bx,bp\n");
    printf("\tsub bx,ax\n");
    printf("\tstorew cx,bx\n");
    arg_ind = 2;
}

//This function generates the assembly code for the loop condition check in a for loop. It pops the top value from the stack (which should be the result of the condition expression), compares it with the current value of the loop variable (identified by id), and jumps out of the loop if the condition is false.
// The ind_od identifier is used to reference the correct label for exiting the loop.

void print_dofor(char * id , int d){
    printf(";DOFOR\n");
    printf("\tpop ax\n");
    printf("\tconst dx,od%d\n",ind_od);
    int ind = indice_id(id, tab_lid[d]);
    if(ind == -1){
        fprintf(stderr, "Identification error\n");
        exit(EXIT_FAILURE);
    }
    while(ind >= 0){
        arg_ind += 2;
        ind--;
    }
    printf("\tconst cx,%d\n"
            "\tcp bx,bp\n"
            "\tsub bx,cx\n"
            "\tloadw cx,bx\n",arg_ind);
    printf("\tsless ax,cx\n");
    printf("\tjmpc dx\n");
    arg_ind = 2;
}

//Iterates through the instruction table and prints assembly code for each instruction.

void print_all(tcell *t) {
    while (t != NULL) {
        switch (t->action) {
            case ACT_DEBUT:
                print_debut();
                break;
            case ACT_RETVALUE:
                print_retvalue();
                break;
            case ACT_CALL:
                print_call(t->chaine);
                break;
            case ACT_AFFICHE:
                print_affiche();
                break;
            case ACT_ALGO:
                print_algo(t->chaine);
                break;
            case ACT_RETURN:
                print_return(t->entier);
                break;
            case ACT_EQUAL:
                print_equal();
                break;
            case ACT_DIFF:
                print_diff();
                break;
            case ACT_SUP:
                print_sup();
                break;
            case ACT_INF:
                print_inf();
                break;
            case ACT_SUPE:
                print_supe();
                break;
            case ACT_INFE:
                print_infe();
                break;
            case ACT_ADD:
                print_add();
                break;
            case ACT_SUB:
                print_sub();
                break;
            case ACT_MUL:
                print_mul();
                break;
            case ACT_DIV:
                print_div();
                break;
            case ACT_AND:
                print_and();
                break;
            case ACT_OR:
                print_or();
                break;
            case ACT_NOT:
                print_not();
                break;
            case ACT_NUM:
                print_num(t->entier);
                break;
            case ACT_TRUE:
                print_true();
                break;
            case ACT_FALSE:
                print_false();
                break;
            case ACT_ID:
                print_id(t->chaine, t->entier);
                break;
            case ACT_SETID:
                print_setid(t->chaine, t->entier);
                break;
            case ACT_ELSE:
                print_else();
                break;
            case ACT_IFELSE:
                print_ifelse();
                break;
            case ACT_FI:
                print_fi();
                break;
            case ACT_JMP:
                print_jmp();
                break;
            case ACT_DOWHILE:
                print_dowhile();
                break;
            case ACT_DO:
                print_do();
                break;
            case ACT_OD:
                print_od();
                break;
            case ACT_JMPWHILE:
                print_jmpwhile();
                break;
            case ACT_DOFORI:
                print_dofori();
                break;
            case ACT_JMPFOR:
                print_jmpfor();
                break;
            case ACT_DOFOR:
                print_dofor(t->chaine, t->entier);
                break;
            case ACT_INCR:
                print_incr(t->chaine, t->entier);
                break;
            case ACT_CALLREC:
                print_callrec(t->chaine);
                break;
            default:
                break;
        }
        t = t->next;
    }
}


