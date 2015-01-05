
/*	Write a program to check a C program for rudimentary syntax errors like unbalanced
	parantheses, brackets and braces. Don't forget about quotes, both single and double,
	escape sequences, and comments. (This program is hard if you do it in full generality.)
*/

# include <stdio.h>
# include <stdlib.h>

int main () {
	int parantheses, brackets, braces;
	int curr_char, prev_char, line;
	enum state_values 
		{ 	Normal, Slash, Old, 
			New, End, Quotes 
	} state;

	parantheses = brackets = braces = 0;
	line = 1;
	state = Normal;

	while ( (curr_char = getchar ()) != EOF ) {
		switch ( state ) {
			case Normal:
				if ( curr_char == '{' )
					++parantheses;
				else if ( curr_char == '[' )
					++brackets;
				else if ( curr_char == '(' )
					++braces;
				else if ( curr_char == '}' ) {
					if ( parantheses )
						--parantheses;
					else {
						fprintf ( stderr, "Line %d: No matching '{'.\n", line );
						exit ( 1 );
					}
				} else if ( curr_char == ']' ) {
					if ( brackets ) --brackets;
					else {
						fprintf ( stderr, "Line %d: No matching '['.\n", line );
						exit ( 1 );
					}
				} else if ( curr_char == ')' ) {
					if ( braces ) --braces;
					else {
						fprintf ( stderr, "Line %d: No matching '('.\n", line );
						exit ( 1 );
					}
				} else if ( curr_char == '\'' || curr_char == '\"' ) {
					state = Quotes;
					prev_char = curr_char;
				}
				else if ( curr_char == '/' )
					state = Slash;
				break;
			case Slash:
				if ( curr_char == '*' )
					state = Old;
				else if ( curr_char == '/' )
					state = New;
				else state = Normal;
				break;
			case Old:
				if ( curr_char == '*' )
					state = End;
				break;
			case End:
				if ( curr_char == '/' )
					state = Normal;
				else state = Old;
				break;
			case New:
				if ( curr_char == '\n' )
					state = Normal;
				break;
			case Quotes:
				if ( curr_char == '\\' ) getchar ();	// Ignore escape sequence
				else if ( curr_char == prev_char )
					state = Normal;
				break;
		}
		if ( curr_char == '\n' )
			line++;
	}

	if ( parantheses ) 	printf ( "Unbalanced Parantheses\n" );
	if ( brackets ) 	printf ( "Unbalanced brackets\n" );
	if ( braces ) 		printf ( "Unbalanced braces\n" );

	return 0;
}
