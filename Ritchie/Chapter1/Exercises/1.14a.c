
/*	Write a program to print a histogram (vertical) of the frequencies of different characters
	in its input */

# include <stdio.h>
# include <ctype.h>

int main (void) {
	int c, i, j, maxcount, m, count[26] = {0};

	printf ("Enter input text (Ctrl-D to end)\n");
	while ((c = getchar()) != EOF) {
		if (islower (c))
			count[c - 97]++;
		else if (isupper (c))
			count[c - 65]++;
	}
	
	maxcount = 0;
	for (i = 0; i < 26; i++)
		if (count[i] > maxcount)
			maxcount = count[i];
	putchar ('\n');
	
	m  = maxcount;
	for (i = 0; i < maxcount; i++) {
		for (j = 0; j < 26; j++) {
			if (count[j]) {
				if (count[j] >= m)
					printf (". ");
				else
					printf ("  ");
			}
		}
		m--;
		putchar ('\n');
	}

	for (i = 0; i < 26; i++)
		if (count[i])
			printf ("%c ", (i + 97));
	putchar ('\n');

	return 0;
}
