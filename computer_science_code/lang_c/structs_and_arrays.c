#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int homeScore;
    int awayScore;
    char gameLocation[100];
} SOCCER;

int main() {
    SOCCER notFun[100] = { 1, 0, 'A' };
    int count = 50, i = 0, total = 0;
    count++;
    for (i = 0; i < count; i++) {
        notFun[i].homeScore = i + 1;
        notFun[i].awayScore = i + 1;
    }
        total += notFun[i].homeScore + notFun[i].awayScore;
        printf("Total Score: %d\n", total);
    
    system("pause");
    return 0;
}
