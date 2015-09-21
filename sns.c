//
// Created by hrl on 9/21/15.
//

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
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
    if(*self != NULL){
        return SNS_INITED_ERROR;
    }

    *self = (Sns*)malloc(sizeof(Sns));
    if(*self == NULL) {
        return SNS_INIT_FAIL_ERROR;
    }

    (*self)->id_max = 0;
    (*self)->_peoples = NULL;

    return SNS_OP_SUCCESS;
}

int sns_del(Sns **self){
    if(*self == NULL){
        return SNS_OP_SUCCESS;
    }

    set_del(&((*self)->_peoples));
    free(*self);
    *self = NULL;

    return SNS_OP_SUCCESS;
}

int sns_insert(Sns *self, People *people){
    if(self == NULL){
        return SNS_UNINIT_ERROR;
    }

    if(people == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    people->id = (*self)->id_max + 1;

    int result;
    if(self->_peoples == NULL){
        result = set_init_with_data(&(self->_peoples), people);
    } else {
        result = set_insert(&(self->_peoples), people, people_compar);
    }
    if(result != SET_OP_SUCCESS) return SNS_INSERT_FAIL_ERROR;
    self->id_max++;

    return SNS_OP_SUCCESS;
}

int people_init(Sns *universal, People **self, char name[100]){
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

    (*self)->id = 0;
    strcpy((*self)->name, name);
    (*self)->_followings = NULL;
    (*self)->_followers = NULL;
    (*self)->_friends = NULL;

    int result;
    result = sns_insert(universal, *self);
    if(result != SNS_OP_SUCCESS) return PEOPLE_INIT_FAIL_ERROR;

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
