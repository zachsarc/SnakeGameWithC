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


// ---------------------------------
// Trophy system (JK) 
int trophy_x, trophy_y;
int trophy_value;
time_t trophy_spawn_time;
int trophy_duration; 
int trophy_active = 0;
// ----------------------------------

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
//draw snake
    for (int i = 0; i < length; i++) {
        mvaddch(snake[i].y, snake[i].x, 'O');}
        // Draw trophy
    if (trophy_active) {
        mvaddch(trophy_y, trophy_x, '0' + trophy_value);
    }
refresh();
}

void spawn_trophy(){
    trophy_x = rand() % (COLS -2) +1;
    trophy_y = rand() % (LINES -2) +1;
    
trophy_value = rand() % 9 +1;
  trophy_spawn_time = time(NULL);
            trophy_duration = rand() % 9 + 1;

        trophy_active = 1;
}

void trophies(){
    time_t now = time(NULL);

    if(!trophy_active){
        spawn_trophy();
    }
    // if(){} logic to check the expiration 
    /*if(){} logic to check if snake eats trophy 
    This will probably check if snake[].x and y are 
    at the same x and y as the trophy
    
    then if it's true, lenght + value, checking if
    it's also not more than max value. 
    */ 

//in game loop, uncomment trophy() when the system is done. (Line 166)
}


void game_loop() {//jk
    while (!gameover) {
        handle_input();
        move_snake();
        //trophies(); 
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