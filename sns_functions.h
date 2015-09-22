//
// Created by hrl on 9/21/15.
//

#ifndef AVL_SNS_FUNCTIONS_H
#define AVL_SNS_FUNCTIONS_H

#include "sns_structs.h"

int people_compar(const void *a, const void *b);
int sns_init(Sns **self);
int sns_del(Sns **self);
int sns_search_people(Sns *self, People *people, People **result_people, int *result_found);
int sns_search_tag(Sns *self, Tag *tag, Tag **result_tag, int *result_found);
int sns_insert_people(Sns *self, People *people, int id_given);
int sns_insert_tag(Sns *self, Tag *tag, int id_given);
int sns_delete_people(Sns *self, People *people);
int sns_map(Sns *self, void *pipe, int (*callback)(const void *, void *));
int tag_init(Sns *universal, Tag **self, char name[100], int id, int id_given);
int tag_del(Sns *universal, Tag **self);
int people_init(Sns *universal, People **self, char name[100], int id, int id_given);
int people_del(Sns *universal, People **self);
int people_follow(People *self, People *target);
int people_unfollow(People *self, People *target);
int people_friend(People *self, People *target);
int people_unfriend(People *self, People *target);
int people_tag(People *self, Tag *target);
int people_untag(People *self, Tag *target);
int people_followings(People *self, Set **followings);
int people_followers(People *self, Set **followers);
int people_friends(People *self, Set **friends);
int people_tags(People *self, Set **tags);
int people_has_following(People *self, People *target, int *is_following);
int people_has_follower(People *self, People *target, int *is_follower);
int people_has_friend(People *self, People *target, int *is_friend);
int people_common_followings(People *self, People *target, Set **common_followings);
int people_common_followers(People *self, People *target, Set **common_followers);
int people_common_tags(People *self, People *target, Set **common_tags);
int people_extend_friends(Set *universal, People *self, Set **extend_friends);

#endif //AVL_SNS_FUNCTIONS_H
