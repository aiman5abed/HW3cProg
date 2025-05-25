#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 20
#include <stdio.h>
int main(void) {
    int arr[MAX_LEN], n = 0;
    int c, num = 0, sign = 1;
    // --- 1) Parse up to MAX_LEN comma-separated ints via getchar() ---
    while ((c = getchar()) != EOF && c != '\n') {
        if (c == '-') {sign = -1;} // negative value array members
        else if (c == '+') {sign = 1;} // positive value array members
        else if (c >= '0' && c <= '9') {num = num * 10 + (c - '0');} // accumulate digits into a number
        else if (c == ',') { // end of a number
            if (n < MAX_LEN) {arr[n++] = sign * num;}
            // reset for next number
			num  = 0;
            sign = 1;
        }
	}
    // push the last number (no trailing comma)
    if (n < MAX_LEN) {arr[n++] = sign * num;}
    // if nothing was read, no water can be trapped
    if (n == 0) {
        printf("0");
        return 0;
    }
    // --- 2) Build left_max and right_max arrays ---
    int left_max[MAX_LEN], right_max[MAX_LEN];
    left_max[0] = arr[0];
    for (int i = 1; i < n; i++) {left_max[i] = (arr[i] > left_max[i-1]) ? arr[i] : left_max[i-1];}
    right_max[n-1] = arr[n-1];
    for (int i = n-2; i >= 0; i--) {right_max[i] = (arr[i] > right_max[i+1]) ? arr[i] : right_max[i+1];}
    // --- 3) Compute trapped water ---
    int water = 0;
    for (int i = 0; i < n; i++) {
        int h = left_max[i] < right_max[i] ? left_max[i] : right_max[i];
        if (h > arr[i]) {water += (h - arr[i]);}
    }
    printf("%d", water);
    return 0;
}
