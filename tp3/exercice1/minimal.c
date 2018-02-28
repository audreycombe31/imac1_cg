#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/*Nombres de segments pour former cercle*/
static const unsigned int NB_SEG_CIRCLE = 100;
/*Valeur de PI*/
static const float PI = 3.1415926535897932384626433832795;

/*Fonctions*/
/*Dessiner un carré de cote 1 centré sur l'origine*/
void drawSquare(float r, float v, float b, float x, float y){
	glBegin(GL_QUADS);
	glColor3f(r, v, b);
	glVertex2f(-x,y);
	glVertex2f(x,y);
	glVertex2f(x,-y);
	glVertex2f(-x,-y);
	glEnd();
}

/*Dessiner un repère*/
/*Paramètres : xH et yH = coordonnées axe horizontal, yV et xV = coordonnées axes vertical*/
void drawLandmark(float xH, float yH, float xV, float yV){
	int i, j; 

	glBegin(GL_LINES);
	glColor3f(1.,0.,0.);
	glVertex2f(-xH, yH);
	glVertex2f(xH, yH);
	glColor3f(0.,1.,0.);
	glVertex2f(xV,yV);
	glVertex2f(xV,yV);
	glEnd();

	/*Dessiner points repères*/
	glPointSize(5);
	glBegin(GL_POINTS);
	for(i=-xH; i <=xH; i++){
		glColor3f(1.0,0.,0.);
		glVertex2f(i,0);
	}
	for(j=-yV; j<=yV; j++){
		glColor3f(0.,1.,0.);
		glVertex2f(0,j);
	}
	glEnd();

}

/*Dessiner cercle de diamètre 1 centré sur origine*/
void drawCircle(float r, float v, float b){
	float angle;
	int i;
	angle = 2*PI/NB_SEG_CIRCLE;

	glBegin(GL_POLYGON); /*pour remplir, remplacer par GL_POLYGON*/
	glColor3f(r,v,b);

	for(i=0; i <= NB_SEG_CIRCLE; i++){
		glVertex2f(cos(angle*i),sin(angle*i));
	}

	glEnd();
}

/*Dessiner un carré avec bords arrondis*/
void drawRoundedSquare(){
	glPushMatrix();

		drawSquare(1., 1., 1., 0.25, 0.5);
		drawSquare(1., 1., 1., 0.5, 0.25);
		glPushMatrix();
			glScalef(0.25,0.25,0);
			glPushMatrix();
				glTranslatef(1.,1.,0);
				drawCircle(1.,1.,1.);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-1.,1.,0);
				drawCircle(1.,1.,1.);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(1.,-1.,0);
				drawCircle(1.,1.,1.);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-1.,-1.,0);
				drawCircle(1.,1.,1.);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	
}

void drawFirstArm(){
	glPushMatrix();
		glTranslatef(-1.5,0.,0.);
		drawCircle(1.,1.,1.);	
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.5,0.,0.);
		glScalef(0.5,0.5,0);
		drawCircle(1.,1.,1.);
	glPopMatrix();
	
	glBegin(GL_LINES);
		glVertex2f(-1.5,1.);
		glVertex2f(1.5,0.5);
		glVertex2f(-1.5,-1.);
		glVertex2f(1.5,-0.5);
	glEnd();
	
	
}

void resize(){
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-4., 4., -3., 3.);
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
    resize();
    
	/*Nettoyage de la fenêtre*/
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	int loop = 1;
/*	float x =0;
	float y=0;
	float posXCarre = 0.;
	float posYCarre =0;
	int rotation = 0;
	int mode=0;
	int lastTime =0;
	int currentTime;
	float randX=0;
	float randY= 0;*/

	glMatrixMode(GL_MODELVIEW);

	/* Boucle d'affichage */
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        //drawRoundedSquare();
		drawFirstArm();
							
                
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
					break;

                case SDL_VIDEORESIZE:
               	 	WINDOW_HEIGHT= e.resize.h;
   					WINDOW_WIDTH= e.resize.w;                    
					resize();
					glMatrixMode(GL_MODELVIEW);
                    break;
					
				 /* Clic souris */
                case SDL_MOUSEBUTTONUP:
					//x = -4 + 8. * e.button.x / WINDOW_WIDTH;
                    //y = -(-3 + 6. * e.button.y / WINDOW_HEIGHT);
                  //  posXCarre = -4 + 8. * e.button.x / WINDOW_WIDTH;
                   // posYCarre = -(-3 + 6. * e.button.y / WINDOW_HEIGHT);
		
					//mode =0;
					break;   

				case SDL_MOUSEBUTTONDOWN:
					//if(e.button.button == SDL_BUTTON_RIGHT)
						//mode =1;
					break;   	

				case SDL_MOUSEMOTION:
					//if(mode == 1){
						//posXCarre = -4 + 8. *e.motion.x/WINDOW_WIDTH;
						//posYCarre = -(-3 + 6. * e.motion.y/WINDOW_HEIGHT);
						//rotation++;
				//	}
                    	
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
	
    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}