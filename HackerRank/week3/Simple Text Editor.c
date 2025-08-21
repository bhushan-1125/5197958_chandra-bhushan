#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPS 1000000
#define MAX_LEN 1000000

// History of operations
typedef struct {
    int type;       // 1=append, 2=delete
    char *data;     // deleted substring OR appended substring
    int len;        // length of stored string
} Operation;

Operation history[MAX_OPS];
int top = -1;

char *S;     // main string buffer
int len = 0; // current length

// Push operation onto stack
void push(int type, char *data, int dlen) {
    top++;
    history[top].type = type;
    history[top].len = dlen;
    history[top].data = (char*)malloc(dlen + 1);
    memcpy(history[top].data, data, dlen);
    history[top].data[dlen] = '\0';
}

// Pop last operation
Operation pop() {
    return history[top--];
}

int main() {
    int Q;
    scanf("%d", &Q);

    // allocate large buffer
    S = (char*)malloc((MAX_LEN + 5) * sizeof(char));

    for (int i = 0; i < Q; i++) {
        int type;
        scanf("%d", &type);

        if (type == 1) {  // Append
            char W[1000005];
            scanf("%s", W);
            int wlen = strlen(W);

            memcpy(S + len, W, wlen);  // efficient append
            len += wlen;
            S[len] = '\0';

            push(1, W, wlen);

        } else if (type == 2) {  // Delete
            int k;
            scanf("%d", &k);

            char deleted[1000005];
            memcpy(deleted, S + len - k, k);
            deleted[k] = '\0';

            push(2, deleted, k);

            len -= k;
            S[len] = '\0';

        } else if (type == 3) {  // Print
            int k;
            scanf("%d", &k);
            printf("%c\n", S[k - 1]);

        } else if (type == 4) {  // Undo
            Operation last = pop();

            if (last.type == 1) {  // undo append
                len -= last.len;
                S[len] = '\0';
            } else if (last.type == 2) {  // undo delete
                memcpy(S + len, last.data, last.len);
                len += last.len;
                S[len] = '\0';
            }

            free(last.data);
        }
    }

    free(S);
    return 0;
}
