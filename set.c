//
// Created by hrl on 9/11/15.
//
// SET function lib
// based on AVL function lib

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "avl_functions.h"
#include "set_functions.h"
#include "set_structs.h"
#include "avl_defines.h"
#include "set_defines.h"

// NULL : UNINIT
// size == 0 (_tree == NULL) : null set

int set_init(Set **self){
    /*
     * create a null SET
     * *self must point to NULL
     *
     * */
    if(*self != NULL){
        return SET_INITED_ERROR;
    }

    *self = (Set*)malloc(sizeof(Set));
    if(*self == NULL){
        return SET_INIT_FAIL_ERROR;
    }

    (*self)->size = 0;
    (*self)->_tree = NULL;

    return SET_OP_SUCCESS;
}

int set_del(Set **self){
    /*
     * recursively delete(free) a SET
     *
     */
    if(*self == NULL){
        return SET_OP_SUCCESS;
    }

    avl_del(&((*self)->_tree));
    free(*self);
    *self = NULL;

    return SET_OP_SUCCESS;
}

int set_search(Set *self, void *data, void **result_data, int *result_found, int (*compar)(const void *, const void *)){
    /*
     * Search data in SET `self`
     * data in param and data in SET struct will be compared in function compar
     *
     * if found, *result_data will be set to the target data
     *           result_found will be set to TRUE
     * if not, result_found will be set to FALSE
     *
     * this function is a simple warpper to function avl_search
     *
     * */
    if(self == NULL){
        return SET_UNINIT_ERROR;
    }
    if(self->size == 0){
        *result_data = NULL;
        *result_found = 0;
        return SET_OP_SUCCESS;
    }

    int result;
    result = avl_search(self->_tree, data, result_data, result_found, compar);
    if(result != TREE_OP_SUCCESS) return SET_SEARCH_ERROR;
    return SET_OP_SUCCESS;
}

int set_is_member(Set *self, void *data, int *result_is_member, int (*compar)(const void *, const void *)){
    /*
     * Search data in SET `self`
     * data in param and data in SET struct will be compared in function compar
     *
     * if found, result_is_member will be set to TRUE
     * if not, result_is_member will be set to FALSE
     *
     * this function is a simple warpper to function set_is_member
     *
     * */
    if(self == NULL){
        return SET_UNINIT_ERROR;
    }

    void *result_data=NULL;
    int result;
    result = set_search(self, data, &result_data, result_is_member, compar);
    if(result != SET_OP_SUCCESS) return SET_SEARCH_ERROR;

    return SET_OP_SUCCESS;
}

int set_insert(Set **self, void *data, int (*compar)(const void *, const void *)){
    /*
     * Insert data into SET `self`
     * data in param and data in SET struct will be compared in function compar
     *
     * this function is a simple warpper to function avl_insert
     *
     */
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
    /*
     * Delete data from SET `self`
     * data in param and data in AVL struct will be compared in function compar
     *
     */
    if(*self == NULL){
        return SET_UNINIT_ERROR;
    }

    int result;
    int deleted=1;
    result = avl_delete(&((*self)->_tree), data, &deleted, compar);
    if(result != TREE_OP_SUCCESS)return SET_DELETE_FAIL_ERROR;
    if(deleted == 1){
        (*self)->size--;
    }

    return SET_OP_SUCCESS;
}

int _set_sort_by_size(Set **set_a, Set **set_b){
    /*
     * inner function
     * *set_a will be set to the SET which is larger
     * *set_b will be set to the SET whic is smaller
     *
     * */
    if((*set_a)->size < (*set_b)->size){
        Set *tmp;
        tmp = *set_a;
        *set_a = *set_b;
        *set_b = tmp;
    }
    return SET_OP_SUCCESS;
}

int _set_init_or_insert(Set **self, int pass_same, void *data, int (*compar)(const void *, const void *)){
    /*
     * inner function
     * init a SET with param data, then set `self` to this SET
     * or insert param data into SET `self`
     *
     * */
    int result;
    if(*self == NULL){
        result = set_init(self);
        if(result != SET_OP_SUCCESS)return result;
    }
    result = set_insert(self, data, compar);
    if(pass_same && result == SET_INSERT_SAME_VALUE_ERROR)result = SET_OP_SUCCESS;
    if(result != SET_OP_SUCCESS)return result;

    return SET_OP_SUCCESS;
}

struct _set_common_pipe {
    /*
     * common pipe to store tmp value during map
     *
     * */
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

int _set_common_pipe_del(_Set_common_pipe **_pipe){
    if(*_pipe == NULL){
        return SET_OP_SUCCESS;
    }
    free(*_pipe);
    *_pipe = NULL;
    return SET_OP_SUCCESS;
}

int _set_intersection(const void *data, void *pipe){
    /*
     * this function will be called by the map/traversal function
     * if param data is in SET _pipe->set_large, param data will be inserted into SET _pipe->set_large
     *
     * */
    _Set_common_pipe *_pipe=NULL;
    _pipe = (_Set_common_pipe*)pipe;
    int result, search_result;
    result = set_is_member(_pipe->set_large, (void *)data, &search_result, _pipe->compar);
    if(result != SET_OP_SUCCESS)return result;
    if(search_result != 0){
        result = _set_init_or_insert(&(_pipe->result), 0, (void *)data, _pipe->compar);
        if(result != SET_OP_SUCCESS)return SET_INTERSECTION_ERROR;
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
    // init commom pipe
    _Set_common_pipe *_pipe=NULL;
    _set_common_pipe_init(&_pipe, compar);

    // find the larger one
    _set_sort_by_size(&set_a, &set_b);
    _pipe->set_large = set_a;
    // init result set
    set_init(&(_pipe->result));

    // map set_b's member to function _set_intersection
    result = set_map(set_b, _pipe, _set_intersection);
    if(result != SET_OP_SUCCESS)return result;

    *result_intersection = _pipe->result;

    // free common pipe
    _set_common_pipe_del(&_pipe);

    return SET_OP_SUCCESS;
}

int _set_extend(const void *data, void *pipe){
    /*
     * this function will be called by the map/traversal function
     * param data will be inserted into SET _pipe->set_large
     *
     * */
    _Set_common_pipe *_pipe=NULL;
    _pipe = (_Set_common_pipe*)pipe;
    int result;
    result = _set_init_or_insert(&(_pipe->result), 1, (void *)data, _pipe->compar);
    if(result != SET_OP_SUCCESS)return result;

    return SET_OP_SUCCESS;
}

int set_extend(Set *set_a, Set *set_b, int (*compar)(const void *, const void *)){
    if(set_a == NULL || set_b == NULL){
        return SET_UNINIT_ERROR;
    }
    int result;
    // init common pipe
    _Set_common_pipe *_pipe=NULL;
    _set_common_pipe_init(&_pipe, compar);

    _pipe->result = set_a;

    // map set_b's member to function _set_extend
    result = set_map(set_b, _pipe, _set_extend);
    if(result != SET_OP_SUCCESS)return result;

    // free common pipe
    _set_common_pipe_del(&_pipe);

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
    // init common pipe
    _Set_common_pipe *_pipe=NULL;
    _set_common_pipe_init(&_pipe, compar);
    // init result SET
    set_init(&(_pipe->result));

    // map set_a's member to function _set_extend
    result = set_map(set_a, _pipe, _set_extend);
    if(result != SET_OP_SUCCESS)return result;
    // map set_b's member to function _set_extend
    result = set_map(set_b, _pipe, _set_extend);
    if(result != SET_OP_SUCCESS)return result;

    *result_union = _pipe->result;

    // free common pipe
    _set_common_pipe_del(&_pipe);

    return SET_OP_SUCCESS;
}

int _set_difference(const void *data, void *pipe){
    /*
     * this function will be called by the map/traversal function
     * if param data is !NOT! in SET _pipe->set_large, param data will be inserted into SET _pipe->set_large
     *
     * */
    _Set_common_pipe *_pipe=NULL;
    _pipe = (_Set_common_pipe*)pipe;
    int result, search_result;
    result = set_is_member(_pipe->set_large, (void *)data, &search_result, _pipe->compar);
    if(result != SET_OP_SUCCESS)return result;
    if(search_result == 0){
        result = _set_init_or_insert(&(_pipe->result), 0, (void *)data, _pipe->compar);
        if(result != SET_OP_SUCCESS)return SET_DIFFERENCE_ERROR;
    }
    return SET_OP_SUCCESS;
}

int set_difference(Set *set_a, Set *set_b, Set **result_difference, int (*compar)(const void *, const void *)){
    if(set_a == NULL || set_b == NULL){
        return SET_UNINIT_ERROR;
    }
    if(*result_difference != NULL){
        return SET_INITED_ERROR;
    }

    int result;
    // init common pipe
    _Set_common_pipe *_pipe=NULL;
    _set_common_pipe_init(&_pipe, compar);
    set_init(&(_pipe->result));

    // large is nonsensical here
    _pipe->set_large = set_b;

    // map set_a's member to function _set_difference
    result = set_map(set_a, _pipe, _set_difference);
    if(result != SET_OP_SUCCESS)return result;

    *result_difference = _pipe->result;

    // free common pipe
    _set_common_pipe_del(&_pipe);

    return SET_OP_SUCCESS;
}

int _set_contract(const void *data, void *pipe){
    /*
     * this function will be called by the map/traversal function
     * if param data is in SET _pipe->set_large, param data will be deleted from SET _pipe->set_large
     *
     * */
    _Set_common_pipe *_pipe=NULL;
    _pipe = (_Set_common_pipe*)pipe;
    int result, search_result;
    result = set_is_member(_pipe->set_large, (void *)data, &search_result, _pipe->compar);
    if(result != SET_OP_SUCCESS)return result;
    if(search_result != 0){
        result = set_delete(&(_pipe->set_large), (void *)data, _pipe->compar);
        if(result != SET_OP_SUCCESS)return SET_DIFFERENCE_ERROR;
    }
    return SET_OP_SUCCESS;
}

int set_contract(Set *set_a, Set *set_b, int (*compar)(const void *, const void *)){
    if(set_a == NULL || set_b == NULL){
        return SET_UNINIT_ERROR;
    }

    int result;
    // init common pipe
    _Set_common_pipe *_pipe=NULL;
    _set_common_pipe_init(&_pipe, compar);

    // large is nonsensical here
    _pipe->set_large = set_a;

    // map set_b's member to function _set_contract
    result = set_map(set_b, _pipe, _set_contract);
    if(result != SET_OP_SUCCESS)return result;

    // free common pipe
    _set_common_pipe_del(&_pipe);

    return SET_OP_SUCCESS;
}

int _set_is_subset(const void *data, void *pipe) {
    /*
     * this function will be called by the map/traversal function
     * if param data is in SET _pipe->set_large, _pipe->result_int will be set to FALSE
     *
     * */
    _Set_common_pipe *_pipe = NULL;
    _pipe = (_Set_common_pipe *) pipe;
    int result, search_result;
    result = set_is_member(_pipe->set_large, (void *)data, &search_result, _pipe->compar);
    if(result != SET_OP_SUCCESS)return result;
    if(search_result == 0){
        _pipe->result_int = 0;
    }
    return SET_OP_SUCCESS;
}

int set_is_subset(Set *set_a, Set *set_b, int *result_is_subset, int (*compar)(const void *, const void *)){
    /*
     * if set_a is a subset of set_b, result_is_subset will be set to TRUE
     * if not, result_is_subset will set to FALSE
     *
     * */
    if(set_a == NULL || set_b == NULL){
        return SET_UNINIT_ERROR;
    }

    if(set_a->size > set_b->size){
        *result_is_subset = 0;
        return SET_OP_SUCCESS;
    }

    int result;
    // init common pipe
    _Set_common_pipe *_pipe=NULL;
    _set_common_pipe_init(&_pipe, compar);

    _pipe->set_large = set_b;
    // set the default result
    _pipe->result_int = 1;

    // map set_b's member to function _set_is_subset
    result = set_map(set_a, _pipe, _set_is_subset);
    if(result != SET_OP_SUCCESS)return result;

    *result_is_subset = _pipe->result_int;

    // free common pipe
    _set_common_pipe_del(&_pipe);

    return SET_OP_SUCCESS;
}

int set_is_equal(Set *set_a, Set *set_b, int *result_is_equal, int (*compar)(const void *, const void *)){
    if(set_a == NULL || set_b == NULL){
        return SET_UNINIT_ERROR;
    }

    if(set_a->size != set_b->size){
        *result_is_equal = 0;
        return SET_OP_SUCCESS;
    }

    return set_is_subset(set_a, set_b, result_is_equal, compar);
}

int set_map(Set *self, void *pipe, int (*callback)(const void *, void *)){
    /*
     * apply callback function to each data and the input param
     *
     * if the callback function's return value is not `SET_OP_SUCCESS`, map will be aborted
     *
     * this function is a simple warpper to function avl_level_order_traversal
     *
     * */
    int result;
    result = avl_level_order_traversal(self->_tree, pipe, callback);
    if(result != TREE_OP_SUCCESS)return result;
    return SET_OP_SUCCESS;
}
