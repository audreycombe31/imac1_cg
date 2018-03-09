#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

const char* filename = "logo_imac_400x400.jpg";

int main(int argc, char** argv) {

    // Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    // Ouverture d'une fenêtre et création d'un contexte OpenGL
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("td04", NULL);
    resizeViewport();
	
	//Récupération du temps
	struct tm instant;
	int seconde = instant.tm_sec;
	int minute = instant.tm_min;
	int hour = instant.tm_hour;
	

    // TODO: Chargement et traitement de la texture
	SDL_Surface *nb_0;
	SDL_Surface *nb_1;
	SDL_Surface *nb_2;
	SDL_Surface *nb_3;
	SDL_Surface *nb_4;
	SDL_Surface *nb_5;
	SDL_Surface *nb_6;
	SDL_Surface *nb_7;
	SDL_Surface *nb_8;
	SDL_Surface *nb_9;
	SDL_Surface *nb_colon;

	
	nb_0 = IMG_Load("numbers/0.png");
	nb_1 = IMG_Load("numbers/1.png");
	nb_2 = IMG_Load("numbers/2.png");
	nb_3 = IMG_Load("numbers/3.png");
	nb_4 = IMG_Load("numbers/4.png");
	nb_5 = IMG_Load("numbers/5.png");
	nb_6 = IMG_Load("numbers/6.png");
	nb_7 = IMG_Load("numbers/7.png");
	nb_8 = IMG_Load("numbers/8.png");
	nb_9 = IMG_Load("numbers/9.png");
	nb_colon = IMG_Load("numbers/colon.png");
	
	if(nb_0 == NULL || nb_1 == NULL || nb_2 == NULL || nb_3 == NULL || nb_4 == NULL || nb_5 == NULL || nb_6 == NULL || nb_7 == NULL || nb_8 == NULL || nb_9 == NULL || nb_colon == NULL)
		printf("erreur avec l'image\n");
	
	//Création de la texture
	GLuint textureID;
	glGenTextures(10, &textureID);
	
	//Attacher texxture à un point de bind
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	//Chargement des données sur la carte graphique
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGB,
		nb_0->w,
		nb_0->h,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		nb_0->pixels
	);
	
	//Détacher la texture de son point de bind
	glBindTexture(GL_TEXTURE_2D, 0);
	printf("%d\n", textureID);
    // TODO: Libération des données CPU
	SDL_FreeSurface(nb_0);
	SDL_FreeSurface(nb_1);
	SDL_FreeSurface(nb_2);
	SDL_FreeSurface(nb_3);
	SDL_FreeSurface(nb_4);
	SDL_FreeSurface(nb_5);
	SDL_FreeSurface(nb_6);
	SDL_FreeSurface(nb_7);
	SDL_FreeSurface(nb_8);
	SDL_FreeSurface(nb_9);
	SDL_FreeSurface(nb_colon);
	

    // Boucle de dessin (à décommenter pour l'exercice 3)
    int loop = 1;
    glClearColor(0.1, 0.1, 0.1 ,1.0);
    while(loop) {

        Uint32 startTime = SDL_GetTicks();

        // TODO: Code de dessin
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D); //on précise qu'on veut activer la fonctionnalité de texturing
       	glBindTexture(GL_TEXTURE_2D, textureID);//On bind la texture pour pouvoir l'utiliser
		
	
        glBegin(GL_QUADS);
			glTexCoord2f(0,0);
			glVertex2f(-0.5,0.5);
			glTexCoord2f(1,0);
			glVertex2f(0.5,0.5);
			glTexCoord2f(1,1);
			glVertex2f(0.5,-0.5);
			glTexCoord2f(0,1);
			glVertex2f(-0.5,-0.5);
		glEnd();	
	
		glDisable(GL_TEXTURE_2D); //on désactive la fonctionnalité de texturing
       	glBindTexture(GL_TEXTURE_2D, 0);//On débind la texture pour pouvoir l'utiliser
		
	
        // Fin du code de dessin

        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            switch(e.type) {

                case SDL_QUIT:
                    loop = 0;
                    break;

                case SDL_VIDEORESIZE:
                    WINDOW_WIDTH = e.resize.w;
                    WINDOW_HEIGHT = e.resize.h;
                    resizeViewport();

                default:
                    break;
            }
        }

        SDL_GL_SwapBuffers();
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    // TODO: Libération des données GPU
    glDeleteTextures(1, &textureID);

    // Liberation des ressources associées à la SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}
