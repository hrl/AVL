//
// Created by hrl on 9/9/15.
//

#include <stddef.h>
#include <stdlib.h>
#include "avl_functions.h"
#include "avl_structs.h"
#include "avl_defines.h"

int avl_init(Tree **self){
    if(*self != NULL){
        return TREE_INITED_ERROR;
    }

    *self = (Tree*)malloc(sizeof(Tree));
    if(*self == NULL){
        return TREE_INIT_FAIL_ERROR;
    }

    (*self)->data = NULL;
    (*self)->height = 1;
    (*self)->left = NULL;
    (*self)->right = NULL;

    return TREE_OP_SUCCESS;
}

int avl_del(Tree **self){
    if((*self) == NULL){
        return TREE_OP_SUCCESS;
    }

    avl_del(&((*self)->left));
    avl_del(&((*self)->right));
    free(*self);
    *self = NULL;

    return TREE_OP_SUCCESS;
}

int avl_height(Tree **self, int *height){
    // tmp handle
    *height = (*self)->height;
    return TREE_OP_SUCCESS;
}

int avl_search(Tree **self, void *data, Tree **result, int (*compar)(const void *, const void *)){
    return TREE_OP_SUCCESS;
}

int avl_insert(Tree **self, void *data, int (*compar)(const void *, const void *)){
    return TREE_OP_SUCCESS;
}

int avl_delete(Tree **self, void *data, int (*compar)(const void *, const void *)){
    return TREE_OP_SUCCESS;
}

int avl_pre_order_traversal(Tree **self, int (*callback)(const Tree *)){
    return TREE_OP_SUCCESS;
}

int avl_in_order_traversal(Tree **self, int (*callback)(const Tree *)){
    return TREE_OP_SUCCESS;
}

int avl_post_order_traversal(Tree **self, int (*callback)(const Tree *)){
    return TREE_OP_SUCCESS;
}

int avl_level_order_traversal(Tree **self, int (*callback)(const Tree *)){
    return TREE_OP_SUCCESS;
}
