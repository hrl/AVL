//
// Created by hrl on 9/21/15.
//

#ifndef AVL_SNS_FUNCTIONS_H
#define AVL_SNS_FUNCTIONS_H

#import "sns_structs.h"

int people_compar(const void *a, const void *b);
int people_init(Set *universal, People **self);
int people_del(Set *universal, People **self);
int people_follow(Set *universal, People *self, People *target);
int people_friend(Set *universal, People *self, People *target);
int people_followings(People *self, Set **followings);
int people_followers(People *self, Set **followers);
int people_friends(People *self, Set **friends);
int people_is_following(People *self, People *target, int *is_following);
int people_is_follower(People *self, People *target, int *is_follower);
int people_is_friend(People *self, People *target, int *is_friend);
int people_common_followings(People *self, People *target, Set **common_followings);
int people_common_followers(People *self, People *target, Set **common_followers);
int people_extend_friends(Set *universal, People *self, Set **extend_friends);

#endif //AVL_SNS_FUNCTIONS_H
