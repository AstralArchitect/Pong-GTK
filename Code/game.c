#include <gtk/gtk.h>
#include <glib.h>
#include <time.h>
#include <stdbool.h>

#define BALL_SIZE 20
#define PLAYERS_WIDTH 20
#define PLYERS_HEIGHT 80
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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
struct Player player = {0, WINDOW_HEIGHT / 2, PLAYERS_WIDTH, PLYERS_HEIGHT};
struct Player ennemi = {WINDOW_WIDTH - PLAYERS_WIDTH, 0, PLAYERS_WIDTH, PLYERS_HEIGHT};

struct Ball ball = {0, 0, 5.0, 3.0};

time_t start, stop;

unsigned short score = 0;

int meilleur_score;
char score_text[50] = "Pong, première partie";

GtkWidget* window;

gboolean keyboard_manager(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    if (event->keyval == GDK_KEY_Up) {
        if (player.y > 0)
        {
            player.y -= 10;
        }
    }
    else if (event->keyval == GDK_KEY_Down) {
        if (player.y + player.size_y > WINDOW_HEIGHT)
        {
            player.y -= 10;
        }
        player.y += 10;
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
        fwrite(&score, sizeof(unsigned short), 1, save);
        fclose(save);
    }
    
    exit(0);
}

void Perdu() {
    gtk_init(NULL, NULL);

    gtk_widget_hide(window);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window, 400, 100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable((GtkWindow*)window, false);

    char score_text[50];
    sprintf(score_text, "Perdu ! Score : %d", score);
    gtk_window_set_title(GTK_WINDOW(window), score_text);

    GtkWidget *button_quit = gtk_button_new_with_label("Cliquez pour quitter.");

    g_signal_connect(button_quit, "clicked", G_CALLBACK(quitter), NULL);

    gtk_container_add(GTK_CONTAINER(window), button_quit);

    gtk_widget_show_all(window);

    gtk_main();
}

gboolean update_ball_and_ennemi_position() {
    //bouger la balle
    ball.x += ball.moveSpeedX;
    ball.y += ball.moveSpeedY;
    ennemi.y = ball.y - ennemi.size_y / 2;
    //si la balle est à gauch alors
    if (ball.x <= 0 + player.size_x)
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
            gtk_window_set_title(GTK_WINDOW(window), score_text);
        }
        //sinon
        else{
            //vous avez perdu, arret du jeu
            stop = time(NULL);
            Perdu(window);
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
    window = (GtkWidget*)pointer;
    FILE *save = fopen("score.bin", "rb");
    if(save != NULL){
        fread(&meilleur_score, sizeof(unsigned short), 1, save);
        sprintf(score_text, "Pong, meilleur score : %d, score: %d", meilleur_score, score);
        fclose(save);
    }
    else{
        FILE *save = fopen("score.bin", "w+b");
        meilleur_score = 0;
        fwrite(&meilleur_score, sizeof(unsigned short), 1, save);
        fclose(save);
    }
    start = time(NULL);
    gtk_widget_hide(window);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable((GtkWindow*)window, false);

    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_title(GTK_WINDOW(window), score_text);
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_callback), NULL);
    g_signal_connect(window, "key-press-event", G_CALLBACK(keyboard_manager), NULL);

    ball.x = WINDOW_WIDTH / 2 - BALL_SIZE / 2;
    ball.y = WINDOW_HEIGHT / 2 - BALL_SIZE / 2;

    g_timeout_add(30, (GSourceFunc)update_ball_and_ennemi_position, NULL);


    gtk_widget_show_all(window);
}

void game_setup(GtkButton *button, gpointer *pointer){
    srand(time(NULL));
    ball.moveSpeedY = rand() % 2 + 2;
    play(button, pointer);
}