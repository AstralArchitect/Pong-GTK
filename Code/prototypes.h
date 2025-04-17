#include <gtk/gtk.h>

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

void game_setup(GtkButton *button, gpointer *pointer);
void info();
void settings();