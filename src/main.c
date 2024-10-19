#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include "display.h"
#include "type.h"
#include "graph.h"

#define FPS 10


#define TABS 4
#define TABS_TEXT {"Generate", "Solve", "Settings", "Exit"}


int main() {
    display* d = getDisplay();


    if (d == NULL) {
        fprintf(stderr, "Error getting display\n");
        return 1;
    }

    clearDisplay(d);

    showSplit(d);

    int selectedTab = 1;

    showTabs(d, TABS, (char*[])TABS_TEXT);
    showTabSelected(d, TABS, selectedTab);

    graph* g = createEmptyGraph((d->size.x * d->size.y) / (CELL_SIZE * CELL_SIZE));

    DWORD start = GetTickCount();

    bool running = true;

    while (running) {
        if (GetTickCount() - start >= 1000 / FPS) {
            start = GetTickCount();
        }

        if (_kbhit()) {
            char key = _getch();
            switch (key) {
                case 'q':
                    running = false;
                break;

                case 'r':
                    naiveGenerate(d, g);
                break;
                
                case 0x48:
                    ;
                break;
                
                case 0x50:
                    ;
                break;
                
                case 0x4B:
                    selectedTab--;
                    if (selectedTab < 1) {
                        selectedTab = TABS;
                    }
                    showTabSelected(d, TABS, selectedTab);
                break;
                
                case 0x4D:
                    selectedTab++;
                    if (selectedTab > TABS) {
                        selectedTab = 1;
                    }
                    showTabSelected(d, TABS, selectedTab);
                break;
                
                case 13:
                    if (selectedTab == 4) {
                        running = false;
                    }
                break;
                
                default:
                    ;
                break;
            }
        }

    }

    clearDisplay(d);

    printf("Exiting...\n");
  
    free(d);
    return 0;
}