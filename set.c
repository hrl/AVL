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
    return SET_OP_SUCCESS;
}

int set_insert(Set **self, void *data, int (*compar)(const void *, const void *)){
    return SET_OP_SUCCESS;
}

int set_remove(Set **self, void *data, int (*compar)(const void *, const void *)){
    return SET_OP_SUCCESS;
}

int set_is_member(Set *self, void *data, int *result_is_member, int (*compar)(const void *, const void *)){
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
