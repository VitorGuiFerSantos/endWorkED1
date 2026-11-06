#ifndef USER_TREE_H
#define USER_TREE_H

#define MAXchar 300
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char member[MAXchar];
    char gmail[MAXchar];
} User;

struct _arbor{
    int height;
    User *data;
    struct _arbor *left;
    struct _arbor *right;
};
typedef struct _arbor userTree;

//struct to book 
typedef struct _dados{
    uint64_t id;
    char title[MAXchar];
    char author[MAXchar];
    int year;
    User *bookOcupedUser;
    int amount;
    int amountLent;
}Book;

struct _treeB{
    Book *data;
    int height;
    struct _treeB *right;
    struct _treeB *left;
};
typedef struct _treeB Node;

#endif