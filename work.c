#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
    int id;
    char title[MAXchar];
    char author[MAXchar];
    int year;
    bool status[MAXchar];
    User Userlent[MAXchar][MAXchar];
    int amount;
    int amountLent;
}Book;
// criar uma estrutura de controle para heaps 