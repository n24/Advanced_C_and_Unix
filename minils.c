
/*	Treat the command line arguments as directory names and display their contents.
	Handle -R -i -l switches.

	Usage :
		gcc minils.c
		./a.out [switches]
*/

# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/stat.h>
# include <time.h>
# include <string.h>

void List_Contents ( const char * directory_name );

int R, i, l;	// switches

int main ( int argc, char ** argv ) {
	char ** dname = NULL, * p;
	int n = 0;

	while ( *++argv ) {
		p = *argv;
		if ( *p == '-' && * ( p + 1 ) != '\0' ) {
			while ( *++p ) {
				switch ( *p ) {
					case 'i' : i = 1; break;
					case 'l' : l = 1; break;
					case 'R' : R = 1; break;
					default:
						fprintf ( stderr, "Invalid option %s\n", *argv );
						exit ( 1 );
				}
			}
		} else {
			dname = ( char ** ) realloc ( dname, ++n * sizeof ( char * ) );
			dname[n - 1] = *argv;
		}
	}

	if ( n ) {
		dname[n] = NULL;
		while ( *dname )
			List_Contents ( *dname++ );
	}
	else
		List_Contents ( "./" );

	return 0;
}

void List_Contents ( const char * directory_name ) {
	char dname[1000], ndname[1000];
	DIR * dir;
	struct dirent * dentry;
	struct stat st;

	strcpy ( dname, directory_name );
	if ( dname[strlen ( dname ) - 1] != '/' )
		strcat ( dname, "/" );
	if ( ( dir = opendir ( dname ) ) == NULL) {
		perror ( dname );
		return;
	}
	
	if ( R )
		printf ( "%s:\n", dname );
	while ( ( dentry = readdir ( dir ) ) ) {
		if ( dentry -> d_name[0] != '.') {
			if ( i ) 
				printf ( "%ld ", dentry -> d_ino);
			if ( l ) {
				char time[100];
				strcpy ( ndname, dname );
				strcat ( ndname, dentry -> d_name );
				if ( lstat ( ndname, & st ) == -1 )
					perror ( ndname );
				else {
					if ( S_ISDIR ( st . st_mode ) ) putchar ( 'd' );
					else putchar ( '-' );
					if ( st . st_mode & S_IRUSR ) putchar ( 'r' );
					else putchar ( '-' );
					if ( st . st_mode & S_IWUSR ) putchar ( 'w' );
					else putchar ( '-' );
					if ( st . st_mode & S_IXUSR ) putchar ( 'x' );
					else putchar ( '-' );
					if ( st . st_mode & S_IRGRP ) putchar ( 'r' );
					else putchar ( '-' );
					if ( st . st_mode & S_IWGRP ) putchar ( 'w' );
					else putchar ( '-' );
					if ( st . st_mode & S_IXGRP ) putchar ( 'x' );
					else putchar ( '-' );
					if ( st . st_mode & S_IROTH ) putchar ( 'r' );
					else putchar ( '-' );
					if ( st . st_mode & S_IWOTH ) putchar ( 'w' );
					else putchar ( '-' );
					if ( st . st_mode & S_IXOTH ) putchar ( 'x' );
					else putchar ( '-' );
					printf ( ". " );
					printf ( "%2d ", st . st_nlink ); 
					printf ( "%u ", st . st_uid );
					printf ( "%u ", st . st_gid );
					printf ( "%6ld ", st . st_size );
					ctime_r ( & st . st_mtime, time  );
					time[strlen ( time ) - 9] = '\0';
					printf ( "%s ", ( time + 4 ) );

				}
			}
			printf ( "%s ", dentry -> d_name );	
			putchar ( '\n' );
		}
	}

	if ( R ) {
		rewinddir ( dir );
		while ( ( dentry = readdir ( dir ) ) ) {
			if ( dentry -> d_name[0] != '.') {
				strcpy ( ndname, dname );
				strcat ( ndname, dentry -> d_name );
				if ( lstat ( ndname, & st ) == -1 )
					perror ( ndname );
				else if ( S_ISDIR ( st . st_mode ) )
					List_Contents ( ndname );
			}
		}
	}
	closedir ( dir );
}
