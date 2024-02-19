%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "types.h"
	#include "compilation.tab.h"
	
	int strtoEntier(char const *s);
	char * strduplication(const char *s);
%}

%option noyywrap

%%
"true" {return TRUE;}
"false" {return FALSE;}
"==" {return EQUAL;}
"<" {return INF;}
">" {return SUP;}
">=" {return SUPE;}
"<=" {return INFE;}
"!" {return NOT;}
"!=" {return DIFF;}
"&&" {return AND;}
"||" {return OR;}
"output" {return OUTPUT;}
[a-z|A-Z]* {yylval.id = strduplication(yytext);return ID;}
[1-9][0-9]*|[0] {yylval.entier = strtoEntier(yytext);return NUM;}
"+"|"-"|"*"|"/"|"("|")"|"=" {return (yytext[0]);}
"\n" {return '\n';}
[[:space:]] {}
. {fprintf(stderr,"caractère inconnu: %c\n",yytext[0]);}
%%

int strtoEntier(char const *s){
	char *endptr;
	int res = strtol(s,&endptr,10);
	if(*endptr != '\0'){
		fprintf(stderr,"Erreur de conversion de %s en entier\n",s);
		exit(EXIT_FAILURE);
	}
	return res;
}

char * strduplication(const char *s){
	char *res = malloc(strlen(s)+1);
	if(res == NULL){
		fprintf(stderr,"Erreur d'allocation mémoire\n");
		exit(EXIT_FAILURE);
	}
	strcpy(res,s);
	return res;
}