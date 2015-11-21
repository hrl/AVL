//
// Created by hrl on 9/9/15.
//
// AVL function lib

#include <stddef.h>
#include <stdlib.h>
#include "avl_functions.h"
#include "avl_structs.h"
#include "avl_defines.h"

// NULL: empty tree

int _max(int a, int b){
    return a>b?a:b;
}

int avl_init(Tree **self, void *data) {
    /*
     * init an empty AVL Tree
     * *self must point to NULL
     * (*self)->data need to be set immediately after call this function
     *
     * */
    if(*self != NULL){
        return TREE_INITED_ERROR;
    }

    *self = (Tree*)malloc(sizeof(Tree));
    if(*self == NULL){
        return TREE_INIT_FAIL_ERROR;
    }

    (*self)->data = data;
    (*self)->height = 1;
    (*self)->left = NULL;
    (*self)->right = NULL;
    return TREE_OP_SUCCESS;
}

int avl_del(Tree **self){
    /*
     * recursively delete(free) an AVL Tree
     *
     * */
    if((*self) == NULL){
        return TREE_OP_SUCCESS;
    }

    avl_del(&((*self)->left));
    avl_del(&((*self)->right));
    free(*self);
    *self = NULL;

    return TREE_OP_SUCCESS;
}

int avl_height_direct(Tree *self){
    if(self == NULL){
        return 0;
    }
    return self->height;
}

int avl_search(Tree *self, void *data, void **result_data, int *result_found, int (*compar)(const void *, const void *)){
    /*
     * Search data in AVL Tree `self`
     * data in param and data in AVL struct will be compared in function compar
     *
     * if found, *result_data will be set to the target data
     *           result_found will be set to TRUE
     * if not, result_found will be set to FALSE
     *
     * */
    if(self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int search_result=(*compar)(data, self->data);
    if(search_result == 0){
        *result_data = self->data;
        *result_found = 1;
    } else if (search_result > 0 && self->right != NULL) {
        return avl_search(self->right, data, result_data, result_found, compar);
    } else if (search_result < 0 && self->left != NULL) {
        return avl_search(self->left, data, result_data, result_found, compar);
    } else {
        *result_data = NULL;
        *result_found = 0;
    }
    return TREE_OP_SUCCESS;
}

int _avl_single_rotate_with_left(Tree **self){
    /*
     * inner function to rotate AVL Tree when insert/delete member in AVL Tree
     * */
    Tree *tmp;
    tmp = (*self)->left;
    (*self)->left = tmp->right;
    tmp->right = *self;
    *self = tmp;

    tmp = (*self)->right;
    tmp->height = _max(avl_height_direct(tmp->left), avl_height_direct(tmp->right)) + 1;
    (*self)->height = _max(avl_height_direct((*self)->left), avl_height_direct((*self)->right)) + 1;
    return TREE_OP_SUCCESS;
}

int _avl_single_rotate_with_right(Tree **self){
    Tree *tmp;
    tmp = (*self)->right;
    (*self)->right = tmp->left;
    tmp->left = *self;
    *self = tmp;

    tmp = (*self)->left;
    tmp->height = _max(avl_height_direct(tmp->left), avl_height_direct(tmp->right)) + 1;
    (*self)->height = _max(avl_height_direct((*self)->left), avl_height_direct((*self)->right)) + 1;
    return TREE_OP_SUCCESS;
}

int _avl_double_rotate_with_left(Tree **self){
    int result=TREE_OP_SUCCESS;
    result = _avl_single_rotate_with_right(&((*self)->left));
    if(result != TREE_OP_SUCCESS)return result;
    return _avl_single_rotate_with_left(self);
}

int _avl_double_rotate_with_right(Tree **self){
    int result;
    result = _avl_single_rotate_with_left(&((*self)->right));
    if(result != TREE_OP_SUCCESS)return result;
    return _avl_single_rotate_with_right(self);
}

int avl_insert(Tree **self, void *data, int (*compar)(const void *, const void *)){
    /*
     * Insert data into AVL Tree `self`
     * data in param and data in AVL struct will be compared in function compar
     *
     */
    if(*self == NULL){
        return avl_init(self, data);
    }

    int result=TREE_OP_SUCCESS;

    int compar_result=(*compar)(data, (*self)->data);
    if(compar_result == 0) {
        return TREE_INSERT_SAME_VALUE_ERROR;
    }
    if(compar_result < 0){
        if((*self)->left == NULL){
            // left child is empty, just init an AVL Tree
            result = avl_init(&((*self)->left), data);
            if(result != TREE_OP_SUCCESS)return TREE_INSERT_FAIL_ERROR;
        } else {
            // recursively insert into left child
            result = avl_insert(&((*self)->left), data, compar);
            if(result != TREE_OP_SUCCESS)return result;
            // rotate AVL Tree
            if(avl_height_direct((*self)->left) - avl_height_direct((*self)->right) == 2){
                if((*compar)(data, (*self)->left->data) < 0){
                    result = _avl_single_rotate_with_left(self);
                } else {
                    result = _avl_double_rotate_with_left(self);
                }
                if(result != TREE_OP_SUCCESS)return result;
            }
        }
    } else {
        if((*self)->right == NULL){
            result = avl_init(&((*self)->right), data);
            if(result != TREE_OP_SUCCESS)return result;
        } else {
            result = avl_insert(&((*self)->right), data, compar);
            if(result != TREE_OP_SUCCESS)return result;
            if(avl_height_direct((*self)->right) - avl_height_direct((*self)->left) == 2){
                if((*compar)(data, (*self)->right->data) > 0){
                    result = _avl_single_rotate_with_right(self);
                } else {
                    result = _avl_double_rotate_with_right(self);
                }
                if(result != TREE_OP_SUCCESS)return result;
            }
        }
    }
    // update height according to sub tree
    (*self)->height = _max(avl_height_direct((*self)->left), avl_height_direct((*self)->right)) + 1;

    return TREE_OP_SUCCESS;
}

int _avl_rotate(Tree **self){
    // choose rotate type according to AVL Tree's height
    if(avl_height_direct((*self)->left) - avl_height_direct((*self)->right) == 2){
        if(avl_height_direct((*self)->left->left) > avl_height_direct((*self)->left->right)){
            return _avl_single_rotate_with_left(self);
        }
        return _avl_double_rotate_with_left(self);
    }
    if(avl_height_direct((*self)->right) - avl_height_direct((*self)->left) == 2){
        if(avl_height_direct((*self)->right->right) > avl_height_direct((*self)->right->left)){
            return _avl_single_rotate_with_right(self);
        }
        return _avl_double_rotate_with_right(self);
    }
    return TREE_OP_SUCCESS;
}

int avl_delete(Tree **self, void *data, int *deleted, int (*compar)(const void *, const void *)){
    /*
     * Delete data from AVL Tree `self`
     * data in param and data in AVL struct will be compared in function compar
     *
     * if success found and deleted the target data, deleted will be set to TRUE
     * if not, deleted will be set to FALSE
     *
     */
    if(*self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int result=TREE_OP_SUCCESS;

    int compar_result=(*compar)(data, (*self)->data);
    if(compar_result == 0){
        // delete current Node
        if((*self)->right == NULL){
            Tree *need_free;
            need_free = *self;
            *self = (*self)->left;
            free(need_free);
            if(*self == NULL){
                return TREE_OP_SUCCESS;
            }
        } else {
            // find the minimum child in right tree
            Tree *left_iterator;
            left_iterator = (*self)->right;
            while(left_iterator->left != NULL){
                left_iterator = left_iterator->left;
            }
            // set current node's data to the minimum data in right tree
            (*self)->data = left_iterator->data;

            // then delete the minimum child in right tree
            result = avl_delete(&((*self)->right), (*self)->data, deleted, compar);
            if(result != TREE_OP_SUCCESS)return result;
            (*self)->height = _max(avl_height_direct((*self)->left), avl_height_direct((*self)->right)) + 1;
        }
    } else if(compar_result < 0){
        if((*self)->left == NULL){
            *deleted = 0;
            return TREE_OP_SUCCESS;
        }
        result = avl_delete(&((*self)->left), data, deleted, compar);
        if(result != TREE_OP_SUCCESS)return result;
    } else {
        if((*self)->right == NULL){
            *deleted = 0;
            return TREE_OP_SUCCESS;
        }
        result = avl_delete(&((*self)->right), data, deleted, compar);
        if(result != TREE_OP_SUCCESS)return result;
    }

    // re balance the AVL Tree
    if((*self)->left != NULL){
        result = _avl_rotate(&((*self)->left));
        if(result != TREE_OP_SUCCESS)return result;
    }
    if((*self)->right != NULL){
        result = _avl_rotate(&((*self)->right));
        if(result != TREE_OP_SUCCESS)return result;
    }
    if(*self != NULL){
        result = _avl_rotate(self);
        if(result != TREE_OP_SUCCESS)return result;
    }
    // update AVL Tree's height
    (*self)->height = _max(avl_height_direct((*self)->left), avl_height_direct((*self)->right)) + 1;
    return TREE_OP_SUCCESS;
}

int avl_pre_order_traversal(Tree *self, void *pipe, int (*callback)(const void *, void *)){
    /*
     * traversal whole AVL Tree in pre order
     * apply callback function to each Node's data and the input param pipe during traversal
     *
     * if the callback function's return value is not `TREE_OP_SUCCESS`, traversal will be aborted
     *
     * */
    if(self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int result=TREE_OP_SUCCESS;

    result = (*callback)(self->data, pipe);
    if(result != TREE_OP_SUCCESS)return result;

    if(self->left != NULL){
        result = avl_pre_order_traversal(self->left, callback, pipe);
        if(result != TREE_OP_SUCCESS)return result;
    }

    if(self->right != NULL){
        result = avl_pre_order_traversal(self->right, callback, pipe);
        if(result != TREE_OP_SUCCESS)return result;
    }

    return TREE_OP_SUCCESS;
}

int avl_in_order_traversal(Tree *self, void *pipe, int (*callback)(const void *, void *)){
    if(self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int result=TREE_OP_SUCCESS;

    if(self->left != NULL){
        result = avl_in_order_traversal(self->left, callback, pipe);
        if(result != TREE_OP_SUCCESS)return result;
    }

    result = (*callback)(self->data, pipe);
    if(result != TREE_OP_SUCCESS)return result;

    if(self->right != NULL){
        result = avl_in_order_traversal(self->right, callback, pipe);
        if(result != TREE_OP_SUCCESS)return result;
    }

    return TREE_OP_SUCCESS;
}

int avl_post_order_traversal(Tree *self, void *pipe, int (*callback)(const void *, void *)){
    if(self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int result=TREE_OP_SUCCESS;

    if(self->left != NULL){
        result = avl_post_order_traversal(self->left, callback, pipe);
        if(result != TREE_OP_SUCCESS)return result;
    }

    if(self->right != NULL){
        result = avl_post_order_traversal(self->right, callback, pipe);
        if(result != TREE_OP_SUCCESS)return result;
    }

    result = (*callback)(self->data, pipe);
    if(result != TREE_OP_SUCCESS)return result;

    return TREE_OP_SUCCESS;
}

int avl_level_order_traversal(Tree *self, void *pipe, int (*callback)(const void *, void *)){
    if(self == NULL){
        return TREE_OP_SUCCESS;
    }

    int result=TREE_OP_SUCCESS;

    Tree* queue[TREE_MAX_SIZE];
    int first=0;
    int last=0;

    queue[first] = self;
    first++;

    while(first != last){
        result = (*callback)(queue[last]->data, pipe);
        if(result != TREE_OP_SUCCESS)return result;

        if(queue[last]->left != NULL){
            queue[first] = queue[last]->left;
            first++;
        }
        if(queue[last]->right != NULL){
            queue[first] = queue[last]->right;
            first++;
        }
        last++;
    }

    return TREE_OP_SUCCESS;
}
