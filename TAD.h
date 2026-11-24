#ifndef USER_TREE_H
#define USER_TREE_H
#define MAXchar 300
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <inttypes.h>
#include <time.h>
typedef struct _time_D{
    int day;
    int month;
    int year;
}Date;

typedef struct {
    char member[MAXchar];
    char gmail[MAXchar];
    int books;
} User;

typedef struct _dados_book{
    uint64_t id;
    char title[MAXchar];
    char author[MAXchar];
    int year;
    int amount;
    int amountLent;
}Book;
//lista encadeada que guarda o endereço dos usuarios que retiraram o livro
struct _l_E_B;
struct _lE_User;

typedef struct _l_E_B ListD_E_user;

typedef struct _lE_User ListD_E_Book;

typedef struct _wactherUser{
    ListD_E_user* first;
    ListD_E_user* last;
}WDogUser;

typedef struct _wacther_Book{
    ListD_E_Book* first;
    ListD_E_Book* last;
}WDogBook;
struct _l_E_B{
    Date *loanSt;
    Date *loanEnd;
    User *data;
    
    struct _l_E_B *prev;
    struct _l_E_B *next;
    struct _lE_User *correspondingLoan;

    WDogBook *otherWarden;
};
// lista encadeada que guarda os livros que o usuário retirou 

struct _lE_User{
    Date *loanSt;
    Date *loanEnd;
    Book *data;
    
    struct _lE_User *prev;
    struct _lE_User *next;

    struct _l_E_B *correspondingLoan;

    WDogUser *otherWarden;
};

struct _arbor{
    int height;
    User *data;
    struct _arbor *left;
    struct _arbor *right;
    WDogBook *wardenB;
};
typedef struct _arbor userTree;

struct _treeB{
    Book *data;
    int height;
    struct _treeB *right;
    struct _treeB *left;
    WDogUser *wardenU;
};
typedef struct _treeB treeBook;

int max(int a,int b){
    return a > b ? a : b;
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

// Handles date operations, validation, loan periods, and overdue checks.

int yearLeap(int year){
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}
Date* returnDate(int day, int month,int year){
    int day1 = day,month1 = month, year1 = year; 
    int diasMes[] = { 0, 31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31};

    Date* end = malloc(sizeof(Date));

    if(end == NULL){
        return NULL;
    }

    if(yearLeap(year)){
        diasMes[2] = 29;
    }
    day1 += 10;

    while(day1 > diasMes[month1]){
        day1 -= diasMes[month1];
        month1++;

        if(month1 > 12){
            month1= 1;
            year1++;

            diasMes[2] = yearLeap(year1) ? 29 : 28;
        }
    }
    end -> day = day1;
    end -> month = month1; 
    end -> year = year1; 
    return end;
}

int dateToDays(int day, int month, int year){
    int diasMes[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(yearLeap(year)){
        diasMes[2] = 29;
    }

    int total = day;

    for(int i = 1; i < month; i++){
        total += diasMes[i];
    }

    total += year * 365;
    total += year / 4 - year / 100 + year / 400;

    return total;
}
bool isLate(Date *end, Date *today){
    int endDays = dateToDays(end->day, end->month, end->year);

    int todayDays = dateToDays(today->day, today->month, today->year);

    return todayDays > endDays;
}
void printDate(Date* day){
    printf("%02d/%02d/%04d ",day -> day, day -> month, day ->year);

}

#endif