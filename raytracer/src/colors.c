#include "../include/colors.h"

/*Fonctions*/

/*Role : initialiser une couleur*/
Color3f createColor(float r, float g, float b){
	Color3f color;
	
	color.r = r;
	if(color.r > 1.0)
		color.r = 1.0;
	if(color.r < 0.0)
		color.r = 0.0;
	
	color.g = g;
	if(color.g > 1.0)
		color.g = 1.0;
	if(color.g < 0.0)
		color.g = 0.0;
	
	color.b = b;
	if(color.b > 1.0)
		color.b = 1.0;
	if(color.b < 0.0)
		color.b = 0.0;
	
	return color;
}
	
/*Role : Calculer la somme de deux couleurs*/
Color3f addColors(Color3f c1, Color3f c2){
	Color3f color;
	color = createColor((c1.r + c2.r), (c1.g + c2.g), (c1.b + c2.b));
	
	return color;
}

/*Role : Calculer la soustraction de deux couleurs*/
Color3f subColors(Color3f c1, Color3f c2){
	Color3f color;
	color = createColor((c1.r - c2.r), (c1.g - c2.g), (c1.b - c2.b));
	
	return color;
}

/*Role : Calculer la multiplication de deux couleurs*/
Color3f multColors(Color3f c1, Color3f c2){
	Color3f color;
	color = createColor((c1.r * c2.r), (c1.g * c2.g), (c1.b * c2.b));
	
	return color;
}

/*Role : Calculer la division de deux couleurs*/
Color3f divColors(Color3f c1, Color3f c2){
	Color3f color;
	color = createColor((c1.r / c2.r), (c1.g / c2.g), (c1.b / c2.b));
	
	return color;
}

/*Role : Calculer la multiplication d'une couleur par un scalaire*/
Color3f multColor(Color3f c, float a){
	Color3f color;
	color = createColor((c.r * a), (c.g * a), (c.b * a));
	
	return color;
}

/*Role : Calculer la division d'une couleur par un scalaire*/
Color3f divColor(Color3f c, float a){
	Color3f color;
	color = createColor((c.r / a), (c.g / a), (c.b / a));
	
	return color;
}