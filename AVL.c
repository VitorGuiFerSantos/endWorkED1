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

int heightBook(node *root){
    if(root == NULL){
        return 0;
    }
    return root-> data -> level;
}
int getBalance(node *root){
    if(root == NULL){
        return 0;
    }
    return heightBook(root -> left) - heightBook(root -> right);
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
    node *aux = root -> left;
    node *temp = aux -> right;

    aux -> right  = root;
    root->left = temp;

    root -> data -> level = 1 + max(heightBook(root->right),heightBook(root->left));
    aux -> data -> level = 1 + max(heightBook(aux->right),height(aux->left));
    
    return aux;
}
node *rotateRR(node *root){
    node *aux = root -> right;
    node *temp = aux -> left;

    aux -> left  = root;
    root->right = temp;

    root -> data -> level = 1 + max(heightBook(root->right),heightBook(root->left));
    aux -> data -> level = 1 + max(heightBook(aux->right),heightBook(aux->left));

    return aux;
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
        root->left = insertAVL(root->left,new);
    }else{
        if(root ->data->valor < new->data->valor){
            root->right = insertAVL(root->right,new);
        }else{
            return root;
        }
    }

    root ->data ->level =  1 + max(heightBook(root-> left), heightBook(root-> right));

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
node *delite(node *root, int ind){
    if(root == NULL){
        return root;
    }
    if(root->data->valor > ind){
        root ->left = delite(root ->left,ind);
    }else{
        if(root->data->valor < ind){
            root -> right = delite(root -> right,ind);
        }
    }
    if(root -> data ->valor == ind){
        if(root->left == NULL){
            node *aux = root->right;
            free(root->data);
            free(root);
            return aux;
        }
        if(root->right == NULL){
            node *aux = root->left;
            free(root->data);
            free(root);
            return aux;
        }
        node *aux = root->right;
        for(;aux->left !=NULL;aux = aux -> left){};
        root ->data ->valor = aux -> data -> valor;
        root->right = delite(root->right, aux -> data ->valor);
    }
    root ->data ->level =  1 + max(heightBook(root-> left), heightBook(root-> right));

    int fb = getBalance(root);
    
    if(fb > 1 && getBalance(root->left)>=0){
       return rotateLL(root);
    }
    if(fb > 1 && getBalance(root->left) < 0){
        root -> left = rotateRR(root->left);
        return rotateLL(root);
    }
    if(fb < -1 && getBalance(root->right) <= 0){
        return rotateRR(root);
    }
    if(fb < -1 && getBalance(root->right) > 0){
        root -> right = rotateLL(root->right);
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
    root = insertAVL(root,createElemnt(49));
    printTreeLe(root);
    printf("\n \n");
    printTree(root);
    printf("\n \n");
    
    root = delite(root,20);

    printTreeLe(root);
    printf("\n \n");
    printTree(root);
    printf("\n \n");
    return 0;
}