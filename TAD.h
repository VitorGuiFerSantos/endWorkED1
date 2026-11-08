#ifndef USER_TREE_H
#define USER_TREE_H
#define MAXchar 300
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
typedef struct _time_D{
    int day;
    int month;
    int year;
}Date;

typedef struct {
    char member[MAXchar];
    char gmail[MAXchar];
} User;

typedef struct _dados_book{
    uint64_t id;
    char title[MAXchar];
    char author[MAXchar];
    int year;
    int amount;
    int amountLent;
}Book;
//lista encadeada que guarda o endereço dos usuarios que retiraram o livro
struct _l_E_B{
    Date* loanSt;
    Date* loanEnd;
    User* data;
    struct _l_E_B *next;
    struct _l_E_B *prev;
};
typedef struct _l_E_B ListD_E_book;

typedef struct _wactherBook{
    ListD_E_book* first;
    ListD_E_book* last;
}WdogBook;
// lista encadeada que guarda os livros que o usuário retirou 
struct _lE_User{
    Date* loanSt;
    Date* loanEnd;
    Book* data;
    struct _lE_User *next;
    struct _lE_User *prev;
};
typedef struct _lE_User ListD_E_user;

typedef struct _wacther_User{
    ListD_E_user* first;
    ListD_E_user* last;
}WDogUser;


struct _arbor{
    int height;
    User *data;
    struct _arbor *left;
    struct _arbor *right;
    //guardo os endereço dos livros emprestados
    WDogUser *wardenB;
};
typedef struct _arbor userTree;

//struct to book 

struct _treeB{
    Book *data;
    int height;
    struct _treeB *right;
    struct _treeB *left;
    //guarda o endereço dos usuarios com os livros 
    WdogBook *wardenU;
};
typedef struct _treeB Node;
//lista encadeada para registrar os livros no usuário
WdogBook *creatWardenUser(){
    WdogBook* warden = malloc(sizeof(WdogBook));

    warden -> first = NULL;
    warden -> last = NULL;

    return warden;
}
WDogUser *creatWardenBook(){
    WDogUser* warden = malloc(sizeof(WDogUser));
    
    warden -> first = NULL;
    warden -> last = NULL;

    return warden;
}
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
void BSTuser(userTree *root, User *member, Book *item){
    if(root == NULL){
        return;
    }
    int comp = strcmp(root -> data -> gmail, member -> gmail);
    if(comp == 0){
        returnLoanUser(root -> wardenB,item);
        return;
    }
    if(comp > 0){
        BSTuser(root -> left,member, item);
    }else{
        if(comp < 0){
            BSTuser(root -> right,member, item);
        }
        return;
    }
 }
 void BSTBook(Node *root, Book *element, User *item){
     if(root == NULL){
        return;
    }
    if(root ->data ->id == element -> id){
        returnLoanBook(root -> wardenU,item);
        return;
    }
    if(root ->data ->id > element -> id){
        BSTBook(root -> left,element, item);
    }else{
        if(root ->data -> id < element -> id){
            BSTBook(root -> right,element, item);
        }
        return;
    }
}
void removeAllUser(WdogBook *copUs,Book *tome, Node* rootBo){
    ListD_E_book *aux = copUs ->first, *ant;
    while (aux != NULL){
        ant = aux;
        aux = aux -> next;
        //criar uma função de BST para buscar os livros empresatdos para usuário
        //passo os dados do usuário para procurar na árvore depois ocupa os dados 
        //do livro para fazer a remoção na lista encadeada para depois remover na outra lista
        BSTBook( rootBo, tome, ant->data);
        returnLoanBook(copUs,ant->data);
    }
}
void removeAllBook(WDogUser *copBo,User* people, userTree* rootUs){
    ListD_E_user *aux = copBo ->first, *ant;
    while (aux != NULL){
        ant = aux;
        aux = aux -> next;
        BSTuser(rootUs, people, ant->data);
        returnLoanUser(copBo, ant->data);
    }
}
#endif