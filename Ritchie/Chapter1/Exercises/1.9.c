
/*	Write a program to copy its input to its output, replacing each string of one
	or more blanks by a single blank	*/

# include <stdio.h>

int main (void) {
	int flag, c;

	flag = 0;
	while ((c = getchar ()) != EOF) {
		if (c == ' ') {
			if (!flag) {
				putchar (c);
				flag = 1;
			}
		} else {
			putchar (c);
			flag = 0;
		}
	}

	return 0;
}
