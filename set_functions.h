//
// Created by hrl on 9/9/15.
//

#ifndef AVL_SET_FUNCTIONS_H
#define AVL_SET_FUNCTIONS_H

#include "set_structs.h"

int set_init(Set **self);
int set_init_with_data(Set **self, void *data);
int set_del(Set **self);
int set_is_member(Set *self, void *data, int *result_is_member, int (*compar)(const void *, const void *));
int set_insert(Set **self, void *data, int (*compar)(const void *, const void *));
int set_delete(Set **self, void *data, int (*compar)(const void *, const void *));
int set_intersection(Set *set_a, Set *set_b, Set **result_intersection, int (*compar)(const void *, const void *));
int set_union(Set *set_a, Set *set_b, Set **result_union, int (*compar)(const void *, const void *));
int set_difference(Set *set_a, Set *set_b, Set **result_difference, int (*compar)(const void *, const void *));
int set_is_subset(Set *set_a, Set *set_b, int result_is_subset, int (*compar)(const void *, const void *));
int set_is_equal(Set *set_a, Set *set_b, int result_is_equal, int (*compar)(const void *, const void *));
int set_map(Set *self, void *pipe, int (*callback)(const void *, void *));

#endif //AVL_SET_FUNCTIONS_H
