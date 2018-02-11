#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;

/*Type d'objet à dessiner*/
static unsigned char P = GL_POINTS;
static unsigned char L = GL_LINES;
static unsigned char T = GL_TRIANGLES;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/*variables globales*/
float posX=1.0;
float posY=1.0;

void resize(int width, int height){
	WINDOW_HEIGHT= height;
    WINDOW_WIDTH= width;
	SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}


void dessinerForme(char forme){
	float x=1.0;
	float y=1.0;
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);

	 /* Boucle traitant les evenements */
     SDL_Event e;
     while(SDL_PollEvent(&e)) {

		
		switch(e.type) {

			/* Clic souris */
			case SDL_MOUSEBUTTONDOWN:
				printf("clic en (%d, %d)\n", e.button.x, e.button.y);
				x=e.button.x;
				y=e.button.y;
				/*Changer couleur fond
				glClear(GL_COLOR_BUFFER_BIT);
				glClearColor((x/WINDOW_WIDTH), (y/WINDOW_HEIGHT), 0, 1);
				*/
				break;
		}
	 }
    
	glPointSize(5);

    glBegin(forme);
		glColor3f(x/WINDOW_WIDTH,0,y/WINDOW_HEIGHT);
		if(forme == P)
        	glVertex2f(-1 + 2. * posX / WINDOW_WIDTH, -(-1 + 2. *posY / WINDOW_HEIGHT));
		if(forme == L){
        	glVertex2f(-1 + 2. * x / WINDOW_WIDTH, -(-1 + 2. *y / WINDOW_HEIGHT));
        	glVertex2f(-1 + 2. * x+20 / WINDOW_WIDTH, -(-1 + 2. *y / WINDOW_HEIGHT));
		}
		if(forme == T){
        	glVertex2f(-1 + 2. * x / WINDOW_WIDTH, -(-1 + 2. *y / WINDOW_HEIGHT));
        	glVertex2f(-1 + 2. * x / WINDOW_WIDTH, -(-1 + 2. *y / WINDOW_HEIGHT));
        	glVertex2f(-1 + 2. * x / WINDOW_WIDTH, -(-1 + 2. *y / WINDOW_HEIGHT));
		}
    glEnd();
}

/*Role : dessiner un point
 *Paramètres : x et y : coordonnées du point
*/
void dessinerPoint(float x, float y){
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);

    /*Dessinons des points*/
	glPointSize(5);

    glBegin(P);
		glColor3f(x/WINDOW_WIDTH,0,y/WINDOW_HEIGHT);
        glVertex2f(-1 + 2. * posX / WINDOW_WIDTH, -(-1 + 2. *posY / WINDOW_HEIGHT));
    glEnd();
}

/*Role : dessiner une ligne
 *Paramètres : x et y : coordonnées du point
*/
void dessinerLigne(float x, float y){
	char forme = L;
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);

    /*Dessinons des lignes*/
	

    glBegin(forme);
		glColor3f(x/WINDOW_WIDTH,0,y/WINDOW_HEIGHT);
        glVertex2f(-1 + 2. * x / WINDOW_WIDTH, -(-1 + 2. *y / WINDOW_HEIGHT));
	 	glVertex2f(-1 + 2. * (x+10) / WINDOW_WIDTH, -(-1 + 2. *y / WINDOW_HEIGHT));
		
				
    glEnd();
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
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) {

                /* Clic souris */
               /* case SDL_MOUSEBUTTONDOWN:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    x=e.button.x;
                    y=e.button.y;*/
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
					
				case SDL_KEYDOWN:
					if(e.key.keysym.sym == 112){
						if(SDL_MOUSEBUTTONDOWN){
                    		printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    		posX=e.button.x;
                    		posY=e.button.y;
						}
						dessinerForme(P);
					}
					if(e.key.keysym.sym == 108)
						dessinerForme(L);
					//if(e.key.keysym.sym == 116)
					//	dessinerTriangle(x,y);
							
					break;

                case SDL_VIDEORESIZE:
                    //projection();
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
