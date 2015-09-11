//
// Created by hrl on 9/9/15.
//

#include <stddef.h>
#include <stdlib.h>
#include "avl_functions.h"
#include "avl_structs.h"
#include "avl_defines.h"

int _max(int a, int b){
    return a>b?a:b;
}

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

int avl_height_direct(Tree *self){
    if(self == NULL){
        return 0;
    }
    return self->height;
}

int avl_search(Tree *self, void *data, Tree **result, int (*compar)(const void *, const void *)){
    if(self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int search_result=(*compar)(data, self->data);
    if(search_result == 0){
        *result = self;
    } else if (search_result > 0 && self->right != NULL) {
        return avl_search(self->right, data, result, compar);
    } else if (search_result < 0 && self->left != NULL) {
        return avl_search(self->left, data, result, compar);
    } else {
        *result = NULL;
    }
    return TREE_OP_SUCCESS;
}

int _avl_single_rotate_with_left(Tree **self){
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

int _avl_direct_init(Tree **self, void *data) {
    int result=TREE_OP_SUCCESS;
    result = avl_init(self);

    if(result == TREE_INIT_FAIL_ERROR){
        result = TREE_INSERT_FAIL_ERROR;
    }

    (*self)->data = data;

    return result;
}

int avl_insert(Tree **self, void *data, int (*compar)(const void *, const void *)){
    if(*self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int result=TREE_OP_SUCCESS;

    int compar_result=(*compar)(data, (*self)->data);
    if(compar_result == 0) {
        return TREE_INSERT_SAME_VALUE_ERROR;
    }
    if(compar_result < 0){
        if((*self)->left == NULL){
            result = _avl_direct_init(&((*self)->left), data);
            if(result != TREE_OP_SUCCESS)return result;
        } else {
            result = avl_insert(&((*self)->left), data, compar);
            if(result != TREE_OP_SUCCESS)return result;
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
            result = _avl_direct_init(&((*self)->right), data);
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
    (*self)->height = _max(avl_height_direct((*self)->left), avl_height_direct((*self)->right)) + 1;

    return TREE_OP_SUCCESS;
}

int _avl_rotate(Tree **self){
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

int avl_delete(Tree **self, void *data, int (*compar)(const void *, const void *)){
    if(*self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int result=TREE_OP_SUCCESS;

    int compar_result=(*compar)(data, (*self)->data);
    if(compar_result == 0){
        if((*self)->right == NULL){
            Tree *need_free;
            need_free = *self;
            *self = (*self)->left;
            free(need_free);
        } else {
            Tree *left_iterator;
            left_iterator = (*self)->right;
            while(left_iterator->left != NULL){
                left_iterator = left_iterator->left;
            }
            (*self)->data = left_iterator->data;

            result = avl_delete(&((*self)->right), data, compar);
            if(result != TREE_OP_SUCCESS)return result;
            (*self)->height = _max(avl_height_direct((*self)->left), avl_height_direct((*self)->right)) + 1;
        }
    } else if(compar_result < 0){
        if((*self)->left == NULL){
            return TREE_OP_SUCCESS;
        }
        result = avl_delete(&((*self)->left), data, compar);
        if(result != TREE_OP_SUCCESS)return result;
    } else {
        if((*self)->right == NULL){
            return TREE_OP_SUCCESS;
        }
        result = avl_delete(&((*self)->right), data, compar);
        if(result != TREE_OP_SUCCESS)return result;
    }

    (*self)->height = _max(avl_height_direct((*self)->left), avl_height_direct((*self)->right)) + 1;
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
    return TREE_OP_SUCCESS;
}

int avl_pre_order_traversal(Tree *self, int (*callback)(const void *)){
    if(self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int result=TREE_OP_SUCCESS;

    result = (*callback)(self->data);
    if(result != TREE_OP_SUCCESS)return result;

    if(self->left != NULL){
        result = avl_pre_order_traversal(self->left, callback);
        if(result != TREE_OP_SUCCESS)return result;
    }

    if(self->right != NULL){
        result = avl_pre_order_traversal(self->right, callback);
        if(result != TREE_OP_SUCCESS)return result;
    }

    return TREE_OP_SUCCESS;
}

int avl_in_order_traversal(Tree *self, int (*callback)(const void *)){
    if(self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int result=TREE_OP_SUCCESS;

    if(self->left != NULL){
        result = avl_in_order_traversal(self->left, callback);
        if(result != TREE_OP_SUCCESS)return result;
    }

    result = (*callback)(self->data);
    if(result != TREE_OP_SUCCESS)return result;

    if(self->right != NULL){
        result = avl_in_order_traversal(self->right, callback);
        if(result != TREE_OP_SUCCESS)return result;
    }

    return TREE_OP_SUCCESS;
}

int avl_post_order_traversal(Tree *self, int (*callback)(const void *)){
    if(self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int result=TREE_OP_SUCCESS;

    if(self->left != NULL){
        result = avl_post_order_traversal(self->left, callback);
        if(result != TREE_OP_SUCCESS)return result;
    }

    if(self->right != NULL){
        result = avl_post_order_traversal(self->right, callback);
        if(result != TREE_OP_SUCCESS)return result;
    }

    result = (*callback)(self->data);
    if(result != TREE_OP_SUCCESS)return result;

    return TREE_OP_SUCCESS;
}

int avl_level_order_traversal(Tree *self, int (*callback)(const void *)){
    if(self == NULL){
        return TREE_UNINIT_ERROR;
    }

    int result=TREE_OP_SUCCESS;

    Tree* queue[TREE_MAX_SIZE];
    int first=0;
    int last=0;

    queue[first] = self;
    first++;

    while(first != last){
        result = (*callback)(queue[last]->data);
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
