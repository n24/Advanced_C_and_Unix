
/*	Replace a word in a file.
	Ex: all "the" with "and".	

	Usage:
		gcc replace.c
		./a.out input_file output_file in_word out_word
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define 	IN		1
# define 	OUT	0
# define 	WHITE(c)	( ( c == ' ' ) || ( c == '\n' ) || ( c == '\t' ) )

int main ( int argc, char ** argv ) {
	char * in_word, * out_word, * temp_word, * i, * t;
	int state, c;
	FILE * in_file, * out_file;
	
	if ( argc != 5 ) {
		fprintf ( stderr, "Error: Missing arguments\n");
		fprintf ( stderr, "Usage: ./a.out <in_file> <out_file> <in_word> <out_word>\n" );
		exit ( 1 );
	}
	if ( !( strcmp ( argv[1], argv[2] ) ) ) {
		fprintf ( stderr, "Error: <in_file> and <out_file> should be different\n" );
		exit ( 2 );
	}
	if ( ( in_file = fopen ( argv[1], "r" ) ) == NULL ) {
		perror ( argv[1] );
		exit ( 3 );
	}
	if ( ( out_file = fopen ( argv[2], "w" ) ) == NULL ) {
		perror ( argv[2] );
		exit ( 4 );
	}

	i = in_word = argv[3];
	out_word = argv[4];
	t = temp_word = malloc ( strlen ( in_word ) + 1 );
	state = OUT;
	
	while ( ( c = fgetc ( in_file ) ) != EOF ) {
		if ( *i == '\0' ) {
			i = in_word;
			t = temp_word;
			if ( state == IN && WHITE ( c ) )
					fputs ( out_word, out_file );
			else
				fputs ( temp_word, out_file );
			fputc ( c, out_file );
			*t = '\0';
		} else if ( c == *i++ ) {
			*t++ = c;
			*t = '\0';
		} else {
			i = in_word;
			t = temp_word;
			fputs ( temp_word, out_file );
			fputc ( c, out_file );
			*t = '\0';
			if ( WHITE ( c ) )
				state = IN;
			else
				state = OUT;
		}
	}
	
	fclose ( in_file );
	fclose ( out_file );
	free ( temp_word );

	return 0;
}
