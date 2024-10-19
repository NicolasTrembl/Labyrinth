#ifndef DISPLAY_H
#define DISPLAY_H

#include "type.h"

#include <stdbool.h>
#include <windows.h>

typedef struct {
    HANDLE hConsole;
    iVector2 size;
    bool supportsColor;
} display;


iVector2 getDisplaySize(CONSOLE_SCREEN_BUFFER_INFO csbi);
display* getDisplay();


bool clearDisplay(display* d);
bool showSplit(display* d);
bool showTabs(display* d, int tabCount, char* tabs[]);
bool showTabSelected(display* d, int tabCount, int selectedTab);


#endif