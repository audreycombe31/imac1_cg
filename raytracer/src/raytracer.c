#include <stdio.h>
#include "../include/raytracer.h"

/*Fonctions*/
/*Construire un rayon*/
Ray createRay(Point3D position, Vector3D direction){
	Ray ray;
	ray.position = position;
	ray.direction = direction;
	
	return ray;
}

Intersection createIntersect(Point3D position, Color3f color){
	Intersection intersect;
	intersect.position = position;
	intersect.color = color;
	
	return intersect;
}


/*Role : tester si le rayon intersecte la sphere
 *Paramètres : rayon r, sphere s, intersection
 *Retour : 1 si intersection, 0 sinon
 */
int intersectsSphere(Ray r, Sphere s, Intersection* i){
	//a, b, c : coefficients de l'équation d'intersection
	float a = norm(r.direction); //norme de la direction du rayon
	float b = 2*dot(r.position, pointPlusVector(multVector((s.centre), -1.), (r.direction)));
	float c = norm(r.position)+norm(s.centre)-2*norm(r.position)-s.rayon;
	float delta = pow(b,2)-(4*pow(a,2)*pow(c,2));
	float t;
	
	if(delta < 0){
		printf("Il n'y a pas de solution réelle\n");
		return 0;
	}
	else if(delta ==0){
		t = (-b/(2*a));
		printf("Le delta est nul et la solution double est : %f\n", t);
		return 1;
	}
	else if(delta > 0){
		float x1 = (-b-sqrt(delta)/2*a);
		float x2 = (-b+sqrt(delta)/2*a);
		printf("le delta est positif et les solutions sont x1 = %f et x2 = %f\n", x1, x2);
		if(x1 > 0 || x2 > 0){
			if(x1 >= x2)
				t = x1;
			else
				t = x2;
		i->position = pointXYZ(r.position.x + r.direction.x*t, r.position.y + r.direction.y*t, r.position.z + r.direction.z*t);
		i->color = s.color;
		return 1;
		}
		else
			return 0;
	}
	return 0;
}


Scene createScene(Sphere tabSphere[], Cube tabCube[]){
	Scene scene;
	
	int i;
	for (i=0; i<10; i++){
		scene.tabSphere[i] = tabSphere[i];
		scene.tabCube[i] = tabCube[i];
	}
	return scene;
	
}

void addCubeToScene(Scene *scene, Cube cube){
}

void addSphereToScene(Scene *scene, Sphere sphere){
}


/*
int intersectsCube(Ray r, Cube c, Intersection*){
	
}
*/