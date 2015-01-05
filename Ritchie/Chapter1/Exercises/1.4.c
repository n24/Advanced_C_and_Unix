
/*	Write a program to print corresponding Celsius to Fahrenheit table	*/

# include <stdio.h>

int main (void) {
	float fahr, celsius;
	int lower, upper, step;

	lower = 0; 		// Lower limit of temperature table
	upper = 300;	// Upper limit
	step = 20;		// Step size
	
	printf ("Celsius \t Fahrenheit\n");
	
	celsius = lower;
	while (celsius <= upper) {
		fahr = (celsius * 9.0) / 5.0 + 32.0;
		printf ("%3.0f \t\t%9.1f\n", celsius, fahr);
		celsius = celsius + step;
	}

	return 0;
}
