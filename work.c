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
  node *addTree(node *root, node *new){
    if(root == NULL){
        return new;
    }
    if(root->data->id > new->data->id){
        root -> rigth = addTree(root ->rigth, new);
    }else{
        root -> left = addTree(root ->left, new);
    }
    int *hr = 0, *hl = 0 ;
    if(root -> rigth != NULL && root -> left != NULL ){
        hr =  root -> rigth -> height + 1; 
        hl =  root -> left -> height + 1;
        root -> height = (hl > hr ? hl : hr);
    }else{
        if(root -> rigth != NULL ){
            root -> height  =  root -> rigth -> height + 1; 

        }else{
            if(root -> left != NULL ){
                root -> height =  root -> left -> height + 1; 
            }
        }
    }
    return root;  
 }
 void printTree(node *aux){
    if(aux == NULL){
        return;
    }
    printTree(aux -> left);
    printf(" |%ld|\n", aux->data ->id);
    printTree(aux -> rigth);
 }
int main(){
    uint64_t id = 1;
    node *root = malloc( sizeof (node));
    root = NULL;
    root = addTree(root, createElemnt("paz"," paz", 2006,4,id));
    id++;
    root = addTree(root, createElemnt("paz"," paz", 2006,4,id));
    id++;
    root = addTree(root, createElemnt("paz"," paz", 2006,4,id));
    id++;
    root = addTree(root, createElemnt("paz"," paz", 2006,4,id));
    id++;
    root = addTree(root, createElemnt("paz"," paz", 2006,4,id));
    id++;
    printTree(root);
    return 0;
}