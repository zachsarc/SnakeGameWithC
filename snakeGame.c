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
int score = 0;


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
                if (dir_x != 1) { // Ignore opposite direction
                    dir_x = -1;
                    dir_y = 0;
                }
                break;

            case KEY_RIGHT:
            case 'd':
            case 'D':
                if (dir_x != -1) { // Ignore opposite direction
                    dir_x = 1;
                    dir_y = 0;
                }
                break;

            case KEY_UP:
            case 'w':
            case 'W':
                if (dir_y != 1) { // Ignore opposite direction
                    dir_x = 0;
                    dir_y = -1;
                }
                break;

            case KEY_DOWN:
            case 's':
            case 'S':
                if (dir_y != -1) { // Ignore opposite direction
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
    // Check boundary collision
    if (snake[0].x + dir_x < 1 || snake[0].x + dir_x >= COLS - 1 ||
        snake[0].y + dir_y < 1 || snake[0].y + dir_y >= LINES - 1) {
        gameover = 1;
        return;
    }

    for (int i = length - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    snake[0].x += dir_x;
    snake[0].y += dir_y;

    // Check self-collision (Snake hits its own body) //ZL
    for (int i = 1; i < length; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            gameover = 1;
            return;
        }
    }
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
    // Draw score
    mvprintw(0, 2, "Score: %d", score);
refresh();
}

void spawn_trophy(){ //ZL
    int valid = 0;
    while (!valid) {
        trophy_x = rand() % (COLS - 2) + 1;
        trophy_y = rand() % (LINES - 2) + 1;
        valid = 1;

        // Ensure trophy doesn't spawn inside the snake
        for (int i = 0; i < length; i++) {
            if (snake[i].x == trophy_x && snake[i].y == trophy_y) {
                valid = 0;
                break;
            }
        }
    }

    
trophy_value = rand() % 9 +1;
  trophy_spawn_time = time(NULL);
            trophy_duration = rand() % 21 + 20; // Trophy now lasts between 20 and 40 seconds

        trophy_active = 1;
}

void trophies(){ //ZL
    time_t now = time(NULL);

    if(!trophy_active){
        spawn_trophy();
    }
    // Check expiration
    if (trophy_active && (now - trophy_spawn_time) > trophy_duration) {
        trophy_active = 0;
    }
    // Check if snake eats trophy
    if (trophy_active && snake[0].x == trophy_x && snake[0].y == trophy_y) {
        score += trophy_value;
        if (length < MAX_LENGTH) {
            length += trophy_value;
            if (length > MAX_LENGTH) length = MAX_LENGTH;
        }
        trophy_active = 0;
    }
}


void game_loop() {//jk
    while (!gameover) {
        handle_input();
        move_snake();
        trophies(); 
        draw();

        // Speed up slightly as length increases
        int delay = 80000 - (length * 800);
        usleep(delay < 35000 ? 35000 : delay); 
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

    // Game over message
    clear();
    mvprintw(LINES / 2, COLS / 2 - 10, "GAME OVER!");
    mvprintw(LINES / 2 + 1, COLS / 2 - 12, "Final Score: %d", score);
    refresh();
    sleep(2);

    endwin();             
    return 0;
}