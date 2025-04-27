#include <stdio.h>

void show_max_factorial_int()
{
	int result = 1;
	for (int i = 2; 1; ++i) {
		int next = result * i;
		if (result > next) {
			printf("max number for n! is: %d\n", i - 1);
			break;
		}

		result = next;
	}
}

void show_max_factorial_int64()
{
	long long int result = 1;
	for (int i = 2; 1; ++i) {
		long long int next = result * i;
		if (result > next) {
			printf("max number for n! is: %d\n", i - 1);
			break;
		}

		result = next;
	}
}

int main(int argc, char *argv[])
{
	show_max_factorial_int();
	show_max_factorial_int64();
	return 0;
}
