#include <stdio.h>
#include "../include/shape.h"


/*Fonctions*/

/*Fonctions*/
Sphere createSphere(Point3D centre, float rayon, Color3f color){
	Sphere sphere;
	
	sphere.centre = centre;
	sphere.rayon = rayon;
	sphere.color = color;
	
	return sphere;
}

Cube createCube(Point3D minimum, Point3D maximum, Color3f color){
	Cube cube;
	
	cube.minimum = minimum;
	cube.maximum = maximum;
	cube.color = color;
	
	return cube;
}
