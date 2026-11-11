#ifdef Lista_Book
#define Lista_Book
#include "TAD.h"
#include "AVL_B.h"
#include "AVL_U.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
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

    new -> next = NULL; 
    new -> prev = NULL; 
    
    return new;
    
}
#endif