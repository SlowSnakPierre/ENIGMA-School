#include <stdio.h>

void drawLines(int len) {
    for (int i = 0; i < len; i++) {
        printf("*");
    }
}

int main() {
    drawLines(5);
    return 0;
}
