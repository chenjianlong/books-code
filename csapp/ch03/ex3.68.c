#include <stdio.h>

#define LINE_LEN 10

int main() {
	char buf[LINE_LEN] = { '\0' };
	while (1) {
		char *str = fgets(buf, LINE_LEN, stdin);
		if (str == NULL) {
			return 1;
		}

		fputs(buf, stdout);
	}

	return 0;
}
