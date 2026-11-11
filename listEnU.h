#ifdef Lista_User
#define Lista_User
#include "TAD.h"
#include "AVL_B.h"
#include "AVL_U.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
WDogUser *creatWardenUser(){
    WDogUser* warden = malloc(sizeof(WDogUser));
    
    warden -> first = NULL;
    warden -> last = NULL;

    return warden;
}
#endif