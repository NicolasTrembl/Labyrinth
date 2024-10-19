#include "display.h"
#include "type.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

iVector2 getDisplaySize(CONSOLE_SCREEN_BUFFER_INFO csbi) {
    iVector2 size;
    size.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    size.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return size;
}

display* getDisplay() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    if (hConsole == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error getting console handle\n");
        return NULL;
    }

    
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        fprintf(stderr, "Error getting console screen buffer info\n");
        return NULL;
    }


    display* d = (display*) malloc(sizeof(display));

    d->hConsole = hConsole;
    
    d->size = getDisplaySize(csbi);

    DWORD mode;
    
    if (GetConsoleMode(hConsole, &mode)) {
        if (mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) {
            d->supportsColor = true;
        } else {
            d->supportsColor = false;
        }
    } else {
        fprintf(stderr, "Error getting console mode\n");
        return NULL;
    }


    return d;
}

bool clearDisplay(display* d) {
    if (d == NULL) {
        return false;
    }

    system("cls");

    return true;
}


bool showSplit(display* d) {

    if (d == NULL) {
        return false;
    }

    COORD coord;
    coord.X = d->size.x / 2;

    coord.Y = 0;

    for (int i = 0; i < d->size.y; i++) {
        SetConsoleCursorPosition(d->hConsole, coord);
        printf("|");
        coord.Y++;
    }

    return true;

}



bool showTabs(display* d, int tabCount, char* tabs[]) {
    
    if (d == NULL) {
        return false;
    }

    COORD coord;
    coord.X = d->size.x / 2;
    coord.Y = 0;

    for (int i = 0; i < tabCount; i++) {
        coord.X += d->size.x / (tabCount * 4) - strlen(tabs[i]) / 2;
        SetConsoleCursorPosition(d->hConsole, coord);
        printf("%s", tabs[i]);
        coord.X += d->size.x / (tabCount * 4) + strlen(tabs[i]) / 2;
    }

    coord.X = d->size.x / 2;

    for (int i = 0; i < tabCount-1; i++) {
        coord.X += d->size.x / (tabCount * 2);
        SetConsoleCursorPosition(d->hConsole, coord);
        printf("|");
    }

    coord.X = d->size.x / 2 + 1;
    coord.Y = 1;

    for (; coord.X < d->size.x ; coord.X++) {
        SetConsoleCursorPosition(d->hConsole, coord);
        printf("-");
    }

    return true;
}

bool showTabSelected(display* d, int tabCount, int selectedTab) {
    if (d == NULL) {
        return false;
    }

    COORD coord;

    
    coord.X = d->size.x / 2 + 1;
    coord.Y = 1;

    for (; coord.X < d->size.x ; coord.X++) {
        SetConsoleCursorPosition(d->hConsole, coord);
        printf("-");
    }

    coord.X = d->size.x / 2 + d->size.x / (tabCount * 4);

    for (int i = 0; i < selectedTab - 1; i++) {
        coord.X += d->size.x / (tabCount * 2);
    }

    coord.X--;

    for (int i = 0; i < 3; i++) {
        SetConsoleCursorPosition(d->hConsole, coord);
        printf("^");
        coord.X++;
    }



    return true;
}

bool showVertex(display* d, int vertex, graph* g) {
    if (d == NULL) {
        return false;
    }

    if (g == NULL) {
        return false;
    }

    COORD coord;
    coord.X = (vertex * CELL_SIZE) % (d->size.x / 2);
    coord.Y = ((vertex * CELL_SIZE) - coord.X) / d->size.y;

    SetConsoleCursorPosition(d->hConsole, coord);
    printf("#");
    if (coord.Y > 0 && g->edges[vertex][vertex - (d->size.x / CELL_SIZE * 2)] == 1) {
        printf(" ");
    } else {
        printf("#");
    }
    printf("#");

    coord.Y++;
    coord.X -= CELL_SIZE;
    
    SetConsoleCursorPosition(d->hConsole, coord);
    if (coord.X > 0 && g->edges[vertex][vertex - 1] == 1) {
        printf(" ");
    } else {
        printf("#");
    }
    printf(" ");
    if (coord.X + CELL_SIZE < d->size.x / 2 && g->edges[vertex][vertex + 1] == 1) {
        printf(" ");
    } else {
        printf("#");
    }


    coord.Y++;
    coord.X -= CELL_SIZE;

    SetConsoleCursorPosition(d->hConsole, coord);
    printf("#");
    if (coord.Y * CELL_SIZE < d->size.y && g->edges[vertex][vertex + (d->size.x / CELL_SIZE * 2)] == 1) {
        printf(" ");
    } else {
        printf("#");
    }
    printf("#");

    return true;
}