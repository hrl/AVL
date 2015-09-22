//
// Created by hrl on 9/22/15.
//

#ifndef AVL_GUI_FUNCTIONS_H
#define AVL_GUI_FUNCTIONS_H

void build_UI();

/* -SNS menu */
/* --SNS file menu */
void gui_sns_file_new(void *pass, int call_type);
void gui_sns_file_load(void *pass, int call_type);
void gui_sns_file_save(void *pass, int call_type);
/* --SNS people menu */
void gui_sns_people_new(void *pass, int call_type);
void gui_sns_people_all(void *pass, int call_type);
void gui_sns_people_follow(void *pass, int call_type);
void gui_sns_people_friend(void *pass, int call_type);
void gui_sns_people_tag(void *pass, int call_type);
void gui_sns_people_unfollow(void *pass, int call_type);
void gui_sns_people_unfriend(void *pass, int call_type);
void gui_sns_people_untag(void *pass, int call_type);
void gui_sns_people_followings(void *pass, int call_type);
void gui_sns_people_followers(void *pass, int call_type);
void gui_sns_people_friends(void *pass, int call_type);
void gui_sns_people_tags(void *pass, int call_type);
void gui_sns_people_c_followings(void *pass, int call_type);
void gui_sns_people_c_followers(void *pass, int call_type);
void gui_sns_people_e_friends(void *pass, int call_type);
void gui_sns_people_c_tags(void *pass, int call_type);
void gui_sns_people_delete(void *pass, int call_type);
/* --SNS tag menu */
void gui_sns_tag_new(void *pass, int call_type);
void gui_sns_tag_all(void *pass, int call_type);
void gui_sns_tag_delete(void *pass, int call_type);
/* -Other menu */
void gui_other_about(void *pass, int call_type);
void gui_other_quit(void *pass, int call_type);

#endif //AVL_GUI_FUNCTIONS_H
