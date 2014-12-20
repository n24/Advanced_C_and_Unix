
/*	Write the program 'last.c' that prints the last 'n' 
	lines of a file. By default, 'n' should be 5. 
	But your program should accept an optional argument (like -8). 
	Use standard input if input file name is not specified.

	Usage:
		gcc last.c
		./a.out ==> print last 5 lines of stdin
		./a.out - ==> Same as above
		./a.out -20 a ==> last 20 lines of a
		./a.out -10 a -20 b ==> last 10 lines of a followed by last 20 lines of b
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>

int PrintLines ( FILE * fp, int n, const char * fname);
void Handle_Stdin ( int n );

int main ( int argc, char ** argv) {
	char * a;
	int n = 5;	// default no. of lines
	FILE * fp;

	if ( argc == 1 )
		Handle_Stdin ( n );

	while ( *++argv ) {
		a = *argv;
		if ( !( strcmp ( "-", a ) ) ) {
			Handle_Stdin ( n );
			continue;
		}
		if ( *a == '-' ) {
			a++;
			while ( *a ) {
				if ( ! ( isdigit ( *a++ ) ) ) {
					fprintf ( stderr, "Invalid option %s\n", *argv );
					exit ( 1 );
				}
			}
			n = atoi ( ++*argv );
		}
		else {
			if ( ( fp = fopen ( *argv, "r" ) ) == NULL ) {
				perror ( *argv );
				continue;
			}
			PrintLines ( fp, n, *argv );
			fclose ( fp );
		}
	}

	return 0;
}

int PrintLines ( FILE * fp, int n, const char * fname ) {
	int c, i, l;
	long b;

	fseek ( fp, 0, SEEK_END );
	b = ftell ( fp );

	l = i = 0;
	while ( b-- > 0 ) {
		c = getc ( fp );
		if ( c == '\n' ) {
			l++;
			if ( l > n ) break;
		}
		fseek ( fp, -( ++i ), SEEK_END );
	}
	
	printf ( "Last %d Lines of %s\n", n, fname );
	while ( ( c = getc ( fp ) ) != EOF )
		fputc ( c, stdout );
	putchar ( '\n' );
	
	return 0;
}

void Handle_Stdin ( int n ) {
	char temp[100];
	FILE * fp;

	sprintf ( temp, "temp%d", getpid () );
	if ( (fp = fopen ( temp, "w+" )) == NULL ) {
		perror ( temp );
		return ;
	}
	int c;
	while ( (c = getchar () ) != EOF )
		fputc ( c, fp );
	PrintLines ( fp, n, "stdin" );
	fclose ( fp );
	unlink ( temp );
}
