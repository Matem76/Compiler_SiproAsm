#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "variables.h"

lid* empty(){ 
    lid* new = (lid*)malloc(sizeof(lid));
    if (new == NULL) {
        fprintf(stderr, "Malloc errror\n");
        exit(EXIT_FAILURE);
    }
    new->head = NULL;
    new->size = 0;
    new->arg_size = 0;
    new->local_size = 0;
    new->id = NULL;
    return new;
}

tid *empty_liste() { 
    tid *new_tid = (tid *)malloc(sizeof(tid));
    if (new_tid == NULL) {
        fprintf(stderr, "Malloc errror\n");
        exit(EXIT_FAILURE);
    }
    new_tid->head = NULL;
    new_tid->tail = NULL;
    new_tid->size = 0;
    return new_tid;
}


lid ** empty_tab(){
    lid **new_tab = (lid **)malloc(tab_size * sizeof(lid *));
    if (new_tab == NULL) {
        fprintf(stderr, "Malloc errror\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < tab_size; i++) {
        new_tab[i] = empty();
    }
    return new_tab;
}

void llid_dispose(lid **tab_lid) {
  for (int i = 0; i < tab_size; i++) {
    if (tab_lid[i] != NULL) {
      lcell *tmp = tab_lid[i]->head;
      while (tmp != NULL) {
        lcell *next = tmp->next;
        free(tmp);
        tmp = next;
      }
    }
    free(tab_lid[i]);
  }
  free(tab_lid);
}

void tid_dispose(tid *liste_tid) {
  tcell *tmp = liste_tid->head;
  while (tmp != NULL) {
    tcell *next = tmp->next;
    free(tmp);
    tmp = next;
  }
  free(liste_tid);
}

void add_lid(char* id, type_synth t, lid* liste){ 
    lcell *new = (lcell*)malloc(sizeof(lcell));
    lcell * tmp = liste->head;
    new->id = id;
    new->type = t;
    new->next = tmp;
    liste->head = new;
    liste->size++;
}

type_synth type(char* id, lid* liste){ 
    lcell *tmp = liste->head;
    while(tmp != NULL){
        if(strcmp(tmp->id, id) == 0){
            return tmp->type;
        }
        tmp = tmp->next;
    }
    return ERR_T;
}

void add_tcell(id_act action, char *chaine, int i){ 
    tcell *new = (tcell *)malloc(sizeof(tcell));
    if (new == NULL) {
        fprintf(stderr, "Memory error\n");
        exit(EXIT_FAILURE);
    }
    new->action = action;
    new->chaine = chaine;
    new->entier = i;
    new->next = NULL;
    
    if (liste_tid->head == NULL) {
        liste_tid->head = new;
        liste_tid->tail = new;
    } else {
        liste_tid->tail->next = new;
        liste_tid->tail = new;
    }
    liste_tid->size++;
}

void add_tab(char *id){
    tab_lid[ind_tab]->id = id;
}


//TOOLS-----------------------------------------------------------------------------

int size_of_tab_lid(lid **tab_lid) {
    int size = 0;
    for (int i = 0; i < tab_size; i++) {
        if (tab_lid[i]->id != NULL) {
            size++;
        } else {
            break;
        }
    }
    return size;
}

int search_tab_ind(char *id){
    for(int i = 0; i < tab_size; i++){
        if(tab_lid[i]->id == NULL){
            return -1;
        }
        if(strcmp(tab_lid[i]->id, id) == 0){
            return i;
        }
    }
    return -1;
}

int indice_id(char* id, lid* liste){ 
    lcell *tmp = liste->head;
    int i = 0;
    while(tmp != NULL){
        if(tmp->id == NULL){
            fprintf(stderr, "NULL id\n");
            exit(EXIT_FAILURE);
        }
        if(strcmp(tmp->id, id) == 0){
            return i;
        }
        tmp = tmp->next;
        i++;
    }
    return -1;
}

bool is_present(char* id, lid* liste){ 
    lcell *tmp = liste->head;
    while(tmp != NULL){
        if(strcmp(tmp->id, id) == 0){
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}