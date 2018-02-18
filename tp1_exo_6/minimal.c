#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

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


void resize(int width, int height){
	WINDOW_HEIGHT= height;
    WINDOW_WIDTH= width;
	SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

void projection(){
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
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
	PrimitiveList listePrim = NULL;
	Primitive *p = allocPrimitive(GL_POINTS);

	addPrimitive(p, &listePrim);
	
	
	/* Boucle d'affichage */
	 int loop = 1;
	float x, y;
	
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
       glClear(GL_COLOR_BUFFER_BIT);
        
        
        /* Echange du front et du back buffer : mise à jour de la fenêtre */
      //  SDL_GL_SwapBuffers();
        
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

                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
					
					x = -1 + 2. * e.button.x / WINDOW_WIDTH;
                    y = -(-1 + 2. * e.button.y / WINDOW_HEIGHT);
					/*Ajout du point à la liste de la primitive active*/
					Point* point = allocPoint(x,y,1.0,1.0,1.0);
					addPointToList(point, &listePrim->points);
					break;                    
					
				/*Touche clavier*/
				case SDL_KEYDOWN:
					if(e.key.keysym.sym == SDLK_p){
						addPrimitive(allocPrimitive(GL_POINTS), &listePrim);
						printPrimitiveList(listePrim);
					}
						//dessinerForme(P);
					
					if(e.key.keysym.sym == SDLK_l){
						addPrimitive(allocPrimitive(GL_LINES), &listePrim);
						printPrimitiveList(listePrim);
					}
					
					if(e.key.keysym.sym == SDLK_t){
						addPrimitive(allocPrimitive(GL_TRIANGLES), &listePrim);
						printPrimitiveList(listePrim);
					}
							
					break;

                case SDL_VIDEORESIZE:
                    
					resize(e.resize.w, e.resize.h);
                    break;

                default:
                    break;
            }

        }

        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

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
	PointList tmp = *list;
		
	/*Parcours la liste*/
	while (tmp->next != NULL)
		tmp = tmp->next;
		
	/*Créer nouveau point, insère à la fin*/
	tmp->next = point;	
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
	printf("1\n");
	if(tmp == NULL){
		printf("Erreur allocation\n");
		exit(1);
	}
	printf("2\n");
	tmp->primitiveType = primitiveType;
	tmp->points = NULL;
	tmp->next = NULL;
	printf("3\n");
	return tmp;	
}

/*Role : ajouter une primitive à la liste
 *Paramètre : primitive à ajouter, liste
 */
void addPrimitive(Primitive *primitive, PrimitiveList *list){
	printf("je suis là1\n");
	
	if ((*list) == NULL)
		(*list) = primitive;
	
	/*Parcours la liste*/
	else
		addPrimitive(primitive, &(*liste)->next);	
}

/*Role : dessine une liste de primitves
 *Paramètre : liste de primitive
 */
void drawPrimitives(PrimitiveList list){
	while (list != NULL){
		glPointSize(5);
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
