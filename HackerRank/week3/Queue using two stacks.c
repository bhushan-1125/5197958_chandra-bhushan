#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX 1000000   // large enough for constraints

int queue[MAX];
int front = 0, rear = 0;

int main() {
    int q;
    scanf("%d", &q);   // number of queries

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            int x;
            scanf("%d", &x);
            queue[rear++] = x;   // enqueue
        } 
        else if (type == 2) {
            if (front < rear) {
                front++;         // dequeue
            }
        } 
        else if (type == 3) {
            if (front < rear) {
                printf("%d\n", queue[front]);  // print front
            }
        }
    }
    return 0;
}
