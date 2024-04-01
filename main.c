#include <gtk/gtk.h>
#include <glib.h>
#include <time.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BALL_SIZE 20
#define PLAYERS_WIDTH 20
#define PLYERS_HEIGHT 80

GtkWidget *drawing_area;
struct Ball
{
    int x;
    int y;
    float moveSpeedX;
    float moveSpeedY;
};
struct Player
{
    int x;
    int y;
    int size_x;
    int size_y;
};
struct Player player = {0, 0, PLAYERS_WIDTH, PLYERS_HEIGHT};
struct Player ennemi = {WINDOW_WIDTH - PLAYERS_WIDTH, 0, PLAYERS_WIDTH, PLYERS_HEIGHT};

struct Ball ball = {0, 0, 5.0, 3.0};

gboolean keyboard_manager(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    if (event->keyval == GDK_KEY_Up) {
        player.y-=5;
    }
    else if (event->keyval == GDK_KEY_Down) {
        player.y+=10;
    }
    else if (event->keyval == 'q' || event->keyval == 'Q')
    {
        exit(0);
    }
    
    return TRUE;
}

gboolean update_ball_and_ennemi_position(int argc, char *argv[]) {
    //bouger la balle
    ball.x += ball.moveSpeedX;
    ball.y += ball.moveSpeedY;
    if(ball.y < WINDOW_HEIGHT / 2){
        ennemi.y = ball.y;
    }
    else{
        ennemi.y = ball.y - (ennemi.size_y - BALL_SIZE);
    }
    //si la balle est à droite alors
    if (ball.x <= 0 + player.size_x)
        //si elle touche le joueur alors
        if(ball.y < player.y + player.size_y && ball.y + 20 > player.y){
            //rebondir et augmenter la vitesse
            ball.moveSpeedX = -ball.moveSpeedX;
            if(ball.moveSpeedX < 0){
                ball.moveSpeedX -= 0.5;
            }
            else{
                ball.moveSpeedX += 0.5;
            }
        }
        //sinon
        else{
            //vous avez perdu, arret du jeu
            sleep(2);
            exit(0);
        }
    //sinon, si elle est à gauche alors
    else if (ball.x + BALL_SIZE >= WINDOW_WIDTH)
    {
        //rebondir et augmenter la vitesse
        ball.moveSpeedX = -ball.moveSpeedX;
        if(ball.moveSpeedX < 0){
            ball.moveSpeedX -= 0.5;
        }
        else{
            ball.moveSpeedX += 0.5;
        }
    }
    
    //si elle rebondit sur les murs horizontals alors
    if (ball.y <= 0 || ball.y + BALL_SIZE >= WINDOW_HEIGHT){
        //rebondir
        ball.moveSpeedY = -ball.moveSpeedY;
        if(ball.moveSpeedY < 0){
            ball.moveSpeedY -= 0.5;
        }
        else{
            ball.moveSpeedY += 0.5;
        }
    }
    gtk_widget_queue_draw(drawing_area);

    return G_SOURCE_CONTINUE;
}

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    cairo_fill(cr);

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_rectangle(cr, ball.x, ball.y, BALL_SIZE, BALL_SIZE);
    cairo_fill(cr);

    cairo_set_source_rgb(cr, 0, 1, 0);
    cairo_rectangle(cr, player.x, player.y, player.size_x, player.size_y);
    cairo_fill(cr);

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_rectangle(cr, ennemi.x, ennemi.y, ennemi.size_x, ennemi.size_y);
    cairo_fill(cr);

    return FALSE;
}

gboolean delet_all(GtkWidget *widget, cairo_t *cr, gpointer data) {
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_rectangle(cr, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    cairo_fill(cr);
    return false;
}

void play(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable (window, false);

    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_title(GTK_WINDOW(window), "Pong");
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_callback), NULL);
    g_signal_connect(window, "key-press-event", G_CALLBACK(keyboard_manager), NULL);

    ball.x = WINDOW_WIDTH / 2 - BALL_SIZE / 2;
    ball.y = WINDOW_HEIGHT / 2 - BALL_SIZE / 2;

    g_timeout_add(30, (GSourceFunc)update_ball_and_ennemi_position, NULL);


    gtk_widget_show_all(window);
}

void quit(GtkWidget *widget, gpointer data) {
    g_print("Quitter l'application\n");
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    g_print("Bienvenu sur pong !\n");

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable(window, false);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    GtkWidget *button_play = gtk_button_new_with_label("Jouer à Pong");
    GtkWidget *button_quit = gtk_button_new_with_label("Quitter");

    g_signal_connect(button_play, "clicked", G_CALLBACK(play), NULL);
    g_signal_connect(button_quit, "clicked", G_CALLBACK(quit), NULL);

    gtk_container_add(GTK_CONTAINER(box), button_play);
    gtk_container_add(GTK_CONTAINER(box), button_quit);

    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
