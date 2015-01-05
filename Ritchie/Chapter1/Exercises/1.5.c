
/*	Modify the temperature conversion program to print the table in reverse order.	*/

# include <stdio.h>

int main (void) {
	float fahr, celsius;
	int lower, upper, step;

	lower = 0; 		// Lower limit of temperature table
	upper = 300;	// Upper limit
	step = 20;		// Step size
	
	printf ("Fahrenheit \t Celsius\n");
	fahr = upper;
	while (fahr >= lower) {
		celsius = (5.0 / 9.0) * (fahr - 32.0);
		printf ("%3.0f\t%12.1f\n", fahr, celsius);
		fahr = fahr - step;
	}

	return 0;
}
