#include <gtk/gtk.h>
#include <glib.h>
#include <stdbool.h>

int info(){
    gtk_init(NULL, NULL);

    GtkWidget *window;
    GtkWidget *label;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window, 1000, 0);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable((GtkWindow*)window, true);

    gtk_window_set_title(GTK_WINDOW(window), "Info");

    // Création et configuration du label
    label = gtk_label_new("\nCeci est un pong créé par Astral Architect\n\n1. Le but du jeu: \n\tLe but du jeu est de renvoyer la balle le plus de fois possible et de ne pas la laisser passer derière vous.\n\n2. Comment Jouer:\n\tVous êtes la raquette (rectangle) verte que vous devrez bouger avec les flèches du clavier.\n3. Arrêt du Jeu:\n\tL'ordinateur est imbattable, le jeu s'arrète donc lorsque vous avez perdu.\n");
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);  // Permet de faire un retour à la ligne si le texte est trop long

    // Ajout du label à la fenêtre
    gtk_container_add(GTK_CONTAINER(window), label);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
