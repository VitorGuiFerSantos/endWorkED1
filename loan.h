#ifndef LOAN_H
#define LOAN_H
#include "TAD.h"
#include "AVL_B.h"
#include "AVL_U.h"
#include "listEnB.h"
#include "listEnU.h"
#include <inttypes.h>
void loan(treeBook *rootBook, userTree* rootUser){
        uint64_t code = 0;
        char gmail[MAXchar];

        printf("\n\n\t\t +---------------EMPRÉSTIMO------------------+ \n\t\t|\t\t\t\t\t\t|\n");
        printf("\n\t\t Informe o Código do livro: ");
        scanf("%"SCNu64, &code);

        treeBook* auxBK = searchIdBook(rootBook,code);

        if(auxBK == NULL){
            printf("\n\t\t Livro não encontrado!");
            return;//mudar para continue quando inserir no código original
        }
        printf("\n\t\t Livro encotrado!");
        
        if(auxBK ->data ->amount >= auxBK ->data ->amountLent){
            printf("\n\t\t Livro indisponível no momento!");
            return;
        }
        
        printf("\n\t\t Insira o e-mail do usuário: ");
        scanf("%s",gmail);

        userTree* auxUs = NULL;
        auxUs = searchCopyUser(rootUser,gmail);

        if(auxUs == NULL){
            printf("\n\t\t Usuáio não encontrado!");
            return;
        }
        printf("\n\t\t Usuário encotrado!");

        Date* start = malloc(sizeof(Date));
        Date* end = NULL;

        printf("\n\t\t Data de retirada:");
        scanf("%d %d %d",&start ->day, &start ->month, &start ->year);

        end = returnDate(start -> day, start -> month, start -> year);

        ListD_E_user *coorU = createLoanUser(start,end,auxUs->data);
        ListD_E_Book *coorB = createLoanBook(start,end,auxBK->data);

        // pointer for the nodo corresponding
        coorB->correspondingLoan = coorU;
        coorU->correspondingLoan = coorB;

        // pointer for the warden list
        coorU->otherWarden = auxUs->wardenB;
        coorB->otherWarden = auxBK->wardenU;

        addLoanUser(auxBK->wardenU,coorU);
        addLoanBook(auxUs->wardenB,coorB);
        //increment 
        auxBK -> data ->amountLent++;
        auxUs -> data ->books ++;

        printf("\n\t\t Data devolução: ");
        printDate(end);printf("\n");
        printf("\n\t\t A devolução após o prazo estará sujeita à multa!");
        printf("\n\t\t Informação adicional:");
        printf("\n\t\t Para renovar o empréstimo é na seção de (Atualização)!");
}

#endif