#include <glib.h>
#include <time.h>
#include <stdbool.h>
#include "prototypes.h"

#define BALL_SIZE 20
#define PLAYERS_WIDTH 20
#define PLYERS_HEIGHT 80
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

GtkWidget *drawing_area;

struct Player player = {0, WINDOW_HEIGHT / 2, PLAYERS_WIDTH, PLYERS_HEIGHT};
struct Player ennemi = {WINDOW_WIDTH - PLAYERS_WIDTH, 0, PLAYERS_WIDTH, PLYERS_HEIGHT};

struct Ball ball = {0, 0, 5.0, 3.0};

time_t start, stop;

char score = 0;

int meilleur_score;
char score_text[50] = "Pong, première partie";

int playerMoveSpeed = 10;

GtkWidget *game_window;
extern GtkWidget *launcher_window;

void error();

gboolean keyboard_manager(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    if (event->keyval == GDK_KEY_Up) {
        if (player.y > 0)
        {
            player.y -= playerMoveSpeed;
        }
    }
    else if (event->keyval == GDK_KEY_Down) {
        if (player.y + player.size_y > WINDOW_HEIGHT)
        {
            player.y -= playerMoveSpeed;
        }
        player.y += playerMoveSpeed;
    }
    else if (event->keyval == 'q' || event->keyval == 'Q')
    {
        exit(0);
    }
    
    return TRUE;
}

void quitter(){
    if(meilleur_score < score){
        FILE *save = fopen("score.bin", "w+b");
        if (save != NULL)
        {
            fwrite(&score, sizeof(char), 1, save);
            fclose(save);
        }
        else
        {
            error();
        }
    }
    score = 0;
    meilleur_score = 0;
    strcpy(&score_text[0], "Pong, première partie");
    gtk_widget_destroy(game_window);
    gtk_widget_show_all(launcher_window);
}

gboolean update_ball_and_ennemi_position(gpointer* pointer) {
    //bouger la balle
    ball.x += ball.moveSpeedX;
    ball.y += ball.moveSpeedY;
    ennemi.y = ball.y - ennemi.size_y / 2;
    //si la balle est à gauch alors
    if (ball.x <= 0 + player.size_x)
    {
        //si elle touche le joueur alors
        if(ball.y < player.y + player.size_y && ball.y + 20 > player.y){
            //rebondir, augmenter la vitesse et augmenter le score
            ball.moveSpeedX = -ball.moveSpeedX;
            if(ball.moveSpeedX < 0){
                ball.moveSpeedX -= (double)(rand() % 2) / 2.0;
            }
            else{
                ball.moveSpeedX += (double)(rand() % 2) / 2.0;
            }
            score++;
            sprintf(score_text, "Pong, meilleur score : %d, score: %d", meilleur_score, score);
            gtk_window_set_title(GTK_WINDOW(game_window), score_text);
        }
        //sinon
        else{
            //vous avez perdu, arret du jeu
            stop = time(NULL);
            quitter();
        }
        playerMoveSpeed++;
    }
    //sinon, si elle est à droite alors
    else if (ball.x + BALL_SIZE >= WINDOW_WIDTH - ennemi.size_x)
    {
        //rebondir et augmenter la vitesse
        ball.moveSpeedX = -ball.moveSpeedX;
        if(ball.moveSpeedX < 0){
            ball.moveSpeedX -= (double)(rand() % 3) / 2.0;
        }
        else{
            ball.moveSpeedX += (double)(rand() % 3) / 2.0;
        }
    }
    
    //si elle rebondit sur les murs horizontals alors
    if (ball.y <= 0 || ball.y + BALL_SIZE >= WINDOW_HEIGHT){
        //rebondir
        ball.moveSpeedY = -ball.moveSpeedY;
        if(ball.moveSpeedY < 0){
            ball.moveSpeedY -= (double)(rand() % 3) / 2.0;
        }
        else{
            ball.moveSpeedY += (double)(rand() % 3) / 2.0;
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

void play(GtkButton *button, gpointer *pointer) {
    FILE *save = fopen("score.bin", "rb");
    if(save != NULL){
        fread(&meilleur_score, sizeof(char), 1, save);
        sprintf(score_text, "Pong, meilleur score : %d, score: %d", meilleur_score, score);
        fclose(save);
    }
    else{
        FILE *save = fopen("score.bin", "w+b");
        meilleur_score = 0;
        fwrite(&meilleur_score, sizeof(char), 1, save);
        fclose(save);
    }
    start = time(NULL);
    gtk_widget_hide(launcher_window);
    game_window = gtk_application_window_new(GTK_APPLICATION(pointer));
    g_signal_connect(game_window, "destroy", G_CALLBACK(gtk_widget_destroy), game_window);
    gtk_window_set_resizable(GTK_WINDOW(game_window), false);

    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_title(GTK_WINDOW(game_window), score_text);
    gtk_container_add(GTK_CONTAINER(game_window), drawing_area);

    g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_callback), NULL);
    g_signal_connect(game_window, "key-press-event", G_CALLBACK(keyboard_manager), NULL);

    ball.x = WINDOW_WIDTH / 2 - BALL_SIZE / 2;
    ball.y = WINDOW_HEIGHT / 2 - BALL_SIZE / 2;

    g_timeout_add(30, (GSourceFunc)update_ball_and_ennemi_position, pointer);

    gtk_widget_show_all(game_window);
}

void game_setup(GtkButton *button, gpointer *pointer){
    srand(time(NULL));
    ball.moveSpeedY = rand() % 2 + 2;
    play(button, pointer);
}