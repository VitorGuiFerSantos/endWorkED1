#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "TAD.h"
//setting of weight
int heightBook(treeBook* root){
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

//Balance tree
int getBalanceBook(treeBook* root){
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

userTree* rotateRightU(userTree* root){
    userTree* aux = root -> left;
    userTree* temp = aux -> right; 

    aux -> right = root;
    root -> left = temp;
    
    root -> height = 1 + max(heightUser(root -> left), heightUser(root -> right));
    aux -> height = 1 + max(heightUser(aux -> left), heightUser(aux -> right));
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

userTree* rotateLeftU(userTree* root){
    userTree* aux = root -> right;
    userTree* temp = aux -> left; 

    aux -> left = root;
    root -> right = temp;

    root -> height = 1 + max(heightUser(root -> left), heightUser(root -> right));
    aux -> height = 1 + max(heightUser(aux -> left), heightUser(aux -> right));
    
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

//create ID for book
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
void printTreeBook(treeBook* nodo){
    if(nodo == NULL) return;

    printf("\n\t\t|ID: %ld\t\t\t\t|",nodo ->data -> id);
    printf("\n\t\t|Título: %s\t\t\t\t|",nodo ->data -> title);
    printf("\n\t\t|Autor: %s\t\t\t\t|",nodo ->data -> author);
    printf("\n\t\t|Ano de publicação: %d\t\t|",nodo ->data -> year);
    printf("\n\t\t|Cópias: %d\t\t\t\t|",nodo ->data -> amount);
    printf("\n\t\t|Copias retiradas: %d\t\t\t|\n",nodo ->data -> amountLent);
}

void printTreeUser(userTree* nodo){
    if(nodo == NULL) return;

    printf("\n|Nome: %s\t\t|",nodo ->data -> member);
    printf("\n|E-mail: %s\t|\n",nodo ->data -> gmail);
}

//busca o usuario
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
void inOrderB(treeBook *aux){
    if(aux == NULL){
        return;
    }
    inOrderB(aux -> left);
    printTreeBook(aux);
    inOrderB(aux -> right);
}
void inOrderU(userTree *aux){
    if(aux == NULL){
        return;
    }
    inOrderU(aux -> left);
    printTreeUser(aux);
    inOrderU(aux -> right);
}



int main(){
    //control ID
    int c;
    uint64_t ref = 4294967296, idP = 1,ipN = 0, control = 0;
    treeBook* rootBook = NULL;
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
        printf("\nEscolha uma opção:  ");
        scanf("%d", &opc);
        if(opc == 1){
            printf("\n\n\t\t+-------------Opções de Cadastro----------------+\n\t\t|\t\t\t\t\t\t|\n");
            printf("\t\t|\t\t( 1 ) . Livros \U0001F4DA\t\t|\n\t\t|\t\t\t\t\t\t|\n");
            printf("\t\t|\t\t( 2 ) . Usuários \xF0\x9F\x91\xA4 \t\t|\n\t\t|\t\t\t\t\t\t|\n");
            printf("\t\t|\t\t( 0 ) . Voltar \u21A9\t\t|");
            printf("\n\t\t+-----------------------------------------------+\n\n");
            printf("\nEscolha uma opção:  ");
            scanf("%d", &op_cad);
            if(op_cad == 1){
                treeBook* newBook = creatBook(newID(&ref,&idP,&ipN,&control)), *temp;
                temp = searchCopyBook(rootBook,newBook ->data ->title);
                if(temp == NULL){
                    rootBook = addBook(rootBook,newBook);
                    printf("\n\t\tLivro cadastrado com êxito!\n");
                    continue;
                }else{
                    int escolha = 0;
                    printf("\n\tEsse livro já existe no acervo!\n\n\tDeseja adicionar uma cópia deste livro?\n");
                    printf("\n\t\t| 1 | . Sim\n");
                    printf("\n\t\t| 2 | . Não\n");
                    printf("\n\t\t| 0 | . Menu principal\n");
                    printf("\n\t\t Qual opção deseja?  ");
                    scanf("%d",&escolha);
                    if( escolha == 1){
                        temp ->data ->amount++;
                        printf("\nLivro adicionado com êxito!\n");
                    }else if(escolha == 2){
                        sprintf(newBook -> data ->title + strlen(newBook -> data ->title), "-%ld", newBook ->data ->id );
                        rootBook = addBook(rootBook,newBook);
                        printf("\nLivro cadastrado com êxito!\n");
                        continue;
                    }
                    free(newBook ->data);
                    free(newBook ->wardenU);
                    free(newBook);
                }
                continue;
            }
            if(op_cad == 2){
                userTree *newUser = creatUser(rootUser);
                if(newUser != NULL){
                    rootUser = addUser(rootUser,newUser);
                }
                continue;
            }
        }else if(opc == 2){
            int escolha1 = 0,escolha2 = 0;
            bool cond = false; 
            treeBook* tempoB = NULL;
            userTree* tempoU = NULL;
                printf("\n\n\t\t+-------------Opções-de-Consulta----------------+\n\t\t|\t\t\t\t\t\t|\n");
                printf("\t\t|\t\t( 1 ) . Livros \U0001F4DA\t\t|\n\t\t|\t\t\t\t\t\t|\n");
                printf("\t\t|\t\t( 2 ) . Usuários \xF0\x9F\x91\xA4 \t\t|\n\t\t|\t\t\t\t\t\t|\n");
                printf("\t\t|\t\t( 0 ) . Voltar \u21A9\t\t|");
                printf("\n\t\t+-----------------------------------------------+\n\n");
                printf("\nEscolha uma opção:  ");
                scanf("%d", &escolha1);
                if(escolha1 == 1){
                    printf("\n\n\t\t+---------Opções-de-Consulta-do-livro-----------+\n\t\t|\t\t\t\t\t\t|\n");
                    printf("\t\t|\t\t( 1 ) . Código \U0001F522\t\t|\n\t\t|\t\t\t\t\t\t|\n");
                    printf("\t\t|\t\t( 2 ) . Autor \xF0\x9F\x91\xA4 \t\t|\n\t\t|\t\t\t\t\t\t|\n");
                    printf("\t\t|\t\t( 3 ) . Empréstimos \U0001F4D6 \t\t|\n\t\t|\t\t\t\t\t\t|\n");
                    printf("\t\t|\t\t( 4 ) . Todo o registro \U0001F4DA\t|\n\t\t|\t\t\t\t\t\t|\n");
                    printf("\t\t|\t\t( 0 ) . Voltar \u21A9\t\t|");
                    printf("\n\t\t+-----------------------------------------------+\n\n");
                    printf("\nEscolha uma opção:  ");
                    scanf("%d", &escolha2);
                    if(escolha2 == 1){
                        uint64_t cod;
                        printf("\n\t\tDigite o código do livro:  ");
                        scanf("%ld", & cod); 
                        tempoB = searchIdBook(rootBook,cod);
                        if(tempoB == NULL){
                            printf("\n|\t Livro não encontrado \t|\n");
                        }
                        printTreeBook(tempoB);
                    }else if(escolha2 == 2){

                        while ((c = getchar()) != '\n' && c != EOF);                    
                        char author[MAXchar];
                        printf("\n\t\tDigite o autor dos livros:  ");
                        fgets(author,MAXchar-1,stdin); 
                        author[strcspn(author, "\n")] = '\0';

                        printf("\n\t\t+---------------------------------------+\n");
                        searchAuthorBook(rootBook,author,&cond);
                        if(cond == false){
                            printf("Não foi possível encontrar livros\n");
                            printf("desse autor!");
                        }
                        printf("\n\t\t+---------------------------------------+\n");

                    }else if(escolha2 == 3){ 

                        uint64_t cod;
                        printf("\n\t\tDigite o código do livro:  ");
                        scanf("%ld", & cod);
                        tempoB = searchIdBook(rootBook,cod);
                        if(tempoB == NULL){
                            printf("\n|\t Livro não encontrado! \t|\n");
                        }else{
                            printWDogUser(tempoB -> wardenU);
                        }
                    }else if(escolha2 == 4){
                        inOrderB(rootBook);
                            //printa todos os livros
                    }
                }else if(escolha1 == 2){
                        printf("\n\n\t\t+---------Opções-de-Consulta-do-Usuário---------+\n\t\t|\t\t\t\t\t\t|\n");
                        printf("\t\t|\t\t( 1 ) . E-mail \u2709\uFE0F\t\t|\n\t\t|\t\t\t\t\t\t|\n");
                        printf("\t\t|\t\t( 2 ) . Nome \U0001FAAA \t\t|\n\t\t|\t\t\t\t\t\t\t|\n");
                        printf("\t\t|\t\t( 3 ) . Empréstimos \U0001F4D6 \t\t|\n\t\t|\t\t\t\t\t\t|\n");
                        printf("\t\t|\t\t( 4 ) . Todo o registro \U0001F4DA\t|\n\t\t|\t\t\t\t\t\t|\n");
                        printf("\t\t|\t\t( 0 ) . Voltar \u21A9\t\t|");
                        printf("\n\t\t+-----------------------------------------------+\n\n");
                        printf("\nEscolha a opção uma opção:  ");
                        scanf("%d", &escolha2);
                        if(escolha2 == 1){

                            while ((c = getchar()) != '\n' && c != EOF);
                            char gmail[MAXchar];
                            printf("\n\t\t E-mail do usuário: :  ");
                            fgets(gmail,MAXchar-1,stdin);
                            tempoU = searchCopyUser(rootUser,gmail);
                            gmail[strcspn(gmail, "\n")] = '\0';

                            if(tempoU == NULL){
                                printf("\nUsuário não encontrado!\n");
                            }else{
                                printTreeUser(tempoU);
                            }

                        }else if(escolha2 == 2){

                            char member[MAXchar];
                            while ((c = getchar()) != '\n' && c != EOF);
                            printf("\n\t\t Nome do usuário:  ");
                            fgets(member,MAXchar-1,stdin); 
                            member[strcspn(member, "\n")] = '\0';

                            bool cond = false;
                            searchNameUser(rootUser,member,&cond);

                            if(cond == false){
                                printf("\nUsuário não encontrado!\n");
                            }
                        }else if(escolha2 == 3){

                            while ((c = getchar()) != '\n' && c != EOF);
                            char gmail[MAXchar];
                            printf("\n\t\t E-mail do usuário com os livros:  ");
                            fgets(gmail,MAXchar-1,stdin); 
                            gmail[strcspn(gmail, "\n")] = '\0';
                            tempoU = searchCopyUser(rootUser,gmail);

                            if(tempoU == NULL){
                                printf("\nUsuário não encontrado!\n");
                            }else{
                                printWDogBook(tempoU ->wardenB);
                            }
                        }else if(escolha2 == 4){
                            inOrderU(rootUser);
                        }
                }
            }
        
    }

    return 0;
}
