//
// Created by hrl on 9/22/15.
//

#ifndef AVL_GUI_DEFINES_H
#define AVL_GUI_DEFINES_H

#define UI_FILE "UI.xml"

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
    CALL_TYPE_NORMAL,
    CALL_TYPE_REDO,
};

enum {
    FILE_CHOOSE_OPEN,
    FILE_CHOOSE_SAVE,
    FILE_CHOOSE_SAVE_AS,
};

#endif //AVL_GUI_DEFINES_H
