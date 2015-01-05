
/*	Rewrite the temperature conversion program of Section 1.2 to use a function for 
	conversion	*/

# include <stdio.h>

float celsius (float fahr);

/*	Print Fahrenheit - Celsius table
	for fahr = 0, 20, 40, ..... 300; Floating point version	*/

int main (void) {
	float fahr;
	int lower, upper, step;

	lower = 0; 		/* Lower limit of temperature table	*/
	upper = 300;	/* Upper limit	*/
	step = 20;		/* Step size	*/

	fahr = lower;
	while (fahr <= upper) {
		printf ("%3.0f\t%6.1f\n", fahr, celsius (fahr));
		fahr = fahr + step;
	}

	return 0;
}

float celsius (float fahr) {
	return (5.0 / 9.0) * (fahr - 32.0);
}
