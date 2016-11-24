#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <FMOD/fmod.h>
#include "jeu.h"
#include "editeur.h"
#include "constantes.h"

// 1200 lignes pour tout le jeu
int main(int argc, char *argv[])
{

    SDL_Surface *ecran = NULL, *imgQuitter = NULL, *imgFond = NULL, *imgQuitter1 = NULL;
    SDL_Surface *imgJouer = NULL, *imgNiveau = NULL, *imgEditer = NULL, *caisse = NULL;
    SDL_Surface *imgJouerRouge = NULL, *imgNiveauRouge = NULL, *imgEditerRouge = NULL;
    SDL_Surface *texteTitre = NULL, *mur = NULL, *fleche = NULL, *zelda_bas = NULL, *zelda_droite = NULL, *Objectif = NULL;
    SDL_Surface *textePause = NULL;
    SDL_Rect positionMenu, positionQuitter, positionFond, positionJouer, positionNiveau, positionEditer,posTitre, posMur1, posMur2, posMur3;
    SDL_Rect posZelda_bas, posZelda_droite, posFleche, posObjectif, posCaisse;
    SDL_Rect posPause;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();


    TTF_Font *police = NULL;
    TTF_Font *policeTitre = NULL;
    TTF_Font *policePause = NULL;
    police = TTF_OpenFont("font.ttf", 23);
    policeTitre = TTF_OpenFont("font.ttf",40);
    policePause = TTF_OpenFont("font.ttf",10);
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurRouge = {237,28,36};
    SDL_Color couleurBlanche = {255,255,255};

     FMOD_BOOL etat;
    FMOD_SYSTEM *system;
    FMOD_SOUND *clic = NULL;
    FMOD_SOUND *sound = NULL;
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
    FMOD_CHANNEL *canal_mus;

    FMOD_System_CreateSound(system, "DATA/clic1.wav", FMOD_CREATESAMPLE, 0, &clic);
    FMOD_System_CreateSound(system, "DATA/main.mp3", FMOD_2D | FMOD_CREATESTREAM| FMOD_LOOP_NORMAL, 0, &sound);

    FMOD_System_PlaySound(system,sound,NULL, 0, &canal_mus); // Lecture musique
    FMOD_Sound_SetLoopCount(sound, -1); // repetition de la musique

     FMOD_Channel_SetPaused(canal_mus, 1); // Met en pause le canal
    FMOD_Channel_SetVolume(canal_mus, 0.5); // Change le volume du canal
    FMOD_Channel_SetPaused(canal_mus, 0); // Remet en route le canal


     imgJouer = TTF_RenderText_Blended(police, "1  : Jouer (Mode Histoire)", couleurNoire);
    imgNiveau = TTF_RenderText_Blended(police, "2 : Jouer Niveau libre", couleurNoire);
    imgEditer = TTF_RenderText_Blended(police, "3 : Editer Niveau",couleurNoire);

     imgJouerRouge = TTF_RenderText_Blended(police, "1  : Jouer (Mode Histoire)", couleurRouge);
    imgNiveauRouge = TTF_RenderText_Blended(police, "2 : Jouer Niveau libre", couleurRouge);
    imgEditerRouge = TTF_RenderText_Blended(police, "3 : Editer Niveau",couleurRouge);

    texteTitre = TTF_RenderText_Blended(policeTitre,"Zelda Sokoban",couleurBlanche);
    textePause = TTF_RenderText_Blended(policePause,"P : Pause de la musique",couleurNoire);

    SDL_WM_SetIcon(IMG_Load("DATA/zelda_droite.gif"), NULL);
    ecran = SDL_SetVideoMode(Longueur, Largeur, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Zelda Sokoban Officiel SPECIALE NIVEAUX 4.0", NULL);

    int continuer = 1;
    int menu1 = 0;
    int menu2 = 0;
    int menu3 = 0;
    int menuspe = 0;
    int quitter1 = 0;


    imgQuitter = IMG_Load("DATA/quitter.gif");
    imgQuitter1 = IMG_Load("DATA/quitter1.gif");
    mur = IMG_Load("DATA/mur.png");
    zelda_bas = IMG_Load("DATA/zelda_bas.gif");
    zelda_droite = IMG_Load("DATA/zelda_droite.gif");
    fleche = IMG_Load("DATA/fleche.png");
    Objectif = IMG_Load("DATA/objectif.png");
    caisse = IMG_Load("DATA/caisse.png");
SDL_SetColorKey(imgQuitter, SDL_SRCCOLORKEY, SDL_MapRGB(imgQuitter->format, 0, 0, 0));
SDL_SetColorKey(imgQuitter1, SDL_SRCCOLORKEY, SDL_MapRGB(imgQuitter1->format, 0, 0, 0));

SDL_SetColorKey(zelda_bas, SDL_SRCCOLORKEY, SDL_MapRGB(zelda_bas->format, 255, 255, 255));
SDL_SetColorKey(zelda_droite, SDL_SRCCOLORKEY, SDL_MapRGB(zelda_droite->format, 255, 255, 255));
SDL_SetColorKey(fleche, SDL_SRCCOLORKEY, SDL_MapRGB(fleche->format, 19, 206, 92));
SDL_SetColorKey(Objectif, SDL_SRCCOLORKEY, SDL_MapRGB(Objectif->format, 19, 206, 92));
    imgFond = IMG_Load("DATA/fond.png");
    positionMenu.x = (Longueur/2) - (Largeur/2);
    positionMenu.y = 0;
    positionQuitter.x = Longueur * 4/5;
    positionQuitter.y = 410;
    positionFond.x = 0;
    positionFond.y = 0;

    positionJouer.x = 74;
    positionJouer.y = 198;

    positionNiveau.x = 74;
    positionNiveau.y = 230;

    positionEditer.x = 74;
    positionEditer.y = 262;

    posTitre.x = (ecran->w/2)-(texteTitre->w /2);
    posTitre.y = 50;

    posMur1.x = 20;
    posMur1.y = 50;

    posMur2.x = 354;
    posMur2.y = 50;

    posCaisse.x = 121;
    posCaisse.y = 324;

    posZelda_bas.x = 202;
    posZelda_bas.y = 100;

    posZelda_droite.x = 90;
    posZelda_droite.y =320;

    posFleche.x = 161;
    posFleche.y = 320;

    posObjectif.x = 303;
    posObjectif.y = 320;

    posPause.x = 300;
    posPause.y = 1;
debut:



while(continuer)
{


SDL_WaitEvent(&event);
        switch(event.type)
        {

            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_MOUSEMOTION:
                if (event.button.y > 197 && event.button.y < 225 && event.button.x > 73 && event.button.x < 345) {   menu1 = 1;}
                else if (event.button.y > 236 && event.button.y < 260 && event.button.x > 74 && event.button.x < 305 ) { menu2 = 1; }
                else if (event.button.y > 271 && event.button.y < 291 && event.button.x > 74 && event.button.x < 259 ) {menu3 = 1;}
                else {

                    menu1 = 0;
                    menu2 = 0;
                    menu3 = 0;

                }


                if((event.motion.y > positionQuitter.y +10 && event.motion.y < positionQuitter.y + 25) && (event.motion.x > positionQuitter.x + 15 && event.motion.x < positionQuitter.x + 65) ) { quitter1 = 1;}
                else {quitter1 = 0;}
                if(event.motion.y > 326 && event.motion.y < 357 && event.motion.x > 86 && event.motion.x < 120) {menuspe = 1; }
                else { menuspe = 0;}
                break;
            case SDL_MOUSEBUTTONDOWN:

                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:

                    if(event.button.y > 197 && event.button.y < 225 && event.button.x > 73 && event.button.x < 345) {  FMOD_System_PlaySound(system,clic,NULL, 0, NULL); continuer = partieJeu(ecran,0);}
                    if(event.button.y >236 && event.button.y < 260 && event.button.x > 73 && event.button.x < 305) {  FMOD_System_PlaySound(system,clic,NULL, 0, NULL); continuer = niveau(ecran);}
                    if (event.button.y > 271 && event.button.y < 291 && event.button.x > 73 && event.button.x < 259 ) {  FMOD_System_PlaySound(system,clic,NULL, 0, NULL); continuer = edit(ecran);}
                    if((event.button.y > positionQuitter.y +10 && event.button.y < positionQuitter.y + 25) && (event.button.x > positionQuitter.x + 15 && event.button.x < positionQuitter.x + 65) ){continuer = 0;}
                break;
            }

                break;


            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {

                case SDLK_ESCAPE:

                    break;

                case SDLK_1:
                   continuer = partieJeu(ecran,0);
                    break;
                case SDLK_KP1:
                   continuer = partieJeu(ecran,0);
                    break;
                case SDLK_2:
                    continuer = niveau(ecran);
                    break;
                case SDLK_KP2:
                    continuer = niveau(ecran);
                    break;
                case SDLK_3:
                    continuer = edit(ecran);
                    break;
                case SDLK_KP3:
                    continuer = edit(ecran);
                    break;
                case SDLK_p:

                    FMOD_Channel_GetPaused(canal_mus, &etat);

        if (etat == 1) // Si la chanson est en pause
            FMOD_Channel_SetPaused(canal_mus, 0); // On enlève la pause
        else // Sinon, elle est en cours de lecture
            FMOD_Channel_SetPaused(canal_mus, 1); // On met en pause



                }
            break;
        }

SDL_BlitSurface(imgFond,NULL,ecran, &positionFond);
SDL_BlitSurface(texteTitre,NULL,ecran,&posTitre);
SDL_BlitSurface(mur,NULL,ecran,&posMur1);
SDL_BlitSurface(mur,NULL,ecran,&posMur2);
SDL_BlitSurface(caisse,NULL,ecran,&posCaisse);
SDL_BlitSurface(zelda_bas,NULL,ecran,&posZelda_bas);
SDL_BlitSurface(fleche,NULL,ecran,&posFleche);
SDL_BlitSurface(Objectif,NULL,ecran,&posObjectif);
if(menuspe == 1) { SDL_BlitSurface(zelda_bas,NULL,ecran,&posZelda_droite);        }
else {SDL_BlitSurface(zelda_droite,NULL,ecran,&posZelda_droite);}


if(menu1 == 1) {      SDL_BlitSurface(imgJouerRouge,NULL,ecran,&positionJouer); }
else { SDL_BlitSurface(imgJouer,NULL,ecran,&positionJouer);}

if(menu2 == 1) { SDL_BlitSurface(imgNiveauRouge,NULL,ecran,&positionNiveau);}
else {SDL_BlitSurface(imgNiveau,NULL,ecran,&positionNiveau);}

if(menu3 == 1) {  SDL_BlitSurface(imgEditerRouge,NULL,ecran,&positionEditer);}
else {SDL_BlitSurface(imgEditer,NULL,ecran,&positionEditer);}


if(quitter1 == 1)
{


SDL_BlitSurface(imgQuitter1, NULL, ecran, &positionQuitter);
}
else
{
    SDL_BlitSurface(imgQuitter, NULL, ecran, &positionQuitter);
}

SDL_BlitSurface(textePause,NULL,ecran, &posPause);

SDL_Flip(ecran);


}

SDL_FreeSurface(imgFond);

SDL_FreeSurface(imgQuitter);
SDL_FreeSurface(imgQuitter1);

SDL_FreeSurface(imgJouer);
SDL_FreeSurface(imgNiveau);
SDL_FreeSurface(imgEditer);
SDL_FreeSurface(imgJouerRouge);
SDL_FreeSurface(imgNiveauRouge);
SDL_FreeSurface(imgEditerRouge);
SDL_FreeSurface(texteTitre);
SDL_FreeSurface(mur);
SDL_FreeSurface(Objectif);
SDL_FreeSurface(caisse);
SDL_FreeSurface(fleche);
SDL_FreeSurface(zelda_bas);
SDL_FreeSurface(zelda_droite);
SDL_FreeSurface(textePause);
TTF_CloseFont(police);
TTF_CloseFont(policeTitre);
TTF_CloseFont(policePause);

TTF_Quit();
FMOD_Sound_Release(clic);
FMOD_Sound_Release(sound);
FMOD_System_Close(system);
FMOD_System_Release(system);
    SDL_Quit();

    return EXIT_SUCCESS;


}
