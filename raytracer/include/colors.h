#ifndef COLORS_H
#define COLORS_H

/*Structures*/

/*Couleurs : r, g, b compris entre 0.0 et 1.0*/
typedef struct Color3f{
	float r;
	float g;
	float b;
}Color3f;

/*Prototypes*/

/*Role : initialiser une couleur*/
Color3f createColor(float r, float g, float b);

/*Role : Calculer la somme de deux couleurs*/
Color3f addColors(Color3f c1, Color3f c2);

/*Role : Calculer la soustraction de deux couleurs*/
Color3f subColors(Color3f c1, Color3f c2);

/*Role : Calculer la multiplication de deux couleurs*/
Color3f multColors(Color3f c1, Color3f c2);

/*Role : Calculer la division de deux couleurs*/
Color3f divColors(Color3f c1, Color3f c2);

/*Role : Calculer la multiplication d'une couleur par un scalaire*/
Color3f multColor(Color3f c, float a);

/*Role : Calculer la division d'une couleur par un scalaire*/
Color3f divColor(Color3f c, float a);

#endif