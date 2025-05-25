#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 20
#define INT_MAX 2147483647 //although this is not necessary in C because prdefined in limits.h, it is included for clarity
#include <stdio.h>
#include <limits.h>
int main(void) {
    int arr[20], n = 0;
    int c, num = 0, sign = 1;
    while ((c = getchar()) != EOF && c != '\n') { // read until EOF or newline
        if (c == '-') {sign = -1;} //negative value array members  
		else if (c=='+'){sign = 1;} // positive value array members     
        else if (c >= '0' && c <= '9') {num = num * 10 + (c - '0');} // accumulate digits into a number
		else if (c == '+') {sign = 1;} // positive value array members
        else if (c == ',') { // end of a number
            if (n < MAX_LEN) { arr[n++] = sign * num;} // store the number in the array if we haven't reached the limit
			// reset for the next number
            num = 0;
            sign = 1;
        }
    }
    if (n < MAX_LEN) {arr[n++] = sign * num;} // store the last number if any
    //  Build prefix sums: prefix[k] = sum(arr[0..k-1]) 
    int prefix[21]; // prefix[0] = 0, prefix[1] = arr[0], ..., prefix[n] = sum(arr[0..n-1])
    prefix[0] = 0; // prefix[0] is always 0 for convenience
    for (int i = 0; i < n; i++) {prefix[i+1] = prefix[i] + arr[i];}// compute prefix sums
    //  Find minimum subarray sum and count how many achieve it 
    int minSum = INT_MAX; // Initialize to maximum possible value
    int count  = 0; // Initialize count of subarrays with minimum sum
    for (int i = 0; i < n; i++) { // iterate over all starting points
        for (int j = i; j < n; j++) {// For each starting point, iterate over all possible ending points
            int sum = prefix[j+1] - prefix[i]; // Calculate the sum of the subarray arr[i..j]
			if (sum < minSum) { // If we found a new minimum, update minSum and reset count
                minSum = sum; // Update the minimum sum found
                count  = 1; // Reset count to 1 since we found a new minimum
            }
            else if (sum == minSum) {count++;}	// If it equals the current minimum, just increment count	
        }
    }
    printf("Min sum: %d\nNumber of subarrays: %d", minSum, count);
    return 0;
}