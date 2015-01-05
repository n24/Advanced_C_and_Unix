
/*	Write a program detab that replaces tabs in the input with the proper number of blanks
	to space to the next tab stop. Assume a fixed set of tab stops, say every n columns.
	Should n be a variable or a symbolic parameter?
*/

# include <stdio.h>
# include <stdlib.h>

int main (int argc, char **argv) {
	
	if (argc != 2) {
		fprintf (stderr, "Usage: a.out <tab_stop>.\n");
		exit (1);
	}

	char *a = argv[1];
	while (*a) {
		if (!(isdigit (*a++))) {
			fprintf (stderr, "Invalid integer for tab_stop\n");
			exit (2);
		}
	}
	
	int tab_stop = atoi (argv[1]);
	if (tab_stop < 1 || tab_stop > 10) {
		fprintf (stderr, "tab_stop must be in range 1 - 10 (inclusive)\n");
		exit (3);
	}
	
	int pos= 0, c;
	while ((c = getchar ()) != EOF) {
		if (c == '\t') {
			do {
				putchar (' ');
				++pos;
			} while (pos % tab_stop);
		}
		else {
			putchar (c);
			(c == '\n') ? (pos = 0) : ++pos;
		}
	}

	return 0;
}
