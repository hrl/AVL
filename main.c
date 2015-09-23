//
// Created by hrl on 9/9/15.
//

#include <gtk/gtk.h>
#include "gui_functions.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    build_UI();
    gui_sns_file_new(NULL, 0);
    gtk_main();
    return 0;
}
