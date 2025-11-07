#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define WIDTH 80
#define HEIGHT 60

int i, j, gameover, score;
int x, y, fruitX, fruitY, flag;
int tailX[200], tailY[200];
int nTail = 0;

void gotoxy(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setup() {
    gameover = 0;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    nTail = 0;
}

void draw() {
    gotoxy(0, 0);

    for (i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (j == 0) printf("#");

            if (i == y && j == x)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("F");
            else {
                int print = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("*");
                        print = 1;
                        break;
                    }
                }
                if (!print) printf(" ");
            }

            if (j == WIDTH - 1) printf("#");
        }
        printf("\n");
    }

    for (i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': flag = 1; break;
        case 'd': flag = 2; break;
        case 'w': flag = 3; break;
        case 's': flag = 4; break;
        case 'x': gameover = 1; break;
        }
    }
}

void logic() {
    Sleep(210);

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (flag) {
        case 1: x--; break;
        case 2: x++; break;
        case 3: y--; break;
        case 4: y++; break;
        default: break;
    }

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameover = 1;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameover = 1;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}

int main() {
    char choice;

start:
    system("cls");
    setup();

    while (!gameover) {
        draw();
        input();
        logic();
    }

    gotoxy(0, HEIGHT + 5);
    printf("\nGAME OVER!!!\n");
    printf("Final Score: %d\n", score);
    printf("Press 'R' to Restart or any key to Exit: ");

    choice = _getch();
    if (choice == 'r' || choice == 'R') {
        system("cls");
        goto start;
    }

    return 0;
}
