#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "geometry.h"
#include "colors.h"
#include "shape.h"

/*Structures*/

typedef struct Ray{
	Point3D position;
	Vector3D direction;
}Ray;

typedef struct Intersection{
	Point3D position;
	Color3f color;
}Intersection;

/*Fonctions*/
Ray createRay(Point3D position, Vector3D direction);
Intersection createIntersect(Point3D position, Color3f color);
int intersectsSphere(Ray r, Sphere s, Intersection* i);
int intersectsCube(Ray r, Cube c, Intersection* i);
Scene createScene(Sphere tabSphere[], Cube tabCube[]);
void addCubeToScene(Scene *scene, Cube cube);
void addSphereToScene(Scene *scene, Sphere sphere);

#endif