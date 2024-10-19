#include <stdio.h>

#include "display.h"
#include "type.h"


int main() {
    display* d = getDisplay();

    if (d == NULL) {
        return 1;
    }

    printf("Display size: %d x %d\n", d->size.x, d->size.y);
    printf("Supports color: %s\n", d->supportsColor ? "true" : "false");

    free(d);
    return 0;
}