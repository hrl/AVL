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
    (*self)->left = NULL;
    (*self)->right = NULL;

    return TREE_OP_SUCCESS;
}
