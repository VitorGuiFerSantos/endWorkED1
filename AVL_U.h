#ifndef AVLU_H
#define AVLU_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TAD.h"
int heightUser(userTree* root){
    if(root == NULL){
        return 0;
    }
    return root->height;
}

int getBalanceUser(userTree* root){
    if(root == NULL){
        return 0;
    }
    return heightUser(root -> left) - heightUser(root -> right);
}

userTree* rotateRightU(userTree* root){
    userTree* aux = root -> left;
    userTree* temp = aux -> right; 

    aux -> right = root;
    root -> left = temp;
    
    root -> height = 1 + max(heightUser(root -> left), heightUser(root -> right));
    aux -> height = 1 + max(heightUser(aux -> left), heightUser(aux -> right));
    return aux;
}

userTree* rotateLeftU(userTree* root){
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
    //1°case
    if(fb > 1  &&  balel >= 0){
        return rotateRightU(root);
    }
    //2°case
    if(fb < -1 && baler <= 0){
        return rotateLeftU(root);
    }
    //3°case
    if(fb < -1 && baler > 0){
        root -> right = rotateLeftU(root ->right);
        return rotateLeftU(root);
    }
    //4°case
    if(fb > 1 &&  balel < 0){
        root -> left = rotateRightU(root ->left);
        return rotateRightU(root);   
    }
    return root;
}

//return one user
userTree* searchCopyUser(userTree* rootU,char gmail[]){
   if(rootU == NULL){
       return NULL;
   }
   int com = strcmp(rootU -> data ->gmail, gmail);
   if(com == 0){
       return rootU;
   }
   if(com < 0){
       return searchCopyUser(rootU -> right,gmail);
   }else{
       return searchCopyUser(rootU -> left,gmail);
   }
}

userTree *creatUser(userTree* rootU){
    User* newdata = malloc( sizeof (User));
    userTree* new = malloc( sizeof (userTree));
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("\nNome do novo usuário:");
    fgets(newdata -> member,MAXchar-1,stdin); 
    newdata -> member[strcspn(newdata ->member,"\n")] = 0;

    printf("\nRegistre o e-mail do usuário:");
    fgets(newdata -> gmail,MAXchar-1,stdin); 
    newdata -> gmail[strcspn(newdata ->gmail,"\n") ] = 0;

    userTree* temp = NULL;
    temp = searchCopyUser(rootU,newdata -> gmail);
    while (temp !=NULL){
        int option = 0;
        memset(newdata -> gmail, 0, sizeof(MAXchar));
        printf("\nE-mail já cadastrado! Deseja continuar ?");
        printf("\n( 1 ) Sim");
        printf("\n( 2 ) Não");
        printf("\nQual opção: ");
        scanf("%d",&option);
        if(option == 1){
            while ((c = getchar()) != '\n' && c != EOF);
            printf("\nRegistre o e-mail do não cadastrado: ");
            fgets(newdata -> gmail,MAXchar-1,stdin); 
            newdata -> gmail[strcspn(newdata ->gmail,"\n") ]= 0;
            temp = searchCopyUser(rootU,newdata -> gmail);
        }else{
            printf("\nOperação cancelada");
            free(new);
            free(newdata);
            return NULL;
        }
    }

    new -> data =  newdata;
    new ->data-> books = 0;

    new-> height = 1;
    // cop the address books retired
    new -> wardenB = creatWardenBook();;

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
    }else if(com > 0){
            root -> left = addUser(root -> left, new);
        }else{
            return root;
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

void printTreeUser(userTree* nodo){
    if(nodo == NULL) return;

    printf("\n|Nome: %s\t\t|",nodo ->data -> member);
    printf("\n|E-mail: %s\t|\n",nodo ->data -> gmail);
    printf("\n|E-mail: %d\t|\n",nodo ->data -> books);
}

//output users  with same name 
void searchNameUser(userTree* rootB,char name[],bool* cond){
    if(rootB == NULL || *cond == true){
        return;
    }
    if(strcmp(rootB -> data ->member, name) == 0){
        printTreeUser(rootB);
        *cond = true;
        return;
    }
    searchNameUser(rootB->left,name,cond);
    if(*cond == true) {return;}
    searchNameUser(rootB->right,name,cond);
}

//print of all the users
void inOrderU(userTree *aux){
    if(aux == NULL){
        return;
    }
    inOrderU(aux -> left);
    printTreeUser(aux);
    inOrderU(aux -> right);
}

#endif