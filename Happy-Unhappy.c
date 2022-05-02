/*
 * Happy vs. Unhappy numbers.
 *
 * Procedure: given a number, add the squares of its digit.
 * If the sum equals 1, the number is happy.
 * If the sum equals the number, the number is unhappy.
 * Otherwise, iterate till either the sum is 1 or the initial number.
 */

#include <memory.h>
#include <stdio.h>

#define MAX_N 500000
#define MAX_ARRAY_N 1000000
#define BITS_PER_LONG (8 * sizeof(unsigned long))
#define bits_to_ul(val) (((val) + BITS_PER_LONG - 1) / BITS_PER_LONG)
#define ARRAY_SIZE bits_to_ul(MAX_ARRAY_N)

unsigned long scratchpad_array[ARRAY_SIZE] = {0};
unsigned long happy_array[ARRAY_SIZE] = {0};
unsigned long unhappy_array[ARRAY_SIZE] = {0};

void mark(unsigned long array[], unsigned long n)
{
	array[n / BITS_PER_LONG] |= (1UL << (n % BITS_PER_LONG)) ;
}
#define mark_scratchpad(n)  mark(scratchpad_array, n)
#define mark_happy(n)       mark(happy_array, n)
#define mark_unhappy(n)     mark(unhappy_array, n)


char is_marked(unsigned long array[], unsigned long n)
{
	return ((array[n / BITS_PER_LONG]) >> (n % BITS_PER_LONG)) & 1;
}
#define is_scratchpad(n)    is_marked(scratchpad_array, n)
#define is_happy(n)         is_marked(happy_array, n)
#define is_unhappy(n)       is_marked(unhappy_array, n)

void merge(unsigned long array[], unsigned long max_n)
{
	unsigned long i;

	for (i = 0; i <= bits_to_ul(max_n); i++)
		if (scratchpad_array[i])
			array[i] |= scratchpad_array[i];
}
#define merge_happy(max_n) merge(happy_array, max_n)
#define merge_unhappy(max_n) merge(unhappy_array, max_n)

int main()
{
	unsigned long n;
	unsigned long max_n;
	unsigned long tmp;
	unsigned long sum;
	unsigned long digit;

	for (n = 1; n < MAX_N; n++) {
		memset(scratchpad_array, 0, ARRAY_SIZE * sizeof(scratchpad_array[0]));
		max_n = 0;
		tmp = n;
		sum = 0;
		while (1) {
			printf("%4lu ", tmp);
			if (tmp > max_n)
				max_n = tmp;
			if ((tmp == 1) || is_happy(tmp)) {
				merge_happy(max_n);
				mark_happy(tmp);
				break;
			} else if (is_unhappy(tmp) || is_scratchpad(tmp)) {
				merge_unhappy(max_n);
				mark_unhappy(tmp);
				break;
			}
			mark_scratchpad(tmp);
			for (sum = 0; tmp;) {
				digit = tmp % 10;
				tmp /= 10;
				sum += digit * digit;
			}
			tmp = sum;
		}
	}
	for (n = 1; n < MAX_N; n++) {
		char h = is_happy(n);
		char u = is_unhappy(n);

		if (h && !u)
			printf("%5lu is happy\n", n);
		else if (u && !h)
			printf("%5lu is unhappy\n", n);
		else
			return -printf("%5lu ERROR\n", n);

	}
	return 0;
}
