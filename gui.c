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

void gui_sns_file_new(void *pass, int call_type){}
void gui_sns_file_load(void *pass, int call_type){}
void gui_sns_file_save(void *pass, int call_type){}
void gui_sns_people_new(void *pass, int call_type){}
void gui_sns_people_all(void *pass, int call_type){}
void gui_sns_people_follow(void *pass, int call_type){}
void gui_sns_people_friend(void *pass, int call_type){}
void gui_sns_people_tag(void *pass, int call_type){}
void gui_sns_people_unfollow(void *pass, int call_type){}
void gui_sns_people_unfriend(void *pass, int call_type){}
void gui_sns_people_untag(void *pass, int call_type){}
void gui_sns_people_followings(void *pass, int call_type){}
void gui_sns_people_followers(void *pass, int call_type){}
void gui_sns_people_friends(void *pass, int call_type){}
void gui_sns_people_tags(void *pass, int call_type){}
void gui_sns_people_c_followings(void *pass, int call_type){}
void gui_sns_people_c_followers(void *pass, int call_type){}
void gui_sns_people_e_friends(void *pass, int call_type){}
void gui_sns_people_c_tags(void *pass, int call_type){}
void gui_sns_people_delete(void *pass, int call_type){}
void gui_sns_tag_new(void *pass, int call_type){}
void gui_sns_tag_all(void *pass, int call_type){}
void gui_sns_tag_delete(void *pass, int call_type){}
void gui_other_about(void *pass, int call_type){}
void gui_other_quit(void *pass, int call_type){}
