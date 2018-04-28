// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acc.h"  /* Include the header here, to obtain the function declaration */



int main(int argc, char* argv[])
{

	struct accelerometer acc_data[7024];
	char filepath[20];
	strcpy(filepath, "src/AccData.csv");
	int error = 0;
	error = readcsv(filepath, acc_data); 
	if (error == 1)
		printf("error: %d\n", error);
	printf("here is the first time: ");
	printf("%g\n", acc_data[1].x);
	printf("here is the last time: ");
	printf("%d\n", acc_data[2].t);

	struct accelerometer instance[1] = {
		{.t = 10, .x=6., .y=3., .z=2.}
	};
	printf("here is the last time: ");
	printf("%d\n", instance[0].t);
	
	double magnitude_array[7024];
	magnitude(acc_data, magnitude_array, 7024);
	printf("length is %lu\n", sizeof(acc_data)/sizeof(acc_data[0]));
	printf("magnitude is %g\n", magnitude_array[2]);
	printf("%g\n", magnitude_array[0]);
	printf("%g\n", magnitude_array[1]);



	/*
	printf("length is %lu\n", sizeof(instance)/sizeof(instance[0]));
	double mag_instance[1];
	magnitude(instance, mag_instance);
	printf("This magnitude should be 7 %g\n", mag_instance[0]);
	
	double x = 3;
	double y = 6;
	double z = 2;
	double magnitude_xyz;
	magnitude_xyz = calculateMagnitude( x, y, z );
	printf("x: %g\n", x);
	printf("y: %g\n", y);
	printf("magnitude_xyz: %g\n", magnitude_xyz);
	*/
    return 0;
}
