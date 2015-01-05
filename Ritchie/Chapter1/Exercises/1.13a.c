
/*	Vertical version of 1.13a.c	*/

# include <stdio.h>

# define IN		1
# define OUT	0

int main (void) {
	int nl, nw, nc, state, c, maxcount = 0, m;
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
	for (i = 0; i < max; i++)
		if (count[i] > maxcount)
			maxcount = count[i];

	m = maxcount;
	for (j = 0; j < maxcount; j++) {
		for (i = 0; i < max; i++) {
			if (count[i]) {
				if (count[i] >= m)
					printf ("* ");
				else 
					printf ("  ");
			}
		}
		m--;
		putchar ('\n');
	}

	for (i = 0; i < max; i++)
		if (count[i])
			printf ("%d ", (i + 1));
	putchar ('\n');
	if (overflow)
		printf ("%d words exceeds length 100\n", overflow);
	return 0;
}
