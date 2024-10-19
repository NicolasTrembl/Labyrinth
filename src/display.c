#include "display.h"
#include "type.h"

#include <stdio.h>
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