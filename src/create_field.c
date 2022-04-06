#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25

int main() {
    int n = 0;
    scanf("%d", &n);
    int found = 0;
    int alive[n][2];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &alive[i][0], &alive[i][1]);
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            for (int k = 0; k < n; k++) {
                if (alive[k][0] == i && alive[k][1] == j) {
                    printf("*");
                    found = 1;
                    break;
                }
            }
            if (found) {
                found = 0;
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}
