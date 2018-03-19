#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../include/geometry.h"

int main(int argc, char ** argv){
	/*Tests fonctions*/
	
	printPoint3D(pointPlusVector(pointXYZ(0,0,0), vectorXYZ(1,2,0)));
	printVector3D(addVectors(vectorXYZ(0.5, 1.0, -2.0), vectorXYZ(0.2, -1.0, 0)));
	printVector3D(subVectors(vectorXYZ(0.5, 1.0, -2.0), vectorXYZ(0.2, -1.0, 0)));
	printVector3D(multVector(vectorXYZ(0.5, 1.0, -2.0), 2.0));
	printVector3D(multVector(vectorXYZ(0.5, 1.0, -2.0), 0.0));
	printVector3D(divVector(vectorXYZ(0.5, 1.0, -2.0), 2.0));
	printf("prodScalaire %f\n",dot(vectorXYZ(1.0, 0.0, 0.0), vectorXYZ(2.0, 0.0, 0.0)));
	
	
	return EXIT_SUCCESS;
}