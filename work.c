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
    User userLent[MAXchar];
    int amount;
    int amountLent;
}Book;  
// criar uma estrutura de controle para heaps 
struct _treeB{
    Book *data;
    int height;
    struct _treeB *rigth;
    struct _treeB *left;
};
typedef struct _treeB Node;

 Node *createElemnt(char title[], char author[], int year, int amount, uint64_t id){
    Book *newdata = malloc( sizeof ( Book ) );
    Node *new = malloc( sizeof ( Node ) );
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
 //add elements in the tree
  Node *addTree(Node *root, Node *new){
    if(root == NULL){
        return new;
    }
    if(root->data->id > new->data->id){
        root -> left = addTree(root ->left, new);
    }else{
        root -> rigth = addTree(root ->rigth, new);
    }
    int hr = 0, hl = 0 ;
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
 //delele the elements in the tree
 Node *deleteElemnt(Node *root, int id){
    if(root == NULL){
        return root;
    }
    if(root -> data -> id > id){
        root -> left = deleteElemnt( root-> left, id);
    }else{
        root -> rigth = deleteElemnt( root-> rigth, id);
    }
    if(root -> data -> id == id){
        if(root -> left == NULL){
            Node *aux = root -> rigth;
            free(root->data);
            free(root);
            return aux;
        }
        if(root -> rigth == NULL){
            Node *aux = root -> left;
            free(root->data);
            free(root);
            return aux;
        }
        Node *aux = root -> rigth;
        for(; aux ->left!= NULL; aux = aux ->left){}
        root ->data = aux -> data;
        root ->rigth = deleteElemnt(root -> rigth, aux -> data -> id);
    }

    int haltleft = (root -> left != NULL ? root->left-> height : 0);
    int haltrigth = (root -> rigth != NULL ? root->rigth-> height: 0);
    root -> height = (haltleft > haltrigth? haltleft : haltrigth);
    return root;
 }
 void printTree(Node *aux){
    if(aux == NULL){
        return;
    }
    printTree(aux -> left);
    printf(" |%ld|", aux -> data->id);
    printTree(aux -> rigth);
 }
 void printTreeHeight(Node *aux){
    if(aux == NULL){
        return;
    }
    printTreeHeight(aux -> left);
    printf(" |%d|", aux -> height);
    printTreeHeight(aux -> rigth);
 }
int main(){
    uint64_t id = 1;
    Node *root = malloc( sizeof (Node));
    root = NULL;
    root = addTree(root, createElemnt("paz"," paz", 2006,4,id));
    id++;
    root = addTree(root, createElemnt("paz"," paz", 2006,4,id));
    id++;
    root = addTree(root, createElemnt("paz"," paz", 2006,4,8));
    id++;
    root = addTree(root, createElemnt("paz"," paz", 2006,4,6));
    id++;
    root = addTree(root, createElemnt("paz"," paz", 2006,4,7));
    id++;

    printTree(root);
    printf("\n");
    printTreeHeight(root);
    return 0;
}