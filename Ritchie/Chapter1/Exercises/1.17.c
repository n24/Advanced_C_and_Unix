
/*	Write a program to print all input lines that are longer than 80 characters	*/

# include <stdio.h>

# define MAXLINE 	1000	// Maximum input line size
# define LIMIT		80

int getlines (char line[], int maxline);
void copy (char to[], char from[]);

int main (void) {
	int len;				// Current line length
	char line[MAXLINE];		// Current input line

	while ((len = getlines (line, MAXLINE)) > 0)
		if (len > LIMIT) 
			printf ("%d, %s", len, line);
	
	
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

