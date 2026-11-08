#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "TAD.h"


Node *createElemnt(char title[], char author[], int year, int amount, uint64_t id){
    Book *newdata = malloc( sizeof ( Book ) );
    Node *new = malloc( sizeof ( Node ) );

    newdata -> id = id;
    newdata -> year = year; 
    //quantity book
    newdata -> amount = amount;
    //none lent
    newdata -> amountLent = 0;

    strcpy( newdata -> author,author); 
    strcpy( newdata -> title,title); 

    
    new -> data = newdata;
    new -> height = 1;
    new -> left = NULL;
    new -> right = NULL;
    //guarda o endereço dos usuários que estão com o livro
    new -> wardenU = creatWardenBook(); 
    
    return new;
 }
 
//função ID
uint64_t newID(uint64_t* ref, uint64_t* p ,uint64_t* n, uint64_t* cont){
    if( *cont % 2 == 0 || *n == *ref){
        (*cont)++;
        (*p)++;
        return *ref + *p;
    }
    (*cont)++;
    (*n)++;
    return *ref - *n;
}
// função que configura a altura do nó
int heightBook(Node* root){
    if(root == NULL){
        return 0;
    }
    return root->height;
}
int max(int a,int b){
    return a > b ? a : b;
}
//função que garante que a árvore sempre fique balaceada
int getBalanceBook(Node* root){
    if(root == NULL){
        return 0;
    }
    return heightBook(root -> left) - heightBook(root -> right);
}
//rotate left for right
Node* rotateRight(Node* root){
    //the node take on the root
    Node* aux = root -> left;
    //warden the right son aux
    Node* temp = aux->right;
    
    // root tack on the position of right son
    aux -> right = root;
    //how the left son take your position he taje on the right son of aux
    root -> left = temp;
    
    //recalculate the son heights
    root->height = 1 + max( heightBook(root -> left), heightBook(root -> right) );
    aux->height = 1 + max( heightBook(aux -> left), heightBook(aux -> right) );
    
    //aux take on the roles father thas subtree
    return aux;
}
//rotate right for left
Node* rotateLeft(Node* root){

    //the node take on the root
    Node* aux = root->right;
    //warden the left son aux
    Node* temp = aux->left;
    
    // root tack on the position of left son
    aux -> left = root;
    //how the right son take your position he taje on the left son of aux
    root -> right = temp;
    
    //recalculate the son heights
    root->height = 1 + max( heightBook(root -> left), heightBook(root -> right) );
    aux->height = 1 + max( heightBook(aux -> left), heightBook(aux -> right) );
    
    //aux take on the roles father thas subtree
    return aux;
}
//AVL insertion

Node* balanceBook(Node* root){
    int fb = getBalanceBook(root);
    //1°case
    if(fb > 1 && getBalanceBook(root -> left) >= 0){
        return rotateRight(root);
    }
    //2°case
    if(fb < -1 && getBalanceBook(root -> right)<=0){
        return rotateLeft(root);
    }
    //3°case
    if(fb > 1 && getBalanceBook(root -> left) < 0){
        root -> left = rotateLeft(root ->left);
        return rotateRight(root);
    }
    //4°case 
    if(fb <- 1 && getBalanceBook(root -> right)>0){
        root -> right = rotateRight( root -> right);
        return rotateLeft(root);
    }
    return root;
}
 //add elements in the tree in a banlance
  Node *addBook(Node *root, Node *new){
    if(root == NULL){
        return new;
    }
    if(root -> data -> id > new -> data -> id){
        root -> left = addBook(root -> left, new);
    }else{
        if(root -> data -> id < new -> data -> id){
            root -> right = addBook(root -> right, new);
        }else{
            return root;
        }
    }
    root -> height = 1 + max( heightBook( root -> left), heightBook( root -> right)); 
    
   return root = balanceBook(root);

 }
 //delele the elements in the tree
 Node *deleteElemnt(Node *root, int id){
    if(root == NULL){
        return root;
    }
    if(root -> data -> id > id){
        root -> left = deleteElemnt( root-> left, id);
    }else{
        root -> right= deleteElemnt( root-> right, id);
    }
    if(root -> data -> id == id){
        if(root -> left == NULL){
            Node *aux = root -> right;
            free(root->data);
            free(root);
            return aux;
        }
        if(root -> right == NULL){
            Node *aux = root -> left;
            free(root->data);
            free(root);
            return aux;
        }
        Node *aux = root -> right;
        for(; aux ->left!= NULL; aux = aux ->left){}
        Book* data;
        data = root ->data;
        root ->data = aux -> data;
        aux ->data = data;
        root ->right= deleteElemnt(root -> right, aux -> data -> id);
    }
    
    root -> height = 1 + max( heightBook( root -> left), heightBook( root -> right)); 
    
    return root = balanceBook(root);
    
 }
 void inOrder(Node *aux){
    if(aux == NULL){
        return;
    }
    inOrder(aux -> left);
    printf("ID: %lu | Altura: %d | FB: %d\n", aux->data->id, aux->height, getBalanceBook(aux));
    inOrder(aux -> right);
 }
 void printTreeHeight(Node *aux){
    if(aux == NULL){
        return;
    }
    printTreeHeight(aux -> left);
    printf(" |%d|", aux -> height);
    printTreeHeight(aux -> right);
 }
int main(){
    //control ID
/*     uint64_t ref = 4294967296, idP = 1,ipN = 0, ID, control = 0;
    Node *root = malloc( sizeof (Node));
    root = NULL; */
    bool ever = true;
       for(;ever;){
        printf("\n\t\t+-----------------------------------------------+\n");
        printf("\t\t|\t\t( 1 ) . Cadastro \U0001F4DD\t\t|\n\t\t|\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t( 2 ) . Consulta \U0001F50D\t\t|\n\t\t|\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t( 3 ) . Atualização \U0001F504\t\t|\n\t\t|\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t( 4 ) . Exclusão \U0001F5D1\t\t|\n\t\t|\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t( 5 ) . Empréstimo \U0001F4D6\t\t|\n\t\t|\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t( 6 ) . Devolução \U0001F4DA\t\t|\n\t\t|\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t( 0 ) . Voltar \u21A9\t\t|");
        printf("\n\t\t+-----------------------------------------------+\n\n");
        usleep(1000);
        //criar um lista duplamente encadeada para colocar os ponteiros dos autores e organizar em ordem os livros
}
    
    return 0;
}