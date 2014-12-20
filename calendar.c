
/*	Write a program to generate calendar.

	Usage:
		
		gcc calendar.c
		./a.out <month> <year>
*/

# include <stdio.h>
# include <stdlib.h>

int No_Of_Days ( int year );

int main ( int argc, char ** argv ) {
	int year, month, i;
	int sday;	// Starting day
	int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	char * month_name[12] = {"January","February","March","April",
							"May","June","July", "August", "September", 
							"October", "November", "December" };
	
	if ( argc != 3 ) {
		fprintf ( stderr, "Usage: ./a.out <month> <year>\n" );
		exit ( 1 );
	}

	month = atoi ( argv[1] );
	if ( month < 1 || month > 12 ) {
		fprintf ( stderr, "Illegal month value: use 1 - 12\n" );
		exit ( 2 );
	}
	
	year = atoi ( argv[2] );
	if ( year < 1 || year > 9999 ) {
		fprintf ( stderr, "Illegal year value: use 1900 - 9999\n" );
		exit ( 3 );
	}
	
	sday = 6; // Monday (Jan 1 0001 is saturday)
	if ( No_Of_Days ( year ) == 366 ) // Feb has 29 days in leap year
		days[1] = 29;
	
	for ( i = 1; i < year; i++ ) 
		sday += No_Of_Days ( i );
	for ( i = 1; i < month; i++ )
		sday += days[i - 1];
	
	sday %= 7;
	
	printf ( "%11s %d\n", month_name[month - 1], year );
	printf ( "Su Mo Tu We Th Fr Sa\n" );
	for ( i = 0; i < sday; i++ )
		printf ( "   " );
	for ( i = 1; i <= days[month - 1]; i++ ) {
		/* Sepetember 1752 is quite different.
			To know more about this read manual page 
			of cal (1) command in Linux by man cal
		*/
		if ( month == 9 && year == 1752 && i == 3 ) 
			i = 14;
		printf ( "%2d ", i );
		sday++;
		sday %= 7;
		if ( !sday ) 
			putchar ( '\n' );
	}
	putchar ( '\n' );
	return 0;
}

int No_Of_Days ( int y ) {
	if ( y == 1752 ) return 354;
	if ( (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0) )
		return 366;
	return 365;
}
