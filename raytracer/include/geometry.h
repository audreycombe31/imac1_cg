#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <math.h>
#include <string.h>

/*Structures*/
typedef struct Vec3{
	float x;
	float y;
	float z;
} Point3D, Vector3D;

/*Prototypes*/

/*Role : Construire point de coordonnées x,y,z*/
Point3D pointXYZ(float x, float y, float z);

/*Role : Construire point de coordonnées x,y,z*/
Vector3D vectorXYZ(float x, float y, float z);

/*Role : Construire vecteur AB = B - A */
Vector3D vector(Point3D A, Point3D B);

/*Role : Construire point P + vect V*/
Point3D pointPlusVector(Point3D P, Vector3D V);

/*Role : Addition de vecteurs*/
Vector3D addVectors(Vector3D A, Vector3D B);

/*Role : Soustraction  de vecteurs*/
Vector3D subVectors(Vector3D A, Vector3D B);

/*Role : Multiplication d'un vecteur par un scalaire */
Vector3D multVector(Vector3D V, float a);

/*Role : Division d'un vecteur par un scalaire*/
Vector3D divVector(Vector3D V, float a);

/*Role : Calcul du produit scalaire de 2 vecteurs*/
float dot(Vector3D A, Vector3D B);

/*Role : Calcul de la norme d'un vecteur*/
float norm(Vector3D A);

/*Role : Retourner le vecteur normalisé*/
Vector3D normalize(Vector3D A);

/*Role : Afficher contenu du point*/
void printPoint3D(Point3D p);

/*Role : Afficher contenu du vecteur*/
void printVector3D(Vector3D v);

#endif