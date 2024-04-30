#include <gtk/gtk.h>
#include <glib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

GtkWidget *window;

void game_setup(GtkButton *button, gpointer *pointer);
void info();
void settings();

void open_repo(){
    system("start https://github.com/astralarchitect/pong-GTK");
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable((GtkWindow*)window, false);
    gtk_window_set_title(GTK_WINDOW(window), "Pong Launcher");

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    GtkWidget *button_play = gtk_button_new_with_label("Jouer à Pong");
    GtkWidget *button_info = gtk_button_new_with_label("info");
    #ifdef _WIN32 
    GtkWidget *button_repo = gtk_button_new_with_label("Repo Github");
    #endif
    GtkWidget *button_configure = gtk_button_new_with_label("Paramètres");
    GtkWidget *button_quit = gtk_button_new_with_label("Quitter");

    g_signal_connect(button_play, "clicked", G_CALLBACK(game_setup), window);
    g_signal_connect(button_info, "clicked", G_CALLBACK(info), NULL);
    #ifdef _WIN32 
    g_signal_connect(button_repo, "clicked", G_CALLBACK(open_repo), NULL);
    #endif
    g_signal_connect(button_configure, "clicked", G_CALLBACK(settings), NULL);
    g_signal_connect(button_quit, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    gtk_container_add(GTK_CONTAINER(box), button_play);
    gtk_container_add(GTK_CONTAINER(box), button_info);
    #ifdef _WIN32 
    gtk_container_add(GTK_CONTAINER(box), button_repo);
    #endif
    gtk_container_add(GTK_CONTAINER(box), button_configure);
    gtk_container_add(GTK_CONTAINER(box), button_quit);

    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
