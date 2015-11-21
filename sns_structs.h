//
// Created by hrl on 9/21/15.
//

#ifndef AVL_SNS_STRUCTS_H
#define AVL_SNS_STRUCTS_H

#include "set_structs.h"

struct sns {
    int peoples_id_max;
    int tags_id_max;
    Set *_peoples;
    Set *_tags;
};

struct tag {
    int id;
    char name[100];
    // inner SET to store peoples who have this tag
    Set *_peoples;
};

struct people {
    int id;
    char name[100];
    // function people_del rely on the order of following pointers
    Set *_followings;
    Set *_followers;
    Set *_friends;
    Set *__incoming_friends;
    Set *_tags;
};

typedef struct sns Sns;
typedef struct tag Tag;
typedef struct people People;

#endif //AVL_SNS_STRUCTS_H
