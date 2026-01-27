#include <stdio.h>

/*
 * C Imperative Paradigm Lab
 * Parts 1–4 are implemented in this file.
 *
 * Do NOT change function signatures.
 * 
 * 1/15/26 - Brian Toone
 */

/* ===== Part 2 ===== */
int sum_to(int n) {
    // Implement using a for loop and mutable local state
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

/* ===== Part 3 ===== */
double avg_1_to_n(int n) {
    // Call sum_to(n)
    // Cast to double to avoid integer division
    return (double)sum_to(n) / n;
}

/* ===== Part 4 ===== */
void increment_bad(int x) {
    x++;
}

void increment(int *x) {
    // Fix using a pointer
    (*x)++;
}

int main() {

    /* ===== Part 1 ===== */
    printf("--- Part 1: State and Sequence ---\n");

    int x = 2;
    x = x + 3;
    x = x * 4;
    printf("x=%d\n", x);

    // Swapped: multiply first, then add
    printf("\nAfter swapping last two assignments:\n");
    int y = 2;
    y = y * 4;
    y = y + 3;
    printf("y=%d\n", y);


    /* ===== Part 2 ===== */
    printf("\n--- Part 2: Control Flow ---\n");
    printf("sum_to(5) = %d (expected 15)\n", sum_to(5));
    printf("sum_to(1) = %d (expected 1)\n", sum_to(1));


    /* ===== Part 3 ===== */
    printf("\n--- Part 3: Functions as Procedures ---\n");
    printf("avg_1_to_n(5) = %.1f (expected 3.0)\n", avg_1_to_n(5));


    /* ===== Part 4 ===== */
    printf("\n--- Part 4: Pass-by-Value vs Pointers ---\n");

    int a = 5;
    increment_bad(a);
    printf("after increment_bad: a=%d (expected 5)\n", a);

    increment(&a);
    printf("after increment:     a=%d (expected 6)\n", a);

    return 0;
}