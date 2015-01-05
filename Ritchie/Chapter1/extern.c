
# include <stdio.h>

# define MAXLINE 1000	// Maximum input line size

int getlines (void);
void copy (void);

int max;				// Maximum length seen so far
char line[MAXLINE];		// Current input line
char longest[MAXLINE];	// Longest line saved here

int main (void) {
	int len;				// Current line length
	extern int max;
	extern char longest[];

	max = 0;
	while ((len = getlines ()) > 0)
		if (len > max) {
			max = len;
			copy ();
		}
	
	if (max > 0)			// There was a line
		printf ("%s", longest);
	
	return 0;
}

// Getline: read a line into s, return length
int getlines (void) {
	int c, i;
	extern char line[];

	for (i = 0; i < (MAXLINE - 1) && (c = getchar ()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}

// Copy: copy 'from' into 'to'; assume 'to' is big enough
void copy (void) {
	int i;
	extern char line[], longest[];

	i = 0;
	while ((longest[i] = line[i]) != '\0')
		++i;
}

