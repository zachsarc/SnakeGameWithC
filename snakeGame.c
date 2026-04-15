#include <ncurses.h>
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


// Initializes the snake in the center of the screen (JK)
void init_snake() {
    int start_x = COLS / 2;
    int start_y = LINES / 2;

    for (int i = 0; i < length; i++) {
        snake[i].x = start_x - i;
        snake[i].y = start_y;
    }
}
void init_direction() { // Set the snake in a random initial direction (JK)
    int dirs[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int r = rand() % 4;
    dir_x = dirs[r][0];
    dir_y = dirs[r][1];
}



void handle_input(){
    //Check user's input (keys) and update directions
}



void move_snake(){
//move the snake forward, changing the direction by +-1 in y or +-1 in x.
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
