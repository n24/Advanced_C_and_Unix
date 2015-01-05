
# include <stdio.h>

# define IN		1	// Inside a word
# define OUT	0	// Outside a word

/*	Count lines, words and characters is input	*/

int main (void) {
	int nl, nw, nc, state, c;

	nl = nw = nc = 0;
	state = OUT;
	while ((c = getchar ()) != EOF) {
		++nc;
		if (c == '\n')
			++nl;
		if (c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if (state == OUT) {
			++nw;
			state = IN;
		}
	}
	printf ("%d %d %d\n", nl, nw, nc);

	return 0;
}
