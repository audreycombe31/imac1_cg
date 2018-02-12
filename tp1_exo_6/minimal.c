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
	printf("je suis là\n");
	PrimitiveList listePrim = NULL;
	printf("je suis ici\n");

	printf("coucou1\n");
	Primitive *p = allocPrimitive(GL_POINTS);
	printf("coucou2\n");
	addPrimitive(p, &listePrim);
	printf("coucou2\n");
	printPrimitiveList(listePrim);
	//deletePoints(&liste1);
	//deletePrimitive(&listePrim);
	
	//printfPointList(liste1);
	printf("coucou2");
	printPrimitiveList(listePrim);
	
	

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
    
    
   /*Coordonnees souris initialisation*/
    float x=1.0;
    float y=1.0;
	
	/*Nettoyage de la fenêtre*/
	glClear(GL_COLOR_BUFFER_BIT);
	
	/* Boucle d'affichage */
	 int loop = 1;
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
       // drawPoints(liste1);
        
        
        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();
        
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            /* L'utilisateur ferme la fenêtre : */
            if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == 113)) {
                loop = 0;
                break;
            }
			
			projection();
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) {

                /* Clic souris */
                case SDL_MOUSEBUTTONDOWN:
					x=e.button.x;
                    y=e.button.y;
					Point* point = allocPoint(x,y,255,255,255);
					addPointToList(point, &listePrim->points);
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    
					/*Changer couleur fond
                    glClear(GL_COLOR_BUFFER_BIT);
                    glClearColor((x/WINDOW_WIDTH), (y/WINDOW_HEIGHT), 0, 1);
					*/
					/*dessinerForme(L);
                    break;*/
					
				/*case SDL_MOUSEBUTTONUP:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    x=e.button.x;
                    y=e.button.y;*/
					/*Changer couleur fond
                    glClear(GL_COLOR_BUFFER_BIT);
                    glClearColor((x/WINDOW_WIDTH), (y/WINDOW_HEIGHT), 0, 1);
					*/
					/*dessinerLigne(x, y);
                    break;*/

                /* Touche clavier 
                case SDL_KEYDOWN:
                    printf("touche pressée (code = %d)\n", e.key.keysym.sym);
                    break;*/
					break;
					
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
		glVertex2f(-1 + 2. * list->x / WINDOW_WIDTH, -(-1 + 2. * list->y / WINDOW_HEIGHT));
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
	PrimitiveList tmp = *list;
	printf("je suis là1\n");
	
	if ((*list) == NULL){
		(*list) = primitive;
		return;
	}
	/*Parcours la liste*/
	while (tmp->next != NULL)
		tmp = tmp->next;
		
	/*Créer nouveau point, insère à la fin*/
	printf("je suis là2\n");
	tmp->next = primitive;	
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
/*	PrimitiveList tmp = *list;
	PrimitiveList ptmp;
	
	if(list == NULL)
		return;

	while(tmp->next != NULL){
		ptmp = tmp->next;
		deletePoints(&(tmp->points));
		free(tmp);
		tmp = ptmp;
	}
	free(tmp);
	*/
	
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
