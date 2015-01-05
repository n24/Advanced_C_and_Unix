
/*	Write a function reverse (s) that reverses the character string s.
	Use it to write a program that reverses its input a line at a time.	*/

# include <stdio.h>

# define MAXLINE 1000	// Maximum input line size

int getlines (char line[], int maxline);
void reverse (char s[]);

int main (void) {
	char line[MAXLINE];		// Current input line

	while ( getlines (line, MAXLINE))
		reverse (line);
	
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
void reverse (char s[]) {
	int i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	i--;
	while (i >= 0)
		putchar (s[i--]);
	putchar ('\n');
}

