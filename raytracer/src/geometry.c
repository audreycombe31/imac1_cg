#include <stdio.h>
#include "../include/geometry.h"


/*Fonctions*/

/*Role : Construire point de coordonnées x,y,z*/
Point3D pointXYZ(float x, float y, float z){
	Point3D point;
	point.x = x;
	point.y = y;
	point.z = z;
	
	return point;
}

/*Role : Construire point de coordonnées x,y,z*/
Vector3D vectorXYZ(float x, float y, float z){
	Vector3D vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	
	return vector;
}

/*Role : Construire vecteur AB = B - A */
Vector3D vector(Point3D A, Point3D B){
	Vector3D vector;
	vector = vectorXYZ((B.x - A.x), (B.y - A.y), (B.z - A.z)); 
	
	return vector;
}

/*Role : Construire point P + vect V*/
Point3D pointPlusVector(Point3D P, Vector3D V){
	Point3D point;
	point = pointXYZ((P.x + V.x), (P.y + V.y), (P.z + V.z));
	
	return point;
}

/*Role : Addition de vecteurs*/
Vector3D addVectors(Vector3D A, Vector3D B){
	Vector3D vector;
	vector  = vectorXYZ((A.x + B.x), (A.y + B.y), (A.z + B.z));
	
	return vector;
}

/*Role : Soustraction  de vecteurs*/
Vector3D subVectors(Vector3D A, Vector3D B){
	Vector3D vector;
	vector = vectorXYZ((A.x - B.x), (A.y - B.y), (A.z - B.z));
	
	return vector;
}

/*Role : Multiplication d'un vecteur par un scalaire */
Vector3D multVector(Vector3D V, float a){
	Vector3D vector;
	vector = vectorXYZ((V.x * a), (V.y * a), (V.z * a));
	
	return vector;	
}

/*Role : Division d'un vecteur par un scalaire*/
Vector3D divVector(Vector3D V, float a){
	Vector3D vector;
	vector = vectorXYZ((V.x / a), (V.y / a), (V.z / a));
	
	return vector;	
}

/*Role : Calcul du produit scalaire de 2 vecteurs*/
float dot(Vector3D A, Vector3D B){
	float prodScalaire;
	prodScalaire = (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
	
	return prodScalaire;
}

/*Role : Calcul de la norme d'un vecteur*/
float norm(Vector3D A){
	float norme;
	norme = sqrtf(powf(A.x, 2) + powf(A.y, 2) + powf(A.z, 2));
	
	return norme;
}

/*Role : Retourner le vecteur normalisé*/
Vector3D normalize(Vector3D A){
	Vector3D vector;
	float normeA = norm(A);
	
	if(normeA == 0){
		printf("Erreur, division par 0 impossible, la normalisation n'a pas été effectuée\n");
		return A;
	}
	
	vector = vectorXYZ(A.x / normeA, A.y / normeA, A.z / normeA);
	
	return vector;
}

/*Role : Afficher contenu du point*/
void printPoint3D(Point3D p){
	printf("Point (%f, %f, %f)\n", p.x, p.y, p.z);
}

/*Role : Afficher contenu du vecteur*/
void printVector3D(Vector3D v){
	printf("Vecteur (%f, %f, %f)\n", v.x, v.y, v.z);
}
