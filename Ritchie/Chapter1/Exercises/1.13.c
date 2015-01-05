
/*	Write a program to print a histogram of the lengths of words in its input.
	It is easy to draw the histogram with the bars horizantal; a vertical orientation
	is more challenging.	*/

# include <stdio.h>

# define IN		1
# define OUT	0

int main (void) {
	int nl, nw, nc, state, c;
	int count[100] = {0};
	int overflow = 0;
	int max = 0, i, j;

	nl = nw = nc = 0;
	state = OUT;
	while ((c = getchar ()) != EOF) {
		if (c != ' ' && c != '\n' && c != '\t')
			++nc;
		if (c == ' ' || c == '\n' || c == '\t') {
			state = OUT;
			if (nc) {
				if (nc > max && nc < 100) max = nc;
				if (nc > 100) overflow++;
				else
					count[nc-1]++;
				nc = 0;
			}
		}		
		else if (state == OUT) {
			state = IN;
		}
	}

	for (i = 0; i < max; i++) {
		if (count[i]) {
			printf ("%d: ", i + 1);
			for (j = 0; j < count[i]; j++)
				printf ("*");
			putchar ('\n');

		}
	}
	putchar ('\n');
	
	if (overflow)
		printf ("%d words exceeds length 100\n", overflow);
	return 0;
}
