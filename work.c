#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXchar 300
typedef struct _user{
    char member[MAXchar];
    char gmail[MAXchar];
}User;
typedef struct _dados{
    char titulo[MAXchar];
    char autor[MAXchar];
    int ano;
    bool status[MAXchar];
    int quat;
    int quantEmpr;
    char userEmpr[MAXchar][MAXchar];

}Book;