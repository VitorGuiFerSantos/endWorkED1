#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "tree.h"
int heightUser(userTree* root){
    if(root == NULL){
        return 0;
    }
    return root->height;
}
int max(int a,int b){
    return a > b ? a : b;
}
//função que garante que a árvore sempre fique balaceada
int getBalanceUser(userTree* root){
    if(root == NULL){
        return 0;
    }
    return heightUser(root -> left) - heightUser(root -> right);
}
userTree* rotateRight(userTree* root){
    userTree* aux = root -> left;
    userTree* temp = aux -> right; 

    aux -> right = root;
    root -> left = temp;
    
    root -> height = 1 + max(heightUser(root -> left), heightUser(root -> right));
    aux -> height = 1 + max(heightUser(aux -> left), heightUser(aux -> right));
    return aux;
}
userTree* rotateLeft(userTree* root){
    userTree* aux = root -> right;
    userTree* temp = aux -> left; 

    aux -> left = root;
    root -> right = temp;

    root -> height = 1 + max(heightUser(root -> left), heightUser(root -> right));
    aux -> height = 1 + max(heightUser(aux -> left), heightUser(aux -> right));
    
    return aux;
}
userTree* balanceUser(userTree *root){
    int fb = getBalanceUser(root);
    int baler = getBalanceUser(root -> left), balel = getBalanceUser(root -> right);
    //left-left
    if(fb > 1  &&  balel >= 0){
        return rotateRight(root);
    }
    //right-right
    if(fb < -1 && baler <= 0){
        return rotateLeft(root);
    }
    if(fb < -1 && baler > 0){
        root -> right = rotateLeft(root ->right);
        return rotateLeft(root);
    }
    if(fb > 1 &&  balel < 0){
        root -> left = rotateRight(root ->left);
        return rotateRight(root);   
    }
    return root;
}

userTree *creatUser(char member[],char gmail[]){
    User* newdata = malloc( sizeof (User));
    userTree* new = malloc( sizeof (userTree));
    strcpy(newdata -> member , member);
    strcpy(newdata -> gmail , gmail);
    new -> data =  newdata;
    new-> height = 1;
    new -> left = NULL;
    new -> right = NULL;

    return new;
}
userTree* addUser(userTree* root, userTree* new){
    if(root == NULL){
        return new;
    }
    int com = strcmp(root -> data ->gmail, new ->data ->gmail);
    if(com  < 0){
        root -> right = addUser(root -> right, new);
    }else{
        if(com > 0){
            root -> left = addUser(root -> left, new);
        }else{
            return root;
        }
    }
    root -> height = 1 + max( heightUser( root -> left), heightUser( root -> right)); 
    
     
    return  balanceUser(root);
    
}
userTree* deleteUser(userTree* root, char gmail[]){
    if(root == NULL){
        return NULL;
    }
    int com = strcmp(root -> data ->gmail, gmail);
    if(com  < 0){
        root -> right = deleteUser(root -> right, gmail);
    }else{
        if(com  > 0){
            root -> left = deleteUser(root -> left, gmail);
        }
    }
    if(com == 0){
        if(root -> left == NULL){
            userTree *aux = root -> right;
            free(root->data);
            free(root);
            return aux;
        }
        if(root -> right == NULL){
            userTree *aux = root -> left;
            free(root->data);
            free(root);
            return aux;
        }
        userTree *aux = root -> right;
        for(; aux ->left!= NULL; aux = aux ->left){}
        User* data;
        data = root ->data;
        root ->data = aux -> data;
        aux ->data = data;
        root ->right = deleteUser(root -> right, aux -> data ->gmail);

    }
    root -> height = 1 + max( heightUser( root -> left), heightUser( root -> right)); 

    return balanceUser(root);
    
}
void inOrder(userTree *aux){
    if(aux == NULL){
        return;
    }
    inOrder(aux -> left);
    printf("\t|Gmail: %s \t| Altura: %d |\t FB: %d|\n", aux->data->gmail, aux->height, getBalanceUser(aux));
    inOrder(aux -> right);
 }
int main(){
    userTree* userRoot = NULL;
    userRoot = addUser(userRoot, creatUser("vitor","vitorgfs10@gmail.com"));
    inOrder(userRoot);
    printf("\n");
    return 0;
}