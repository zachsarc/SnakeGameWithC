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

// Initializes the snake in the center of the screen (JK)
void init_snake() {
    int start_x = COLS / 2;
    int start_y = LINES / 2;

    for (int i = 0; i < length; i++) {
        snake[i].x = start_x - i;
        snake[i].y = start_y;
    }
}
void handle_input() { // Primary author: ZL - Check keyboard input and update snake direction
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


void move_snake(){
//move the snake forward, changing the direction by +-1 in y or +-1 in x. (ZL)
switch (key) {
    case 1: x--; break; // Left
    case 2: x++; break // Right
    case 3: y--; break // Up
    case 4: y++; break // Down
}
}



void draw() { //draw the snake and the border (JK)
    clear();
     box(stdscr, 0, 0);

    for (int i = 0; i < length; i++) {
        mvaddch(snake[i].y, snake[i].x, 'O');}
refresh();
}



void game_loop(){
//game loop combining the previous functions for movement and input handling 
}



int main(){
    srand(time(NULL));


init_snake();
init_direction();



}
