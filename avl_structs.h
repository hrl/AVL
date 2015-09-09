//
// Created by hrl on 9/9/15.
//

#ifndef AVL_AVL_STRUCTS_H
#define AVL_AVL_STRUCTS_H

struct tree {
    void *data;
    int height;
    struct tree *left;
    struct tree *right;
};
typedef struct tree Tree;

#endif //AVL_AVL_STRUCTS_H
