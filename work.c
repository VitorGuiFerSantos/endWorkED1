#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "TAD.h"
#include "AVL_B.h"
#include "AVL_U.h"
#include "loan.h"



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
