#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/*Nombres de segments pour former cercle*/
static const unsigned int NB_SEG_CIRCLE = 100;
/*Valeur de PI*/
static const float PI = 3.1415926535897932384626433832795;

/*Structures*/
typedef struct Point{
	float x, y; /*Position 2D du point*/
	unsigned char r, g, b; /*Couleur du point*/
	struct Point *next; /*Point suivant à dessiner*/
}Point, *PointList;

typedef struct Primitive{
	GLenum primitiveType;
	PointList points;
	struct Primitive *next;
}Primitive, *PrimitiveList;


/*Prototypes*/
Point *allocPoint (float x, float y, unsigned char r, unsigned char v, unsigned char b);
void addPointToList(Point *point, PointList *list);
void drawPoints(PointList list);
void deletePoints(PointList *list);
Primitive *allocPrimitive(GLenum primitiveType);
void addPrimitive(Primitive *primitive, PrimitiveList *list);
void drawPrimitives(PrimitiveList list);
void deletePrimitive(PrimitiveList *list);
void printfPointList(PointList list);
void printPrimitiveList(PrimitiveList list);
void drawSquare();
void drawLandmark();
void drawCircle();


void resize(int width, int height){
	WINDOW_HEIGHT= height;
    WINDOW_WIDTH= width;
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
	SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

int main(int argc, char** argv) {

    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Titre de la fenêtre */
    SDL_WM_SetCaption("First TD OpenGL YEAH", NULL);
    
	/*Nettoyage de la fenêtre*/
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	/*Création d'une primitive*/
	PrimitiveList primitives = NULL;
	/*Définition d'une liste de prim comme pointeur sur la 1ere*/
	Primitive *prim = allocPrimitive(GL_POINTS);
	/*Pointeur sur la dernière primitive de la liste*/
	PrimitiveList lastPrimitive = prim;
	/*Ajouter la primitive à la liste*/
	addPrimitive(prim, &primitives);
	
	
	int loop = 1;
	float x, y;
	int newPrimitivePressed;
	
	GLenum currentPrimitiveType = GL_POINTS; /*Type de la primitive active*/

	/* Boucle d'affichage */
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
		drawPrimitives(primitives);
		drawSquare();
		drawLandmark();
		drawCircle();
                
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            /* L'utilisateur ferme la fenêtre : */
            if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == 113)) {
                loop = 0;
                break;
			}
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) {                 
					
				/*Touche clavier*/
				case SDL_KEYDOWN:
					newPrimitivePressed = 0;
					GLenum newPrimitiveType;
					
					if(e.key.keysym.sym == SDLK_p){
						newPrimitivePressed = 1;
						newPrimitiveType = GL_POINTS;
					}
					
					if(e.key.keysym.sym == SDLK_l){
						newPrimitivePressed = 1;
						newPrimitiveType = GL_LINES;
					}
					
					if(e.key.keysym.sym == SDLK_t){
						newPrimitivePressed = 1;
						newPrimitiveType = GL_TRIANGLES;
					}
					
					if(e.key.keysym.sym == SDLK_c){
						/*Effacer tout*/
						deletePrimitive(&primitives); /*suppression des primitives actives*/
						addPrimitive(allocPrimitive(currentPrimitiveType), &primitives);
					}
					
					if(newPrimitivePressed != 0 && currentPrimitiveType != newPrimitiveType){
						prim = allocPrimitive(newPrimitiveType);
						lastPrimitive = prim;
						addPrimitive(prim, &primitives);
						currentPrimitiveType = newPrimitiveType;
					}
					break;

                case SDL_VIDEORESIZE:                    
					resize(e.resize.w, e.resize.h);
                    break;
					
				 /* Clic souris */
                case SDL_MOUSEBUTTONUP:
					x = -1 + 2. * e.button.x / WINDOW_WIDTH;
                    y = -(-1 + 2. * e.button.y / WINDOW_HEIGHT);
					/*Ajout du point à la liste de la primitive active*/
					addPointToList(allocPoint(x, y, 1.0,1.0,1.0), &lastPrimitive->points);
					break;   

                default:
                    break;		
            }
        }
	    /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();
		
        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }
	deletePrimitive(&primitives);
    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}

/*Fonctions*/

/*Role : allouer mémoire pour un point, initialiser le point
 *Paramètre : position x, y, couleurs r, v, b
 *Retour : pointeur sur le point
 */
Point *allocPoint (float x, float y, unsigned char r, unsigned char g, unsigned char b){
	PointList tmp;
	
	tmp = (Point *)malloc(sizeof(Point));
	
	if(tmp == NULL){
		printf("Erreur allocation\n");
		exit(1);
	}
	
	tmp->x = x;
	tmp->y = y;
	tmp->r = r;
	tmp->g = g;
	tmp->b = b;
	
	tmp->next = NULL;
	
	return tmp;	
}

/*Role : ajouter un point en fin de liste
 *Paramètre : point à ajouter
 */
void addPointToList(Point *point, PointList *list){
	
	if((*list) == NULL){	
		(*list) = point;
		return;
	}
		
	else
		addPointToList(point, &(*list)->next);
}

/*Role : dessiner tous les points de la liste
 *Paramètre : Liste des points
 */
void drawPoints(PointList list){
	/*Dessiner points*/
	
	while(list != NULL){
		glColor3f(list->r,list->g,list->b);
		glVertex2f(list->x,list->y);
		list = list->next;
		
	}
		
}

/*Role : libère l'espace mémoire alloué à tous les points d'une liste
 *Paramètre : liste des points
 */
void deletePoints(PointList *list){
	Point *tmp;
	
	while(*list){
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}

/*Role : Allouer mémoire pour une primitive
 *Paramètre : type de primitive
 */
Primitive *allocPrimitive(GLenum primitiveType){
	PrimitiveList tmp;
	
	tmp = (Primitive *)malloc(sizeof(Primitive));
	
	if(tmp == NULL){
		printf("Erreur allocation\n");
		exit(1);
	}
	
	tmp->primitiveType = primitiveType;
	tmp->points = NULL;
	tmp->next = NULL;

	return tmp;	
}

/*Role : ajouter une primitive à la liste
 *Paramètre : primitive à ajouter, liste
 */
void addPrimitive(Primitive *primitive, PrimitiveList *list){
	
	if((*list) == NULL){
		(*list) = primitive;
		return;
	}
	else
		addPrimitive(primitive, &(*list)->next);
}

/*Role : dessine une liste de primitves
 *Paramètre : liste de primitive
 */
void drawPrimitives(PrimitiveList list){
	while (list != NULL){
		glBegin(list->primitiveType);
		drawPoints(list->points);		
		glEnd();
		list = list->next;
	}
}

/*Role : libère l'espace mémoire alloué à une primitive et à tous les points qu'elle contient
 *Paramètre : liste des points
 */
void deletePrimitive(PrimitiveList *list){	
	Primitive *tmp;
	
	while(*list){
		tmp = *list;
		deletePoints(&(tmp->points));
		*list = (*list)->next;
		
		free(tmp);
	}
}

void printfPointList(PointList list){
	if(list == NULL)
		printf("Liste points vide\n");
	
	while(list != NULL){
		printf("Point (%f, %f)\n", list->x, list->y);
		list = list->next;
	}
}

void printPrimitiveList(PrimitiveList list){
	if(list == NULL)
		printf("Liste primitive vide\n");
	
	while(list != NULL){
		printf("Primitive (%d)\n", list->primitiveType);
		list = list->next;
	}	
}

/*Dessiner un carré de cote 1 centré sur l'origine*/
void drawSquare(){
	glBegin(GL_QUADS);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(-0.5,0.5);
	glVertex2f(0.5,0.5);
	glVertex2f(0.5,-0.5);
	glVertex2f(-0.5,-0.5);
	glEnd();
	
}

/*Dessiner un repère*/
void drawLandmark(){
	glBegin(GL_LINES);
	glColor3f(1.0,0.,0.);
	glVertex2f(-1, 0.);
	glVertex2f(1,0.);
	glColor3f(0.,1.,0.);
	glVertex2f(0.,1);
	glVertex2f(0.,-1);
	glEnd();
}

/*Dessiner cercle de diamètre 1 centré sur origine*/
void drawCircle(){
	float angle;
	int i;
	angle = 2*PI/NB_SEG_CIRCLE;

	glBegin(GL_LINE_STRIP); /*pour remplir, remplacer par GL_POLYGON*/
	glColor3f(1.0,0.,0.);

	for(i=0; i <= NB_SEG_CIRCLE; i++){
		glVertex2f(cos(angle*i),sin(angle*i));
	}

	glEnd();
}