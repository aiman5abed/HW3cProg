#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 20
#include <stdio.h>
int main(void) {
    int arr[MAX_LEN];
    int n = 0;// count of numbers read
    int c, num = 0, sign = 1;
    // --- Parse comma-separated ints via getchar() ---
    while ((c = getchar()) != EOF && c != '\n') {
        if (c == '-') {sign = -1;} // negative number
        else if (c == '+') {sign = 1;} // positive number
        else if (c >= '0' && c <= '9') {num = num * 10 + (c - '0');} // accumulate digits into a number
        else if (c == ',') {
            if (n < MAX_LEN) {arr[n++] = sign * num;}// store the number in the array if we haven't reached the limit
            num  = 0;
            sign = 1;
        }
    }
    // store the final number (if any)
    if (n < MAX_LEN) {arr[n++] = sign * num;}
    // --- Check for duplicates in O(n^2) ---
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                printf("1");
                return 0;
            }
        }
    }
    // no duplicates found
    printf("-1");
    return 0;
}
