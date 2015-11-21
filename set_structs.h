//
// Created by hrl on 9/9/15.
//

#ifndef AVL_SET_STRUCTS_H
#define AVL_SET_STRUCTS_H

#include "avl_structs.h"

struct set {
    // inner tree to store value
    Tree *_tree;
    // store SET's size
    int size;
};

typedef struct set Set;

#endif //AVL_SET_STRUCTS_H
