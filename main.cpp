//g++ -o snake snake.cpp -lncursesw
#include <ncurses.h>
#include <unistd.h>
#include <locale.h>
#include <iostream>
#include <random>

const int GAME_ROW = 8;
const int GAME_COLUMN = 8;
char BOUNDARY_CHARACTER = '#';
char PLAYER_CHARACTER = 'O';
char TAIL_CHARACTER = 'o';
char BERRY_CHARACTER = '@';
bool BendingCharacter = false; // Enable/Disable bending characters for snake body
chtype content[GAME_ROW][GAME_COLUMN];
int MAX_LENGTH = GAME_ROW * GAME_COLUMN;

int ch;
int frame = 0;
int movement_mode = 0; // 0: up, 1: down, 2: left, 3: right
bool running = true;   // for quitting the game
int x = 5;
int y = 5;
int score = 0;
int snake_memory[GAME_ROW][GAME_COLUMN];

void clearSnakeMemory() {
    for (int i = 0; i < GAME_ROW; i++) {
        for (int j = 0; j < GAME_COLUMN; j++) {
            snake_memory[i][j] = 0;
        }
    }
}

void clearContent() {
    for (int i = 0; i < GAME_ROW; i++) {
        for (int j = 0; j < GAME_COLUMN; j++) {
            content[i][j] = ' ';
        }
    }
}

void Draw() {
    setlocale(LC_ALL, "");
    initscr();                  // initialize ncurses
    cbreak();                   // disable line buffering
    noecho();                   // no echo when typing
    curs_set(0);                // hide cursor

    keypad(stdscr, TRUE);       // enable arrow keys
    nodelay(stdscr, TRUE);      // make getch non-blocking

    if(BendingCharacter){
        // Draw top & bottom border
        for (int i = 0; i <= GAME_COLUMN + 1; i++) {
            mvaddch(0, i, BOUNDARY_CHARACTER);
            mvaddch(GAME_ROW + 1, i, BOUNDARY_CHARACTER);
        }
        // Draw left & right border
        for (int i = 0; i <= GAME_ROW + 1; i++) {
            mvaddch(i, 0, BOUNDARY_CHARACTER);
            mvaddch(i, GAME_COLUMN + 1, BOUNDARY_CHARACTER);
        }
    } else {
         // Draw top & bottom border
        for (int i = 0; i <= GAME_COLUMN + 1; i++) {
            mvaddch(0, i * 2, BOUNDARY_CHARACTER);
            mvaddch(0, i * 2 + 1, ' ');
            mvaddch(GAME_ROW + 1, i * 2, BOUNDARY_CHARACTER);
            mvaddch(GAME_ROW + 1, i * 2 + 1, ' ');
        }
        // Draw left & right border
        for (int i = 0; i <= GAME_ROW + 1; i++) {
            mvaddch(i, 0, BOUNDARY_CHARACTER);
            mvaddch(i, (GAME_COLUMN * 2) + 2, BOUNDARY_CHARACTER);
        }
    }

    clearContent();
    clearSnakeMemory();
    refresh();
}

void Input() {
    ch = getch();
    if (ch != ERR) {  // if a key was pressed
        if (ch == 'q') {
            running = false;
        }
        else if (ch == KEY_UP) movement_mode = 0;
        else if (ch == KEY_DOWN) movement_mode = 1;
        else if (ch == KEY_LEFT) movement_mode = 2;
        else if (ch == KEY_RIGHT) movement_mode = 3;
    }
}

void Snake_Logic() {
    if (movement_mode == 0) {
        y--;
    }
    else if (movement_mode == 1) {
        y++;
    }
    else if (movement_mode == 2) {
        x--;
    }
    else if (movement_mode == 3) {
        x++;
    }

    // Wrap around logic
    if(x<0){
        x+=GAME_COLUMN;
    } else if (x>=GAME_COLUMN){
        x-=GAME_COLUMN;
    }
    if(y<0){
        y+=GAME_ROW;
    } else if (y>=GAME_ROW){
        y-=GAME_ROW;
    }

    //Final Update
    content[y][x] = PLAYER_CHARACTER;

    // 🐍 Decrement trail
    for (int i = 0; i < GAME_ROW; i++) {
        for (int j = 0; j < GAME_COLUMN; j++) {
            if (snake_memory[i][j] > 0) {
                snake_memory[i][j]--;
            }
        }
    }

    // 🐍 Mark new head with length
    snake_memory[y][x] = score + 1;

    // 🐍 Update snake body characters
    for (int i = 0; i < GAME_ROW; i++) {
        for (int j = 0; j < GAME_COLUMN; j++) {
            if (snake_memory[i][j] > 0) {
                int last_number = snake_memory[i][j] - 1;
                int next_number = snake_memory[i][j] + 1;
                if (BendingCharacter){
                    if (snake_memory[i+1][j] == last_number && snake_memory[i-1][j] == next_number) {
                        content[i][j] = ACS_VLINE;
                    } else if (snake_memory[i-1][j] == last_number && snake_memory[i+1][j] == next_number) {
                        content[i][j] = ACS_VLINE;
                    } else if (snake_memory[i][j+1] == last_number && snake_memory[i][j-1] == next_number) {
                        content[i][j] = ACS_HLINE;
                    } else if (snake_memory[i][j-1] == last_number && snake_memory[i][j+1] == next_number) {
                        content[i][j] = ACS_HLINE;
                    } else if ((snake_memory[i-1][j] == last_number && snake_memory[i][j+1] == next_number) || (snake_memory[i-1][j] == next_number && snake_memory[i][j+1] == last_number)) {
                        content[i][j] = ACS_LLCORNER;
                    } else if ((snake_memory[i-1][j] == last_number && snake_memory[i][j-1] == next_number) || (snake_memory[i-1][j] == next_number && snake_memory[i][j-1] == last_number)) {
                        content[i][j] = ACS_LRCORNER;
                    } else if ((snake_memory[i+1][j] == last_number && snake_memory[i][j+1] == next_number) || (snake_memory[i+1][j] == next_number && snake_memory[i][j+1] == last_number)) {
                        content[i][j] = ACS_ULCORNER;
                    } else if ((snake_memory[i+1][j] == last_number && snake_memory[i][j-1] == next_number) || (snake_memory[i+1][j] == next_number && snake_memory[i][j-1] == last_number)) {
                        content[i][j] = ACS_URCORNER;
                    } else {
                        content[i][j] = PLAYER_CHARACTER; // Fallback
                    }
                } else {
                    content[i][j] = TAIL_CHARACTER;
                }
            }
        }
    }
}

void Berry_Logic() {
    static int berry_x = -1;
    static int berry_y = -1;

    if (berry_x == -1 && berry_y == -1) {
        do {
            berry_x = rand() % GAME_COLUMN;
            berry_y = rand() % GAME_ROW;
        } while (content[berry_y][berry_x] != ' '); // Ensure berry does not spawn on the snake
    }

    content[berry_y][berry_x] = BERRY_CHARACTER;

    // Check if snake eats the berry
    if (x == berry_x && y == berry_y) {

        // Increase score
        score++;

        // Reset berry position
        berry_x = -1;
        berry_y = -1;
    }
}

void Logic() {
    clearContent();  // clear previous frame
    Snake_Logic();
    Berry_Logic();
}

void Load() {
    for (int i = 0; i < GAME_ROW; i++) {
        for (int j = 0; j < GAME_COLUMN; j++) {
            if(BendingCharacter){
                mvaddch(i + 1, j +1 , content[i][j]);
            } else {
                mvaddch(i + 1, (j * 2) +2 , content[i][j]);
                mvaddch(i + 1, j * 2 + 3, ' ');
            }
        }
    }
    refresh();
}

int main() {

    
    Draw();

    while (running) {
        Input();
        Logic();
        Load();
        usleep(300000); // 0.3s delay
        frame++;
    }

    endwin(); // restore terminal
    return 0;
}
