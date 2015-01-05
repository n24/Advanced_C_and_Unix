
/*	Verify that the expression getchar () != EOF is 0 or 1.	*/

# include <stdio.h>

int main (void) {
	int c;

	while (c = (getchar () != EOF))
		printf ("%d", c);
	printf ("\n%d at EOF\n", c);
	
	return 0;
}
