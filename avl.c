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
    if(*self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int search_result=(*compar)(data, (*self)->data);
    if(search_result == 0){
        *result = 1;
    } else if (search_result > 0 && (*self)->right != NULL) {
        return avl_search(&((*self)->right), data, result, compar);
    } else if (search_result < 0 && (*self)->left != NULL) {
        return avl_search(&((*self)->left), data, result, compar);
    } else {
        *result = 0;
    }
    return TREE_OP_SUCCESS;
}

int avl_insert(Tree **self, void *data, int (*compar)(const void *, const void *)){
    return TREE_OP_SUCCESS;
}

int avl_delete(Tree **self, void *data, int (*compar)(const void *, const void *)){
    return TREE_OP_SUCCESS;
}

int avl_pre_order_traversal(Tree **self, int (*callback)(const void *)){
    if(*self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int result=TREE_OP_SUCCESS;

    result = (*callback)((*self)->data);
    if(result != TREE_OP_SUCCESS)return result;

    if((*self)->left != NULL){
        result = avl_pre_order_traversal(&((*self)->left), callback);
        if(result != TREE_OP_SUCCESS)return result;
    }

    if((*self)->right != NULL){
        result = avl_pre_order_traversal(&((*self)->right), callback);
        if(result != TREE_OP_SUCCESS)return result;
    }

    return TREE_OP_SUCCESS;
}

int avl_in_order_traversal(Tree **self, int (*callback)(const void *)){
    if(*self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int result=TREE_OP_SUCCESS;

    if((*self)->left != NULL){
        result = avl_in_order_traversal(&((*self)->left), callback);
        if(result != TREE_OP_SUCCESS)return result;
    }

    result = (*callback)((*self)->data);
    if(result != TREE_OP_SUCCESS)return result;

    if((*self)->right != NULL){
        result = avl_in_order_traversal(&((*self)->right), callback);
        if(result != TREE_OP_SUCCESS)return result;
    }

    return TREE_OP_SUCCESS;
}

int avl_post_order_traversal(Tree **self, int (*callback)(const void *)){
    if(*self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int result=TREE_OP_SUCCESS;

    if((*self)->left != NULL){
        result = avl_post_order_traversal(&((*self)->left), callback);
        if(result != TREE_OP_SUCCESS)return result;
    }

    if((*self)->right != NULL){
        result = avl_post_order_traversal(&((*self)->right), callback);
        if(result != TREE_OP_SUCCESS)return result;
    }

    result = (*callback)((*self)->data);
    if(result != TREE_OP_SUCCESS)return result;

    return TREE_OP_SUCCESS;
}

int avl_level_order_traversal(Tree **self, int (*callback)(const void *)){
    if(*self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int result=TREE_OP_SUCCESS;

    Tree* queue[TREE_MAX_SIZE];
    int first=0;
    int last=0;

    queue[first] = *self;
    first++;

    while(first != last){
        result = (*callback)(queue[last]->data);
        if(result != TREE_OP_SUCCESS)return result;
        last++;

        if(queue[last]->left != NULL){
            queue[first] = queue[last]->left;
            first++;
        }
        if(queue[last]->right != NULL){
            queue[first] = queue[last]->right;
            first++;
        }
    }

    return TREE_OP_SUCCESS;
}
