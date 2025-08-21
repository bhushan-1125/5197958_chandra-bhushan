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
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);
int parse_int(char*);

/*
 * Complete the 'maxSubarray' function below.
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */
int* maxSubarray(int arr_count, int* arr, int* result_count) {
    int *result = malloc(2 * sizeof(int));
    *result_count = 2;

    // --- Max Contiguous Subarray Sum (Kadane's Algorithm) ---
    int max_so_far = arr[0];
    int current_max = arr[0];

    for (int i = 1; i < arr_count; i++) {
        current_max = (arr[i] > current_max + arr[i]) ? arr[i] : current_max + arr[i];
        if (current_max > max_so_far) {
            max_so_far = current_max;
        }
    }

    // --- Max Non-Contiguous Subarray Sum ---
    int max_non_contig = 0;
    int has_positive = 0;
    int max_element = arr[0];

    for (int i = 0; i < arr_count; i++) {
        if (arr[i] > 0) {
            max_non_contig += arr[i];
            has_positive = 1;
        }
        if (arr[i] > max_element) {
            max_element = arr[i];
        }
    }

    if (!has_positive) {
        max_non_contig = max_element; // all negatives case
    }

    result[0] = max_so_far;     // contiguous max sum
    result[1] = max_non_contig; // non-contiguous max sum

    return result;
}

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n = parse_int(ltrim(rtrim(readline())));

        char** arr_temp = split_string(rtrim(readline()));
        int* arr = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            int arr_item = parse_int(*(arr_temp + i));
            *(arr + i) = arr_item;
        }

        int result_count;
        int* result = maxSubarray(n, arr, &result_count);

        for (int i = 0; i < result_count; i++) {
            fprintf(fptr, "%d", *(result + i));
            if (i != result_count - 1) {
                fprintf(fptr, " ");
            }
        }
        fprintf(fptr, "\n");

        free(arr);
        free(result);
    }

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
        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') break;

        alloc_length <<= 1;
        data = realloc(data, alloc_length);
        if (!data) return '\0';
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);
        data[data_length] = '\0';
    }
    return data;
}

char* ltrim(char* str) {
    if (!str) return '\0';
    if (!*str) return str;
    while (*str != '\0' && isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
    if (!str) return '\0';
    if (!*str) return str;

    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");
    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) return splits;
        splits[spaces - 1] = token;
        token = strtok(NULL, " ");
    }
    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') exit(EXIT_FAILURE);
    return value;
}
