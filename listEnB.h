#ifndef Lista_Book
#define Lista_Book
#include "TAD.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <inttypes.h>
#include <time.h>
// registro o endereço do usuario que livro
WDogBook *creatWardenBook(){
    WDogBook* warden = malloc(sizeof(WDogBook));

    warden -> first = NULL;
    warden -> last = NULL;

    return warden;
}
ListD_E_Book *createLoanBook(Date* newdateS,Date* newdateE, Book* data){
    ListD_E_Book* new = malloc(sizeof(ListD_E_Book));

    
    new -> loanSt = newdateS;
    new -> loanEnd = newdateE;
    
    new -> data = data;

    new->correspondingLoan = NULL;

    new -> next = NULL; 
    new -> prev = NULL; 
    
    return new;
    
}

void addLoanBook(WDogBook* guardU,ListD_E_Book* new){
    if(guardU -> first == NULL){
        guardU -> first = new;
        guardU -> last = new;
        return;
    }
    ListD_E_Book* aux = guardU -> first;
    for(; aux != NULL; aux = aux -> next){
        int comp = strcmp( new -> data -> title, aux -> data -> title);
        // break when o 
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
ListD_E_Book *returnBook(WDogBook* wardenU, uint64_t id){
    if(wardenU -> first == NULL){
        return NULL;
    }
    for(ListD_E_Book* aux = wardenU -> first; aux!= NULL; aux = aux -> next){
        if(id == aux -> data ->id){
            return aux;
        }
    }
    return NULL;

}
void returnLoanBook(WDogBook *copBK,ListD_E_Book* tome){
 if(copBK -> first == NULL){
        return;
    }
    //1°case
    if(tome -> next == NULL && tome ->prev == NULL){
        copBK -> first = NULL;
        copBK -> last = NULL;
        return;
    }
    //2°case
    if(tome -> prev == NULL){
        copBK -> first = tome -> next;
        tome -> next -> prev = NULL;
        tome -> next = NULL;
        return;
    }
    //3°case
    if(tome -> next == NULL){
        copBK -> last = tome -> prev;
        copBK -> last -> next = NULL;
        tome -> prev = NULL;
        return;
    }
    //4°case
        tome -> prev -> next = tome -> next;
        tome -> next -> prev = tome -> prev;
        tome -> prev = NULL;
        tome -> next = NULL;
}
void printWDogBook(WDogBook* wardenB){
    if(wardenB ->first == NULL){
        printf("\n Nenhum livro retirado \n");

        return;
    }
    ListD_E_Book* aux = wardenB ->first;
    printf("\n +----------------------------------+ \n");
    for(;aux!=NULL;aux = aux -> next){
        printf(" \n\t\t | ID: %"PRIu64" \t\t |",aux ->data -> id);
        printf(" \n\t\t | Título: %s \t |",aux ->data -> title);
        printf(" \n\t\t | Autor: %s \t\t |",aux ->data -> author);
        printf(" \n\t\t | Ano de publicação: %d\t\t |",aux ->data -> year);
        printf(" \n\t\t |  Data retirada: ");
        printDate(aux ->loanSt);
        printf("\t\t|\n\t\t| Data devolução:");
        printDate(aux ->loanEnd);
        printf("\t\t|\n");
    }
    printf("\n +-----------------------------------+ \n");
}
#endif