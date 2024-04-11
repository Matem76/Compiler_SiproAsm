#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

//This enumeration type_synth is used to define various types of syntactic
// categories or types that being used in the  compiler or interpreter context, such as numeric, boolean, unknown, and error types.
typedef enum{ 
            NUM_T,
            BOOL_T,
            UNK_T,
            ERR_T
        }
type_synth;


typedef enum {
    ACT_DEBUT,
    ACT_RETVALUE,
    ACT_CALL, 
    ACT_AFFICHE, 
    ACT_ALGO,
    ACT_RETURN,
    ACT_EQUAL,
    ACT_DIFF,
    ACT_SUP,
    ACT_INF,
    ACT_SUPE,
    ACT_INFE,
    ACT_ADD, 
    ACT_SUB, 
    ACT_MUL, 
    ACT_DIV, 
    ACT_AND, 
    ACT_OR, 
    ACT_NOT,
    ACT_NUM,
    ACT_TRUE,
    ACT_FALSE,
    ACT_ID,
    ACT_SETID,
    ACT_ELSE,
    ACT_IFELSE,
    ACT_FI,
    ACT_JMP,
    ACT_DOWHILE,
    ACT_DO,
    ACT_OD,
    ACT_JMPWHILE,
    ACT_DOFORI,
    ACT_JMPFOR,
    ACT_DOFOR,
    ACT_INCR,
    ACT_CALLREC
}id_act;


//The lcell structure represents a linked list cell that holds a type (from
// type_synth), an identifier, and a pointer to the next cell in the list. It's likely used to maintain a list of identifiers with their associated types.

typedef struct lcell lcell;



struct lcell{
            lcell *next;
            type_synth type;
            char *id;
        };

//The lid structure is designed to manage a list of lcell structures, along
//with additional metadata such as the list's size and p the sizes of arguments and local variables.

typedef struct lid lid;

struct lid{
            lcell *head;
            int size;
            int arg_size;
            int local_size;
            char * id;
        };


//The tcell structure represents another form of a linked list cell, which holds an identifier, a
// string, an integer, and a pointer to the next cell. This structure seems to be designed for a different
// purpose or context compared to lcell, possibly to hold more varied data associated with each identifier.
typedef struct tcell tcell;

struct tcell {
    id_act action;
    char *chaine;
    int entier;
    tcell *next;
};


//The tid structure is used to manage a list of tcell structures. It includes pointers to both the head
// and tail of the list for efficient operations, as well as a size attribute to keep track of the list's length.
// This structure is used in scenarios where both the beginning and end of the list are frequently accessed or modified.
typedef struct{
            tcell *head;
            tcell *tail;
            int size;
        }
tid;

//Creates and returns an empty linked list for storing identifiers.
lid* empty();

//Creates and returns an empty table for storing identifiers.
lid ** empty_tab();

//Creates and returns an empty table for storing instructions.
tid *empty_liste();

//Frees the memory allocated for the linked list.
void tid_dispose(tid *liste_tid);

//Frees the memory allocated for the linked list table.
void llid_dispose(lid **tab_lid);

//Adds a new identifier id with type t to the linked list liste.
void add_lid(char* id, type_synth t, lid* liste);

//Adds a new identifier to the identifier table.
void add_tab(char *id);

//Calculates the size of the identifier table.
int size_of_tab_lid(lid **tab_lid);

//Returns the type of the identifier id if it exists in the linked list liste.
type_synth type(char* id, lid* liste);

//Adds an instruction to the instruction table.
void add_tcell(id_act action, char *chaine, int i);

//Checks if the identifier id is present in the linked list liste. Returns true if present, otherwise false.
bool is_present(char* id, lid* liste);

//Search the identifier table for the index of the identifier id. Returns the index if found, otherwise returns -1.
int search_tab_ind(char *id);

//Returns the index of the identifier id in the linked list liste if it exists, otherwise returns -1.
int indice_id(char* id, lid* liste);

#endif