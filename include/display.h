#ifndef DISPLAY_H
#define DISPLAY_H

#include "type.h"

#include <stdbool.h>
#include <windows.h>

typedef struct {
    iVector2 size;
    bool supportsColor;
} display;


iVector2 getDisplaySize(CONSOLE_SCREEN_BUFFER_INFO csbi);
display* getDisplay();


#endif