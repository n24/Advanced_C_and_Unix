
/*	Revise the main routine of the longest-line program so it will print the length
	of arbitraily long input lines, and as much as possible of text	*/

# include <stdio.h>

# define MAXLINE 1000	// Maximum input line size

int getlines (char line[], int maxline);
void copy (char to[], char from[]);

int main (void) {
	int len;				// Current line length
	int max;				// Maximum length seen so far
	char line[MAXLINE];		// Current input line
	char longest[MAXLINE];	// Longest line saved here

	max = 0;
	while ((len = getlines (line, MAXLINE)) > 0) {
		printf ("%d, %s", len, line);
		if (len > max) {
			max = len;
			copy (longest, line);
		}
	}
	
	if (max > 0) 			// There was a line
		printf ("%s", longest);
	
	return 0;
}

// Getline: read a line into s, return length
int getlines (char s[], int lim) {
	int c, i, j;

	j = 0;
	for (i = 0; (c = getchar ()) != EOF && c != '\n'; ++i)
		if (i < lim - 2) {
			s[j] = c;
			++j;
		}
	if (c == '\n') {
		s[j] = c;
		++i;
		++j;
	}
	s[j] = '\0';
	return i;
}

// Copy: copy 'from' into 'to'; assume 'to' is big enough
void copy (char to[], char from[]) {
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}

