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

FILE *sns_file=NULL;
short sns_changed=0;
GtkWindow *window=NULL;
GtkTreeView *treeview=NULL;
Sns *SNS=NULL;

#endif //AVL_GUI_DEFINES_H
