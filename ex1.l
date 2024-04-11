%{
#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "ex1.tab.h"
int strtoEntier(const char *);
char * cpypointer(const char *);

%}
%option noyywrap
%%
"true" {return TRUE;}
"false" {return FALSE;}
"\\RETURN" {return RETURN;}
"\\begin{algo}" {return BALGO;}
"\\end{algo}" {return EALGO;}
"\\CALL" {return CALL;}
"\\SET" {return SET;}
"\\IF" {return IF;}
"\\FI" {return FI;}
"\\ELSE" {return ELSE;}
"\\DOWHILE" {return DOWHILE;}
"\\DOFORI" {return DOFORI;}
"\\OD" {return OD;}
[1-9][0-9]*|[0] { yylval.entier = strtoEntier(yytext); return NUM; }
[a-zA-Z]* { yylval.id = cpypointer(yytext); return ID; }
"\n" {}
"&&" {return AND;}
"||" {return OR;}
"!" {return NOT;}
"==" {return EQUAL;}
">" {return SUP;}
"<" {return INF;}
">=" {return SUPE;}
"<=" {return INFE;}
"!=" {return DIFF;}
"+"|"-"|"*"|"/"|"("|")"|"="|"{"|"}"|"," { return yytext[0];}
[[:space:]] {}
. { fprintf(stderr, "Erreur: %c\n", yytext[0]); }
%%

int strtoEntier(const char *s)
{
    char *endptr;
    int val = (int)strtol(s, &endptr, 10);
    if (*endptr != '\0')
    {
        fprintf(stderr, "Erreur: %s n'est pas un entier\n", s);
        exit(EXIT_FAILURE);
    }
    return val;
}

char * cpypointer(const char *s)
{
    char *p = malloc(strlen(s) + 1);
    if (p != NULL)
    {
        strcpy(p, s);
    }
    return p;
}
