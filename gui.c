//
// Created by hrl on 9/22/15.
//

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <cJSON.h>
#include <gtk/gtk.h>
#include "sns_functions.h"
#include "gui_functions.h"
#include "sns_structs.h"
#include "gui_structs.h"
#include "sns_defines.h"
#include "gui_defines.h"
#include "set_functions.h"

void build_UI() {
    GtkBuilder *builder = NULL;
    GError *error = NULL;
    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, UI_FILE, &error)) {
        g_warning("%s", error->message);
        g_free(error);
        exit(1);
    }

    /* Get objects */
    /* Main window */
    window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));
    treeview = GTK_TREE_VIEW(gtk_builder_get_object(builder, "treeview"));
    /* -SNS menu */
    /* --SNS file menu */
    GtkWidget *menu_sns_file_new = GTK_WIDGET(gtk_builder_get_object(builder, "sns_file_new"));
    GtkWidget *menu_sns_file_load = GTK_WIDGET(gtk_builder_get_object(builder, "sns_file_load"));
    GtkWidget *menu_sns_file_save = GTK_WIDGET(gtk_builder_get_object(builder, "sns_file_save"));
    /* --SNS people menu */
    GtkWidget *menu_sns_people_new = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_new"));
    GtkWidget *menu_sns_people_all = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_all"));
    GtkWidget *menu_sns_people_follow = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_follow"));
    GtkWidget *menu_sns_people_friend = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_friend"));
    GtkWidget *menu_sns_people_tag = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_tag"));
    GtkWidget *menu_sns_people_unfollow = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_unfollow"));
    GtkWidget *menu_sns_people_unfriend = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_unfriend"));
    GtkWidget *menu_sns_people_untag = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_untag"));
    GtkWidget *menu_sns_people_followings = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_followings"));
    GtkWidget *menu_sns_people_followers = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_followers"));
    GtkWidget *menu_sns_people_friends = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_friends"));
    GtkWidget *menu_sns_people_tags = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_tags"));
    GtkWidget *menu_sns_people_c_followings = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_c_followings"));
    GtkWidget *menu_sns_people_c_followers = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_c_followers"));
    GtkWidget *menu_sns_people_e_friends = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_e_friends"));
    GtkWidget *menu_sns_people_c_tags = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_c_tags"));
    GtkWidget *menu_sns_people_delete = GTK_WIDGET(gtk_builder_get_object(builder, "sns_people_delete"));
    /* --SNS tag menu */
    GtkWidget *menu_sns_tag_new = GTK_WIDGET(gtk_builder_get_object(builder, "sns_tag_new"));
    GtkWidget *menu_sns_tag_all = GTK_WIDGET(gtk_builder_get_object(builder, "sns_tag_all"));
    GtkWidget *menu_sns_tag_delete = GTK_WIDGET(gtk_builder_get_object(builder, "sns_tag_delete"));
    /* -Other menu */
    GtkWidget *menu_other_about = GTK_WIDGET(gtk_builder_get_object(builder, "other_about"));
    GtkWidget *menu_other_quit = GTK_WIDGET(gtk_builder_get_object(builder, "other_quit"));
    /* End Get objects */

    /* Connect signals */
    /* Main window */
    g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(gui_other_quit), NULL);
    /* -SNS menu */
    /* --SNS file menu */
    g_signal_connect(G_OBJECT(menu_sns_file_new), "activate", G_CALLBACK(gui_sns_file_new), NULL);
    g_signal_connect(G_OBJECT(menu_sns_file_load), "activate", G_CALLBACK(gui_sns_file_load), NULL);
    g_signal_connect(G_OBJECT(menu_sns_file_save), "activate", G_CALLBACK(gui_sns_file_save), NULL);
    /* --SNS people menu */
    g_signal_connect(G_OBJECT(menu_sns_people_new), "activate", G_CALLBACK(gui_sns_people_new), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_all), "activate", G_CALLBACK(gui_sns_people_all), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_follow), "activate", G_CALLBACK(gui_sns_people_follow), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_friend), "activate", G_CALLBACK(gui_sns_people_friend), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_tag), "activate", G_CALLBACK(gui_sns_people_tag), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_unfollow), "activate", G_CALLBACK(gui_sns_people_unfollow), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_unfriend), "activate", G_CALLBACK(gui_sns_people_unfriend), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_untag), "activate", G_CALLBACK(gui_sns_people_untag), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_followings), "activate", G_CALLBACK(gui_sns_people_followings), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_followers), "activate", G_CALLBACK(gui_sns_people_followers), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_friends), "activate", G_CALLBACK(gui_sns_people_friends), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_tags), "activate", G_CALLBACK(gui_sns_people_tags), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_c_followings), "activate", G_CALLBACK(gui_sns_people_c_followings), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_c_followers), "activate", G_CALLBACK(gui_sns_people_c_followers), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_e_friends), "activate", G_CALLBACK(gui_sns_people_e_friends), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_c_tags), "activate", G_CALLBACK(gui_sns_people_c_tags), NULL);
    g_signal_connect(G_OBJECT(menu_sns_people_delete), "activate", G_CALLBACK(gui_sns_people_delete), NULL);
    /* --SNS tag menu */
    g_signal_connect(G_OBJECT(menu_sns_tag_new), "activate", G_CALLBACK(gui_sns_tag_new), NULL);
    g_signal_connect(G_OBJECT(menu_sns_tag_all), "activate", G_CALLBACK(gui_sns_tag_all), NULL);
    g_signal_connect(G_OBJECT(menu_sns_tag_delete), "activate", G_CALLBACK(gui_sns_tag_delete), NULL);
    /* -Other menu */
    g_signal_connect(G_OBJECT(menu_other_about), "activate", G_CALLBACK(gui_other_about), NULL);
    g_signal_connect(G_OBJECT(menu_other_quit), "activate", G_CALLBACK(gui_other_quit), NULL);

    /* End Connect signals */

    /* Destroy builder */
    g_object_unref(G_OBJECT(builder));

    /* Show window */
    gtk_widget_show_all(GTK_WIDGET(window));
}

/* Basic function */
void _gui_call_last_func(){
    if(last_func != NULL){
        (*last_func)(NULL, CALL_TYPE_REDO);
    }
}

void gui_clean_var(){
    sns_del(&SNS);
    SNS = NULL;
}

void _gui_clean_column(){
    int columns;
    GtkTreeViewColumn *column;
    columns = gtk_tree_view_get_n_columns(treeview);

    while(columns){
        column = gtk_tree_view_get_column(treeview, 0);
        gtk_tree_view_remove_column(treeview, column);
        columns--;
    }
}

GtkWidget** gui_create_message_dialog(GtkWindow *fwindow, char *messages, GtkMessageType type, GtkWidget **dialog_response){
    GtkButtonsType buttons = GTK_BUTTONS_OK;
    switch(type){
        case GTK_MESSAGE_ERROR: buttons = GTK_BUTTONS_OK; break;
        case GTK_MESSAGE_WARNING: buttons = GTK_BUTTONS_OK; break;
        case GTK_MESSAGE_QUESTION: buttons = GTK_BUTTONS_YES_NO; break;
        case GTK_MESSAGE_INFO:break;
        case GTK_MESSAGE_OTHER:break;
    }

    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog_response[0] = GTK_WIDGET(gtk_message_dialog_new(
        fwindow,
        flags,
        type,
        buttons,
        messages
    ));

    return dialog_response;
}

GtkWidget** gui_create_edit_dialog(GtkWindow *fwindow, int rws, char argi[][100], GtkWidget **dialog_response){
    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog_response[0] = GTK_WIDGET(gtk_dialog_new_with_buttons(
            argi[0],
            window,
            flags,
            "确定", GTK_RESPONSE_ACCEPT,
            "取消", GTK_RESPONSE_REJECT,
            NULL));

    dialog_response[1] = gtk_grid_new();
    gtk_grid_insert_column(GTK_GRID(dialog_response[1]), 0);
    gtk_grid_insert_column(GTK_GRID(dialog_response[1]), 1);

    int i;
    for(i=0; i<rws; i++){
        gtk_grid_insert_row(GTK_GRID(dialog_response[1]), i);
    }

    gtk_grid_set_row_spacing(GTK_GRID(dialog_response[1]), 5);
    gtk_grid_set_column_spacing(GTK_GRID(dialog_response[1]), 5);

    for(i=1; i<=rws; i++){
        dialog_response[2*i] = gtk_label_new(argi[i]);
        dialog_response[2*i+1] = gtk_entry_new();
        gtk_entry_set_text(GTK_ENTRY(dialog_response[2*i+1]), argi[i+rws]);
        gtk_grid_attach(GTK_GRID(dialog_response[1]), dialog_response[2*i], 0, i, 1, 1);
        gtk_grid_attach(GTK_GRID(dialog_response[1]), dialog_response[2*i+1], 1, i, 1, 1);
    }

    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog_response[0]))), dialog_response[1]);

    return dialog_response;
}

void gui_show_message(char *messages, GtkMessageType type){
    GtkWidget **question_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));
    question_dialog = gui_create_message_dialog(window, messages, type, question_dialog);
    gtk_widget_show_all(question_dialog[0]);
    gtk_dialog_run(GTK_DIALOG(question_dialog[0]));
    gtk_widget_destroy(GTK_WIDGET(question_dialog[0]));
    free(question_dialog);
}

void gui_save_confirmation(){
    if(sns_changed == 1){
        GtkWidget **question_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));
        question_dialog = gui_create_message_dialog(window, "更改尚未保存，要保存吗?", GTK_MESSAGE_QUESTION, question_dialog);
        gtk_widget_show_all(question_dialog[0]);

        if(gtk_dialog_run(GTK_DIALOG(question_dialog[0])) == GTK_RESPONSE_YES){
            gui_sns_file_save((void*)NULL, CALL_TYPE_NORMAL);
        }
        gtk_widget_destroy(GTK_WIDGET(question_dialog[0]));
        free(question_dialog);
    }
}

void _gui_create_list_store(GtkListStore **liststore, int type){
    switch(type){
        case PEOPLE_ALL:{
            *liststore = gtk_list_store_new(
                PEOPLE_ALL_COLUMNS,
                G_TYPE_POINTER,
                G_TYPE_INT,
                G_TYPE_INT,    // PEOPLE_ALL_ID
                G_TYPE_STRING, // PEOPLE_ALL_NAME
                G_TYPE_INT,    // PEOPLE_ALL_FOLLOWINGS_COUNT
                G_TYPE_INT,    // PEOPLE_ALL_FOLLOWERS_COUNT
                G_TYPE_INT,    // PEOPLE_ALL_FRIENDS_COUNT
                G_TYPE_INT     // PEOPLE_ALL_TAGS_COUNT
            );
            break;
        }
        case TAG_ALL:{
            *liststore = gtk_list_store_new(
                TAG_ALL_COLUMNS,
                G_TYPE_POINTER,
                G_TYPE_INT,
                G_TYPE_INT,   // TAG_ALL_ID
                G_TYPE_STRING // TAG_ALL_NAME
            );
            break;
        }
    };
}

void _gui_insert_into_list_store(GtkListStore **liststore, void *data, int type){
    GtkTreeIter iterator;
    switch(type){
        case PEOPLE_ALL:{
            People *people_iterator=(People*)data;
            gtk_list_store_append(*liststore, &iterator);
            gtk_list_store_set(
                *liststore, &iterator,
                PEOPLE_ALL_POINTER, people_iterator,
                PEOPLE_ALL_TYPE, TYPE_PEOPLE,
                PEOPLE_ALL_ID, people_iterator->id,
                PEOPLE_ALL_NAME, people_iterator->name,
                PEOPLE_ALL_FOLLOWINGS_COUNT, people_iterator->_followings->size,
                PEOPLE_ALL_FOLLOWERS_COUNT, people_iterator->_followers->size,
                PEOPLE_ALL_FRIENDS_COUNT, people_iterator->_friends->size,
                PEOPLE_ALL_TAGS_COUNT, people_iterator->_tags->size,
                -1
            );
            break;
        }
        case TAG_ALL:{
            Tag *tag_iterator=(Tag*)data;
            gtk_list_store_append(*liststore, &iterator);
            gtk_list_store_set(
                *liststore, &iterator,
                TAG_ALL_POINTER, tag_iterator,
                TAG_ALL_TYPE, TYPE_TAG,
                TAG_ALL_ID, tag_iterator->id,
                TAG_ALL_NAME, tag_iterator->name,
                -1
            );
            break;
        }
    };
}

void _gui_append_column(char column_title[][20], int column_line[], int cls){
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    renderer = gtk_cell_renderer_text_new();
    int i = 0;
    for(i=0; i<cls; i++){
        column = gtk_tree_view_column_new_with_attributes(
            column_title[i],
            renderer,
            "text", column_line[i],
            NULL
        );
        gtk_tree_view_column_set_sort_column_id(column, column_line[i]);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }
}

void _gui_create_column(int type){
    switch(type){
        case PEOPLE_ALL:{
            char column_title[6][20] = {"ID", "用户名", "关注数", "粉丝数", "好友数", "爱好数"};
            int column_line[6] = {PEOPLE_ALL_ID, PEOPLE_ALL_NAME, PEOPLE_ALL_FOLLOWINGS_COUNT, PEOPLE_ALL_FOLLOWERS_COUNT, PEOPLE_ALL_FRIENDS_COUNT, PEOPLE_ALL_TAGS_COUNT};
            int cls=6;
            _gui_append_column(column_title, column_line, cls);
            break;
        }
        case TAG_ALL:{
            char column_title[2][20] = {"ID", "爱好名"};
            int column_line[2] = {TAG_ALL_ID, TAG_ALL_NAME};
            int cls=2;
            _gui_append_column(column_title, column_line, cls);
            break;
        }
    };
}

/* Menu function */
void gui_sns_file_new(void *pass, int call_type){
    gui_save_confirmation();
    gui_clean_var();
    _gui_clean_column();
    sns_init(&SNS);
    sns_changed = 0;
    sns_filename = NULL;
}

char* _gui_file_choose(int type){
    GtkWidget *dialog = NULL;
    GtkFileChooser *chooser = NULL;

    if(type == FILE_CHOOSE_OPEN){
        dialog = gtk_file_chooser_dialog_new(
                "打开", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
                "取消", GTK_RESPONSE_CANCEL,
                "确定", GTK_RESPONSE_ACCEPT, NULL);
    } else if(type == FILE_CHOOSE_SAVE){
        dialog = gtk_file_chooser_dialog_new(
                "保存", NULL, GTK_FILE_CHOOSER_ACTION_SAVE,
                "取消", GTK_RESPONSE_CANCEL,
                "确定", GTK_RESPONSE_ACCEPT, NULL);
        gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);
    }

    if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT){
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        gtk_widget_destroy(dialog);
        return filename;
    } else {
        gtk_widget_destroy(dialog);
        return NULL;
    }
}

void gui_sns_file_load(void *pass, int call_type){
    gui_save_confirmation();
    sns_filename=_gui_file_choose(FILE_CHOOSE_OPEN);
    if(sns_filename != NULL){
        gui_clean_var();
        int result;
        result = sns_json_file_read(&SNS, sns_filename);
        if(result != SNS_OP_SUCCESS){
            gui_clean_var();
            gui_show_message("文件损坏", GTK_MESSAGE_ERROR);
        }
        _gui_clean_column();
    }
}

void _gui_sns_file_save_as(void *pass, int call_type){
    sns_filename=_gui_file_choose(FILE_CHOOSE_SAVE);
    if(sns_filename != NULL){
        int result;
        result = sns_json_file_write(SNS, sns_filename);
        if(result != SNS_OP_SUCCESS){
            gui_show_message("文件保存失败", GTK_MESSAGE_ERROR);
        } else {
            sns_changed = 0;
        }
    }
}

void gui_sns_file_save(void *pass, int call_type){
    if(sns_filename == NULL){
        return _gui_sns_file_save_as(pass, call_type);
    }
    int result;
    result = sns_json_file_write(SNS, sns_filename);
    if(result != SNS_OP_SUCCESS){
        gui_show_message("文件保存失败", GTK_MESSAGE_ERROR);
    } else {
        sns_changed = 0;
    }
}

int _gui_sns_people_dialog(void *self){
    People **people=(People**)self;
    int rws=1;
    char title[100];
    char argi[rws*2+1][100];

    if(people == NULL){
        strcpy(title, "新建用户");
        strcpy(argi[rws+1], "");
    } else {
        strcpy(title, "编辑用户");
        strcpy(argi[rws+1], (*people)->name);
    }
    strcpy(argi[0], title);
    strcpy(argi[1], "用户名");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = gui_create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    int result;
    GtkEntryBuffer *buffer;
    char name[100];
    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
        validate_message[0] = '\0';

        buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
        if(gtk_entry_buffer_get_length(buffer) >= 100){
            strcpy(validate_message, "用户名过长");
        } else {
            strcpy(name, gtk_entry_buffer_get_text(buffer));
        }

        if(validate_message[0] != '\0'){
            gui_show_message(validate_message, GTK_MESSAGE_WARNING);
            continue;
        }

        if(people == NULL){
            People *_people_tmp=NULL;
            people = &_people_tmp;
            result = people_init(SNS, people, name, 0, 0);
        } else {
            strcpy((*people)->name, name);
            result = PEOPLE_OP_SUCCESS;
        }
        break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));
    free(dialog_result);

    return result;
}

void gui_sns_people_new(void *pass, int call_type){
    if(_gui_sns_people_dialog(NULL) == PEOPLE_OP_SUCCESS){
        sns_changed = 1;
        _gui_call_last_func();
    }
}

struct _gui_sns_people_pipe {
    GtkListStore **liststore;
};
typedef struct _gui_sns_people_pipe _Gui_sns_people_pipe;

int _gui_sns_people_pipe_init(_Gui_sns_people_pipe **_pipe){
    *_pipe = (_Gui_sns_people_pipe*)malloc(sizeof(_Gui_sns_people_pipe));
    (*_pipe)->liststore = NULL;
    return GUI_OP_SUCCESS;
}

int _gui_sns_people_pipe_del(_Gui_sns_people_pipe **_pipe){
    free(*_pipe);
    *_pipe = NULL;
    return GUI_OP_SUCCESS;
}

int _gui_sns_people_insert_into_column(const void *data, void *_pipe){
    _Gui_sns_people_pipe *pipe=NULL;
    pipe = (_Gui_sns_people_pipe*)_pipe;

    _gui_insert_into_list_store(pipe->liststore, (People*)data, PEOPLE_ALL);

    return GUI_OP_SUCCESS;
}

void _gui_sns_people_common_show(Set *people_set){
    GtkListStore *liststore=NULL;
    _gui_create_list_store(&liststore, PEOPLE_ALL);

    _Gui_sns_people_pipe *_pipe=NULL;
    _gui_sns_people_pipe_init(&_pipe);
    _pipe->liststore = &liststore;

    int result;
    result = set_map(people_set, _pipe, _gui_sns_people_insert_into_column);
    if(result != GUI_OP_SUCCESS) gui_show_message("查询失败", GTK_MESSAGE_WARNING);

    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
    _gui_create_column(PEOPLE_ALL);

    _gui_sns_people_pipe_del(&_pipe);
}

void gui_sns_people_all(void *pass, int call_type){
    last_func = gui_sns_people_all;
    _gui_clean_column();
    _gui_sns_people_common_show(SNS->_peoples);
}

void _gui_sns_people_get_selection(People **people){
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeIter iter;
    GtkTreeModel *model;
    gpointer *self;
    gint type;

    if(gtk_tree_selection_get_selected(selection, &model, &iter)) {
        /* check */
        gtk_tree_model_get(model, &iter, 0, &self, -1);
        gtk_tree_model_get(model, &iter, 1, &type, -1);
        if(self == NULL || type != TYPE_PEOPLE) return gui_show_message("请先选择用户", GTK_MESSAGE_INFO);

        *people = (People*)self;
    } else {
        gui_show_message("请先选择用户", GTK_MESSAGE_INFO);
    }
}

int _gui_sns_people_people_id_dialog(People *self, char *messages, int (*callback)(People *, People *)){
    People *people=(People*)self;
    int rws=1;
    char title[100];
    char argi[rws*2+1][100];

    strcpy(title, messages);
    strcpy(argi[0], title);
    strcpy(argi[1], "用户ID");
    strcpy(argi[rws+1], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = gui_create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    int result;
    GtkEntryBuffer *buffer;
    char id_string[10];
    int id;
    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
        validate_message[0] = '\0';

        buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
        if(gtk_entry_buffer_get_length(buffer) >= 10){
            strcpy(validate_message, "用户ID过长");
        } else {
            strcpy(id_string, gtk_entry_buffer_get_text(buffer));
            id = atoi(id_string);
        }

        if(validate_message[0] != '\0'){
            gui_show_message(validate_message, GTK_MESSAGE_WARNING);
            continue;
        }

        People *target=NULL;
        result = sns_search_people(SNS, id, &target);
        if(result != SNS_OP_SUCCESS) continue;
        result = (*callback)(self, target);
        break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));
    free(dialog_result);

    return result;
}

int _gui_sns_people_tag_id_dialog(People *self, char *messages, int (*callback)(People *, Tag *)){
    People *people=(People*)self;
    int rws=1;
    char title[100];
    char argi[rws*2+1][100];

    strcpy(title, messages);
    strcpy(argi[0], title);
    strcpy(argi[1], "爱好ID");
    strcpy(argi[rws+1], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = gui_create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    int result;
    GtkEntryBuffer *buffer;
    char id_string[10];
    int id;
    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
        validate_message[0] = '\0';

        buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
        if(gtk_entry_buffer_get_length(buffer) >= 10){
            strcpy(validate_message, "爱好ID过长");
        } else {
            strcpy(id_string, gtk_entry_buffer_get_text(buffer));
            id = atoi(id_string);
        }

        if(validate_message[0] != '\0'){
            gui_show_message(validate_message, GTK_MESSAGE_WARNING);
            continue;
        }

        Tag *target=NULL;
        result = sns_search_tag(SNS, id, &target);
        if(result != SNS_OP_SUCCESS) continue;
        result = (*callback)(self, target);
        break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));
    free(dialog_result);

    return result;
}

void gui_sns_people_follow(void *pass, int call_type){
    People *people=NULL;
    _gui_sns_people_get_selection(&people);
    if(people != NULL){
        int result;
        result = _gui_sns_people_people_id_dialog(people, "添加新关注", people_follow);
        if(result != SNS_OP_SUCCESS) return gui_show_message("操作失败", GTK_MESSAGE_WARNING);
    }

    _gui_call_last_func();
}

void gui_sns_people_friend(void *pass, int call_type){
    People *people=NULL;
    _gui_sns_people_get_selection(&people);
    if(people != NULL){
        int result;
        result = _gui_sns_people_people_id_dialog(people, "添加新好友", people_friend);
        if(result != SNS_OP_SUCCESS) return gui_show_message("操作失败", GTK_MESSAGE_WARNING);
    }

    _gui_call_last_func();
}

void gui_sns_people_tag(void *pass, int call_type){
    People *people=NULL;
    _gui_sns_people_get_selection(&people);
    if(people != NULL){
        int result;
        result = _gui_sns_people_people_id_dialog(people, "添加新爱好", people_tag);
        if(result != SNS_OP_SUCCESS) return gui_show_message("操作失败", GTK_MESSAGE_WARNING);
    }

    _gui_call_last_func();
}
void gui_sns_people_unfollow(void *pass, int call_type){}
void gui_sns_people_unfriend(void *pass, int call_type){}
void gui_sns_people_untag(void *pass, int call_type){}

void gui_sns_people_followings(void *pass, int call_type){
    People *people=NULL;
    _gui_sns_people_get_selection(&people);
    if(people != NULL){
        last_func = gui_sns_people_followings;
        _gui_clean_column();
        _gui_sns_people_common_show(people->_followings);
    }
}

void gui_sns_people_followers(void *pass, int call_type){
    People *people=NULL;
    _gui_sns_people_get_selection(&people);
    if(people != NULL){
        last_func = gui_sns_people_followers;
        _gui_clean_column();
        _gui_sns_people_common_show(people->_followers);
    }
}

void gui_sns_people_friends(void *pass, int call_type){
    People *people=NULL;
    _gui_sns_people_get_selection(&people);
    if(people != NULL){
        last_func = gui_sns_people_friends;
        _gui_clean_column();
        _gui_sns_people_common_show(people->_friends);
    }
}

void gui_sns_people_tags(void *pass, int call_type){}
void gui_sns_people_c_followings(void *pass, int call_type){}
void gui_sns_people_c_followers(void *pass, int call_type){}
void gui_sns_people_e_friends(void *pass, int call_type){}
void gui_sns_people_c_tags(void *pass, int call_type){}

void gui_sns_people_delete(void *pass, int call_type){
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeIter iter;
    GtkTreeModel *model;
    gpointer *self;
    gint type;

    if(gtk_tree_selection_get_selected(selection, &model, &iter)){
        /* check */
        gtk_tree_model_get(model, &iter, 0, &self, -1);
        gtk_tree_model_get(model, &iter, 1, &type, -1);
        if(self == NULL || type != TYPE_PEOPLE) return gui_show_message("请先选择用户", GTK_MESSAGE_INFO);

        GtkWidget **question_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));
        question_dialog = gui_create_message_dialog(window, "确定要删除吗?", GTK_MESSAGE_QUESTION, question_dialog);
        gtk_widget_show_all(question_dialog[0]);

        if(gtk_dialog_run(GTK_DIALOG(question_dialog[0])) == GTK_RESPONSE_YES){
            gtk_tree_model_get(model, &iter, 0, &self, -1);
            int result;
            result = people_del(SNS, ((People**)&self));
            if(result != PEOPLE_OP_SUCCESS) gui_show_message("删除失败", GTK_MESSAGE_ERROR);
            sns_changed = 1;
        }
        gtk_widget_destroy(GTK_WIDGET(question_dialog[0]));
        free(question_dialog);
    } else {
        return gui_show_message("请先选择用户", GTK_MESSAGE_INFO);
    }

    _gui_call_last_func();
}

void gui_sns_tag_new(void *pass, int call_type){}
void gui_sns_tag_all(void *pass, int call_type){}
void gui_sns_tag_delete(void *pass, int call_type){}

void gui_other_about(void *pass, int call_type){
    GtkWidget *about_window = NULL;
    about_window = gtk_about_dialog_new();
    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_window), program_name);
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_window), version);
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_window), comments);
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_window), website);
    gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about_window), website_lable);
    gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG(about_window), author);
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(about_window), NULL);
    gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(about_window), GTK_LICENSE_MIT_X11);
    gtk_widget_show_all(about_window);
}

void gui_other_quit(void *pass, int call_type){
    gui_save_confirmation();
    sns_filename = NULL;
    gtk_main_quit();
}
