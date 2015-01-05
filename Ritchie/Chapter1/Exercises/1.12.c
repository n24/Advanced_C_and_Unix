
/*	Write a program that prints its input one word per line	*/

# include <stdio.h>

# define IN		1
# define OUT	0

int main (void) {
	int c, state;

	state = OUT;
	while ((c = getchar ()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (state == IN) {
				state = OUT;
				putchar ('\n');
			}
		} else if (state == OUT) {
			putchar (c);
			state = IN;
		}
		else
			putchar (c);
	}

	return 0;
}
