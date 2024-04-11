SHELL=/bin/sh
LEX=flex
YACC=bison
CC=gcc
CFLAGS=-g -O2 -std=c11 -pedantic -Wall
LDFLAGS=
# --nounput: ne g�n�re pas la fonction yyunput() inutile
# --DYY_NO_INPUT: ne prend pas en compte la fonction input() inutile
# -D_POSIX_SOURCE: d�clare la fonction fileno()
LEXOPTS=-D_POSIX_SOURCE -DYY_NO_INPUT --nounput
YACCOPTS=

# REMPLACER ICI "fichier" PAR LE NOM DE VOS FICHIERS
PROG=ex1

# PROG ASM input file with .a extension
PROG_ASM=expr

.PHONY: all comp asm

all: comp asm

comp: $(PROG)

$(PROG): lex.yy.o $(PROG).tab.o variables.o print_functions.o types.o
	$(CC) $+ -o $@ $(LDFLAGS)

variables.o: variables.c
	$(CC) $(CFLAGS) $< -c

print_functions.o: print_functions.c
	$(CC) $(CFLAGS) $< -c

types.o: types.c
	$(CC) $(CFLAGS) $< -c

lex.yy.c: $(PROG).l $(PROG).tab.h
	$(LEX) $(LEXOPTS) $<

lex.yy.h: $(PROG).l
	$(LEX) $(LEXOPTS) --header-file=$@ $<

$(PROG).tab.c $(PROG).tab.h: $(PROG).y lex.yy.h
	$(YACC) $(YACCOPTS) $< -d -v --graph

%.o: %.c
	$(CC) -DYYDEBUG $(CFLAGS) $< -c

asm:
	./$(PROG) < $(PROG_ASM).a > $(PROG_ASM).asm
	asipro $(PROG_ASM).asm $(PROG_ASM)

clean:
	-rm $(PROG) *.o lex.yy.* $(PROG).tab.* *.err *.output *.out *.dot *.vcg *.asm $(PROG_ASM) newcore*

