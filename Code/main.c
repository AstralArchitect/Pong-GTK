#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include "prototypes.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

GtkWidget *launcher_window;

void open_repo(){
    #ifdef _WIN32
    system("start https://github.com/astralarchitect/pong-GTK");
    #else
    system("xdg-open https://github.com/astralarchitect/pong-GTK");
    #endif
}

int activate(GtkApplication* app, gpointer user_data) {
    #ifdef _WIN32
    g_setenv("GTK_THEME", "win32", FALSE);
    #endif
    launcher_window = gtk_application_window_new(app);
    g_signal_connect(launcher_window, "destroy", G_CALLBACK(gtk_window_close), launcher_window);
    gtk_window_set_resizable(GTK_WINDOW(launcher_window), false);
    gtk_window_set_default_size(GTK_WINDOW(launcher_window), (200 * 4) + (5 * 4) - 5, 70);
    gtk_window_set_title(GTK_WINDOW(launcher_window), "Pong Launcher");

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    GtkWidget *button_play = gtk_button_new_with_label("Jouer à Pong");
    GtkWidget *button_info = gtk_button_new_with_label("info");
    GtkWidget *button_repo = gtk_button_new_with_label("Repo Github");
    GtkWidget *button_configure = gtk_button_new_with_label("Paramètres");

    // Définir la taille minimale des boutons
    gtk_widget_set_size_request(button_play, 200, 70);
    gtk_widget_set_size_request(button_info, 200, 70);
    gtk_widget_set_size_request(button_repo, 200, 70);
    gtk_widget_set_size_request(button_configure, 200, 70);

    g_signal_connect(button_play, "clicked", G_CALLBACK(game_setup), app);
    g_signal_connect(button_info, "clicked", G_CALLBACK(info), NULL);
    g_signal_connect(button_repo, "clicked", G_CALLBACK(open_repo), NULL);
    g_signal_connect(button_configure, "clicked", G_CALLBACK(settings), NULL);

    gtk_container_add(GTK_CONTAINER(box), button_play);
    gtk_container_add(GTK_CONTAINER(box), button_info);
    gtk_container_add(GTK_CONTAINER(box), button_repo);
    gtk_container_add(GTK_CONTAINER(box), button_configure);

    gtk_container_add(GTK_CONTAINER(launcher_window), box);

    gtk_widget_show_all(launcher_window);

    return 0;
}

int main (int argc, char **argv){
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}