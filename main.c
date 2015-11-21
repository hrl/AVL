//
// Created by hrl on 9/9/15.
//

#include <gtk/gtk.h>
#include "gui_functions.h"

int main(int argc, char *argv[]) {
    // create main UI
    gtk_init(&argc, &argv);
    build_UI();
    // init program
    gui_sns_file_new(NULL, 0);
    // start GTK main loop
    gtk_main();
    return 0;
}
