//
// Created by hrl on 9/11/15.
//

#include <stddef.h>
#include <stdlib.h>
#include "avl_functions.h"
#include "set_functions.h"
#include "set_structs.h"
#include "avl_defines.h"
#include "set_defines.h"

int set_init(Set **self){
    if(*self != NULL){
        return SET_INITED_ERROR;
    }

    *self = (Set*)malloc(sizeof(Set));
    if(*self == NULL){
        return SET_INIT_FAIL_ERROR;
    }

    (*self)->size = 0;
    (*self)->_tree = NULL;
    int result;
    result = avl_init(&((*self)->_tree));
    if(result != TREE_OP_SUCCESS)return SET_INIT_FAIL_ERROR;

    return SET_OP_SUCCESS;
}

int set_del(Set **self){
    if(*self == NULL){
        return SET_OP_SUCCESS;
    }

    avl_del(&((*self)->_tree));
    free(*self);
    *self = NULL;

    return SET_OP_SUCCESS;
}

int set_is_member(Set *self, void *data, int *result_is_member, int (*compar)(const void *, const void *)){
    if(self == NULL){
        return SET_UNINIT_ERROR;
    }

    Tree *result_search=NULL;
    avl_search(&(self->_tree), data, &result_search, compar);
    if(result_search == NULL){
        *result_is_member = 1;
    } else {
        *result_is_member = 0;
    }

    return SET_OP_SUCCESS;
}

int set_insert(Set **self, void *data, int (*compar)(const void *, const void *)){
    if(*self == NULL){
        return SET_UNINIT_ERROR;
    }

    int result;
    result = avl_insert(&((*self)->_tree), data, compar);
    if(result == TREE_INSERT_SAME_VALUE_ERROR)return SET_INSERT_SAME_VALUE_ERROR;
    if(result != TREE_OP_SUCCESS)return SET_INSERT_FAIL_ERROR;
    (*self)->size++;

    return SET_OP_SUCCESS;
}

int set_delete(Set **self, void *data, int (*compar)(const void *, const void *)){
    if(*self == NULL){
        return SET_UNINIT_ERROR;
    }

    int result;
    result = set_delete(&((*self)->_tree), data, compar);
    if(result != TREE_OP_SUCCESS)return SET_DELETE_FAIL_ERROR;
    (*self)->size--;

    return SET_OP_SUCCESS;
}

int set_intersection(Set *set_a, Set *set_b, Set **result_intersection, int (*compar)(const void *, const void *)){
    return SET_OP_SUCCESS;
}

int set_union(Set *set_a, Set *set_b, Set **result_union, int (*compar)(const void *, const void *)){
    return SET_OP_SUCCESS;
}

int set_difference(Set *set_a, Set *set_b, Set **result_difference, int (*compar)(const void *, const void *)){
    return SET_OP_SUCCESS;
}

int set_is_subset(Set *set_a, Set *set_b, int result_is_subset, int (*compar)(const void *, const void *)){
    return SET_OP_SUCCESS;
}

int set_is_equal(Set *set_a, Set *set_b, int result_is_equal, int (*compar)(const void *, const void *)){
    return SET_OP_SUCCESS;
}

int set_map(Set *self, void *pipe, int (*callback)(const void *, void *)){
    return SET_OP_SUCCESS;
}
