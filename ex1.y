
%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>    
    #include <string.h>
    #include "types.h"
    #include "variables.h"
    #include "print_functions.h"

    int yylex();

    //Prints the error message s to the standard error stream.

    void yyerror(const char *s);
%}
%union{
    int entier;
    char* id;
    type_synth t_synth;
}
%type <t_synth> EXPR
%token <entier> NUM
%token <id> ID
%token TRUE
%token FALSE
%token RETURN
%token EQUAL
%token NOT
%token AND
%token OR
%token SUP
%token INF
%token SUPE
%token INFE
%token DIFF
%token BALGO
%token EALGO
%token CALL
%token SET
%token IF
%token ELSE
%token DOWHILE 
%token DOFORI
%token OD
%token FI


%left OR
%left AND
%left EQUAL DIFF SUPE INFE SUP INF
%left '+' '-'
%left '*' '/'
%left NOT   

%start PROG

%%
PROG:
    LALGO {add_tcell(ACT_DEBUT, NULL, 0);} CALL {add_tcell(ACT_RETVALUE, NULL, 0);}
     '{' ID '}' '{' LVAL'}'{
        int i = search_tab_ind($6);
        if (i == -1){
            fprintf(stderr, "Appel à une fonction inexistante\n");
            exit(EXIT_FAILURE);
        }
        if(arg_compteur != tab_lid[i]->arg_size){
            fprintf(stderr, "Erreur de nombre d'arguments\n");
            exit(EXIT_FAILURE);
        }
        arg_compteur = 0;
        while(tab_lid[i]->local_size > 0){
            add_tcell(ACT_RETVALUE, NULL, 0);
            tab_lid[i]->local_size--;
        }
        
        add_tcell(ACT_CALL, $6, 0);
        add_tcell(ACT_AFFICHE, NULL, 0);  
    }

LVAL:
    LVAL ',' VAL 
    | VAL
    |
;

VAL: EXPR {
    ++arg_compteur;
    
};

LPARAM:
    LPARAM ',' PARAM 
    | PARAM 
    | 
;

PARAM: ID {
    if(!is_present($1, tab_lid[ind_tab])){
        add_lid($1, UNK_T, tab_lid[ind_tab]);
        tab_lid[ind_tab]->arg_size++;
    }else{
        fprintf(stderr, "Identification error\n");
        exit(EXIT_FAILURE);
    }
};

LALGO:
    LALGO ALGO 
    | ALGO 
;

ALGO:
    BALGO '{' ID '}' {
        if (size_of_tab_lid(tab_lid) < tab_size){
            add_tab($3);
        }else{
            int new_size = tab_size * 2;
            lid **new_tab_lid = realloc(tab_lid, new_size * sizeof(lid *));
            if (new_tab_lid == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
            tab_lid = new_tab_lid;
            tab_size = new_size;
            add_tab($3);
        }
    } '{' LPARAM'}' {add_tcell(ACT_ALGO, $3, 0);}    
        BLOC 
    EALGO {ind_tab++;}
;

BLOC:  BLOC  INSTR 
    |   INSTR ;

INSTR: AFFECT 
    | IF '{' EXPR '}' {
        if($3 == NUM_T){
            fprintf(stderr, "Type error in IF Condition\n");
            exit(EXIT_FAILURE);
        }
         add_tcell(ACT_IFELSE, NULL, 0);} BLOC {add_tcell(ACT_JMP, NULL, 0);} ELSE2 FI {add_tcell(ACT_FI, NULL, 0);}
         

    | DOWHILE {add_tcell(ACT_DOWHILE,NULL,0);} '{' EXPR '}' {add_tcell(ACT_DO,NULL,0);} BLOC {add_tcell(ACT_JMPWHILE,NULL,0);} OD {add_tcell(ACT_OD, NULL, 0);}

    | DOFORI '{' ID '}' '{' EXPR '}' 
    {if (!is_present($3,tab_lid[ind_tab])){
        add_tcell(ACT_SETID, $3, ind_tab);
        add_lid($3, $6, tab_lid[ind_tab]);
        tab_lid[ind_tab]->local_size++;
    }else{
        add_tcell(ACT_SETID, $3, ind_tab);
    }
    add_tcell(ACT_DOFORI, NULL, 0);
    }
     '{' EXPR '}' {add_tcell(ACT_DOFOR, $3, ind_tab);}  BLOC {add_tcell(ACT_INCR, $3, ind_tab);add_tcell(ACT_JMPFOR,NULL,0);} OD {add_tcell(ACT_OD,NULL,0);}

    | RETURN  '{' EXPR '}' {   
        add_tcell(ACT_RETURN, NULL, ind_tab);
    }
;
    
ELSE2: ELSE {add_tcell(ACT_ELSE, NULL, 0);} BLOC 
| {add_tcell(ACT_ELSE, NULL, 0);}
;

AFFECT: SET '{' ID '}' '{' EXPR '}' {
    if (!is_present($3,tab_lid[ind_tab])){
        add_tcell(ACT_SETID, $3, ind_tab);
        add_lid($3, $6, tab_lid[ind_tab]);
        tab_lid[ind_tab]->local_size++;
    }else{
        add_tcell(ACT_SETID, $3, ind_tab);
    }
};

EXPR:
 EXPR '+' EXPR {
                    add_tcell(ACT_ADD, NULL, 0);
                    $$ = NUM_T;
                    
                }
|EXPR '-' EXPR {
                    add_tcell(ACT_SUB, NULL, 0);
                    $$ = NUM_T;
                    
                }
|EXPR '*' EXPR {
                    add_tcell(ACT_MUL, NULL, 0);
                    $$ = NUM_T;
                    
                }
|EXPR '/' EXPR {
                    add_tcell(ACT_DIV, NULL, 0);
                    $$ = NUM_T;
                    
                }
| EXPR EQUAL EXPR {
            
                add_tcell(ACT_EQUAL, NULL, 0);
                $$ = BOOL_T;
            
                }
    | EXPR DIFF EXPR {
                        add_tcell(ACT_DIFF, NULL, 0);
                        $$ = BOOL_T;
                        
                }
    | EXPR SUP EXPR {
                        add_tcell(ACT_SUP, NULL, 0);
                        $$ = BOOL_T;
                        
                }
    | EXPR INF EXPR {
                        add_tcell(ACT_INF, NULL, 0);
                        $$ = BOOL_T;
                    
                }
    | EXPR SUPE EXPR {
                        add_tcell(ACT_SUPE, NULL, 0);
                        $$ = BOOL_T;
                        
                }
    | EXPR INFE EXPR {
                        add_tcell(ACT_INFE, NULL, 0);
                        $$ = BOOL_T;
                    }
                
    | EXPR AND EXPR {
                        add_tcell(ACT_AND, NULL, 0);
                        $$ = BOOL_T;
                        
                }
    | EXPR OR EXPR {
                        add_tcell(ACT_OR, NULL, 0);
                        $$ = BOOL_T;
                        
                }
    | NOT EXPR {
                    add_tcell(ACT_NOT, NULL, 0);
                        $$ = BOOL_T;
    }
    | '(' EXPR ')' {$$ = $2;}
    | NUM {
        add_tcell(ACT_NUM, NULL, $1);
         $$ = NUM_T;
         }
    | ID {
        if (!is_present($1,tab_lid[ind_tab])){
            fprintf(stderr, "Variable error %s not declared\n",$1);
            exit(EXIT_FAILURE);
        }
        add_tcell(ACT_ID, $1, ind_tab);
        $$ = type($1,tab_lid[ind_tab]);}
    | CALL {add_tcell(ACT_RETVALUE, NULL, 0);} '{' ID '}' '{' LVAL'}'{
            int i = search_tab_ind($4);
            if(i == -1){
                fprintf(stderr, "Call a bad function\n");
                exit(EXIT_FAILURE);
            }
            if(arg_compteur != tab_lid[i]->arg_size){
                fprintf(stderr, "Arguments number error\n");
                exit(EXIT_FAILURE);
            }
            while(tab_lid[i]->local_size > 0){
                add_tcell(ACT_RETVALUE, NULL, 0);
                tab_lid[i]->local_size--;
            }
            arg_compteur = 0;
            add_tcell(ACT_CALLREC, $4, 0);
        }
    
    | TRUE {
        add_tcell(ACT_TRUE, NULL, 0);
                   $$ = BOOL_T;}
    | FALSE {
        add_tcell(ACT_FALSE, NULL, 0);
                    $$ = BOOL_T;}
;
%%

void yyerror(const char *s){
    fprintf(stderr,"%s\n",s);
}


//The entry point of the program. Initializes data structures, calls the parser, and prints the generated assembly code.

int main() {
  liste_tid = empty_liste();
  tab_lid = empty_tab();
  debut();
  yyparse();
  print_all(liste_tid->head);
  fin();
  llid_dispose(tab_lid);
  tid_dispose(liste_tid);
  return EXIT_SUCCESS;
}






