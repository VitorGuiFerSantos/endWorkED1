#ifndef Lista_User
#define Lista_User
#include "TAD.h"
#include "AVL_B.h"
#include "AVL_U.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <unistd.h>
#include <time.h>
WDogUser *creatWardenUser(){
    WDogUser* warden = malloc(sizeof(WDogUser));
    
    warden -> first = NULL;
    warden -> last = NULL;

    return warden;
}
ListD_E_user *createLoanUser(Date* newdateS,Date* newdateE, User* data){
    ListD_E_user* new = malloc(sizeof(ListD_E_user));

    new -> loanSt = newdateS;
    new -> loanEnd = newdateE;
    
    new -> data = data;

    new->correspondingLoan = NULL;

    new -> next = NULL; 
    new -> prev = NULL; 
    
    return new;
}
void addLoanUser(WDogUser* guardU,ListD_E_user* new){
    if(guardU -> first == NULL){
        guardU -> first = new;
        guardU -> last = new;
        return;
    }
    ListD_E_user* aux = guardU -> first;
    for(; aux != NULL; aux = aux -> next){
        int comp = strcmp( new -> data -> gmail, aux -> data -> gmail);
        if(comp < 0){
            break;
        }
    }
    //1°case last of elements
    if(aux == NULL){
        guardU -> last -> next = new;
        new -> prev = guardU -> last;
        guardU -> last = new;
        return;
    }

    //2°case first of elements
    if(aux -> prev == NULL){
        new -> next = aux;
        aux -> prev = new;
        guardU -> first = new;
        return;
    }

    //3°case quite of elements
    new -> next = aux;
    new -> prev = aux -> prev;
    aux -> prev -> next = new;
    aux -> prev = new;
}

ListD_E_user *returnUser(WDogUser* wardenU, char gmail[]){
    if(wardenU -> first == NULL){
        return NULL;
    }
    for(ListD_E_user* aux = wardenU -> first; aux!= NULL; aux = aux -> next){
        if(strcmp( aux -> data -> gmail,gmail)){
            return aux;
        }
    }
    return NULL;

}
#endif