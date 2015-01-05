
/*	Experiment to find out what happens when printf's argument string contains \c,
	where c is some constant	*/

# include <stdio.h>

int main (void) {
	
	printf ("Hello, World\a"); // beep sound
	printf ("Hello, World\b"); // back space
	printf ("Hello, World\c"); // unknown escape sequence

	return 0;
}
