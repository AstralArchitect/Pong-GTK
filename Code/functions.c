#include <gtk/gtk.h>
#include <glib.h>
#include <stdbool.h>

void info(){
    gtk_init(NULL, NULL);

    GtkWidget *window;
    GtkWidget *label;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window, 1000, 0);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable((GtkWindow*)window, true);

    gtk_window_set_title(GTK_WINDOW(window), "Info");

    // Création et configuration du label
    label = gtk_label_new("\nCeci est un pong créé par Astral Architect\n\n1. Le but du jeu: \n\tLe but du jeu est de renvoyer la balle le plus de fois possible et de ne pas la laisser passer derière vous.\n\n2. Comment Jouer:\n\tVous êtes la raquette (rectangle) verte que vous devrez bouger avec les flèches du clavier.\n\n3. Arrêt du Jeu:\n\tL'ordinateur est imbattable, le jeu s'arrète donc lorsque vous avez perdu.\n");
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);  // Permet de faire un retour à la ligne si le texte est trop long

    // Ajout du label à la fenêtre
    gtk_container_add(GTK_CONTAINER(window), label);

    gtk_widget_show_all(window);

    gtk_main();
}

void quit(){
    exit(1);
}

void on_change_score_clicked(GtkButton *button, GtkEntry *user_data) {
    bool supprFile = false;
    char score;
    FILE *fichier = fopen("score.bin", "rb");
    if (fichier == NULL)
    {
        supprFile = true;
        fichier = fopen("score.bin", "w+b");
        if(fichier == NULL){
            gtk_init(NULL, NULL);

            GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
            g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
            gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
            gtk_window_set_default_size(GTK_WINDOW(window), 100, 100);
            gtk_window_set_title(GTK_WINDOW(window), "Error");

            GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

            GtkWidget *label = gtk_label_new("  Erreur, impossible d'ouvrir le fichier score.bin  ");
            GtkWidget *button_quit = gtk_button_new_with_label("Quitter");

            g_signal_connect(button_quit, "clicked", G_CALLBACK(quit), NULL);

            gtk_widget_set_size_request(button_quit, 200, 70);

            gtk_container_add(GTK_CONTAINER(box),label);
            gtk_container_add(GTK_CONTAINER(box), button_quit);

            gtk_container_add(GTK_CONTAINER(window), box);

            gtk_widget_show_all(window);

            gtk_main();
        }
        score = 0;
        fwrite(&score, sizeof(char), 1, fichier);
        fclose(fichier);
        fichier = fopen("score.bin", "rb");
        if(fichier == NULL){
            gtk_init(NULL, NULL);

            GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
            g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
            gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
            gtk_window_set_default_size(GTK_WINDOW(window), 100, 100);
            gtk_window_set_title(GTK_WINDOW(window), "Error");

            GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

            GtkWidget *label = gtk_label_new("  Erreur, impossible d'ouvrir le fichier score.bin  ");
            GtkWidget *button_quit = gtk_button_new_with_label("Quitter");

            g_signal_connect(button_quit, "clicked", G_CALLBACK(quit), NULL);

            gtk_widget_set_size_request(button_quit, 200, 70);

            gtk_container_add(GTK_CONTAINER(box),label);
            gtk_container_add(GTK_CONTAINER(box), button_quit);

            gtk_container_add(GTK_CONTAINER(window), box);

            gtk_widget_show_all(window);

            gtk_main();
        }
    }
    fread(&score, sizeof(char), 1, fichier);
    fclose(fichier);
    if (supprFile)
    {
        remove("score.bin");
    }

    if (score >= 10)
    {
        GtkEntry *entry = GTK_ENTRY(user_data);
        const gchar *text = gtk_entry_get_text(entry);

        char score = atoi(text);

        FILE *fichier = fopen("score.bin", "w+b");
        if (fichier == NULL)
        {
            gtk_init(NULL, NULL);

            GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
            g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
            gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
            gtk_window_set_default_size(GTK_WINDOW(window), 100, 100);
            gtk_window_set_title(GTK_WINDOW(window), "Error");

            GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

            GtkWidget *label = gtk_label_new("  Erreur, impossible d'ouvrir le fichier score.bin  ");
            GtkWidget *button_quit = gtk_button_new_with_label("Quitter");

            g_signal_connect(button_quit, "clicked", G_CALLBACK(quit), NULL);

            gtk_widget_set_size_request(button_quit, 200, 70);

            gtk_container_add(GTK_CONTAINER(box),label);
            gtk_container_add(GTK_CONTAINER(box), button_quit);

            gtk_container_add(GTK_CONTAINER(window), box);

            gtk_widget_show_all(window);

            gtk_main();
        }
        fwrite(&score, sizeof(char), 1, fichier);
        fclose(fichier);
    }
    else
    {
        gtk_init(NULL, NULL);

        GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
        gtk_window_set_default_size(GTK_WINDOW(window), 100, 100);
        gtk_window_set_title(GTK_WINDOW(window), "Error");

        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        
        GtkWidget *label = gtk_label_new("  Impossible d'effectuer l'action car vous n'avez pas le score requit  ");
        GtkWidget *button_quit = gtk_button_new_with_label("Quitter");

        g_signal_connect(button_quit, "clicked", G_CALLBACK(gtk_window_close), window);

        gtk_widget_set_size_request(button_quit, 200, 70);

        gtk_container_add(GTK_CONTAINER(box),label);
        gtk_container_add(GTK_CONTAINER(box), button_quit);
        gtk_container_add(GTK_CONTAINER(window), box);

        gtk_widget_show_all(window);

        gtk_main();
    }
}

void change_score() {
    gtk_init(NULL, NULL);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
    gtk_window_set_title(GTK_WINDOW(window), "Cheat mode");

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkEntry *entry = GTK_ENTRY(gtk_entry_new());
    gtk_entry_set_placeholder_text(entry, "Entrez le nouveau score");
    gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(entry), FALSE, TRUE, 0);

    GtkWidget *button = gtk_button_new_with_label("Change Score (max: 255)");
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, TRUE, 0);

    g_signal_connect(button, "clicked", G_CALLBACK(on_change_score_clicked), entry);
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_window_close), window);

    gtk_widget_show_all(window);

    gtk_main();
}

void reset_best_score(GtkWidget *window){
    remove("score.bin");
    gtk_window_close((GtkWindow*)window);
}

void settings(){
    gtk_init(NULL, NULL);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable((GtkWindow*)window, false);
    gtk_window_set_default_size((GtkWindow*)window, 100, 100);
    gtk_window_set_title(GTK_WINDOW(window), "Paramètres");

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    GtkWidget *button_reset = gtk_button_new_with_label("Réinitialiser le score");
    GtkWidget *button_cheat = gtk_button_new_with_label("Changer le meilleur score.(Requiert un meilleur score superieur à 10)");

    g_signal_connect(button_reset, "clicked", G_CALLBACK(reset_best_score), window);
    g_signal_connect(button_cheat, "clicked", G_CALLBACK(change_score), window);

    gtk_container_add(GTK_CONTAINER(box), button_reset);
    gtk_container_add(GTK_CONTAINER(box), button_cheat);

    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_widget_show_all(window);

    gtk_main();
}