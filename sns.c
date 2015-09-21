//
// Created by hrl on 9/21/15.
//

#include <stddef.h>
#include <stdlib.h>
#include "set_functions.h"
#include "sns_functions.h"
#include "set_structs.h"
#include "sns_structs.h"
#include "set_defines.h"
#include "sns_defines.h"

int people_compar(const void *a, const void *b){
    People *A, *B;
    A = (People*)a;
    B = (People*)b;
    return A->id - B->id;
}

int sns_init(Sns **self){
    return SNS_OP_SUCCESS;
}

int sns_del(Sns **self){
    return SNS_OP_SUCCESS;
}

int sns_add(Sns **self, People *people){
    return SNS_OP_SUCCESS;
}

int people_init(Sns *universal, People **self){
    if(universal == NULL){
        return SNS_UNINIT_ERROR;
    }

    if(*self != NULL){
        return PEOPLE_INITED_ERROR;
    }

    *self = (People*)malloc(sizeof(People));
    if(*self == NULL) {
        return PEOPLE_INIT_FAIL_ERROR;
    }
    // init

    return PEOPLE_OP_SUCCESS;
}

int people_del(Sns *universal, People **self){
    return PEOPLE_OP_SUCCESS;
}

int people_follow(Sns *universal, People *self, People *target){
    return PEOPLE_OP_SUCCESS;
}

int people_friend(Sns *universal, People *self, People *target){
    return PEOPLE_OP_SUCCESS;
}

int people_followings(People *self, Set **followings){
    return PEOPLE_OP_SUCCESS;
}

int people_followers(People *self, Set **followers){
    return PEOPLE_OP_SUCCESS;
}

int people_friends(People *self, Set **friends){
    return PEOPLE_OP_SUCCESS;
}

int people_is_following(People *self, People *target, int *is_following){
    return PEOPLE_OP_SUCCESS;
}

int people_is_follower(People *self, People *target, int *is_follower){
    return PEOPLE_OP_SUCCESS;
}

int people_is_friend(People *self, People *target, int *is_friend){
    return PEOPLE_OP_SUCCESS;
}

int people_common_followings(People *self, People *target, Set **common_followings){
    return PEOPLE_OP_SUCCESS;
}

int people_common_followers(People *self, People *target, Set **common_followers){
    return PEOPLE_OP_SUCCESS;
}

int people_extend_friends(Set *universal, People *self, Set **extend_friends){
    return PEOPLE_OP_SUCCESS;
}
