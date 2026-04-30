# Snake Game With C

A terminal-based Snake game written in C using the `ncurses` library. This project recreates the classic Snake experience in the command line while demonstrating core C programming concepts such as structs, arrays, loops, keyboard input handling, collision detection, random spawning, and real-time screen updates.

This project was created as part of our course work and is also being used for our project presentation.

## Project Overview

The goal of this project was to build a playable Snake game in C that runs directly in the terminal. The player controls a snake that moves around the screen, collects numbered trophies, grows in length, and gains score points. The game ends when the snake hits the border, collides with itself, or the player exits the game.

The project uses `ncurses` to handle terminal graphics, keyboard input, screen clearing, borders, and real-time updates.

## Features

- Terminal-based game interface
- Snake movement using arrow keys or WASD
- Non-blocking keyboard input
- Border collision detection
- Self-collision detection
- Random trophy spawning
- Trophy values from 1 to 9
- Score tracking
- Snake growth after collecting trophies
- Trophy expiration timer
- Game speed increases as the snake grows
- Final score displayed after game over

## Controls

| Key | Action |
|---|---|
| Arrow Up or `W` | Move up |
| Arrow Down or `S` | Move down |
| Arrow Left or `A` | Move left |
| Arrow Right or `D` | Move right |
| `X` | Exit the game |

## How the Game Works

The snake starts near the center of the terminal window and moves automatically. The player changes its direction using the keyboard.

Trophies appear at random locations on the board. Each trophy has a number value between 1 and 9. When the snake collects a trophy:

1. The score increases by the trophy value.
2. The snake grows by that value.
3. A new trophy is eventually spawned.

The game ends if the snake hits the wall or runs into itself.
