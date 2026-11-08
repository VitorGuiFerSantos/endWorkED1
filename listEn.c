#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "TAD.h"
// registro o endereço do usuario que livro
ListD_E_user *createLoanUser(int day1,int day2,int month1,int month2,int year1,int year2, User* data){
    ListD_E_user* new = malloc(sizeof(ListD_E_user));
    Date* newdateS =  malloc(sizeof(Date));
    Date* newdateE =  malloc(sizeof(Date));
    
    newdateS -> day = day1;
    newdateE -> day = day2;

    newdateS -> month = month1;
    newdateE -> month = month2;

    newdateS -> year = year1;
    newdateE -> year = year2;
    
    new -> loanSt = newdateS;
    new -> loanEnd = newdateE;
    
    new -> data = data;

    new -> next = NULL; 
    new -> prev = NULL; 
    
    return new;
    
}// registro o endereço do livro para o usuario
ListD_E_book *createLoanUser(int day1,int day2,int month1,int month2,int year1,int year2, Book* data){
    ListD_E_book* new = malloc(sizeof(ListD_E_book));
    Date* newdateS =  malloc(sizeof(Date));
    Date* newdateE =  malloc(sizeof(Date));
    
    newdateS -> day = day1;
    newdateE -> day = day2;

    newdateS -> month = month1;
    newdateE -> month = month2;

    newdateS -> year = year1;
    newdateE -> year = year2;
    
    new -> loanSt = newdateS;
    new -> loanEnd = newdateE;
    
    new -> data = data;

    new -> next = NULL; 
    new -> prev = NULL; 
    
    return new;
}
void addLoanUser(WdogBook* guardU,ListD_E_book* new){
    if(guardU -> first == NULL){
        guardU -> first = new;
        guardU -> last = new;
        return;
    }
    ListD_E_book* aux = guardU -> first;
    for(; aux != NULL; aux = aux -> next){
        int comp = strcmp( new -> data -> gmail, aux -> data -> gmail);
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
void addLoanUser(WdogBook* guardU,ListD_E_book* new){
    if(guardU -> first == NULL){
        guardU -> first = new;
        guardU -> last = new;
        return;
    }
    ListD_E_book* aux = guardU -> first;
    for(; aux != NULL; aux = aux -> next){
        int comp = strcmp( new -> data -> gmail, aux -> data -> gmail);
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
void returnLoanUser(WDogUser *copUs,Book* tome){
    if(copUs -> first == NULL){
        return;
    }
    ListD_E_user* aux = copUs -> first;
    for(;aux != NULL; aux = aux ->next ){
        int comp = strcmp(aux -> data -> title,tome -> title);
        if(comp == 0){
            if(aux -> next == NULL && aux ->prev == NULL){
                copUs -> first = NULL;
                copUs -> last = NULL;
                free(aux);
                return;
            }
            if(aux -> prev == NULL){
                copUs ->first = aux -> next; 
                aux -> next -> prev = NULL;
                free(aux);
                return;
            }
            if(aux -> next == NULL){
                copUs -> last = aux -> prev;
                copUs->last->next = NULL;
                free(aux);
                return;
            }
            aux -> prev -> next = aux -> next;
            aux -> next -> prev = aux -> prev;
            aux -> next = NULL;
            aux -> prev = NULL;
            free(aux);
            return;
        }

    }
}
void returnLoanBook(WdogBook *copUs,User* tome){
    if(copUs -> first == NULL){
        return;
    }
    ListD_E_book* aux = copUs;
    for(;aux != NULL; aux = aux ->next ){
        int comp = strcmp(aux -> data -> gmail,tome -> gmail);
        if(comp == 0){
            if(aux -> next == NULL && aux ->prev == NULL){
                copUs -> first = NULL;
                copUs -> last = NULL;
                free(aux ->loanEnd);
                free(aux ->loanSt);
                free(aux);
                return;
            }
            if(aux -> prev == NULL){
                copUs ->first = aux -> next; 
                aux -> next -> prev = NULL;
                free(aux -> loanEnd);
                free(aux -> loanSt);
                free(aux);
                return;
            }
            if(aux -> next == NULL){
                copUs -> last = aux -> prev;
                copUs->last->next = NULL;
                free(aux -> loanEnd);
                free(aux -> loanSt);
                free(aux);
                return;
            }
            aux -> prev -> next = aux -> next;
            aux -> next -> prev = aux -> prev;
            aux -> next = NULL;
            aux -> prev = NULL;
            free(aux -> loanEnd);
            free(aux -> loanSt);
            free(aux);
            return;
        }

    }
}
void removeAllUser(WdogBook *copUs,Book *tome){
    ListD_E_book *aux = copUs ->first, *ant;
    while (aux != NULL){
        ant = aux;
        aux = aux -> next;
        //criar uma função de BST para buscar os livros empresatdos para usuário
        //passo os dados do usuário para procurar na árvore depois ocupa os dados 
        //do livro para fazer a remoção na lista encadeada para depois remover na outra lista
        returnLoanBook(copUs,ant);
    }
}
void removeAllBook(WDogUser *copUs){
    ListD_E_user *aux = copUs ->first, *ant;
    while (aux != NULL){
        ant = aux;
        aux = aux -> next;
        returnLoanUser(copUs, ant);
    }
}