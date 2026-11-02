#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct{
    int valor; 
    int level;
}dado;
struct _leTre{
    dado *data;
    struct _leTre *left; //menores 
    struct _leTre *right;   // maiores
};

typedef struct _leTre node;

int height(node *root){
    if(root == NULL){
        return 0;
    }
    return root-> data -> level;
}
int getBalance(node *root){
    if(root == NULL){
        return 0;
    }
    return height(root -> left) - height(root -> right);
}
int max(int a, int b){
    return a > b ? a : b;
}
//move os três nos seguidos da esquerda(os menores) e balenceia
/* 
        |a| -> |b| -> |c|
        |c| <- |b| -> |a|
*/
node *rotateLL(node *root){
    // x =|c|<-|b| root = |a| -> |b| -> |c|
    node *x = root -> left;
    // |a| = b->|...|
    root -> left = x->right;
    //   |b|-> = |a| ->... 
    x -> right = root;
    // ...<-|c| <- |b| -> |a| ->....
    root ->data ->level = 1 + max(height(root-> left) ,height(root-> right));
    x ->data ->level = 1 + max(height(x-> left) , height(x-> right));
    return x;
}
node *rotateRR(node *root){
    // x =|c|<-|b| root = |a| -> |b| -> |c|
    node *x = root -> right;
    // |a| = b->|...|
    root -> right = x->left;
    //   |b|-> = |a| ->... 
    x -> left = root;
    // ...<-|c| <- |b| -> |a| ->....
    root ->data ->level = 1 + max(height(root-> left), height(root-> right));
    x ->data ->level = 1 + max(height(x-> left), height(x-> right));
    return x;
}
node *createElemnt(int valor){
    node *new = malloc( sizeof( node));
    dado *newdata = malloc( sizeof( dado));
    newdata -> valor = valor;
    newdata -> level = 0;
    new -> data = newdata;
    new -> left = NULL;
    new -> right = NULL;
    return new;
}
node *insertAVL(node *root, node *new){
    if(root == NULL){
        return new;
    }
    if(root->data->valor > new->data->valor){
        root->right = insertAVL(root->right,new);
    }else{
        if(root ->data->valor < new->data->valor){
            root->left = insertAVL(root->left,new);
        }else{
            return root;
        }
    }
    root ->data ->level =  1 + max(height(root-> left), height(root-> right));
    int fb = getBalance(root);
    if(fb > 1 && new->data->valor < root->left->data->valor){
       return rotateLL(root);
    }
    if(fb < -1 && new->data->valor > root->right->data->valor){
        return rotateRR(root);
    }
    if(fb > 1 && new->data->valor > root->left->data->valor){
        root -> left = rotateRR(root->left);
        return rotateLL(root);
    }
    if(fb < -1 && new->data->valor < root->right->data->valor){
        root -> left = rotateLL(root->right);
        return rotateRR(root);
    }
    return root;
}
void printTree(node *aux){
    if(aux==NULL){
        return;
    }
    printTree(aux->left);
    printf("|%d| ", aux -> data -> valor);
    printTree(aux->right);
}
void printTreeLe(node *aux){
    if(aux==NULL){
        return;
    }
    
    printTreeLe(aux->left);
    printf("| %d |", aux -> data -> level);
    printTreeLe(aux->right);
}
int main(){
    node *root = NULL;
    root = insertAVL(root,createElemnt(30));
    root = insertAVL(root,createElemnt(90));
    root = insertAVL(root,createElemnt(20));
    root = insertAVL(root,createElemnt(80));
    root = insertAVL(root,createElemnt(16));
    root = insertAVL(root,createElemnt(50));
    root = insertAVL(root,createElemnt(60));
    root = insertAVL(root,createElemnt(10));
    root = insertAVL(root,createElemnt(40));
    root = insertAVL(root,createElemnt(50));

/*     root = deligth(root,20);
 */
    printTreeLe(root);
    printf("\n \n");
    printTree(root);
    printf("\n \n");
    return 0;
}