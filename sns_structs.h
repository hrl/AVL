//
// Created by hrl on 9/21/15.
//

#ifndef AVL_SNS_STRUCTS_H
#define AVL_SNS_STRUCTS_H

#include "set_structs.h"

struct sns {
    int id_max;
    Set *_peoples;
};

struct people {
    int id;
    char name[100];
    Set *friends;
    Set *followings;
    Set *followers;
};

typedef struct sns Sns;
typedef struct people People;

#endif //AVL_SNS_STRUCTS_H
