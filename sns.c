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

    people->id = self->id_max + 1;

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

int sns_delete(Sns *self, People *people){
    if(self == NULL){
        return SNS_UNINIT_ERROR;
    }

    if(people == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    int result;
    result = set_delete(&(self->_peoples), people, people_compar);
    if(result != SET_OP_SUCCESS) return SNS_DELETE_FAIL_ERROR;

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
    (*self)->__incoming_friends = NULL;

    int result;
    result = sns_insert(universal, *self);
    if(result != SNS_OP_SUCCESS) return PEOPLE_INIT_FAIL_ERROR;

    return PEOPLE_OP_SUCCESS;
}

struct _people_common_pipe {
    People *self;
    int refresh_shift;
    int (*compar)(const void *, const void *);
};
typedef struct _people_common_pipe _People_common_pipe;

int _people_common_pipe_init(_People_common_pipe **_pipe, int (*compar)(const void *, const void *)){
    *_pipe = (_People_common_pipe*)malloc(sizeof(_People_common_pipe));
    (*_pipe)->self = NULL;
    (*_pipe)->refresh_shift = 0;
    (*_pipe)->compar = compar;
    return PEOPLE_OP_SUCCESS;
}

int _people_common_pipe_del(_People_common_pipe **_pipe){
    if(*_pipe == NULL){
        return PEOPLE_OP_SUCCESS;
    }
    free(*_pipe);
    *_pipe = NULL;
    return PEOPLE_OP_SUCCESS;
}

int _people_del_refresh_set(const void *data, void *_pipe){
    _People_common_pipe *pipe;
    pipe = (_People_common_pipe*)_pipe;
    Set *target_set;
    target_set = (Set*) ((char*)data + pipe->refresh_shift);
    int result;
    result = set_delete(&target_set, pipe->self, pipe->compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_DEL_FAIL_ERROR;
    return PEOPLE_OP_SUCCESS;
}

int people_del(Sns *universal, People **self){
    if(universal == NULL){
        return SNS_UNINIT_ERROR;
    }

    if(*self == NULL){
        return PEOPLE_OP_SUCCESS;
    }

    _People_common_pipe *_pipe=NULL;
    _people_common_pipe_init(&_pipe, people_compar);

    _pipe->self = *self;

    // refresh followers' followings set
    _pipe->refresh_shift = 0;
    set_map((*self)->_followers, _pipe, _people_del_refresh_set);

    // refresh followings' followers set
    _pipe->refresh_shift += sizeof(Set*);
    set_map((*self)->_followings, _pipe, _people_del_refresh_set);

    // refresh incoming friends' friends set
    _pipe->refresh_shift += sizeof(Set*);
    set_map((*self)->__incoming_friends, _pipe, _people_del_refresh_set);

    // refresh friends' incoming friends set
    _pipe->refresh_shift += sizeof(Set*);
    set_map((*self)->_friends, _pipe, _people_del_refresh_set);

    // refresh universal set
    sns_delete(universal, *self);

    // delete self
    set_del(&((*self)->_followings));
    set_del(&((*self)->_followers));
    set_del(&((*self)->_friends));
    set_del(&((*self)->__incoming_friends));
    free(*self);
    *self = NULL;

    _people_common_pipe_del(&_pipe);

    return PEOPLE_OP_SUCCESS;
}

int people_follow(People *self, People *target){
    if(self == NULL || target == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    int result;
    result = set_insert(&(self->_followings), target, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_FOLLOW_FAIL_ERROR;
    result = set_insert(&(target->_followers), self, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_FOLLOW_FAIL_ERROR;

    return PEOPLE_OP_SUCCESS;
}

int people_friend(People *self, People *target){
    if(self == NULL || target == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    int result;
    result = set_insert(&(self->_friends), target, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_FRIEND_FAIL_ERROR;
    result = set_insert(&(target->__incoming_friends), self, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_FRIEND_FAIL_ERROR;

    return PEOPLE_OP_SUCCESS;
}

int people_followings(People *self, Set **followings){
    if(self == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    // tmp handle
    *followings = self->_followings;

    return PEOPLE_OP_SUCCESS;
}

int people_followers(People *self, Set **followers){
    if(self == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    // tmp handle
    *followers = self->_followers;

    return PEOPLE_OP_SUCCESS;
}

int people_friends(People *self, Set **friends){
    if(self == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    // tmp handle
    *friends = self->_friends;

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
