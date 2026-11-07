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
    newdateS -> year = year2;
    
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
    newdateS -> year = year2;
    
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
        new -> prev = aux;
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
void addLoanBook(WDogUser* guardU,ListD_E_user* new){
    if(guardU -> first == NULL){
        guardU -> first = new;
        guardU -> last = new;
        return;
    }
    ListD_E_user* aux = guardU -> first;
    for(; aux != NULL; aux = aux -> next){
        int comp = strcmp( new -> data ->title , aux -> data -> title);
        // break when o 
        if(comp < 0){
            break;
        }
    }
    //1°case last of elements
    if(aux == NULL){
        guardU -> last -> next = new;
        new -> prev = aux;
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