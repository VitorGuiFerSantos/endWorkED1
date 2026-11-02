#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#define MAXchar 300
//struct to user
typedef struct _user{
    //weigth para que eu possa organizar em arvore essa estrutura
    int weight;
    char member[MAXchar];
    char gmail[MAXchar];
}User;
//struct to book 
typedef struct _dados{
    uint64_t id;
    char title[MAXchar];
    char author[MAXchar];
    int year;
    bool status[MAXchar];
    User userLent[MAXchar][MAXchar];
    int amount;
    int amountLent;
}Book;  
// criar uma estrutura de controle para heaps 
struct _treeB{
    Book *data;
    int *height;
    struct _treeB *rigth;
    struct _treeB *left;
};
typedef struct _treeB node;

 node *createElemnt(char title[], char author[], int year, int amount, uint64_t id){
    Book *newdata = malloc( sizeof ( Book ) );
    node *new = malloc( sizeof ( node ) );
    newdata -> id = id;
    newdata -> year = year; 
    newdata -> amount = amount;
    newdata -> amountLent = 0;
    memset(newdata -> status, false, sizeof(newdata -> status)); 
    strcpy( newdata -> author,author); 
    strcpy( newdata -> title,title); 
    new -> data = newdata;
    new -> height = 0;
    new -> left = NULL;
    new -> rigth = NULL;
    return new;
 }
