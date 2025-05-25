
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 20
#include <stdio.h>
int main(void) {
    int arr[MAX_LEN];
    int n = 0;// number of elements read
    int c;
    int num = 0;
    int sign = 1;
    // Read characters until newline/EOF, build numbers on the fly
    while ((c = getchar()) != EOF && c != '\n') {
        if (c == '-') {sign = -1;} // negative number
        else if (c == '+') {sign = 1;} // positive number
        else if (c >= '0' && c <= '9') {num = num * 10 + (c - '0');}  // accumulate digit
        else if (c == ',') {
			if (n < MAX_LEN) {arr[n++] = sign * num;} // store the number in the array
            // reset for the next number
            num  = 0;
            sign = 1;
        }
    }
    if (n < MAX_LEN) {arr[n++] = sign * num;} // store the last number if any
    // Now compute how many swaps to move odds left
    // 1) count total odds
    int countOdds = 0;
    for (int i = 0; i < n; i++) { if (arr[i] % 2 != 0) {countOdds++;}} // count total odds in the array
    // 2) in the first countOdds slots, count how many evens are misplaced
    int swaps = 0;
    for (int i = 0; i < countOdds; i++) {if (arr[i] % 2 == 0) {swaps++;}} // count misplaced evens in the first countOdds slots
    printf("Number of swaps: %d", swaps);
    return 0;
}