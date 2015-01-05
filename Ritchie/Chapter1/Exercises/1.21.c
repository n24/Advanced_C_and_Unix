
/*	Write a program entab that replaces strings of blanks by the minimum number of
	tabs and blanks to achieve the same spacing. Use the same tab stops as for detab.
	When either a tab or a single blank would suffice to reach a tab stop, which
	should be given preference?	*/

# include <stdio.h>
# include <stdlib.h>

# define TAB	8

int main (int argc, char **argv) {
	
	if (argc != 1) {
		fprintf (stderr, "Usage: a.out\n");
		exit (1);
	}

	int pos, c, spaces, tabs;
	spaces = pos = tabs = 0;
	while ((c = getchar ()) != EOF) {
		if (c == ' ')
			++spaces;
		else if (c == '\t') {
			do ++spaces;
			while (spaces % TAB);
		}
		else {
			if (c != '\n') {
				tabs = spaces / TAB;
				spaces %= TAB;
				for ( ; tabs > 0; --tabs)
					putchar ('\t');
				for ( ; spaces > 0; --spaces)
					putchar (' ');
			}
			tabs = spaces = 0;
			putchar (c);
		}
	}

	return 0;
}
