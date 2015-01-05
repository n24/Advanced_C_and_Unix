
/*	Write a program to remove trailing blanks and tabs from each line of input, 
	and to delete entirely blank lines	*/

# include <stdio.h>

# define MAXLINE 1000	// Maximum input line size

int getlines (char line[], int maxline);
int copy (char to[], char from[]);

int main (void) {
	int len;				// Current line length
	char line[MAXLINE];		// Current input line
	char newline[MAXLINE];	// Longest line saved here

	while ((len = getlines (line, MAXLINE)) > 0)
			if ((copy (newline, line)) > 0)
				printf ("%s", newline);
	
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
int copy (char to[], char from[]) {
	int i, j;

	i = 0;
	j = 0;
	if (from[i] == '\n' || from[i] == '\0')
		to[j] = '\0';
	else {
		while (from[i] == ' ' || from[i] == '\t')
			i++;
		while ((to[j] = from[i]) != '\0') {
			++i;
			++j;
		}
	}
	return i;
}
