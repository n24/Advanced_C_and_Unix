
/*	Implementation of Unix command cat.

	Usage:
		gcc minicat.c
		
		My program accepts all the options accepted by cat (1)
		Read through man cat to know more.
	
	Note:
		Make sure that the files cat_help and cat_version are in your
		current directory, to get output for ./a.out --help and ./a.out --version
*/

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

void handle_stdin (void);			// Function to handle keyboard input
void print_files (void);			// Function to print the contents
void store_files (char **fname);	// Function to store files and options
void error_message (char **fname);	// Function to print the error message and exit

char **file = NULL;					// Used to store input file names
int nof;							// No.of input files
int op;								// op = 0 [No options]; 1 [Atleast 1 option];
int A, b, E, e, n, s, t, T, v;		// switches

int main (int argc, char **argv) {	// Main Function
	
	if (argc == 1) {				// If argument count is 1 
		handle_stdin ();			// handle keyboard input 
		exit (0);					// and exit
	}
	
	while (*++argv)					// Loop to store
		store_files (argv);			// all file names and options
	
	if (A || n || E || e || s || v || t || T || b)
		op = 1;						// Option is present if any one of the flag is 1
	
	if (!nof) {						
		if ((file = (char **) realloc (file, sizeof (char *))) == NULL) {
			fprintf (stderr, "Cannot allocate dynamic memory.\n");
			exit (1);
		}							// If no file is present but option is
		file[0] = "-";				// specified, then handle keyboard input
		print_files ();				// by specifying file[0] as stdin("-"),
		exit (0);					// call print_files() and exit
	}
	
	while (nof--)					// Loop to print contents of all the files
		print_files ();
	
	return 0;
}

void handle_stdin (void) {
	int c;
	
	while ((c = getchar ()) != EOF)	// Take 1 character at a time untill End Of File
		putchar (c);				// Send the character to standard output
}

void print_files (void) {
	int c;							// Input character
	int nb;							// No.of consecutive blanks for -s option
	int lastc;						// Last input character 
	int stdin_file;					// stdin_file = 1 [If stdin with option is present]
	static int l;					// Line number for -n option
	char temp[100];					// Array to hold temporary file name for stdin
	FILE *fp;						// File Pointer
	
	nb = stdin_file = 0;
	lastc = '\n';
	
	if (!(strcmp(*file,"-"))) {
		if (!op) {					// stdiin_file without options
			handle_stdin ();
			return;
		} else {					// stdin_file with options
			stdin_file = 1;
			sprintf (temp, "temp%d", getpid());
			if ((fp = fopen (temp, "w+")) == NULL) {
				perror (*file);
				return;
			}
			while ((c = getchar ()) != EOF)
				fputc (c, fp);
			fclose (fp);
			if ((fp = fopen (temp, "r")) == NULL) {
				perror (temp);
				return;
			}
		}
	} else if ((fp = fopen (*file, "r")) == NULL) {
		perror (*file);
		return;
	}
	while ((c = getc(fp)) != EOF) {
		if (c == '\n') {
			if (s && (++nb > 2)) 
				continue;
		}
		else nb = 0;
		if (lastc == '\n') {
			if (n || b) {
				if (!b)
					printf ("%6d  ", ++l);
				else if (c != '\n') 
					printf ("%6d  ", ++l);
			}
		}
		if (c == '\t') {
			if (T) {
				printf ("^I");
				lastc = c;
				continue;
			}
		}
		if (c == '\n')
			if (E)
				putchar ('$');
		if (v && c < ' ' && c != '\n' && c != '\t') {
			putchar ('^');
			putchar (c + 0X40);	// Convert into  printable ASCII character
		} else
			fputc (c, stdout);
		lastc = c;
	}
	fclose (fp);
	
	if (stdin_file)
		unlink(temp);	// Delete the temporary file
	file++;
}

void store_files (char **fname) {
	static int only_file;		// only_file = 1 ["--" option specified]
	int hpn = 0;				// hpn = 1 [2 consecutive hypen present]
	
	if (!(strcmp(*fname,"-"))) {
		file = (char **) realloc (file, ++nof * sizeof (char *));	
		file[nof - 1] = *fname;
	}
	else if (**fname == '-' && (!only_file)) {
		while (*++*fname) {
			if (**fname != 'h' && **fname != 'v')
				if (hpn)
					error_message (fname);
			switch (**fname) {
				case '-':
					if (A || n || E || e || s || v || t || T || b)
						error_message (fname);
					only_file = 1;
					hpn = 1;
					break;
				case 'A':
					v = E = T = 1; 
					break;
				case 'b':
					b = 1;
					break;
				case 'n':
					n = 1;
					break;
				case 'E':
					E = 1;
					break;
				case 'T':
					T = 1;
					break;
				case 's':
					s = 1;
					break;
				case 'e':
					v = E = 1;
					break;
				case 't':
					v = T = 1;
					break;
				case 'v':
					if (hpn) {
						system ("./a.out cat_version");
						exit (0);
					}
					v = 1;
					break;
				case 'h':
					if (hpn) {
						system ("./a.out cat_help");
						exit (0);
					}
				// No break;
				default:
					error_message (fname);
					break;
			}
		}
	} else {
		if ((file = (char **) realloc (file, ++nof * sizeof (char *))) == NULL) {
			fprintf (stderr, "Cannot allocate dynamic memory.\n");
			exit (2);
		}
		file[nof - 1] = *fname;
	}
}

void error_message (char **fname) {
	printf ("./a.out: Invalid option: %s\n", *fname);
	printf ("Try './a.out --help' for more information\n");
	exit (1);
}
