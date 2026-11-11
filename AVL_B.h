#ifndef AVLB_H
#define AVLB_H
#include "TAD.h"
#include "listEnB.h"
#include "listEnU.h"
#include <inttypes.h>
int heightBook(treeBook* root){
    if(root == NULL){
        return 0;
    }
    return root->height;
}

int getBalanceBook(treeBook* root){
    if(root == NULL){
        return 0;
    }
    return heightBook(root -> left) - heightBook(root -> right);
}

//rotate
treeBook* rotateRightB(treeBook* root){
    //the treeBook take on the root
    treeBook* aux = root -> left;
    //warden the right son aux
    treeBook* temp = aux->right;
    
    aux -> right = root;
    root -> left = temp;
    
    //recalculate the son heights
    root->height = 1 + max( heightBook(root -> left), heightBook(root -> right) );
    aux->height = 1 + max( heightBook(aux -> left), heightBook(aux -> right) );
    
    //aux take on the roles father thas subtree
    return aux;
}

treeBook* rotateLeftB(treeBook* root){

    treeBook* aux = root->right;
    treeBook* temp = aux->left;
    
    aux -> left = root;
    root -> right = temp;
    
    root->height = 1 + max( heightBook(root -> left), heightBook(root -> right) );
    aux->height = 1 + max( heightBook(aux -> left), heightBook(aux -> right) );
    
    return aux;
}
//Condition for AVL both for insertion or deletion
treeBook* balanceBook(treeBook* root){
    int fb = getBalanceBook(root);
    //1°case
    if(fb > 1 && getBalanceBook(root -> left) >= 0){
        return rotateRightB(root);
    }
    //2°case
    if(fb < -1 && getBalanceBook(root -> right)<=0){
        return rotateLeftB(root);
    }
    //3°case
    if(fb > 1 && getBalanceBook(root -> left) < 0){
        root -> left = rotateLeftB(root ->left);
        return rotateRightB(root);
    }
    //4°case 
    if(fb <- 1 && getBalanceBook(root -> right)>0){
        root -> right = rotateRightB( root -> right);
        return rotateLeftB(root);
    }
    return root;
}
//return one copy
treeBook* searchCopyBook(treeBook* rootB,char title[]){
    if(rootB == NULL){
        return NULL;
    }
    treeBook* aux1 = NULL, *aux = NULL;
    int com = strcmp(rootB -> data ->title, title);
    if(com == 0){
       return rootB;
    }
    aux1 = searchCopyBook(rootB -> right,title);
    
    if(aux1 != NULL)
    return aux1;

    aux = searchCopyBook(rootB -> left,title);

    return aux;
}

treeBook *creatBook(uint64_t id){
    Book *newdata = malloc( sizeof ( Book ) );
    treeBook *new = malloc( sizeof ( treeBook ) );
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("\n Nome do livro: ");
    fgets(newdata -> title,MAXchar-1,stdin); 
    newdata -> title[strcspn(newdata ->title,"\n") ]= 0;
    
    printf("\n Autor do livro: ");
    fgets(newdata -> author,MAXchar-1,stdin); 
    newdata -> author[strcspn(newdata ->author,"\n") ]= 0;
    printf("\n Ano de publicação do livro: ");
    scanf("%d",&newdata -> year); 
    
    printf("\n Quantidade de copias do livro: ");
    scanf("%d",&newdata -> amount);

    newdata -> id = id;
    newdata -> amountLent = 0;

    new -> data = newdata;
    new -> height = 1;
    new -> left = NULL;
    new -> right = NULL;
    //cop of user with the books
    new->wardenU = creatWardenUser();;
    
    return new;
 }
 
 //new books in the arbor
 treeBook *addBook(treeBook *root, treeBook *new){
   if(root == NULL){
       return new;
   }
   int id1 = root -> data -> id, id2 = new -> data -> id; 
   if(id1  < id2){
       root -> right = addBook(root -> right, new);
   }else if(id1 > id2){
           root -> left = addBook(root -> left, new);
       }else{
           return root;
       }

   root -> height = 1 + max( heightBook( root -> left), heightBook( root -> right)); 
   
  return root = balanceBook(root);
}

//delete elements of arbor
treeBook *deleteBook(treeBook *root, int id){
   if(root == NULL){
       return root;
   }
   int id1 = root -> data -> id; 
   if(id1  < id){
       root -> right = deleteBook(root -> right, id);
   }else{
       if(id1  > id){
           root -> left = deleteBook(root -> left, id);
       }
   }
   if(id1 == id){
       if(root -> left == NULL){
           treeBook *aux = root -> right;
           free(root->data);
           free(root);
           return aux;
       }
       if(root -> right == NULL){
           treeBook *aux = root -> left;
           free(root->data);
           free(root);
           return aux;
       }
       treeBook *aux = root -> right;
       for(; aux ->left!= NULL; aux = aux ->left){}
       Book* data;
       data = root ->data;
       root ->data = aux -> data;
       aux ->data = data;
       root ->right= deleteBook(root -> right, aux ->data -> id);
   }
   
   root -> height = 1 + max( heightBook( root -> left), heightBook( root -> right)); 
   
   return root = balanceBook(root); 
}


void printTreeBook(treeBook* nodo){
    if(nodo == NULL) return;

    printf("\n\t\t|ID: %" PRIu64 "\t\t\t\t|",nodo ->data -> id);
    printf("\n\t\t|Título: %s\t\t\t\t|",nodo ->data -> title);
    printf("\n\t\t|Autor: %s\t\t\t\t|",nodo ->data -> author);
    printf("\n\t\t|Ano de publicação: %d\t\t|",nodo ->data -> year);
    printf("\n\t\t|Cópias: %d\t\t\t\t|",nodo ->data -> amount);
    printf("\n\t\t|Copias retiradas: %d\t\t\t|\n",nodo ->data -> amountLent);
}
//search id and return one copy
treeBook* searchIdBook(treeBook* rootB, uint64_t id){
    if(rootB == NULL){
        return NULL;
    }
    if(rootB -> data -> id == id){
        return rootB;
    }
    if(rootB -> data -> id < id){
        return searchIdBook(rootB -> right, id );
    }else{
       return searchIdBook(rootB -> left, id );
    }
}

//return all the books of author
void searchAuthorBook(treeBook* rootB,char author[],bool* cond){
    if(rootB == NULL){
        return;
    }
    if(strcmp(rootB -> data ->author, author) == 0){
        printTreeBook(rootB);
        *cond = true;
    }
    searchAuthorBook(rootB->left,author,cond);
    searchAuthorBook(rootB->right,author,cond);
}

//print of all the books
void inOrderB(treeBook *aux){
    if(aux == NULL){
        return;
    }
    inOrderB(aux -> left);
    printTreeBook(aux);
    inOrderB(aux -> right);
}
#endif