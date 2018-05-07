#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../include/geometry.h"
#include "../include/shape.h"
#include "../include/raytracer.h"


int main(int argc, char ** argv){

	/*Tests fonctions*/
	printPoint3D(pointPlusVector(pointXYZ(0,0,0), vectorXYZ(1,2,0)));
	printVector3D(addVectors(vectorXYZ(0.5, 1.0, -2.0), vectorXYZ(0.2, -1.0, 0)));
	printVector3D(subVectors(vectorXYZ(0.5, 1.0, -2.0), vectorXYZ(0.2, -1.0, 0)));
	printVector3D(multVector(vectorXYZ(0.5, 1.0, -2.0), 2.0));
	printVector3D(multVector(vectorXYZ(0.5, 1.0, -2.0), 0.0));
	printVector3D(divVector(vectorXYZ(0.5, 1.0, -2.0), 2.0));
	printf("prodScalaire %f\n",dot(vectorXYZ(1.0, 0.0, 0.0), vectorXYZ(2.0, 0.0, 0.0)));
	printf("prodScalaire %f\n",dot(vectorXYZ(1.0, 0.0, 0.0), vectorXYZ(0.0, 1.0, 0.0)));
	printf("norm %f\n",norm(vectorXYZ(2, 0.0, 0.0)));
	printf("norm %f\n",norm(vectorXYZ(1, 1,1)));
	printVector3D(normalize(vectorXYZ(1, 1,1)));
	printVector3D(normalize(vectorXYZ(0, 0,0)));
	
	/*Test intersection*/
	printf("------------------Test intersection------------------\n");
	Sphere sphere1 = createSphere(pointXYZ(0.,0.,0.), 1., createColor(0.8,0.0,0.0)); 
	Ray rayon1 = createRay(pointXYZ(-10.,0.,0.), vectorXYZ(1., 0., 0.));
	Intersection intersect1=createIntersect(pointXYZ(-1.,0.,0.), createColor(0.,0.8,0.));
	
	printf("Intersection sphere 1 et rayon1 : code retour : %d\n", intersectsSphere(rayon1, sphere1, &intersect1));
	printPoint3D(intersect1.position);
	
	
	return EXIT_SUCCESS;
}