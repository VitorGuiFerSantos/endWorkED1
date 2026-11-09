#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "TAD.h"
// função que configura a altura do nó
int heightBook(Node* root){
    if(root == NULL){
        return 0;
    }
    return root->height;
}

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
int getBalanceBook(Node* root){
    if(root == NULL){
        return 0;
    }
    return heightBook(root -> left) - heightBook(root -> right);
}

int getBalanceUser(userTree* root){
    if(root == NULL){
        return 0;
    }
    return heightUser(root -> left) - heightUser(root -> right);
}

//rotate left for right
Node* rotateRightB(Node* root){
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

userTree* rotateRightU(userTree* root){
    userTree* aux = root -> left;
    userTree* temp = aux -> right; 

    aux -> right = root;
    root -> left = temp;
    
    root -> height = 1 + max(heightUser(root -> left), heightUser(root -> right));
    aux -> height = 1 + max(heightUser(aux -> left), heightUser(aux -> right));
    return aux;
}

//rotate right for left
Node* rotateLeftB(Node* root){

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

userTree* rotateLeftU(userTree* root){
    userTree* aux = root -> right;
    userTree* temp = aux -> left; 

    aux -> left = root;
    root -> right = temp;

    root -> height = 1 + max(heightUser(root -> left), heightUser(root -> right));
    aux -> height = 1 + max(heightUser(aux -> left), heightUser(aux -> right));
    
    return aux;
}
//AVL insertion

Node* balanceBook(Node* root){
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

//função que garante que a árvore sempre fique balaceada
userTree* balanceUser(userTree *root){
    int fb = getBalanceUser(root);
    int baler = getBalanceUser(root -> left), balel = getBalanceUser(root -> right);
    //left-left
    if(fb > 1  &&  balel >= 0){
        return rotateRightU(root);
    }
    //right-right
    if(fb < -1 && baler <= 0){
        return rotateLeftU(root);
    }
    if(fb < -1 && baler > 0){
        root -> right = rotateLeftU(root ->right);
        return rotateLeftU(root);
    }
    if(fb > 1 &&  balel < 0){
        root -> left = rotateRightU(root ->left);
        return rotateRightU(root);   
    }
    return root;
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
int searchCopyUser(userTree* rootU,char gmail[]){
   if(rootU == NULL){
       return 0;
   }
   int com = strcmp(rootU -> data ->gmail, gmail);
   if(com == 0){
       return 1;
   }
   if(com < 0){
       return searchCopyUser(rootU -> right,gmail);
   }else{
       return searchCopyUser(rootU -> left,gmail);
   }
}
Node* searchCopyBook(Node* rootB,char title[]){
   if(rootB == NULL){
       return NULL;
   }
   int com = strcmp(rootB -> data ->title, title);
   if(com == 0){
       return rootB;
   }
   if(com < 0){
       return searchCopyBook(rootB -> right,title);
   }else{
       return searchCopyBook(rootB -> left,title);
   }
}
Node *creatBook(uint64_t id){
    Book *newdata = malloc( sizeof ( Book ) );
    Node *new = malloc( sizeof ( Node ) );
    printf("\n Nome do livro: ");
    scanf( "%s",newdata -> title); 
    
    printf("\n Autor do livro: ");
    scanf("%s", newdata -> author); 
    
    printf("\n Ano de publicação do livro: ");
    scanf("%d",&newdata -> year); 
    
    printf("\n Quantidade de copias do livro: ");
    scanf("%d",&newdata -> amount);

    newdata -> id = id;
    //quantity book
    //none lent
    newdata -> amountLent = 0;

    new -> data = newdata;
    new -> height = 1;
    new -> left = NULL;
    new -> right = NULL;
    //guarda o endereço dos usuários que estão com o livro
    new->wardenU = creatWardenUser();;
    
    return new;
 }
 
userTree *creatUser(userTree* rootU){
    User* newdata = malloc( sizeof (User));
    userTree* new = malloc( sizeof (userTree));
    printf("\nNome do novo usuário:");
    scanf("%s",newdata -> member);
    printf("\nRegistre seu e-mail do usuário:");
    int temp = 1;
    while (temp == 1){
        scanf("%s",newdata -> gmail);
        temp = searchCopyUser(rootU,newdata -> gmail);
        if(temp == 1){
            memset(newdata -> gmail, 0, sizeof(MAXchar));
            printf("\nE-mail já cadastrado, insira outro: ");
        }   
    }
    new -> data =  newdata;
    new-> height = 1;
    // guardo o endereço dos livros 
    WDogUser* wardenB = creatWardenBook();
    new -> wardenB = wardenB;

    new -> left = NULL;
    new -> right = NULL;

    return new;
}
//add elements in the tree in a banlance
 Node *addBook(Node *root, Node *new){
   if(root == NULL){
       return new;
   }

   int com = strcmp(root -> data ->title, new ->data ->title);
   if(com  < 0){
       root -> right = addBook(root -> right, new);
   }else{
       if(com > 0){
           root -> left = addBook(root -> left, new);
       }else{
           return root;
       }
   }
   root -> height = 1 + max( heightBook( root -> left), heightBook( root -> right)); 
   
  return root = balanceBook(root);
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
//delete elements of arbor
Node *deleteBook(Node *root, char title[]){
   if(root == NULL){
       return root;
   }
   int com = strcmp(root -> data ->title, title);
   if(com  < 0){
       root -> right = deleteBook(root -> right, title);
   }else{
       if(com  > 0){
           root -> left = deleteBook(root -> left, title);
       }
   }
   if(com == 0){
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
       root ->right= deleteBook(root -> right, aux ->data -> title);
   }
   
   root -> height = 1 + max( heightBook( root -> left), heightBook( root -> right)); 
   
   return root = balanceBook(root); 
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
void inOrderU(userTree *aux){
    if(aux == NULL){
        return;
    }
    inOrderU(aux -> left);
    printf("\t|Gmail: %s \t| Altura: %d |\t FB: %d|\n", aux->data->gmail, aux->height, getBalanceUser(aux));
    inOrderU(aux -> right);
 }

 //delele the elements in the tree
 void inOrderB(Node *aux){
    if(aux == NULL){
        return;
    }
    inOrderB(aux -> left);
    printf("ID: %lu | Altura: %d | FB: %d\n", aux->data->id, aux->height, getBalanceBook(aux));
    inOrderB(aux -> right);
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
    uint64_t ref = 4294967296, idP = 1,ipN = 0, control = 0;
    Node* rootBook = NULL;
    userTree* rootUser = NULL;
    //opções
    int opc,op_cad;
    //strings
/*     char name[MAXchar], gmail[MAXchar], title[MAXchar], author[MAXchar];
    int year,amount; */
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
        printf("\nEscolha a opção uma opção: ");
        scanf("%d", &opc);
        if(opc == 1){
            printf("\n\n\t\t+-------------Opções de Cadastro----------------+\n\t\t|\t\t\t\t\t\t|\n");
            printf("\t\t|\t\t( 1 ) . Livros \U0001F4DA\t\t|\n\t\t|\t\t\t\t\t\t|\n");
            printf("\t\t|\t\t( 2 ) . Usuários \xF0\x9F\x91\xA4 \t\t|\n\t\t|\t\t\t\t\t\t|\n");
            printf("\t\t|\t\t( 0 ) . Voltar \u21A9\t\t|");
            printf("\n\t\t+-----------------------------------------------+\n\n");
            printf("\nEscolha a opção uma opção: ");
            scanf("%d", &op_cad);
            if(op_cad == 1){
                Node* new = creatBook(newID(&ref,&idP,&ipN,&control)), *temp;
                temp = searchCopyBook(rootBook,new ->data ->title);
                if(temp == NULL){
                    rootBook = addBook(rootBook,new);
                    printf("\n\t\tLivro cadastrado com êxito!\n");
                    continue;
                }else{
                    printf("\n\tEsse livro já existe!\n\n\tDeseja adicionar uma cópia para esse livro?\n");
                    printf("\n\t\t| 1 | . Sim\n");
                    printf("\n\t\t| 2 | . Não\n");
                    printf("\n\t\t| 0 | . Menu principal\n");
                    printf("\n\t\t Qual opção deseja? ");
                    int escolha = 0;
                    scanf("%d",&escolha);
                    if( escolha == 1){
                        temp ->data ->amount++;
                        printf("\nLivro adicionado com êxito!\n");
                    }else{
                        if(escolha == 2){
                            sprintf(new -> data ->title + strlen(new -> data ->title), "-%ld", new ->data ->id );
                            rootBook = addBook(rootBook,new);
                            printf("\nLivro cadastrado com êxito!\n");
                            continue;
                        }
                    }
                    free(new ->data);
                    free(new ->wardenU);
                    free(new);
                }
                continue;
            }
            if(op_cad == 2){
                rootUser = addUser(rootUser, creatUser(rootUser));
                continue;
            }
        }else{
            if(opc == 2){
                int escolha1 = 0,escolha2 = 0;
                printf("\n\n\t\t+-------------Opções-de-Consulta----------------+\n\t\t|\t\t\t\t\t\t|\n");
                printf("\t\t|\t\t( 1 ) . Livros \U0001F4DA\t\t|\n\t\t|\t\t\t\t\t\t|\n");
                printf("\t\t|\t\t( 2 ) . Usuários \xF0\x9F\x91\xA4 \t\t|\n\t\t|\t\t\t\t\t\t|\n");
                printf("\t\t|\t\t( 3 ) . Empréstimos \U0001F4D6 \t\t|\n\t\t|\t\t\t\t\t\t|\n");
                printf("\t\t|\t\t( 0 ) . Voltar \u21A9\t\t|");
                printf("\n\t\t+-----------------------------------------------+\n\n");
                printf("\nEscolha a opção uma opção: ");
                scanf("%d", &escolha1);
                if(escolha1 == 1){
                    printf("\n\n\t\t+---------Opções-de-Consulta-do-livro-----------+\n\t\t|\t\t\t\t\t\t|\n");
                    printf("\t\t|\t\t( 1 ) . Código \U0001F522\t\t|\n\t\t|\t\t\t\t\t\t|\n");
                    printf("\t\t|\t\t( 2 ) . Autor \xF0\x9F\x91\xA4 \t\t|\n\t\t|\t\t\t\t\t\t|\n");
                    printf("\t\t|\t\t( 3 ) . Todo o registro \U0001F4DA\t|\n\t\t|\t\t\t\t\t\t|\n");
                    printf("\t\t|\t\t( 0 ) . Voltar \u21A9\t\t|");
                    printf("\n\t\t+-----------------------------------------------+\n\n");
                    printf("\nEscolha a opção uma opção: ");
                    scanf("%d", &escolha2);
                    if(escolha2 == 1){

                    }
                }
            }
        }
    }

    return 0;
}