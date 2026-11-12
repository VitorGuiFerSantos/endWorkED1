#ifndef DEVOL_H
#define DEVOL_H
#include "TAD.h"
#include "AVL_B.h"
#include "AVL_U.h"
#include "listEnB.h"
#include "listEnU.h"
#include <inttypes.h>
#include <time.h>
void devol(userTree* rootU,treeBook* rootB){
    char  gmail[MAXchar];
    uint64_t code = 0;

    printf("\n\n\t\t+---------------DEVOLUÇÂO------------------+\n\t\t|\t\t\t\t\t\t|\n");
    printf("\n\t\tInforme o e-mail do usuário: ");
    scanf("%s", gmail);

    userTree *auxUs = searchCopyUser(rootU,gmail);

    if(auxUs -> wardenB -> first == NULL){
        printf("\n\t\t Nenhum livro retirado\n");
        return;
    }

    if(auxUs->wardenB->first == NULL){
        printf("\n\t\tNenhum livro retirado");
        return;
    }

    printf("\n\t\t Livros retirados pelo usuário :");
    printWDogBook(auxUs->wardenB);

    printf("\n\t\t Insira o código do livro para devolver:");
    scanf("%"SCNu64, &code);

    ListD_E_Book *loanB = returnBook(auxUs -> wardenB,code);

    if(loanB == NULL){
        printf("\n\t\t Livro não encontrado!");
        return;
    }

    printf("\n\t\t Livro encontrado!");


    time_t agora = time(NULL);
    struct tm *data = localtime(&agora);

    Date today = { data->tm_mday, data->tm_mon + 1, data->tm_year + 1900};

    if(isLate(loanB->loanEnd, &today)){
        printf("\n\t\t Livro em atraso!\n\t\t A devolução após o prazo estará sujeita à multa.");
    }
    
    ListD_E_user *loanU = loanB->correspondingLoan;

    Date *St = loanB ->loanSt,* En = loanB ->loanEnd;
    
    returnLoanBook(loanB -> otherWarden,loanU -> correspondingLoan);
    returnLoanUser(loanU ->otherWarden, loanB ->correspondingLoan);
    
    auxUs->data->books--;
    loanB->data->amountLent--;

    free(loanB);
    free(loanU);
    free(St);
    free(En);
    printf("\n\t\t Livro devolvido! Volte sempre.");
        
}
#endif