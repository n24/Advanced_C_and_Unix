
/*	Read a string more than 25 characters. If it contains a specific substring
	(say, unix), print it. else discard it.

	Usage :
			gcc substring.c
			./a.out <substring> [<file1>....<filen>]
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define LENGTH 1000

int sub_string ( char * str, char * sub_str);

int main ( int argc, char ** argv ) {
	char str[LENGTH], * sub_str;
	FILE * fp;

	if ( argc < 2 ) {
		fprintf ( stderr, "Error: Invalid number of arguments\n" );
		fprintf ( stderr, "Usage: ./a.out <sub_string> [<file1> ...... <filen>]\n" );
		exit ( 1 );
	}
	
	sub_str = argv[1];

	if ( argc == 2 ) {
		while ( fgets ( str, LENGTH, stdin ) ) {
			if ( sub_string ( str, sub_str ) )
				printf ( "stdin: %s", str );
		}
		exit ( 0 );
	}

	++argv;
	while ( *++argv ) {
		if ( !strcmp ( *argv, "-" ) )
			fp = stdin;
		else if ( (fp = fopen ( *argv, "r" )) == NULL ) {
			perror ( *argv );
			continue;
		}
		while ( fgets ( str, LENGTH, fp ) ) {
			if ( sub_string ( str, sub_str ) )
				printf ( "%s: %s", *argv, str );
		}
		fclose ( fp );
	}
	
	return 0;
}

int sub_string ( char * str, char * sub_str ) {
	char * i, * j, * k;
	
	j = sub_str;
	for ( i = str; *i; i++ ) {
		if ( !*j )
			return 1;
		for ( k = i; *j; k++, j++ ) {
			if ( *j != *k ) {
				j = sub_str;
				break;
			}
		}
	}

	return 0;
}
