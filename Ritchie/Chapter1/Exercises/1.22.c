
/*	Write a program to "fold" long input lines into two or more shorter lines
	after the last non-blank character that occurs before the n-th column of
	input. Make sure you program does something intelligent with very long
	lines, and if there are no blanks or tabs before the specified column.	*/

# include <stdio.h>
# include <stdlib.h>

int main ( int argc, char **argv ) {

	if ( argc != 3 ) {
		fprintf ( stderr, "Usage: a.out <width> <tab_stop>.\n" );
		exit ( 1 );
	}
	int width = atoi ( argv[1] );
	int tabs = atoi ( argv[2] );
	int pos = 0;
	int c;

	char *fold = (char *) malloc ( width + 1 + 2 );

	pos = 0;
	while ( (c = getchar ()) != EOF ) {
		if ( pos == width ) {
			if ( !isspace ( c ) )
				fold[pos++] = '-';
			fold[pos++] = '\n';
			fold[pos] = '\0';
			fputs ( fold, stdout );
			pos = 0;
			if ( c != ' ' || c != '\t' ) ungetc ( c, stdin );
		} else if ( c == '\t' ) {
			do {
				fold[pos++] = ' ';
				if ( pos == width ) break;
			} while ( pos % tabs );
		} else if ( c == '\n' ) {
			fold[pos++] = '\n';
			fold[pos] = '\0';
			pos = 0;
			fputs ( fold, stdout );
		}
		else fold[pos++] = c;
	}

	return 0;
}
