
/*	A preprocessor directive that only handles # include <FILENAME>.

	Directive usage: ./a.out <input_file> <out_file>.
*/

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>

void in_to_out (FILE *in_fp, FILE *out_fp);
int check_header (char *name);

int main (int argc, char **argv) {
	FILE *in_fp, *out_fp;
	
	if (argc != 3) {
		fprintf (stderr, "Error: Invalid arguments\n");
		fprintf (stderr, "Usage: ./a.out <input_file> <output_file>\n");
		exit (1);
	}

	if ((in_fp = fopen (argv[1], "r")) == NULL) {
		perror (argv[1]);
		exit (2);
	}
	
	if ((out_fp = fopen (argv[2], "w+")) == NULL) {
		perror (argv[2]);
		exit (3);
	}

	if (!(strcmp (argv[1], argv[2]))) {
		fprintf (stderr, "Input and output files must be different\n");
		exit (4);
	}
	
	in_to_out (in_fp, out_fp);
	
	fclose (in_fp);
	fclose (out_fp);
	
	return 0;
}

void in_to_out (FILE *in_fp, FILE *out_fp) {
	FILE *new_fp;
	char name[100], temp[1000];
	int i, k;

	while ((fgets (temp, 1000, in_fp))) {
		k = i = 0;
		while (isspace(temp[k])) // Skip whitespaces.
			k++;
		if (temp[k++] == '#') {
			while (isspace(temp[k]))	// Skip whitespaces.
				k++;
			while (i < 7)	// Collect include
				name[i++] = temp[k++];
			name[i] = '\0';
			if (strcmp ("include", name) == 0) {
				while (isspace(temp[k]))	// Skip whitespaces.
					k++;
				if (temp[k++] == '<') {
					i = 0;
					while (temp[k] != '>' && temp[k] != '\n')
						name[i++] = temp[k++];
					name[i] = '\0';
					if (temp[k] == '\n') {
						fputs ("#include expects <FILENAME>", out_fp);
						fputs (temp, out_fp);
						continue;
					}
					if (check_header (name)) {
						char fname[256] = "/usr/include/";
						strcat (fname,name);
						if ((new_fp = fopen (fname, "r")) == NULL) {
							//perror (fname);
							//fputs (temp, out_fp);
							continue;
						}
						in_to_out (new_fp, out_fp);
						fclose (new_fp);
					}
				} else {
					fputs ("#include expects <FILENAME>", out_fp);
					fputs (temp, out_fp);
				}
			} else
				fputs (temp, out_fp);
		} else
			fputs (temp, out_fp);
	}
}

int check_header (char *name) {
	static char *headers[100000];
	static int head;
	int header_included, h;

	header_included = h = 0;
	
	for (h = 0; h < head; h++) {
		if (strcmp(headers[h],name) == 0) {
			header_included = 1;
			break;
		}
	}
	
	if (!header_included) {
		headers[head++] = strdup (name);
		printf ("Included: %s\n", name);
		return 1;
	}
	return 0;
}
