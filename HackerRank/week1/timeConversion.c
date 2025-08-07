#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

char* timeConversion(char* s) {
    static char result[9]; // HH:MM:SS\0
    int hour;
    char period[3];

    sscanf(s, "%2d:%*2d:%*2d%2s", &hour, period);

    if (strncmp(period, "AM", 2) == 0) {
        if (hour == 12)
            hour = 0;
    } else if (strncmp(period, "PM", 2) == 0) {
        if (hour != 12)
            hour += 12;
    }

    snprintf(result, sizeof(result), "%02d:%.2s:%.2s", hour, s + 3, s + 6);
    return result;
}

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();
    char* result = timeConversion(s);

    fprintf(fptr, "%s\n", result);
    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) break;

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n')
            break;

        alloc_length <<= 1;
        data = realloc(data, alloc_length);
        if (!data) {
            data = NULL;
            break;
        }
    }

    if (data && data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
    } else if (data) {
        data = realloc(data, data_length + 1);
        data[data_length] = '\0';
    }

    return data;
}
