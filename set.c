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

int set_init_with_data(Set **self, void *data) {
    if(*self != NULL){
        return SET_INITED_ERROR;
    }

    *self = (Set*)malloc(sizeof(Set));
    if(*self == NULL){
        return SET_INIT_FAIL_ERROR;
    }

    (*self)->size = 1;
    (*self)->_tree = NULL;
    int result;
    result = avl_init_with_data(&((*self)->_tree), data);
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

int _set_sort_by_size(Set **set_a, Set **set_b){
    if((*set_a)->size < (*set_b)->size){
        Set *tmp;
        tmp = *set_a;
        *set_a = *set_b;
        *set_b = tmp;
    }
    return SET_OP_SUCCESS;
}

struct _set_common_pipe {
    Set *set_large;
    Set *set_small;
    Set *result;
    int result_int;
    int (*compar)(const void *, const void *);
};

typedef struct _set_common_pipe _Set_common_pipe;

int _set_common_pipe_init(_Set_common_pipe **_pipe, int (*compar)(const void *, const void *)){
    *_pipe = (_Set_common_pipe*)malloc(sizeof(_Set_common_pipe));
    (*_pipe)->set_small = NULL;
    (*_pipe)->set_large = NULL;
    (*_pipe)->result = NULL;
    (*_pipe)->result_int = 0;
    (*_pipe)->compar = compar;
    return SET_OP_SUCCESS;
}

int _set_intersection(const void *data, void *pipe){
    _Set_common_pipe *_pipe=NULL;
    _pipe = (_Set_common_pipe*)pipe;
    int i, result, search_result;
    for(i=0; i<_pipe->set_large->size; i++){
        result = set_is_member(_pipe->set_large, (void *)data, &search_result, _pipe->compar);
        if(result != SET_OP_SUCCESS)return result;
        if(search_result != 0){
            if(_pipe->result == NULL){
                result = set_init_with_data(&(_pipe->result), (void *)data);
                if(result != SET_OP_SUCCESS)return result;
            } else {
                result = set_insert(&(_pipe->result), (void *)data, _pipe->compar);
                if(result != TREE_OP_SUCCESS)return SET_INTERSECTION_ERROR;
            }
        }
    }
    return SET_OP_SUCCESS;
}

int set_intersection(Set *set_a, Set *set_b, Set **result_intersection, int (*compar)(const void *, const void *)){
    if(set_a == NULL || set_b == NULL){
        return SET_UNINIT_ERROR;
    }
    if(*result_intersection != NULL){
        return SET_INITED_ERROR;
    }

    int result;
    _Set_common_pipe *_pipe=NULL;
    _set_common_pipe_init(&_pipe, compar);

    _set_sort_by_size(&set_a, &set_b);
    _pipe->set_large = set_a;

    result = set_map(set_b, _pipe, _set_intersection);
    if(result != SET_OP_SUCCESS)return result;

    *result_intersection = _pipe->result;

    return SET_OP_SUCCESS;
}

int _set_union(const void *data, void *pipe){
    _Set_common_pipe *_pipe=NULL;
    _pipe = (_Set_common_pipe*)pipe;
    int result;
    if(_pipe->result == NULL){
        result = set_init_with_data(&(_pipe->result), (void *)data);
        if(result != SET_OP_SUCCESS && result != SET_INSERT_SAME_VALUE_ERROR)return result;
    } else {
        result = set_insert(&(_pipe->result), (void *)data, _pipe->compar);
        if(result != SET_OP_SUCCESS && result != SET_INSERT_SAME_VALUE_ERROR)return result;
    }

    return SET_OP_SUCCESS;
}

int set_union(Set *set_a, Set *set_b, Set **result_union, int (*compar)(const void *, const void *)){
    if(set_a == NULL || set_b == NULL){
        return SET_UNINIT_ERROR;
    }
    if(*result_union != NULL){
        return SET_INITED_ERROR;
    }

    int result;
    _Set_common_pipe *_pipe=NULL;
    _set_common_pipe_init(&_pipe, compar);

    result = set_map(set_a, _pipe, _set_union);
    if(result != SET_OP_SUCCESS)return result;
    result = set_map(set_b, _pipe, _set_union);
    if(result != SET_OP_SUCCESS)return result;

    *result_union = _pipe->result;

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
    int result;
    result = avl_level_order_traversal(self->_tree, pipe, callback);
    if(result != TREE_OP_SUCCESS)return result;
    return SET_OP_SUCCESS;
}
