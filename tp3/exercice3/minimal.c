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
void drawSquare(float x, float y){
	glBegin(GL_QUADS);
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
void drawCircle(){
	float angle;
	int i;
	angle = 2*PI/NB_SEG_CIRCLE;

	glBegin(GL_POLYGON); /*pour remplir, remplacer par GL_POLYGON*/

	for(i=0; i <= NB_SEG_CIRCLE; i++){
		glVertex2f(cos(angle*i),sin(angle*i));
	}

	glEnd();
}

/*Dessiner un carré avec bords arrondis*/
void drawRoundedSquare(){
	glPushMatrix();

		drawSquare(0.25, 0.5);
		drawSquare(0.5, 0.25);
		glPushMatrix();
			glScalef(0.25,0.25,0);
			glPushMatrix();
				glTranslatef(1.,1.,0);
				drawCircle();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-1.,1.,0);
				drawCircle();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(1.,-1.,0);
				drawCircle();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-1.,-1.,0);
				drawCircle();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	
}

void drawFirstArm(){
	drawCircle(1.,1.,1.);	
	glPushMatrix();
		glTranslatef(3,0.,0.);
		glScalef(0.5,0.5,0);
		drawCircle(1.,1.,1.);
	glPopMatrix();

	glBegin(GL_LINES);
		glVertex2f(0,1.);
		glVertex2f(3,0.5);
		glVertex2f(0.,-1.);
		glVertex2f(3,-0.5);
	glEnd();
}

GLuint createFirstArmIDList(){
	GLuint id = glGenLists(3);

	glNewList(id, GL_COMPILE);
		drawCircle(1.,1.,1.);	
		glPushMatrix();
			glTranslatef(3,0.,0.);
			glScalef(0.5,0.5,0);
			drawCircle(1.,1.,1.);
		glPopMatrix();

		glBegin(GL_LINES);
			glVertex2f(0,1.);
			glVertex2f(3,0.5);
			glVertex2f(0.,-1.);
			glVertex2f(3,-0.5);
		glEnd();
	glEndList();

	return id;
}

void drawSecondArm(){
	glColor3f(1.,0.,0.);
	glPushMatrix();
		glScalef(0.5, 0.5 ,0);
		drawRoundedSquare();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(2.3, 0., 0.);
		glScalef(0.5, 0.5 ,0);
		drawRoundedSquare();
	glPopMatrix();
	glBegin(GL_QUADS);
		glVertex2f(-0.15,0.15);
		glVertex2f(2.45,0.15);
		glVertex2f(2.45, -0.15);
		glVertex2f(-0.15,-0.15);
	glEnd();
}

GLuint createSecondArmIDList(){
	GLuint id = glGenLists(3);

	glNewList(id, GL_COMPILE);
		glColor3f(1.,0.,0.);
		glPushMatrix();
			glScalef(0.5, 0.5 ,0);
			drawRoundedSquare();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(2.3, 0., 0.);
			glScalef(0.5, 0.5 ,0);
			drawRoundedSquare();
		glPopMatrix();
		glBegin(GL_QUADS);
			glVertex2f(-0.15,0.15);
			glVertex2f(2.45,0.15);
			glVertex2f(2.45, -0.15);
			glVertex2f(-0.15,-0.15);
		glEnd();
	glEndList();

	return id;
}

void drawThirdArm(){
	glColor3f(0.,0.,1.);
	glPushMatrix();
		glScalef(0.3, 0.3 ,0);	
		drawRoundedSquare();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.9, 0., 0.);
		glScalef(0.2, 0.2 ,0);		
		drawCircle();
	glPopMatrix();

	glBegin(GL_QUADS);
		glVertex2f(-0.1,0.1);
		glVertex2f(1.9,0.1);
		glVertex2f(1.9, -0.1);
		glVertex2f(-0.1,-0.1);
	glEnd();
}

GLuint createThirdArmIDList(){
	GLuint id = glGenLists(3);

	glNewList(id, GL_COMPILE);
		glColor3f(0.,0.,1.);
		glPushMatrix();
			glScalef(0.3, 0.3 ,0);	
			drawRoundedSquare();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.9, 0., 0.);
			glScalef(0.2, 0.2 ,0);		
			drawCircle();
		glPopMatrix();

		glBegin(GL_QUADS);
			glVertex2f(-0.1,0.1);
			glVertex2f(1.9,0.1);
			glVertex2f(1.9, -0.1);
			glVertex2f(-0.1,-0.1);
		glEnd();
	glEndList();

	return id;
}



void resize(){
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-12., 12., -9., 9.);
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
	int gamma = 35;
	int beta = -45;
	int alpha = 45;
	GLuint id1 = createFirstArmIDList();
	GLuint id2 = createSecondArmIDList();
	GLuint id3 = createThirdArmIDList();

	glMatrixMode(GL_MODELVIEW);

	/* Boucle d'affichage */
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
       glClear(GL_COLOR_BUFFER_BIT);
       
       glPushMatrix();
		glColor3f(1.,1.,1.);
		glRotatef(alpha, 0., 0., 1.);
		//drawFirstArm();
		glCallList(id1);
		glPushMatrix();
			glTranslatef(3.,0.,0.);
			glRotatef(beta, 0., 0., 1.);
			//drawSecondArm();
			glCallList(id2);
			glPushMatrix();
				glTranslatef(2.3,0.,0.);
				glColor3f(1.,1.,1.);
				glPushMatrix();
					glRotatef(gamma+80, 0., 0., 1.);
					//drawThirdArm();	
					glCallList(id3);			
				glPopMatrix();

				glPushMatrix();
					glRotatef(gamma+120, 0., 0., 1.);
					//drawThirdArm();	
					glCallList(id3);						
				glPopMatrix();
				glPushMatrix();
					glRotatef(gamma+210, 0., 0., 1.);
					//drawThirdArm();	
					glCallList(id3);						
				glPopMatrix();
				glPushMatrix();
					glRotatef(gamma+280, 0., 0., 1.);
					//drawThirdArm();	
					glCallList(id3);				
				glPopMatrix();
				glPushMatrix();
					glRotatef(gamma+340, 0., 0., 1.);
					//drawThirdArm();	
					glCallList(id3);				
				glPopMatrix();

				
			glPopMatrix();
		glPopMatrix();
		
	glPopMatrix();
		alpha++;
		beta = beta+1;
		gamma = gamma+1;
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