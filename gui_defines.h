//
// Created by hrl on 9/22/15.
//

#ifndef AVL_GUI_DEFINES_H
#define AVL_GUI_DEFINES_H

// tmp
#define UI_FILE "/home/hrl/ClionProjects/AVL/UI.xml"

const char *version = "0.1";
const char *program_name = "数据结构课设演示系统";
const char *comments = "基于AVL树实现集合，基于集合实现SNS基础功能";
const char *website = "https://github.com/hrl/AVL";
const char *website_lable = "GitHub";
const char *author[] = {"Ruilin Huang", NULL};

char *sns_filename=NULL;
short sns_changed=0;
GtkWindow *window=NULL;
GtkTreeView *treeview=NULL;
void (*last_func)(void *pass, int call_type)=NULL;

Sns *SNS=NULL;

enum {
    GUI_OP_SUCCESS
};

enum {
    CALL_TYPE_NORMAL,
    CALL_TYPE_REDO
};

enum {
    FILE_CHOOSE_OPEN,
    FILE_CHOOSE_SAVE,
    FILE_CHOOSE_SAVE_AS
};

enum {
    TYPE_PEOPLE,
    TYPE_TAG
};

enum {
    PEOPLE_ALL,
    TAG_ALL
};

enum {
    PEOPLE_ALL_POINTER,
    PEOPLE_ALL_TYPE,
    PEOPLE_ALL_ID,
    PEOPLE_ALL_NAME,
    PEOPLE_ALL_FOLLOWINGS_COUNT,
    PEOPLE_ALL_FOLLOWERS_COUNT,
    PEOPLE_ALL_FRIENDS_COUNT,
    PEOPLE_ALL_TAGS_COUNT,
    PEOPLE_ALL_COLUMNS
};

enum {
    TAG_ALL_POINTER,
    TAG_ALL_TYPE,
    TAG_ALL_ID,
    TAG_ALL_NAME,
    TAG_ALL_PEOPLES_COUNT,
    TAG_ALL_COLUMNS
};

#endif //AVL_GUI_DEFINES_H
