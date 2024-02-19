%{
    #include <stdlib.h>
    #include <stdio.h>
    #include "types.h"
    #include <stdbool.h>    
    #include <string.h>
    int yylex();
    void yyerror(const char *s);
    void add(char* id, type_synth t);
    bool estpresent(char* id);
    type_synth type(char* id);
    static int incr = 0;
    lid *liste_id = NULL; // Alloue de la mémoire pour une structure lid


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
%token EQUAL
%token NOT
%token AND
%token OR
%token SUP
%token INF
%token SUPE
%token INFE
%token DIFF

%token OUTPUT

%left OR
%left AND
%left EQUAL DIFF SUPE INFE SUP INF
%left '+' '-' 
%left '*' '/'  
%left NOT   

%start BLOC

%%
BLOC: BLOC INSTR '\n' {}
    | INSTR '\n' {}

INSTR: AFFECT {}
    | OUTPUT '(' EXPR ')' {
        if($3 == NUM_T){
            printf("\tconst cx,entier\n");
            printf("\tcallprintfs cx\n");
            printf("\tcp ax,sp\n");
            printf("\tcallprintfd ax\n");
            printf("\tconst ax,nl\n");
            printf("\tcallprintfs ax\n");
        }else if($3 == BOOL_T){
            printf("\tconst cx,booleen\n");
            printf("\tcallprintfs cx\n");
            printf("\tpop ax\n");
            printf("\tconst dx,istrue%d\n", incr);
            printf("\tconst cx,end%d\n"
                            "\tconst bx,1\n"
                            "\tcmp ax,bx\n"
                            "\tjmpc dx\n"
                            "\tconst dx,false\n"
                            "\tcallprintfs dx\n"
                            "\tconst ax,nl\n"
                            "\tcallprintfs ax\n"
                            "\tjmp cx\n"
                            ":istrue%d\n"
                            "\tconst dx,true\n"
                            "\tcallprintfs dx\n"
                            "\tconst ax,nl\n"
                            "\tcallprintfs ax\n"
                            ":end%d\n", incr, incr, incr);
            incr++;
        }else{
            fprintf(stderr, "Erreur de type\n");
        }
    
    }
    |OUTPUT '(' ID ')' {
        if(estpresent($3)){
            if(type($3) == NUM_T){
                printf("\tconst cx,entier\n");
                printf("\tcallprintfs cx\n");
                printf("\tcp ax,sp\n");
                printf("\tcallprintfd ax\n");
                printf("\tconst ax,nl\n");
                printf("\tcallprintfs ax\n");
            }else if(type($3) == BOOL_T){
                printf("\tconst cx,booleen\n");
                printf("\tcallprintfs cx\n");
                printf("\tpop ax\n");
                printf("\tconst dx,istrue%d\n", incr);
                printf("\tconst cx,end%d\n"
                                "\tconst bx,1\n"
                                "\tcmp ax,bx\n"
                                "\tjmpc dx\n"
                                "\tconst dx,false\n"
                                "\tcallprintfs dx\n"
                                "\tconst ax,nl\n"
                                "\tcallprintfs ax\n"
                                "\tjmp cx\n"
                                ":istrue%d\n"
                                "\tconst dx,true\n"
                                "\tcallprintfs dx\n"
                                "\tconst ax,nl\n"
                                "\tcallprintfs ax\n"
                                ":end%d\n", incr, incr, incr);
                incr++;
            }else{
                fprintf(stderr, "Erreur de type\n");
            }
        }else{
            fprintf(stderr, "Erreur d'identificateur\n");
        }
    }

AFFECT: ID '=' EXPR {
    if(estpresent($1)){
        if(type($1) == $3){
            printf("\tpop ax\n");
            printf("\tconst %s,ax\n", $1);
        }else{
            fprintf(stderr, "Erreur de type\n");
        }
    }else{
        add($1, $3);
    }
}

EXPR:
 EXPR '+' EXPR {
                    if($1 == NUM_T && $3 == NUM_T){
                        printf("\tpop ax\n");
                        printf("\tpop bx\n");
                        printf("\tadd ax,bx\n");
                        printf("\tpush ax\n");
                        $$ = NUM_T;
                    }
                    else{
                        $$ = ERR_T;
                        fprintf(stderr,"Erreur division par 0\n");
                    }
                }
|EXPR '-' EXPR {
                    if($1 == NUM_T && $3 == NUM_T){
                                printf("\tpop ax\n");
                                printf("\tpop bx\n");
                                printf("\tsub bx,ax\n");
                                printf("\tpush bx\n");
                                $$ = NUM_T;
                    }
                    else{   
                        $$ = ERR_T;
                        fprintf(stderr,"Erreur division par 0\n");
                    }
                }
|EXPR '*' EXPR {
                    if($1 == NUM_T && $3 == NUM_T){
                                printf("\tpop ax\n");
                                printf("\tpop bx\n");
                                printf("\tmul ax,bx\n");
                                printf("\tpush ax\n");
                                $$ = NUM_T;
                    }else{
                        $$ = ERR_T;
                        fprintf(stderr,"Erreur division par 0\n");
                    }
                }
|EXPR '/' EXPR {
                    if($1 == NUM_T && $3 == NUM_T){
                                printf("\tpop ax\n");
                                printf("\tpop bx\n");
                                printf("\tconst dx,errDiv0\n");
                                printf("\tdiv bx,ax\n");
                                printf("\tjmpe dx\n");
                                printf("\tpush bx\n");
                                $$ = NUM_T;
                    }else{
                        $$ = ERR_T;
                        fprintf(stderr,"Erreur division par 0\n");
                    }
                }
| EXPR EQUAL EXPR {if($1 == $3){
                        printf("\tpop ax\n"
                            "\tpop bx\n"
                            "\tconst dx,istrue%d\n"
                            "\tconst cx,end%d\n"
                            "\tcmp ax,bx\n"
                            "\tjmpc dx\n"
                            "\tconst dx,0\n"
                            "\tpush dx\n"
                            "\tjmp cx\n"
                            ":istrue%d\n"
                            "\tconst dx,1\n"
                            "\tpush dx\n"
                            ":end%d\n", incr, incr, incr, incr);
                        incr++;
                        $$ = BOOL_T;
                        }else{
                        $$ = ERR_T;
                        fprintf(stderr, "Erreur de type\n");
                    }
                }
    | EXPR DIFF EXPR {if($1 == $3){
                        printf("\tpop ax\n"
                            "\tpop bx\n"
                            "\tconst dx,isfalse%d\n"
                            "\tconst cx,end%d\n"
                            "\tcmp ax,bx\n"
                            "\tjmpc dx\n"
                            "\tconst dx,1\n"
                            "\tpush dx\n"
                            "\tjmp cx\n"
                            ":isfalse%d\n"
                            "\tconst dx,0\n"
                            "\tpush dx\n"
                            ":end%d\n", incr, incr, incr, incr);
                        incr++;
                        $$ = BOOL_T;
                        }else{
                        $$ = ERR_T;
                        fprintf(stderr, "Erreur de type\n");
                    }
                }
    | EXPR SUP EXPR {if($1 == $3){
                        printf("\tpop ax\n"
                            "\tpop bx\n"
                            "\tconst dx,istrue%d\n"
                            "\tconst cx,end%d\n"
                            "\tsless ax,bx\n"
                            "\tjmpc dx\n"
                            "\tconst dx,0\n"
                            "\tpush dx\n"
                            "\tjmp cx\n"
                            ":istrue%d\n"
                            "\tconst dx,1\n"
                            "\tpush dx\n"
                            ":end%d\n", incr, incr, incr, incr);
                        incr++;
                        $$ = BOOL_T;
                        }else{
                        $$ = ERR_T;
                        fprintf(stderr, "Erreur de type\n");
                    }
                }
    | EXPR INF EXPR {if($1 == $3){
                        printf("\tpop ax\n"
                            "\tpop bx\n"
                            "\tconst dx,istrue%d\n"
                            "\tconst cx,end%d\n"
                            "\tsless bx,ax\n"
                            "\tjmpc dx\n"
                            "\tconst dx,0\n"
                            "\tpush dx\n"
                            "\tjmp cx\n"
                            ":istrue%d\n"
                            "\tconst dx,1\n"
                            "\tpush dx\n"
                            ":end%d\n", incr, incr, incr, incr);
                        incr++;
                        $$ = BOOL_T;
                        }else{
                        $$ = ERR_T;
                        fprintf(stderr, "Erreur de type\n");
                    }
                }
    | EXPR SUPE EXPR {if($1 == $3){
                        printf("\tpop ax\n"
                            "\tpop bx\n"
                            "\tconst dx,istrue%d\n"
                            "\tconst cx,end%d\n"
                            "\tcmp ax,bx\n"
                            "\tjmpc dx\n"
                            "\tsless ax,bx\n"
                            "\tjmpc dx\n"
                            "\tconst dx,0\n"
                            "\tpush dx\n"
                            "\tjmp cx\n"
                            ":istrue%d\n"
                            "\tconst dx,1\n"
                            "\tpush dx\n"
                            ":end%d\n", incr, incr, incr, incr);
                        incr++;
                        $$ = BOOL_T;
                        }else{
                        $$ = ERR_T;
                        fprintf(stderr, "Erreur de type\n");
                    }
                }
    | EXPR INFE EXPR {if($1 == $3){
                        printf("\tpop ax\n"
                            "\tpop bx\n"
                            "\tconst dx,istrue%d\n"
                            "\tconst cx,end%d\n"
                            "\tcmp ax,bx\n"
                            "\tjmpc dx\n"
                            "\tsless bx,ax\n"
                            "\tjmpc dx\n"
                            "\tconst dx,0\n"
                            "\tpush dx\n"
                            "\tjmp cx\n"
                            ":istrue%d\n"
                            "\tconst dx,1\n"
                            "\tpush dx\n"
                            ":end%d\n", incr, incr, incr, incr);
                        incr++;
                        $$ = BOOL_T;
                        }else{
                        $$ = ERR_T;
                        fprintf(stderr, "Erreur de type\n");
                    }
                }
    | EXPR AND EXPR {if($1 == BOOL_T && $3 == BOOL_T){
                        printf("\tpop ax\n"
                            "\tpop bx\n"
                            "\tand ax,bx\n"
                            "\tpush ax\n");
                        $$ = BOOL_T;
                        }else{
                        $$ = ERR_T;
                        fprintf(stderr, "Erreur de type\n");
                    }
                }
    | EXPR OR EXPR {if($1 == BOOL_T && $3 == BOOL_T){
                        printf("\tpop ax\n"
                            "\tpop bx\n"
                            "\tor ax,bx\n"
                            "\tpush ax\n");
                        $$ = BOOL_T;
                        }else{
                        $$ = ERR_T;
                        fprintf(stderr, "Erreur de type\n");
                    }
                }
    | NOT EXPR {if($2 == BOOL_T){
                    printf("\tpop ax\n"
                            "\tconst bx,0\n"
                            "\tconst dx,istrue%d\n"
                            "\tconst cx,end%d\n"
                            "\tcmp ax,bx\n"
                            "\tjmpc dx\n"
                            "\tconst dx,0\n"
                            "\tpush dx\n"
                            "\tjmp cx\n"
                            ":istrue%d\n"
                            "\tconst dx,1\n"
                            "\tpush dx\n"
                            ":end%d\n", incr, incr, incr, incr);
                        incr++;
                        $$ = BOOL_T;
                    }else{
                    $$ = ERR_T;
                    fprintf(stderr, "Erreur de type\n");
                }}
    | '(' EXPR ')' {$$ = $2;}
    | NUM {printf("\tconst ax,%d\n"
                  "\tpush ax\n", $1);
                  $$ = NUM_T;}
    | ID {printf("\tconst ax,%s\n",$1);}
    | TRUE {printf("\tconst ax,1\n"
                   "\tpush ax\n");
                   $$ = BOOL_T;}
    | FALSE {printf("\tconst ax,0\n"
                    "\tpush ax\n");
                    $$ = BOOL_T;}
;
%%

void yyerror(const char *s){
    fprintf(stderr,"%s\n",s);
}

void debut(){
    printf("\tconst ax,debut\n");
    printf("\tjmp ax\n");
    printf(":nl\n");
    printf("@string \"\\n\"\n");
    printf(":msgErrorDiv\n");
    printf("@string \"Erreur division par 0\"\n");
    printf(":false\n");
    printf("@string \"false\"\n");
    printf(":true\n");
    printf("@string \"true\"\n");
    printf(":booleen\n");
    printf("@string \"booléen:\"\n");
    printf(":entier\n");
    printf("@string \"entier:\"\n");
    printf(":errDiv0\n");
    printf("\tconst ax,msgErrorDiv\n");
    printf("\tcallprintfs ax\n");
    printf("\tconst ax,nl\n");
    printf("\tcallprintfs ax\n");
    printf("\tend\n");
    printf(":debut\n");
    printf("\tconst bp,pile\n");
    printf("\tconst sp,pile\n");
    printf("\tconst ax,2\n");
    printf("\tsub sp,ax\n");
}

void fin(){
    printf("\tcp ax,sp\n");
    printf("\tcallprintfd ax\n");
    printf("\tconst ax,nl\n");
    printf("\tcallprintfs ax\n");
    printf("\tpop ax\n");
    printf("\tend\n");
    printf(":pile\n");
    printf("@int 0\n");
}

int main(){
    liste_id = (lid*)malloc(sizeof(lid));
    if (liste_id == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la liste d'identificateurs\n");
        exit(EXIT_FAILURE);
    }
    liste_id->head = NULL;
    debut();
    yyparse();
    fin();
    return EXIT_SUCCESS;
}

void add(char* id, type_synth t){
    lcell *new = (lcell*)malloc(sizeof(lcell));
    lcell * tmp = liste_id->head;
    new->id = id;
    new->type = t;
    new->next = tmp;
    liste_id->head = new;
}

bool estpresent(char* id){
    lcell *tmp = liste_id->head;
    while(tmp != NULL){
        if(strcmp(tmp->id, id) == 0){
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

type_synth type(char* id){
    lcell *tmp = liste_id->head;
    while(tmp != NULL){
        if(strcmp(tmp->id, id) == 0){
            return tmp->type;
        }
        tmp = tmp->next;
    }
    return ERR_T;
}
