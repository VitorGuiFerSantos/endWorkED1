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
    int books;
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
typedef struct _l_E_B ListD_E_user;

typedef struct _wactherUser{
    ListD_E_user* first;
    ListD_E_user* last;
}WDogUser;
// lista encadeada que guarda os livros que o usuário retirou 
struct _lE_User{
    Date* loanSt;
    Date* loanEnd;
    Book* data;
    struct _lE_User *next;
    struct _lE_User *prev;
};
typedef struct _lE_User ListD_E_Book;

typedef struct _wacther_Book{
    ListD_E_Book* first;
    ListD_E_Book* last;
}WDogBook;

struct _arbor{
    int height;
    User *data;
    struct _arbor *left;
    struct _arbor *right;
    WDogBook *wardenB;
};
typedef struct _arbor userTree;

struct _treeB{
    Book *data;
    int height;
    struct _treeB *right;
    struct _treeB *left;
    WDogUser *wardenU;
};
typedef struct _treeB treeBook;
//lista encadeada para registrar os livros no usuário
WDogBook *creatWardenBook(){
    WDogBook* warden = malloc(sizeof(WDogBook));

    warden -> first = NULL;
    warden -> last = NULL;

    return warden;
}
WDogUser *creatWardenUser(){
    WDogUser* warden = malloc(sizeof(WDogUser));
    
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
    
}// registro o endereço do livro para o usuario
ListD_E_user *createLoanUser(Date* newdateS,Date* newdateE, User* data){
    ListD_E_user* new = malloc(sizeof(ListD_E_user));

    new -> loanSt = newdateS;
    new -> loanEnd = newdateE;
    
    new -> data = data;

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
/* void returnLoanUser(WDogUser *copUs,User* tome){
    if(copUs -> first == NULL){
        return;
    }
    ListD_E_user* aux = copUs -> first;
    for(;aux != NULL; aux = aux ->next ){
        int comp = strcmp(aux -> data -> member,tome -> member);
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
void returnLoanBook(WDogBook *copUs,Book* tome){
    if(copUs -> first  == NULL){
        return;
    }
    ListD_E_Book* aux  = copUs ->first;
    for(;aux != NULL; aux = aux ->next ){
        int comp = strcmp(aux -> data ->  title,tome ->  title);
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
void BSTuserDe(userTree *root, User *member, Book *item){
    if(root == NULL){
        return;
    }
    int comp = strcmp(root -> data -> gmail, member -> gmail);
    if(comp == 0){
        returnLoanUser(root -> wardenB,item);
        return;
    }
    if(comp > 0){
        BSTuserDe(root -> left,member, item);
    }else{
        if(comp < 0){
            BSTuserDe(root -> right,member, item);
        }
        return;
    }
 }
 void BSTBookDe(treeBook *root, Book *element, User *item){
     if(root == NULL){
        return;
    }
    if(root ->data ->id == element -> id){
        returnLoanBook(root -> wardenU,item);
        return;
    }
    if(root ->data ->id > element -> id){
        BSTBookDe(root -> left,element, item);
    }else{
        if(root ->data -> id < element -> id){
            BSTBookDe(root -> right,element, item);
        }
        return;
    }
}
void removeAllBook(WDogBook *copUs,Book *tome, treeBook* rootBo){
    ListD_E_Book *aux = copUs ->first, *ant;
    while (aux != NULL){
        ant = aux;
        aux = aux -> next;
        //criar uma função de BST para buscar os livros empresatdos para usuário
        //passo os dados do usuário para procurar na árvore depois ocupa os dados 
        //do livro para fazer a remoção na lista encadeada para depois remover na outra lista
        BSTBookDe( rootBo, tome, ant->data);
        returnLoanBook(copUs,ant->data);
    }
}
void removeAllUser(WDogUser *copBo,User* people, userTree* rootUs){
    ListD_E_user *aux = copBo ->first, *ant;
    while (aux != NULL){
        ant = aux;
        aux = aux -> next;
        BSTuserDe(rootUs, people, ant->data);
        returnLoanUser(copBo, ant->data);
    }
} */
void printWDogBook(WDogBook* wardenB){
    if(wardenB ->first == NULL){
        printf("\n Nenhum livro retirado\n");

        return;
    }
    ListD_E_Book* aux = wardenB ->first;
    printf("\n+----------------------------------+\n");
    for(;aux!=NULL;aux = aux -> next){
        printf("\n|%ld\t\t|",aux ->data -> id);
        printf("\n|%s\t|",aux ->data -> title);
        printf("\n|%s\t\t|",aux ->data -> author);
        printf("\n|%d\t\t|\n",aux ->data -> year);
    }
    printf("\n+-----------------------------------+\n");
}

void printWDogUser(WDogUser* wardenU){
    if(wardenU ->first == NULL){
        printf("\n Nenhum usuário retirou esse livro\n");
        return;
    }
    ListD_E_user* aux = wardenU ->first;
    printf("\n+----------------------------------+\n");
    for(;aux!=NULL;aux = aux -> next){
        printf("\n|%s\t|",aux ->data -> member);
        printf("\n|%s\t\t|",aux ->data -> gmail);
    }
    printf("\n+-----------------------------------+\n");
}
#endif