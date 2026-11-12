#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <inttypes.h>
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
    rootBook = registerBooksFile(rootBook,"test.txt",&ref,&idP,&ipN,&control);
    rootUser = registerUsersFile(rootUser,"users.txt");
    for(;ever;){

        printf("\n\t\t +---------------------MENU----------------------+ \n");
        printf("\t\t|\t\t( 1 ) . Cadastro \U0001F4DD\t\t|\n\t\t|\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t( 2 ) . Consulta \U0001F50D\t\t|\n\t\t|\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t( 3 ) . Atualização \U0001F504\t\t|\n\t\t|\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t( 4 ) . Exclusão \U0001F5D1\t\t|\n\t\t|\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t( 5 ) . Empréstimo \U0001F4D6\t\t|\n\t\t|\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t( 6 ) . Devolução \U0001F4DA\t\t|\n\t\t|\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t( 0 ) . Voltar \u21A9\t\t|");
        printf("\n\t\t +-----------------------------------------------+ \n\n");
        usleep(1000);

        printf("\nEscolha uma opção:  ");
        scanf("%d", &opc);

        if(opc == 1){
            printf("\n\n\t\t+-------------OPÇÕES-DE-CADASTRO----------------+\n\t\t|\t\t\t\t\t\t|\n");
            printf("\t\t|\t\t( 1 ) . Livros \U0001F4DA\t\t|\n\t\t|\t\t\t\t\t\t|\n");
            printf("\t\t|\t\t( 2 ) . Usuários \xF0\x9F\x91\xA4 \t\t|\n\t\t|\t\t\t\t\t\t|\n");
            printf("\t\t|\t\t( 0 ) . Voltar \u21A9\t\t|");
            printf("\n\t\t+-----------------------------------------------+\n\n");

            printf("\nEscolha uma opção:  ");
            scanf("%d", &op_cad);

            if(op_cad == 1){
                int escolha = 0;
                treeBook* newBook = creatBook(newID(&ref,&idP,&ipN,&control)), *temp;

                temp = searchCopyBook(rootBook,newBook ->data ->title);

                if(temp == NULL){
                    rootBook = addBook(rootBook,newBook);
                    printf("\n\t\tLivro cadastrado com êxito!\n");
                    continue;
                }else{
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

                printf("\n\n\t\t+-------------OPÇÕES-DE-CONSULTA----------------+\n\t\t|\t\t\t\t\t\t|\n");
                printf("\t\t|\t\t( 1 ) . Livros \U0001F4DA\t\t|\n\t\t|\t\t\t\t\t\t|\n");
                printf("\t\t|\t\t( 2 ) . Usuários \xF0\x9F\x91\xA4 \t\t|\n\t\t|\t\t\t\t\t\t|\n");
                printf("\t\t|\t\t( 0 ) . Voltar \u21A9\t\t|");
                printf("\n\t\t+-----------------------------------------------+\n\n");

                printf("\nEscolha uma opção:  ");
                scanf("%d", &escolha1);

                if(escolha1 == 1){
                    printf("\n\n\t\t+---------OPÇÕES-DE-CONSULTA-PARA-LIVRO---------+\n\t\t|\t\t\t\t\t\t|\n");
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
                        scanf("%"SCNu64, & cod); 

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

                        searchAuthorBook(rootBook,author,&cond);

                        printf("\n\t\t+---------------------------------------+\n");
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
                        //printa todos os livros
                        inOrderB(rootBook);
                    }
                }else if(escolha1 == 2){
                        printf("\n\n\t\t+---------OPÇÕES-DE-CONSULTA-PARA-USUÁRIO-------+\n\t\t|\t\t\t\t\t\t|\n");
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
                            scanf("%s",gmail);
  
                            tempoU = searchCopyUser(rootUser,gmail);

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
                            scanf("%s",gmail);
  
                            tempoU = searchCopyUser(rootUser,gmail);

                            if(tempoU == NULL){
                                printf("\nUsuário não encontrado!\n");
                            }else{
                                printWDogBook(tempoU ->wardenB);
                            }
                        }else if(escolha2 == 4){
                            inOrderU(rootUser);
                        }
                }else if(escolha1 == 3){
                    int code = 0;
                    printf("\n\n\t\t+---------------ATUALIZAÇÃO------------------+\n\t\t|\t\t\t\t\t\t|\n");
                    printf("\n\t\t ( 1 ) Livro  ");
                    printf("\n\t\t ( 2 ) Usuário  ");
                    printf("\n\t\t ( 3 ) Renovar empréstimo");
                    printf("\n\t\t ( 0 ) voltar  ");
                    printf("\n\t\t+-----------------------------------------------+\n\n");

                    printf("\n\t\t Qual opção: ");
                    scanf("%d", &code);

                    if(code == 1){
                        uint64_t id = 0;
                        treeBook *auxBk = NULL;

                        printf("\n\t\t Insira o código do livro para alterar as informações: ");
                        scanf("%"SCNu64, &id);

                        auxBk = searchIdBook(rootBook,id);
                        j
                        if(auxBk == NULL){
                            printf("\n\t\t Livro não encontrado!");
                            return;
                        }
                        printf("\n\t\t Livro encontrado!");
                        printTreeBook(auxBk);
                        printf("\n\t\t Caso não queira alterar alguma informação, só repita a dado que já estava!");
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);

                        memset(auxBk -> data -> title, 0, sizeof(MAXchar));
                        printf("\n\t\t Nome do livro: ");
                        fgets(auxBk -> data -> title,MAXchar-1,stdin); 
                        auxBk  -> data -> title[strcspn(auxBk -> data -> title,"\n") ]= 0;

                        memset(auxBk -> data -> author, 0, sizeof(MAXchar));
                        printf("\n\t\t Autor do livro: ");
                        fgets(auxBk -> data -> author,MAXchar-1,stdin); 
                        auxBk -> data -> author[strcspn(auxBk -> data -> author,"\n") ]= 0;

                        printf("\n\t\t Ano de publicação do livro: ");
                        scanf("ld",&auxBk -> data -> year); 
                            
                        printf("\n\t\t Livro atulizado com êxito");
                        return;
                    }
                    if(code == 2){
                        char gmail[MAXchar];
                        userTree *auxUs = NULL;
                        printf("\n\t\t Insira o e-mail do usuário para alterar as informações: ");
                        scanf("%s",gmail);
                        auxUs = searchCopyUser(rootU,gmail);
                        if(auxUs == NULL){
                            printf("\n\t\t Usuário não encontrado!");
                            return;
                        }
                        printf("\n\t\t Usuário encontrado!");
                        printTreeUser(auxUs);
                        printf("\n\t\t Caso não queira alterar alguma informação, só repita a dado que já estava!");
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                        memset(auxUs -> data -> member, 0, sizeof(MAXchar));
                        fgets(auxUs ->data -> member,MAXchar-1,stdin);  
                        auxUs -> data -> member[strcspn(auxUs -> data -> member,"\n") ]= 0;

                        printf("\n\t\t Usuário atulizado com êxito");
                        return;
                    }
                    if(code == 3){
                        char gmail[MAXchar];
                        userTree *auxUs = NULL;
                        uint64_t id = 0;
                        printf("\n\t\t Insira o e-mail do usuário para atulizar o empréstimo: ");
                        scanf("%s",gmail);
                        auxUs = searchCopyUser(rootU,gmail);
                        if(auxUs == NULL){
                            printf("\n\t\t Usuário não encontrado!");
                            return;
                        }
                        if(auxUs ->data->books == 0){
                            printf("\n\t\t Esse usuário não retirou nenhum livro!");
                            return;
                        }
                        printf("\n\t\t Insira o código do livro para alterar as informações: ");
                        scanf("%l"SCNu64, &id);
                        ListD_E_Book *livro = returnBook(auxUs -> wardenB,id);
                        if(livro == NULL){
                            printf("\n\t\t Livro não encontrado!");
                            return;
                        }
                        printf("\n\t\t Livro encontrado!");

                        time_t agora = time(NULL);
                        struct tm *data = localtime(&agora);

                        Date today = { data->tm_mday, data->tm_mon + 1, data->tm_year + 1900};

                        if(isLate(livro->loanEnd, &today)){
                            printf("\n\t\t Livro atrasado!");
                            printf("\n\t\t A devolução após o prazo estará sujeita à multa!");
                            printf("\n\t\t Renovação indisponível. É necessário devolver o item.\n");
                            return;
                        }else{
                            livro->loanEnd->day = today.day;
                            livro->loanEnd->month = today.month;
                            livro->loanEnd->year = today.year;

                            livro->loanSt->day = today.day;
                            livro->loanSt->month = today.month;
                            livro->loanSt->year = today.year;

                            Date *newEnd = returnDate(today.day, today.month, today.year);

                            livro->loanEnd->day = newEnd->day;
                            livro->loanEnd->month = newEnd->month;
                            livro->loanEnd->year = newEnd->year;

                            free(newEnd);

                            printf("\n\t\t Livro renovado!");
                            printf("\n\t\t Data devolução: ");
                            printDate(livro->loanEnd);
                            printf("\n");
                        }

                    }if(code == 0){
                        return;
                    }
                }
            }
        
    }

    return 0;
}
