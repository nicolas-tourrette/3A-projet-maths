#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int main(int argc, char **argv){


    SDL_Window* fenetre_affichage(0);   //Definition de la fenêtre
    SDL_GLContext contexteOpenGL(0);	//Création d'un contexte OpenGL
    SDL_Event evenements;				//On crée un évènement
    bool terminer = false;				//Booléen pour faire un test


 	//Test sur l'initialisation de la SDL

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
       // cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;  -> Eventuel message d'erreur
        SDL_Quit();
        return -1;
    }


    // Choix de la version d'OpenGL   SetAttribute : spécifier des attributs OpenGL à la SDL

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);   //Version la plus ancienne utilisable
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);	//Version la plus récente utilisable

    // Double Buffer qui permet une meilleur qualité lors de l'affichage

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  //active le double-buffering
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);	 //attribut une profondeur au double buffering


    // Création de la fenêtre

    fenetre_affichage = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    //Test sur l'initialisation de la fenêtre d'affichage

    if(fenetre_affichage == 0){
        //cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;  -> Eventuel message d'erreur
        SDL_Quit();
        return -1;
    }


    // Création du contexte OpenGL

    contexteOpenGL = SDL_GL_CreateContext(fenetre_affichage); //attache le contexte OpenGL à la fenêtre d'affichage

    if(contexteOpenGL == 0){
        //cout << "Erreur liée au contexte OpenGL : "<< SDL_GetError() << endl;
        SDL_DestroyWindow(fenetre_affichage);
        SDL_Quit();
        return -1;
    }


    // Boucle principale

    while(!terminer){
        SDL_WaitEvent(&evenements);
        if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
            terminer = true;
    }


    // Destruction du contexte et de la fenêtre d'affichage et on quitte la SDL

    SDL_GL_DeleteContext(contexteOpenGL);
    SDL_DestroyWindow(fenetre_affichage);
    SDL_Quit();

    return 0;
}
