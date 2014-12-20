
//	Write a program to convert
//	/ * ....... * / style comments
//	to
//	//.........
//	//......... style comments	

// Usage:
//		gcc convert.c
//		./a.out <input_file> <output_file>


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int main ( int argc, char ** argv ) {
	int c;			// Input character
	int lastc;		// Last character 
	int last_c;		// To handle escape sequences
	int state;		// Current state
	int s;			// Used to handle new style multiline comment and multiline strings
	int line;
	FILE * in_fp;	// Input file pointer
	FILE * out_fp;	// Output file pointer;
	enum st { 	NONE, INSIDE_COMMENT, INSIDE_QUOTES,
				SLASH_READ, END_COMMENT, INSIDE_NEW_COMMENT };

	state = NONE;	// Initial state
	s = 0;			// s = 1; multiline new style comment or multiline string is present
	line = 1;

	if ( argc != 3 ) {
		fprintf ( stderr, "Error: Invalid arguments\n" );
		fprintf ( stderr, "Usage: ./a.out <in_file> <out_file>\n" );
		exit ( 1 );
	}
	if ( ! ( strcmp ( argv[1], argv[2] ) ) ) {
		fprintf ( stderr, "Error: in_file and out_file must be different\n" );
		fprintf ( stderr, "Usage: ./a.out <in_file> <out_file>\n" );
		exit ( 2 );
	}
	if ( ( in_fp = fopen ( argv[1], "r" ) ) == NULL ) {
		perror ( argv[1] );
		exit ( 3 );
	}
	if ( ( out_fp = fopen ( argv[2], "w" ) ) == NULL ) {
		perror ( argv[2] );
		exit ( 4 );
	}

	while ( ( c = getc ( in_fp ) ) != EOF ) {
		switch ( state ) {
			case NONE :
				if ( c == '/' ) {
					state = SLASH_READ;
					lastc = c;
					continue;	// while loop
				} else if ( c == '\'' || c == '\"' ) {
					state = INSIDE_QUOTES;
					lastc = c;
				}
				fputc ( c, out_fp );
				break;
			case SLASH_READ :
				if ( c == '*' ) {
					state = INSIDE_COMMENT;
					fputs ( "//", out_fp );
				} else if ( c == '/' ) {
					fputc ( lastc, out_fp );
					fputc ( c, out_fp );
					state = INSIDE_NEW_COMMENT;
				} else {
					state = NONE;
					fputc ( lastc, out_fp );
					fputc ( c, out_fp );
				}
				break;
			case INSIDE_NEW_COMMENT :
				// s = 1; new style comment extends to next line also.
				if ( c == '\\' ) s = 1;
				if ( c == '\n' ) {
					if ( !s )
						state = NONE;
					else s = 0;
				}
				fputc ( c, out_fp );
				break;
			case INSIDE_QUOTES :
				if ( c == lastc ) {
					if ( last_c != '\\' )
						state = NONE;
				}
				else if ( c == '\\' )
					s = 1;
				else if ( c == '\n' ) {
					if ( !s ) {
						fprintf ( stderr,
						"Error: Line %d: %c character should end in same line\n",
						line, lastc );
						unlink ( argv[2] );
						exit ( 1 );
					}
					s = 0;
				}
				fputc ( c, out_fp );
				last_c = c;
				break;
			case INSIDE_COMMENT :
				if ( c == '\n' )
					fputs ( "\n//", out_fp );
				else if ( c == '*' ) {
					state = END_COMMENT;
					lastc = c;
				} else
					fputc ( c, out_fp );
				break;
			case END_COMMENT :
				if ( c == '/' ) {
					while ( ( c = fgetc ( in_fp ) ) ) {
						if ( c == ' ' || c == '\t' )
							continue;
						break;
					}
					ungetc ( c, in_fp );
					if ( c != '\n' )
						fputc ( '\n', out_fp );
					state = NONE;
				} else {
					fputc ( lastc, out_fp );
					fputc ( c, out_fp );
					state = INSIDE_COMMENT;
				}
				break;
		}
		if ( c == '\n' ) line++;
	}
	
	if ( state == INSIDE_COMMENT || state == INSIDE_QUOTES ) {
		fprintf ( stderr, "Syntax Error\n" );
		unlink ( argv[2] );
		exit ( 5 );
	}
	
	return 0;
}
