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
    struct _leTre *right;  
    struct _leTre *left;  
};

typedef struct _leTre node;

int height(node* root){
    if(root == NULL){
        return 0;
    }
    return root -> data -> level;
}
int getBalance(node *root){
    if(root == NULL){
        return 0;
    }
    return height(root->left) - height(root->right);

}

int max(int x, int y){
    return x > y ? x : y;
}

node *rotateRR(node *root){
    node *aux = root -> right;
    node *temp = aux -> left;

    aux -> left  = root;
    root->right = temp;

    root -> data -> level = 1 + max(height(root->right),height(root->left));
    aux -> data -> level = 1 + max(height(aux->right),height(aux->left));

    return aux;
}

node *rotateLL(node *root){
    node *aux = root -> left;
    node *temp = aux -> right;

    aux -> right  = root;
    root->left = temp;

    root -> data -> level = 1 + max(height(root->right),height(root->left));
    aux -> data -> level = 1 + max(height(aux->right),height(aux->left));
    

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
node *createTree(node *root, node *new){
    if(root == NULL){
        return new;
    }
    if(root->data->valor > new->data->valor){
        root->left = createTree(root->left,new);
    }
    else{
        if(root->data->valor < new->data->valor){
            root->right = createTree(root->right,new);
        }else{
            return root;
        }
    }
     root -> data ->level = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);
    if(balance > 1 && new ->data->valor < root -> left->data->valor){
        return rotateLL(root);
    }
    if(balance < -1 && new ->data->valor > root -> right->data->valor){
        return rotateRR(root);
    }
    if(balance > 1 && new ->data->valor > root -> left->data->valor){
        root ->left = rotateRR(root -> left);
        return rotateLL(root);
    }
        if(balance < -1 && new ->data->valor < root -> right->data->valor){
        root ->left = rotateLL(root -> right);
        return rotateRR(root);
    }


    return root;
}
/* antes do AVL tree
 node *createTree(node *root, node *new){
    if(root == NULL){
        return new;
    }
    if(root->data->valor > new->data->valor){
        root->left = createTree(root->left,new);
    }
    else{
        root->right = createTree(root->right,new);
    }
    int haltleft = (root -> left != NULL ? root->left->data->level : 0);
    int haltright = (root -> right != NULL ? root->right->data->level : 0);
    root ->data ->level = (haltleft > haltright? haltleft : haltright)+1;
    return root;
} */
node *deligth(node *root, int ind){
    if(root == NULL){
        return root;
    } 
    if(root->data->valor < ind){
        root ->right = deligth(root->right,ind);
    }else{
        if(root->data->valor > ind){
            root ->left = deligth(root->left,ind);
        }
    }
    if(root -> data -> valor== ind){
        if(root -> left == NULL){
            node *aux = root -> right;
            free(root -> data);
            free(root);
            return aux;
        }else{
            if(root -> right == NULL){
                node *aux = root -> left;
                free(root -> data);
                free(root);
                return aux;
            }
        }
        node *aux = root ->right;
        for(;aux->left!=NULL;aux = aux->left){}
        root -> data ->valor = aux ->data ->valor;
        root ->right = deligth(root ->right, aux->data->valor);
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
    root = createTree(root,createElemnt(30));
    root = createTree(root,createElemnt(90));
    root = createTree(root,createElemnt(20));
    root = createTree(root,createElemnt(80));
    root = createTree(root,createElemnt(16));
    root = createTree(root,createElemnt(50));
    root = createTree(root,createElemnt(60));
    root = createTree(root,createElemnt(10));
    root = createTree(root,createElemnt(40));
    root = createTree(root,createElemnt(50));

    root = deligth(root,20);

    printTreeLe(root);
    printf("\n \n");
    printTree(root);
    printf("\n \n");
    return 0;
}