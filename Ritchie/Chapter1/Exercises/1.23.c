
/*	Write a program to remove all comments from a C program.
	Don't forget to handle quoted strings and character constants properly.
	C comments do not nest.	*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int main (int argc, char **argv) {
	int c;			// Input character
	int lastc;		// Previous character
	int escape;		// To handle escape sequences
	int last_c;
	int state;		// Current state
	int new;		// Used to handle new style multiline comment
	int line;		// Line number
	enum st { 	NONE, INSIDE_COMMENT, INSIDE_QUOTES,
				SLASH_READ, END_COMMENT, INSIDE_NEW_COMMENT };

	state = NONE;	// Initial state
	new = 0;		// new = 1; multiline new style comment is present
	line = 1;

	while ((c = getchar ()) != EOF) {
		switch (state) {
			case NONE:
				if (c == '/') {
					state = SLASH_READ;
					lastc = c;
					continue;	// while loop
				} else if (c == '\'' || c == '\"') {
					state = INSIDE_QUOTES;
					lastc = c;
				}
				putchar (c);
				break;
			case SLASH_READ:
				if (c == '*')
					state = INSIDE_COMMENT;
				else if (c == '/')
					state = INSIDE_NEW_COMMENT;
				else {
					state = NONE;
					putchar (lastc);
					putchar (c);
				}
				break;
			case INSIDE_NEW_COMMENT:
				// new = 1; new style comment extends to next line also.
				if (c == '\\') new = 1;
				else if (c == '\n') {
					if (!new) {
						state = NONE;
						putchar (c);
					}
					else new = 0;
				}
				break;
			case INSIDE_QUOTES:
				if (c == lastc) {
					if (last_c != '\\' || !escape)
						state = NONE;
				}
				else if (c == '\\')
					++escape;
				else if (c == '\n') {
					if (!escape) {
						fprintf (stderr, "Error: Line %d: %c must end in same line", line, lastc);
						exit (1);
					}
					escape = 0;
				}
				else if (c != ' ' || c != '\t')
					escape = 0;
				if (escape) escape %= 2;
				putchar (c);
				last_c = c;
				break;
			case INSIDE_COMMENT:
				if (c == '\n')
					continue;
				else if (c == '*')
					state = END_COMMENT;
				break;
			case END_COMMENT:
				if (c == '/')
					state = NONE;
				break;
		}
		if (c == '\n') line++;
	}
	
	if (state == INSIDE_COMMENT || state == INSIDE_QUOTES) {
		fprintf (stderr, "Syntax Error\n");
		exit (5);
	}
	
	return 0;
}
