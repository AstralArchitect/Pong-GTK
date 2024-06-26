#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include "prototypes.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

GtkWidget *window;

void open_repo(){
    #ifdef _WIN32
    system("start https://github.com/astralarchitect/pong-GTK");
    #else
    system("xdg-open https://github.com/astralarchitect/pong-GTK");
    #endif
}

void quitterFonction(){
    exit(0);
}

int main(int argc, char *argv[]) {
    #ifdef _WIN32
    g_setenv("GTK_THEME", "win32", FALSE);
    #endif
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(quitterFonction), NULL);
    gtk_window_set_resizable((GtkWindow*)window, false);
    gtk_window_set_default_size((GtkWindow*)window, (200 * 5) + ((5 * 5) - 5), 70);
    gtk_window_set_title(GTK_WINDOW(window), "Pong Launcher");

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    GtkWidget *button_play = gtk_button_new_with_label("Jouer à Pong");
    GtkWidget *button_info = gtk_button_new_with_label("info");
    GtkWidget *button_repo = gtk_button_new_with_label("Repo Github");
    GtkWidget *button_configure = gtk_button_new_with_label("Paramètres");
    GtkWidget *button_quit = gtk_button_new_with_label("Quitter");

    // Définir la taille minimale des boutons
    gtk_widget_set_size_request(button_play, 200, 70);
    gtk_widget_set_size_request(button_info, 200, 70);
    gtk_widget_set_size_request(button_repo, 200, 70);
    gtk_widget_set_size_request(button_configure, 200, 70);
    gtk_widget_set_size_request(button_quit, 200, 70);

    g_signal_connect(button_play, "clicked", G_CALLBACK(game_setup), window);
    g_signal_connect(button_info, "clicked", G_CALLBACK(info), NULL);
    g_signal_connect(button_repo, "clicked", G_CALLBACK(open_repo), NULL);
    g_signal_connect(button_configure, "clicked", G_CALLBACK(settings), NULL);
    g_signal_connect(button_quit, "clicked", G_CALLBACK(quitterFonction), NULL);

    gtk_container_add(GTK_CONTAINER(box), button_play);
    gtk_container_add(GTK_CONTAINER(box), button_info);
    gtk_container_add(GTK_CONTAINER(box), button_repo);
    gtk_container_add(GTK_CONTAINER(box), button_configure);
    gtk_container_add(GTK_CONTAINER(box), button_quit);

    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}