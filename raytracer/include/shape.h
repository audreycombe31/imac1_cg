#ifndef SHAPE_H
#define SHAPE_H

#include "geometry.h"
#include "colors.h"


/*Structures*/

typedef struct Sphere{
	Point3D centre;
	float rayon;
	Color3f color;
}Sphere;

typedef struct Cube{
	Point3D minimum;
	Point3D maximum;
	Color3f color;
}Cube;

typedef struct Scene{
	Sphere tabSphere[10];
	Cube tabCube[10];
}Scene;

/*Fonctions*/

Sphere createSphere(Point3D centre, float rayon, Color3f color);
Cube createCube(Point3D minimum, Point3D maximum, Color3f color);


#endif