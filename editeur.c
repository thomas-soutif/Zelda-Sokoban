#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "file.h"
#include "editeur.h"
#include "constantes.h"




int edit(SDL_Surface* ecran)
{
    int i = 0;
    int j = 0;
    int commandes_afficher = 1;
    int save = 0;

    int objetActuel = MUR;
   SDL_Surface *imgMur = NULL, *imgCaisse = NULL, *imgZelda = NULL, *imgObjectif = NULL, *imgCaisseOk = NULL, *imgCommandes = NULL, *imgSave = NULL, *imgPorte = NULL;
    SDL_Surface *imgMur_bleu = NULL, * imgCaisse_bleu = NULL, *imgZelda_bleu = NULL, *imgObjectif_bleu = NULL, *imgCaisseOk_bleu = NULL, *imgBarre = NULL, *imgPorteBleu = NULL, *imgPorteNoir = NULL;
   SDL_Surface *imgMur_noir = NULL, * imgCaisse_noir = NULL, *imgZelda_noir = NULL, *imgObjectif_noir = NULL, *imgCaisseOk_noir = NULL;
SDL_Event event;
SDL_Rect positionCurseur, position, positionSave, positionCaisse, positionCaisseOk, positionZelda, positionObjectif, positionMur, positionBarre, positionPorte;
int continuer = 1;
int carte[Longueur_Bloc][Largeur_Bloc] = {0};
int clicGaucheEnCours = 0;
int clicDroitEnCours = 0;



imgMur = IMG_Load("DATA/mur.png");
imgCaisse = IMG_Load("DATA/caisse.png");
imgObjectif = IMG_Load("DATA/objectif.png");
imgZelda = IMG_Load("DATA/zelda_bas.gif");
imgCaisseOk = IMG_Load("DATA/caisse_ok.png");
imgCommandes = IMG_Load("DATA/commandes_edition.png");
imgSave = IMG_Load("DATA/save.png");
imgPorte = IMG_Load("DATA/porte_ferme.png");

imgMur_bleu = IMG_Load("DATA/mur_bleu.png");
imgCaisse_bleu = IMG_Load("DATA/caisse_bleu.png");
imgCaisseOk_bleu = IMG_Load("DATA/caisse_ok_bleu.png");
imgZelda_bleu = IMG_Load("DATA/zelda_bleu.png");
imgObjectif_bleu = IMG_Load("DATA/objectif_bleu.png");
imgPorteBleu = IMG_Load("DATA/porte_ferme_bleu.png");


imgBarre = SDL_CreateRGBSurface(SDL_HWSURFACE, 408, 40, 32, 0, 0, 0, 0);
SDL_FillRect(imgBarre, NULL, SDL_MapRGB(ecran->format, 0, 163, 232));
imgMur_noir = IMG_Load("DATA/mur_noir.png");
imgCaisse_noir = IMG_Load("DATA/caisse_noir.png");
imgCaisseOk_noir = IMG_Load("DATA/caisse_ok_noir.png");
imgZelda_noir = IMG_Load("DATA/zelda_noir.png");
imgObjectif_noir = IMG_Load("DATA/objectif_noir.png");
imgPorteNoir = IMG_Load("DATA/porte_ferme_noir.png");

    positionCurseur.x = 0;
    positionCurseur.y = 0;
    position.x = 0;
    position.y = 0;
    positionSave.x = (Longueur/2) - (268/2);
    positionSave.y = (Largeur /2) - (84/2);

    positionMur.x = 104;
    positionMur.y = 408;
    positionCaisse.x = 144;
    positionCaisse.y = 408;
    positionObjectif.x = 184;
    positionObjectif.y = 408;
    positionZelda.x = 224;
    positionZelda.y = 408;
    positionCaisseOk.x = 264;
    positionCaisseOk.y = 408;
    positionBarre.x = 0;
    positionBarre.y = 408;
    positionPorte.x = 304;
    positionPorte.y = 408;


    SDL_EnableKeyRepeat(10, 100);

debut:
    while(continuer)

    {

        SDL_WaitEvent(&event);
    switch(event.type)
    {


        case SDL_QUIT:
                return 0;
                break;
        case SDL_MOUSEMOTION:
            // Lorsque la souris bouge
            positionCurseur.x = event.motion.x;
            positionCurseur.y = event.motion.y;
            if(positionCurseur.y < 408)
            {


            if (clicGaucheEnCours) // Si on déplace la souris et que le bouton gauche de la souris est enfoncé
            {
            carte[event.motion.x / 34][event.motion.y / 34] = objetActuel;
            }
            else if (clicDroitEnCours) // Pareil pour le bouton droit de la souris
            {
            carte[event.motion.x / 34][event.motion.y / 34] = VIDE;
            }
            }
                break;

        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {

         case SDL_BUTTON_LEFT:
                if(!commandes_afficher)
                {


                     if(save == 1) {


                   continuer = 0;
                  break;



                }

                if(event.motion.y > 408)
                {
                    if(event.motion.x >104 && event.motion.x < 144) {objetActuel = MUR;}
                    if(event.motion.x >144 && event.motion.x < 184) {objetActuel = CAISSE;}
                    if(event.motion.x >184 && event.motion.x < 224) {objetActuel = OBJECTIF;}
                    if(event.motion.x > 224 && event.motion.x < 264) {objetActuel = ZELDA;}
                    if(event.motion.x >264 && event.motion.x < 304) {objetActuel = CAISSE_OK;}
                    if(event.motion.x >304 && event.motion.x < 325) {objetActuel = PORTE;}

                }
                else
                {


                carte[event.motion.x / 34][event.motion.y / 34] = objetActuel;
                clicGaucheEnCours = 1;
                }


                }
                commandes_afficher = 0;
             // Si on clique sur le bouton gauche souris
                break;
         case SDL_BUTTON_RIGHT:
                carte[event.motion.x / 34][event.motion.y / 34] = VIDE;
                clicDroitEnCours = 1;

            break;
            }
            break;

         case SDL_MOUSEBUTTONUP:
            switch (event.button.button)
            {


                    case SDL_BUTTON_LEFT:
                    clicGaucheEnCours = 0;
                    break;

                    case SDL_BUTTON_RIGHT:
                    clicDroitEnCours = 0;
                    break;


            }
            break;
        case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {

                case SDLK_ESCAPE:
                    continuer =0;
                    break;
                case SDLK_1:
                    objetActuel = MUR;
                    break;
                case SDLK_KP1:
                    objetActuel = MUR;
                    break;
                case SDLK_2:
                    objetActuel = CAISSE;
                    break;
                case SDLK_KP2:
                    objetActuel = CAISSE;
                    break;
                case SDLK_3:
                    objetActuel = OBJECTIF;
                    break;
                case SDLK_KP3:
                    objetActuel = OBJECTIF;
                    break;
                case SDLK_4:
                    objetActuel = ZELDA;
                    break;
                case SDLK_KP4:
                    objetActuel = ZELDA;
                    break;
                case SDLK_5:
                    objetActuel = CAISSE_OK;
                    break;
                case SDLK_KP5:
                    objetActuel = CAISSE_OK;
                    break;

                case SDLK_6:
                    objetActuel = PORTE;
                    break;
                case SDLK_KP6:
                    objetActuel = PORTE;
                    break;
                case SDLK_s:
                    if(!commandes_afficher)
                    {


                    creerPartie(carte);
                    save = 1;
                    }
                    break;
                case SDLK_c:
                    chargerPartie(carte,-1);
                    break;
                case SDLK_r:

                    break;
                case SDLK_BACKSPACE:
                    for (i = 0 ; i < Longueur_Bloc; i++)
                    {
                for (j = 0 ; j < Largeur_Bloc; j++)
                    {
                    position.x = i *34;
                    position.y = j * 34;

                    carte[i][j] = VIDE;

                    }
                    }



                    break;

                }
        break;
    }
    if(positionCurseur.x > (Longueur) ){positionCurseur.x = (Longueur); }
    if(positionCurseur.y > (Largeur)) {positionCurseur.y = (Largeur);}

    if(commandes_afficher == 1)
    {
        SDL_BlitSurface(imgCommandes, NULL, ecran, &position);
    }
    else{
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));


    for (i = 0 ; i < Longueur_Bloc; i++)
{
    for (j = 0 ; j < Largeur_Bloc; j++)
    {
        position.x = i * 34;
        position.y = j * 34;

        switch(carte[i][j])
        {
            case MUR:
                SDL_BlitSurface(imgMur, NULL, ecran, &position);
                break;
            case CAISSE:
                SDL_BlitSurface(imgCaisse, NULL, ecran, &position);
                break;
            case OBJECTIF:
                SDL_BlitSurface(imgObjectif, NULL, ecran, &position);
                break;
            case ZELDA:
                SDL_BlitSurface(imgZelda,NULL,ecran,&position);
                break;
            case CAISSE_OK:
                SDL_BlitSurface(imgCaisseOk,NULL,ecran, &position);
                break;
            case PORTE:
                position.x = position.x +16;
                SDL_BlitSurface(imgPorte,NULL,ecran,&position);
                break;
        }
    }
}








    switch(objetActuel)
    {
    case MUR:
        SDL_BlitSurface(imgMur,NULL,ecran, &positionCurseur);
        break;
    case CAISSE:
        SDL_BlitSurface(imgCaisse,NULL,ecran, &positionCurseur);
        break;
    case OBJECTIF:
        SDL_BlitSurface(imgObjectif,NULL,ecran, &positionCurseur);
        break;
    case ZELDA:
        SDL_BlitSurface(imgZelda,NULL,ecran, &positionCurseur);
        break;
    case CAISSE_OK:
        SDL_BlitSurface(imgCaisseOk,NULL,ecran, &positionCurseur);
        break;
    case PORTE:
        SDL_BlitSurface(imgPorte,NULL,ecran, &positionCurseur);
        break;
    }

    }

    if(save == 1) {SDL_BlitSurface(imgSave,NULL,ecran, &positionSave);}


    SDL_BlitSurface(imgBarre,NULL,ecran,&positionBarre);

    SDL_BlitSurface(imgMur_bleu,NULL,ecran, &positionMur);
     SDL_BlitSurface(imgCaisse_bleu,NULL,ecran, &positionCaisse);
      SDL_BlitSurface(imgObjectif_bleu,NULL,ecran, &positionObjectif);
       SDL_BlitSurface(imgZelda_bleu,NULL,ecran, &positionZelda);
        SDL_BlitSurface(imgCaisseOk_bleu,NULL,ecran, &positionCaisseOk);
        SDL_BlitSurface(imgPorteBleu,NULL,ecran,&positionPorte);


        switch(objetActuel)
        {
        case MUR:
            SDL_BlitSurface(imgMur_noir,NULL,ecran, &positionMur);
            break;
        case CAISSE:
            SDL_BlitSurface(imgCaisse_noir,NULL,ecran, &positionCaisse);
            break;
        case OBJECTIF:
            SDL_BlitSurface(imgObjectif_noir,NULL,ecran, &positionObjectif);
            break;
        case ZELDA:
            SDL_BlitSurface(imgZelda_noir,NULL,ecran, &positionZelda);
            break;
        case CAISSE_OK:
            SDL_BlitSurface(imgCaisseOk_noir,NULL,ecran, &positionCaisseOk);
            break;
        case PORTE:
            SDL_BlitSurface(imgPorteNoir,NULL,ecran,&positionPorte);
        }




    SDL_Flip(ecran);

    // Afficher les images ici


    }


SDL_FreeSurface(imgMur);

SDL_FreeSurface(imgCaisse);
SDL_FreeSurface(imgZelda);
SDL_FreeSurface(imgObjectif);
SDL_FreeSurface(ecran);
SDL_FreeSurface(imgCaisseOk);
SDL_FreeSurface(imgCommandes);
SDL_FreeSurface(imgSave);
SDL_FreeSurface(imgPorte);

SDL_FreeSurface(imgMur_bleu);
SDL_FreeSurface(imgCaisse_bleu);
SDL_FreeSurface(imgCaisseOk_bleu);
SDL_FreeSurface(imgZelda_bleu);
SDL_FreeSurface(imgObjectif_bleu);
SDL_FreeSurface(imgBarre);
SDL_FreeSurface(imgPorteBleu);

SDL_FreeSurface(imgMur_noir);
SDL_FreeSurface(imgCaisse_noir);
SDL_FreeSurface(imgCaisseOk_noir);
SDL_FreeSurface(imgZelda_noir);
SDL_FreeSurface(imgObjectif_noir);
SDL_FreeSurface(imgPorteNoir);

    // Liberer surface ici







}
