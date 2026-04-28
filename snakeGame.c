#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_LENGTH 100

// Structure: Represents one segment of the snake (JK)
typedef struct {
    int x;
    int y;
} Segment;

// Global data
Segment snake[MAX_LENGTH];
int length = 5;

int dir_x, dir_y;
int gameover = 0;

void init_direction() {//jk

    dir_x = 1;   // start moving right
    dir_y = 0;//this could also be random 0 or 1, so that it starts in a diff direction else each time 

}

// Initializes the snake in the center of the screen (JK)
void init_snake() {
    int start_x = COLS / 2;
    int start_y = LINES / 2;

    for (int i = 0; i < length; i++) {
        snake[i].x = start_x - i;
        snake[i].y = start_y;
    }
}
void handle_input() { //keyboard input and change snake direction
    int ch = getch();

    if (ch != ERR) {
        switch (ch) {
            case KEY_LEFT:
            case 'a':
            case 'A':
                if (dir_x == 1) {
                    gameover = 1;
                } else {
                    dir_x = -1;
                    dir_y = 0;
                }
                break;

            case KEY_RIGHT:
            case 'd':
            case 'D':
                if (dir_x == -1) {
                    gameover = 1;
                } else {
                    dir_x = 1;
                    dir_y = 0;
                }
                break;

            case KEY_UP:
            case 'w':
            case 'W':
                if (dir_y == 1) {
                    gameover = 1;
                } else {
                    dir_x = 0;
                    dir_y = -1;
                }
                break;

            case KEY_DOWN:
            case 's':
            case 'S':
                if (dir_y == -1) {
                    gameover = 1;
                } else {
                    dir_x = 0;
                    dir_y = 1;
                }
                break;

            case 'x':
            case 'X':
                gameover = 1;
                break;
        }
    }
}
//------------------------------------------------------------------------


void move_snake() { //Move the snake forward and update head position
    for (int i = length - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    snake[0].x += dir_x;
    snake[0].y += dir_y;
}



void draw() { //draw the snake and the border (JK)
    clear();
     box(stdscr, 0, 0);

    for (int i = 0; i < length; i++) {
        mvaddch(snake[i].y, snake[i].x, 'O');}
refresh();
}



void game_loop() {//jk
    while (!gameover) {
        handle_input();
        move_snake();
        draw();
        usleep(100000); // control speed
    }
}



int main() {
    srand(time(NULL));

    initscr();            // start ncurses
    noecho();             // don't print input
    cbreak();            // disable line buffering

    keypad(stdscr, TRUE); // enable arrow keys
    nodelay(stdscr, TRUE);// non-blocking input
    curs_set(0);          // hide cursor

    init_snake();
    init_direction();

    game_loop();

    endwin();             
    return 0;
}