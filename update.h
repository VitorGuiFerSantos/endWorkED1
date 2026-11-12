#ifndef UPDATE_H
#define UPDATE_H
#include <time.h>
#include "TAD.h"
#include "AVL_B.h"
#include "AVL_U.h"
#include "listEnB.h"
#include "listEnU.h"
#include <inttypes.h>
void update(userTree* rootU, treeBook* rootB){
    int code = 0;
    printf("\n\n\t\t+---------------ATUALIZAÇÃO------------------+\n\t\t|\t\t\t\t\t\t|\n");
    printf("\n\t\t ( 1 ) Livro  ");
    printf("\n\t\t ( 2 ) Usuário  ");
    printf("\n\t\t ( 3 ) Renovar empréstimo");
    printf("\n\t\t ( 0 ) voltar  ");
    printf("\n\t\t Qual opção: ");
    scanf("%d", &code);
    if(code == 1){
        uint64_t id = 0;
        treeBook *auxBk = NULL;
        printf("\n\t\t Insira o código do livro para alterar as informações: ");
        scanf("%"SCNu64, &id);
        auxBk = searchIdBook(rootB,id);
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
#endif