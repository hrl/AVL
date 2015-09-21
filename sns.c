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

int people_init(Set *universal, People **self){
    return SNS_OP_SUCCESS;
}

int people_del(Set *universal, People **self){
    return SNS_OP_SUCCESS;
}

int people_follow(Set *universal, People *self, People *target){
    return SNS_OP_SUCCESS;
}

int people_friend(Set *universal, People *self, People *target){
    return SNS_OP_SUCCESS;
}

int people_followings(People *self, Set **followings){
    return SNS_OP_SUCCESS;
}

int people_followers(People *self, Set **followers){
    return SNS_OP_SUCCESS;
}

int people_friends(People *self, Set **friends){
    return SNS_OP_SUCCESS;
}

int people_is_following(People *self, People *target, int *is_following){
    return SNS_OP_SUCCESS;
}

int people_is_follower(People *self, People *target, int *is_follower){
    return SNS_OP_SUCCESS;
}

int people_is_friend(People *self, People *target, int *is_friend){
    return SNS_OP_SUCCESS;
}

int people_common_followings(People *self, People *target, Set **common_followings){
    return SNS_OP_SUCCESS;
}

int people_common_followers(People *self, People *target, Set **common_followers){
    return SNS_OP_SUCCESS;
}

int people_extend_friends(Set *universal, People *self, Set **extend_friends){
    return SNS_OP_SUCCESS;
}
