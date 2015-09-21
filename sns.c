//
// Created by hrl on 9/21/15.
//

#include "sns_structs.h"
#include "sns_functions.h"

int people_compar(const void *a, const void *b){
    People *A, *B;
    A = (People*)a;
    B = (People*)b;
    return A->id - B->id;
}
