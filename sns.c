//
// Created by hrl on 9/21/15.
//

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "set_functions.h"
#include "sns_functions.h"
#include "set_structs.h"
#include "sns_structs.h"
#include "set_defines.h"
#include "sns_defines.h"

int _sns_int_max(int a, int b){
    return a>b?a:b;
}

int tag_compar(const void *a, const void *b){
    Tag *A, *B;
    A = (Tag*)a;
    B = (Tag*)b;
    return A->id - B->id;
}

int people_compar(const void *a, const void *b){
    People *A, *B;
    A = (People*)a;
    B = (People*)b;
    return A->id - B->id;
}

int sns_init(Sns **self){
    if(*self != NULL){
        return SNS_INITED_ERROR;
    }

    *self = (Sns*)malloc(sizeof(Sns));
    if(*self == NULL) {
        return SNS_INIT_FAIL_ERROR;
    }

    (*self)->peoples_id_max = 0;
    (*self)->tags_id_max = 0;
    (*self)->_peoples = NULL;
    (*self)->_tags = NULL;

    int result;
    result = set_init(&((*self)->_peoples));
    if(result != SET_OP_SUCCESS) return SNS_INIT_FAIL_ERROR;
    result = set_init(&((*self)->_tags));
    if(result != SET_OP_SUCCESS) return SNS_INIT_FAIL_ERROR;

    return SNS_OP_SUCCESS;
}

int sns_del(Sns **self){
    if(*self == NULL){
        return SNS_OP_SUCCESS;
    }

    set_del(&((*self)->_peoples));
    free(*self);
    *self = NULL;

    return SNS_OP_SUCCESS;
}

int sns_search_people(Sns *self, People *people, People **result_people, int *result_found){
    if(self == NULL){
        return SNS_UNINIT_ERROR;
    }

    if(people == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    int result;
    result = set_search(self->_peoples, people, (void **)result_people, result_found, people_compar);
    if(result != SET_OP_SUCCESS) return SNS_SEARCH_ERROR;

    return SNS_OP_SUCCESS;
}

int sns_search_tag(Sns *self, Tag *tag, Tag **result_tag, int *result_found){
    if(self == NULL){
        return SNS_UNINIT_ERROR;
    }

    if(tag == NULL){
        return TAG_UNINIT_ERROR;
    }

    int result;
    result = set_search(self->_tags, tag, (void **)result_tag, result_found, tag_compar);
    if(result != SET_OP_SUCCESS) return SNS_SEARCH_ERROR;

    return SNS_OP_SUCCESS;
}

int sns_insert_people(Sns *self, People *people, int id_given){
    if(self == NULL){
        return SNS_UNINIT_ERROR;
    }

    if(people == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    if(id_given == 0){
        people->id = self->peoples_id_max + 1;
    }

    int result;
    result = set_insert(&(self->_peoples), people, people_compar);
    if(result != SET_OP_SUCCESS) return SNS_INSERT_FAIL_ERROR;

    if(id_given == 1){
        self->peoples_id_max = _sns_int_max(self->peoples_id_max+1, people->id);
    } else {
        self->peoples_id_max++;
    }

    return SNS_OP_SUCCESS;
}

int sns_insert_tag(Sns *self, Tag *tag, int id_given){
    if (self == NULL) {
        return SNS_UNINIT_ERROR;
    }

    if (tag == NULL) {
        return TAG_UNINIT_ERROR;
    }

    if(id_given == 0){
        tag->id = self->tags_id_max + 1;
    }

    int result;
    result = set_insert(&(self->_tags), tag, tag_compar);
    if (result != SET_OP_SUCCESS) return SNS_INSERT_FAIL_ERROR;

    if(id_given == 1){
        self->tags_id_max = _sns_int_max(self->tags_id_max+1, tag->id);
    } else {
        self->tags_id_max++;
    }

    return SNS_OP_SUCCESS;
}

int sns_delete_people(Sns *self, People *people){
    if(self == NULL){
        return SNS_UNINIT_ERROR;
    }

    if(people == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    int result;
    result = set_delete(&(self->_peoples), people, people_compar);
    if(result != SET_OP_SUCCESS) return SNS_DELETE_FAIL_ERROR;

    return SNS_OP_SUCCESS;
}

int sns_delete_tag(Sns *self, Tag *tag) {
    if (self == NULL) {
        return SNS_UNINIT_ERROR;
    }

    if (tag == NULL) {
        return TAG_UNINIT_ERROR;
    }

    int result;
    result = set_delete(&(self->_tags), tag, tag_compar);
    if (result != SET_OP_SUCCESS) return SNS_DELETE_FAIL_ERROR;

    return SNS_OP_SUCCESS;
}

int sns_map_people(Sns *self, void *pipe, int (*callback)(const void *, void *)){
    int result;
    result = set_map(self->_peoples, pipe, callback);
    if(result != SET_OP_SUCCESS)return result;
    return SNS_OP_SUCCESS;
}

int tag_init(Sns *universal, Tag **self, char name[100], int id, int id_given) {
    if (universal == NULL) {
        return SNS_UNINIT_ERROR;
    }

    if (*self != NULL) {
        return TAG_INITED_ERROR;
    }

    *self = (Tag*)malloc(sizeof(Tag));
    if (*self == NULL) {
        return TAG_INIT_FAIL_ERROR;
    }

    if (id_given == 1) {
        (*self)->id = id;
    } else {
        (*self)->id = 0;
    }
    strcpy((*self)->name, name);
    int result;
    result = sns_insert_tag(universal, *self, id_given);
    if(result != SNS_OP_SUCCESS) return TAG_INIT_FAIL_ERROR;

    return TAG_OP_SUCCESS;
}

int tag_del(Sns *universal, Tag **self){
    if (universal == NULL) {
        return SNS_UNINIT_ERROR;
    }

    if (*self == NULL) {
        return TAG_OP_SUCCESS;
    }

    sns_delete_tag(universal, *self);
    free(*self);
    *self = NULL;

    return TAG_OP_SUCCESS;
}

int people_init(Sns *universal, People **self, char name[100], int id, int id_given){
    if(universal == NULL){
        return SNS_UNINIT_ERROR;
    }

    if(*self != NULL){
        return PEOPLE_INITED_ERROR;
    }

    *self = (People*)malloc(sizeof(People));
    if(*self == NULL) {
        return PEOPLE_INIT_FAIL_ERROR;
    }

    if(id_given == 1){
        (*self)->id = id;
    } else {
        (*self)->id = 0;
    }
    strcpy((*self)->name, name);

    Set **wait_init=&((*self)->_followings);
    int i;
    int result;
    for(i=0; i<5; i++){
        // 0: _followings
        // 1: _followers
        // 2: _friends
        // 3: __incoming_friends
        // 4: _tags
        *wait_init = NULL;
        result = set_init(wait_init);
        if(result != SET_OP_SUCCESS) return PEOPLE_INIT_FAIL_ERROR;
        wait_init++;
    }

    result = sns_insert_people(universal, *self, id_given);
    if(result != SNS_OP_SUCCESS) return PEOPLE_INIT_FAIL_ERROR;

    return PEOPLE_OP_SUCCESS;
}

struct _people_common_pipe {
    People *self;
    int refresh_shift;
    Set *result_set;
    int (*compar)(const void *, const void *);
};
typedef struct _people_common_pipe _People_common_pipe;

int _people_common_pipe_init(_People_common_pipe **_pipe, int (*compar)(const void *, const void *)){
    *_pipe = (_People_common_pipe*)malloc(sizeof(_People_common_pipe));
    (*_pipe)->self = NULL;
    (*_pipe)->refresh_shift = 0;
    (*_pipe)->result_set = NULL;
    set_init(&((*_pipe)->result_set));
    (*_pipe)->compar = compar;
    return PEOPLE_OP_SUCCESS;
}

int _people_common_pipe_del(_People_common_pipe **_pipe){
    if(*_pipe == NULL){
        return PEOPLE_OP_SUCCESS;
    }
    set_del(&((*_pipe)->result_set));
    free(*_pipe);
    *_pipe = NULL;
    return PEOPLE_OP_SUCCESS;
}

int _people_del_refresh_set(const void *data, void *_pipe){
    _People_common_pipe *pipe;
    pipe = (_People_common_pipe*)_pipe;
    // data: People*
    //   ->_followings: Set*
    Set *target_set;
    target_set = *(&(((People*)data)->_followings) + pipe->refresh_shift);

    int result;
    result = set_delete(&target_set, pipe->self, pipe->compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_DEL_FAIL_ERROR;
    return PEOPLE_OP_SUCCESS;
}

int people_del(Sns *universal, People **self){
    if(universal == NULL){
        return SNS_UNINIT_ERROR;
    }

    if(*self == NULL){
        return PEOPLE_OP_SUCCESS;
    }

    _People_common_pipe *_pipe=NULL;
    _people_common_pipe_init(&_pipe, people_compar);

    _pipe->self = *self;
    Set *tmp=(*self)->_followings;

    // refresh followers' followings set
    _pipe->refresh_shift = 0;
    set_map((*self)->_followers, _pipe, _people_del_refresh_set);

    // refresh followings' followers set
    _pipe->refresh_shift++;
    set_map((*self)->_followings, _pipe, _people_del_refresh_set);

    // refresh incoming friends' friends set
    _pipe->refresh_shift++;
    set_map((*self)->__incoming_friends, _pipe, _people_del_refresh_set);

    // refresh friends' incoming friends set
    _pipe->refresh_shift++;
    set_map((*self)->_friends, _pipe, _people_del_refresh_set);

    // refresh universal set
    sns_delete_people(universal, *self);

    // delete self
    set_del(&((*self)->_followings));
    set_del(&((*self)->_followers));
    set_del(&((*self)->_friends));
    set_del(&((*self)->__incoming_friends));
    set_del(&((*self)->_tags));
    free(*self);
    *self = NULL;

    _people_common_pipe_del(&_pipe);

    return PEOPLE_OP_SUCCESS;
}

int people_follow(People *self, People *target){
    if(self == NULL || target == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    int result;
    result = set_insert(&(self->_followings), target, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_FOLLOW_FAIL_ERROR;
    result = set_insert(&(target->_followers), self, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_FOLLOW_FAIL_ERROR;

    return PEOPLE_OP_SUCCESS;
}

int people_unfollow(People *self, People *target){
    if(self == NULL || target == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    int result;
    result = set_delete(&(self->_followings), target, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_FOLLOW_FAIL_ERROR;
    result = set_delete(&(target->_followers), self, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_FOLLOW_FAIL_ERROR;

    return PEOPLE_OP_SUCCESS;
}

int people_friend(People *self, People *target){
    if(self == NULL || target == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    int result;
    result = set_insert(&(self->_friends), target, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_FRIEND_FAIL_ERROR;
    result = set_insert(&(target->__incoming_friends), self, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_FRIEND_FAIL_ERROR;

    return PEOPLE_OP_SUCCESS;
}

int people_unfriend(People *self, People *target){
    if(self == NULL || target == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    int result;
    result = set_delete(&(self->_friends), target, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_FRIEND_FAIL_ERROR;
    result = set_delete(&(target->__incoming_friends), self, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_FRIEND_FAIL_ERROR;

    return PEOPLE_OP_SUCCESS;
}

int people_tag(People *self, Tag *target){
    if(self == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    if(target == NULL){
        return TAG_UNINIT_ERROR;
    }

    int result;
    result = set_insert(&(self->_tags), target, tag_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_TAG_FAIL_ERROR;

    return PEOPLE_OP_SUCCESS;
}

int people_untag(People *self, Tag *target){
    if(self == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    if(target == NULL){
        return TAG_UNINIT_ERROR;
    }

    int result;
    result = set_delete(&(self->_tags), target, tag_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_TAG_FAIL_ERROR;

    return PEOPLE_OP_SUCCESS;
}

int people_followings(People *self, Set **followings){
    if(self == NULL){
        return PEOPLE_UNINIT_ERROR;
    }
    if(*followings != NULL){
        return SET_INITED_ERROR;
    }

    // tmp handle
    *followings = self->_followings;

    return PEOPLE_OP_SUCCESS;
}

int people_followers(People *self, Set **followers){
    if(self == NULL){
        return PEOPLE_UNINIT_ERROR;
    }
    if(*followers != NULL){
        return SET_INITED_ERROR;
    }

    // tmp handle
    *followers = self->_followers;

    return PEOPLE_OP_SUCCESS;
}

int people_friends(People *self, Set **friends){
    if(self == NULL){
        return PEOPLE_UNINIT_ERROR;
    }
    if(*friends != NULL){
        return SET_INITED_ERROR;
    }

    // tmp handle
    *friends = self->_friends;

    return PEOPLE_OP_SUCCESS;
}

int people_tags(People *self, Set **tags){
    if(self == NULL){
        return PEOPLE_UNINIT_ERROR;
    }
    if(*tags != NULL){
        return SET_INITED_ERROR;
    }

    // tmp handle
    *tags = self->_tags;

    return PEOPLE_OP_SUCCESS;
}

int people_has_following(People *self, People *target, int *has_following){
    if(self == NULL || target == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    int result;
    result = set_is_member(self->_followings, target, has_following, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_SEARCH_FAIL_ERROR;

    return PEOPLE_OP_SUCCESS;
}

int people_has_follower(People *self, People *target, int *has_follower){
    if(self == NULL || target == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    int result;
    result = set_is_member(self->_followers, target, has_follower, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_SEARCH_FAIL_ERROR;

    return PEOPLE_OP_SUCCESS;
}

int people_has_friend(People *self, People *target, int *has_friend){
    if(self == NULL || target == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    int result;
    result = set_is_member(self->_friends, target, has_friend, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_SEARCH_FAIL_ERROR;

    return PEOPLE_OP_SUCCESS;
}

int people_has_tag(People *self, Tag *target, int *has_tag){
    if(self == NULL){
        return PEOPLE_UNINIT_ERROR;
    }

    if(target == NULL){
        return TAG_UNINIT_ERROR;
    }

    int result;
    result = set_is_member(self->_tags, target, has_tag, tag_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_SEARCH_FAIL_ERROR;

    return PEOPLE_OP_SUCCESS;
}

int people_common_followings(People *self, People *target, Set **common_followings){
    if(self == NULL || target == NULL){
        return PEOPLE_UNINIT_ERROR;
    }
    if(*common_followings != NULL){
        return SET_INITED_ERROR;
    }

    int result;
    result = set_intersection(self->_followings, target->_followings, common_followings, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_CIRCLE_FAIL_ERROR;
    return PEOPLE_OP_SUCCESS;
}

int people_common_followers(People *self, People *target, Set **common_followers){
    if(self == NULL || target == NULL){
        return PEOPLE_UNINIT_ERROR;
    }
    if(*common_followers != NULL){
        return SET_INITED_ERROR;
    }

    int result;
    result = set_intersection(self->_followers, target->_followers, common_followers, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_CIRCLE_FAIL_ERROR;
    return PEOPLE_OP_SUCCESS;
}

int people_common_tags(People *self, People *target, Set **common_tags){
    if(self == NULL || target == NULL){
        return PEOPLE_UNINIT_ERROR;
    }
    if(*common_tags != NULL){
        return SET_INITED_ERROR;
    }

    int result;
    result = set_intersection(self->_tags, target->_tags, common_tags, tag_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_CIRCLE_FAIL_ERROR;
    return PEOPLE_OP_SUCCESS;
}

int _people_extend_friends(const void *data, void *_pipe){
    _People_common_pipe *pipe=NULL;
    pipe = (_People_common_pipe*)_pipe;
    People *friend=NULL;
    friend = (People*)data;

    int result;
    result = set_extend(pipe->result_set, friend->_friends, pipe->compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_CIRCLE_FAIL_ERROR;

    return PEOPLE_OP_SUCCESS;
}

int people_extend_friends(Set *universal, People *self, Set **extend_friends){
    if(universal == NULL){
        return SNS_UNINIT_ERROR;
    }
    if(self == NULL){
        return PEOPLE_UNINIT_ERROR;
    }
    if(*extend_friends != NULL){
        return SET_INITED_ERROR;
    }

    _People_common_pipe *_pipe=NULL;
    _people_common_pipe_init(&_pipe, people_compar);

    _pipe->self = self;

    int result;

    // map self->_friends to extend result
    result = set_map(self->_friends, _pipe, _people_extend_friends);
    if(result != SET_OP_SUCCESS) return PEOPLE_CIRCLE_FAIL_ERROR;

    // delete self from result
    result = set_delete(&(_pipe->result_set), self, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_CIRCLE_FAIL_ERROR;

    // delete self->_friends from result
    result = set_contract(_pipe->result_set, self->_friends, people_compar);
    if(result != SET_OP_SUCCESS) return PEOPLE_CIRCLE_FAIL_ERROR;

    *extend_friends = _pipe->result_set;

    _people_common_pipe_del(&_pipe);

    return PEOPLE_OP_SUCCESS;
}
