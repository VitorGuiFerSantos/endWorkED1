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
    WdogBook *wardenB;
};
typedef struct _arbor userTree;

//struct to book 

struct _treeB{
    Book *data;
    int height;
    struct _treeB *right;
    struct _treeB *left;
    //guarda o endereço dos usuarios com os livros 
    WDogUser *wardenU;
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
#endif