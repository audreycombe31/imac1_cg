#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

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

    // TODO: Chargement et traitement de la texture
	SDL_Surface *logo_imac_jpg;
	logo_imac_jpg = IMG_Load(filename);
	if(logo_imac_jpg == NULL)
		printf("erreur avec l'image\n");
	
	//Création de la texture
	GLuint textureID;
	glGenTextures(1, &textureID);
	
	//Attacher texture à un point de bind
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	//Chargement des données sur la carte graphique
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGB,
		logo_imac_jpg->w,
		logo_imac_jpg->h,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		logo_imac_jpg->pixels
	);
	
	//Détacher la texture de son point de bind
	glBindTexture(GL_TEXTURE_2D, 0);
	
    // TODO: Libération des données CPU
	SDL_FreeSurface(logo_imac_jpg);
    // ...

    // Boucle de dessin (à décommenter pour l'exercice 3)
    int loop = 1;
    glClearColor(0.1, 0.1, 0.1 ,1.0);
    while(loop) {

        Uint32 startTime = SDL_GetTicks();

        // TODO: Code de dessin
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D); //on précise qu'on veut activer la fonctionnalité de texturing
       	glBindTexture(GL_TEXTURE_2D, textureID);//On bind la texture pour pouvoir l'utiliser
		glPushMatrix();
			glScalef(0.2,0.2,1.);
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
		glPopMatrix();
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
