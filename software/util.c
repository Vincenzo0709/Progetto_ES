#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[100], t[100];
	fread(s, sizeof(char), 32, stdin);

	int i = 0, j = 0;
	for (0; s[i] != 0; i++) {
		if (i % 2 == 0) {
			t[j++] = '\\';
			t[j++] = 'x';
		}

		t[j++] = s[i];
	}

	t[j] = 0;

	printf("uint8_t hashTrue[16] =\n\t\"%s\";\n", t);

	return 0;
}
