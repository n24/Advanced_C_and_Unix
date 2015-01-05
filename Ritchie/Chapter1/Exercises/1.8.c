
/*	Write a program to count blanks, tabs and newlines	*/

# include <stdio.h>

int main (void) {
	int c, nl, nb, nt;

	nl = nb = nt = 0;
	while ((c = getchar ()) != EOF) {
		if (c == '\n') nl++;
		else if (c == '\t') nt++;
		else if (c == ' ') nb++;
	}
	printf ("Blanks: %d, Tabs: %d, Newlines: %d\n", nb, nt, nl);

	return 0;
}
