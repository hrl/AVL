//
// Created by hrl on 9/9/15.
//

#ifndef AVL_AVL_FUNCTIONS_H
#define AVL_AVL_FUNCTIONS_H

#include "avl_structs.h"

int avl_init(Tree **self);
int avl_del(Tree **self);
int avl_height(Tree **self, int *height);
int avl_search(Tree **self, void *data, Tree **result, int (*compar)(const void *, const void *));
int avl_insert(Tree **self, void *data, int (*compar)(const void *, const void *));
int avl_delete(Tree **self, void *data, int (*compar)(const void *, const void *));
int avl_pre_order_traversal(Tree **self, int (*callback)(const Tree *));
int avl_in_order_traversal(Tree **self, int (*callback)(const Tree *));
int avl_post_order_traversal(Tree **self, int (*callback)(const Tree *));
int avl_level_order_traversal(Tree **self, int (*callback)(const Tree *));

#endif //AVL_AVL_FUNCTIONS_H
