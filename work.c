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
    struct _treeB *right;
    struct _treeB *left;
};
typedef struct _treeB Node;
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

    // função que define que todos os livros estão diponível
    memset(newdata -> status, false, sizeof(newdata -> status)); 

    new -> data = newdata;
    new -> height = 1;
    new -> left = NULL;
    new -> right = NULL;
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
    (*n++);
    return *ref - *n;
}
// função que configura a altura do nó
int height(Node* root){
    if(root == NULL){
        return 0;
    }
    return root->height;
}
int max(int a,int b){
    return a > b ? a : b;
}
//função que garante que a árvore sempre fique balaceada
int getBalance(Node* root){
    if(root == NULL){
        return 0;
    }
    return height(root -> left) - height(root -> right);
}
//rotate left for right
Node* rotateRR(Node* root){
    //the node take on the root
    Node* aux = root->left;
    //warden the right son aux
    Node* temp = aux->right;
    
    // root tack on the position of right son
    aux -> right = root;
    //how the left son take your position he taje on the right son of aux
    root -> left = temp;
    
    //recalculate the son heights
    root->height = 1 + max( height(root -> left), height(root -> right) );
    aux->height = 1 + max( height(aux -> left), height(aux -> right) );
    
    //aux take on the roles father thas subtree
    return aux;
}
//rotate right for left
Node* rotateLL(Node* root){

    //the node take on the root
    Node* aux = root->right;
    //warden the left son aux
    Node* temp = aux->left;
    
    // root tack on the position of left son
    aux -> left = root;
    //how the right son take your position he taje on the left son of aux
    root -> right = temp;
    
    //recalculate the son heights
    root->height = 1 + max( height(root -> left), height(root -> right) );
    aux->height = 1 + max( height(aux -> left), height(aux -> right) );
    
    //aux take on the roles father thas subtree
    return aux;
}
//AVL insertion
Node* inBalance( Node* root, Node* new){
    int fb = getBalance(root);
    // 1° case right-right: change the element for left 
    if( fb < -1 && new -> data -> id > root -> right -> data -> id){
        return rotateLL(root);
    }
    //2° case left-left change the element for right
    if(fb > 1 && new -> data -> id < root -> left -> data -> id){
        return rotateRR(root);
    }
    //3° case right-left: change the element for right to become right-right and treat how 1° case 
    if(fb < -1 && new -> data -> id < root -> right -> data -> id){
        root -> right = rotateRR(root -> right);
        return rotateLL(root);
    }
    //4° case left-right change the element for left to become(para tornar) left-left and treat how 2° case
    if(fb > 1 && new -> data -> id > root -> left -> data -> id){
        root -> left = rotateLL(root -> left);
        return rotateRR(root);
    }
    
    return root;
}
Node* deBalance(Node* root){
    int fb = getBalance(root);
    //1°case
    if(fb > 1){
        
    }
    //2°case
    if(fb < -1){
        
    }
    //3°case
    if(fb > 1){
        
    }
    //4°case 
    if(fb <- 1){
        
    }
    return root;
}
 //add elements in the tree in a banlance
  Node *addTree(Node *root, Node *new){
    if(root == NULL){
        return new;
    }
    if(root -> data -> id > new -> data -> id){
        root -> left = addTree(root -> left, new);
    }else{
        if(root -> data -> id < new -> data -> id){
            root -> right = addTree(root -> right, new);
        }else{
            return root;
        }
    }
    root -> height = 1 + max( height( root -> left), height( root -> right)); 
    
   return root = inBalance(root,new);

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
        root ->data = aux -> data;
        root ->right= deleteElemnt(root -> right, aux -> data -> id);
    }
    
    root -> height = 1 + max( height( root -> left), height( root -> right)); 
    
    int  balanc = getBalance( root);
    
    return root;
 }
 void inOrder(Node *aux){
    if(aux == NULL){
        return;
    }
    inOrder(aux -> left);
printf("ID: %lu | Altura: %d | FB: %d\n", aux->data->id, aux->height, getBalance(aux));
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
    uint64_t ref = 4294967296, idP = 1,ipN = 0, ID, control = 0;
    Node *root = malloc( sizeof (Node));
    root = NULL;
    root = addTree(root, createElemnt("paz"," paz", 2006,4,2));
    root = addTree(root, createElemnt("paz"," paz", 2006,4,3));
    root = addTree(root, createElemnt("paz"," paz", 2006,4,8));
    root = addTree(root, createElemnt("paz"," paz", 2006,4,6));
    root = addTree(root, createElemnt("paz"," paz", 2006,4,7));
    root = addTree(root, createElemnt("paz"," paz", 2006,4,5));
    root = addTree(root, createElemnt("paz"," paz", 2006,4,4));
    root = addTree(root, createElemnt("paz"," paz", 2006,4,1));
    root = addTree(root, createElemnt("paz"," paz", 2006,4,9));
    root = addTree(root, createElemnt("paz"," paz", 2006,4,10));

    inOrder(root);
    printf("\n");
/*     printTreeHeight(root); */
    return 0;
}