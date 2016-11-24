#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "file.h"
#include "constantes.h"



int niveau(SDL_Surface* ecran)
{


    SDL_Event event;
    int continuer = 1;
    int i = 0, j = 0;
    int largeur[nombre_niveau + 2] = {0};
    int longueur[nombre_niveau + 2] = {0};
    int zoom[nombre_niveau + 2] = {0};
    int zoomRetour = 0;
    char chaineChiffre[5] = {0};
    SDL_Surface *imgFond = NULL, *Texte = NULL, *chiffre = NULL, *texteRetour = NULL;
    TTF_Init();


    imgFond = IMG_Load("DATA/fond2.png");
    SDL_Rect position, posTexte, positionChiffre, posRetour;

    for(i = 1; i < nombre_niveau; i++) // Stock les coordonnées de chaque chiffre
    {

        longueur[i] = i* longueur_chiffre;
        largeur[i] = i* largeur_chiffre;


    }



    TTF_Font *police = NULL;
    TTF_Font *policeTitre = NULL;
    TTF_Font *policezoom = NULL;
    police = TTF_OpenFont("font.ttf", 23);
    policezoom = TTF_OpenFont("font.ttf", 35);
    policeTitre = TTF_OpenFont("font.ttf",35);
    TTF_SetFontStyle(policeTitre, TTF_STYLE_ITALIC|TTF_STYLE_UNDERLINE);
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurRouge = {237,28,36};
    SDL_Color couleurBlanche = {255,255,255};
    Texte = TTF_RenderText_Blended(policeTitre, "Selectionne un niveau !", couleurRouge);
    chiffre = TTF_RenderText_Blended(police, "1",couleurRouge);
    texteRetour = TTF_RenderText_Blended(police,"Retour",couleurNoire);
    position.x =0;
    position.y = 0;
    posTexte.x = (ecran->w /2) -(Texte->w /2);
    posTexte.y = 0;
    positionChiffre.x = 0;
    positionChiffre.y = ecran->h / 5;
    posRetour.x = 290;
    posRetour.y = 400;
    while(continuer)

    {



        SDL_WaitEvent(&event);

        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            return 0;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {

            case SDLK_ESCAPE:
                continuer = 1;
                break;

            }
            break;

        case SDL_MOUSEMOTION:

            for(i = 0; i < nombre_niveau + 2; i++)
            {
                positionChiffre.x = i * longueur_chiffre;
                if(event.motion.y  > (positionChiffre.y ) && event.motion.y < (positionChiffre.y + 30) && event.motion.x > (positionChiffre.x) && event.motion.x < (positionChiffre.x + 20) )
                {
                    zoom[i -1] = 1;

                }
                else
                {
                    zoom[i - 1] = 0;

                }



            }



            if(event.motion.y > posRetour.y && event.motion.y < (posRetour.y + 30) && event.motion.x > posRetour.x && event.motion.x < (posRetour.x + 70))
            {
                zoomRetour = 1;

            }
            else
            {
                zoomRetour = 0;
            }


            break;









        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:

                for(i = 1; i < nombre_niveau + 2; i++)
                {
                    positionChiffre.x = i * longueur_chiffre;
                    if(event.motion.y > positionChiffre.y && event.motion.y < (positionChiffre.y + 30) && event.motion.x > positionChiffre.x && event.motion.x < (positionChiffre.x + 30) )
                    {
                        partieJeu(ecran,i - 2);
                        break;
                    }
                }
                if(event.motion.y > posRetour.y && event.motion.y < (posRetour.y + 30) && event.motion.x > posRetour.x && event.motion.x < (posRetour.x + 70))
                {
                    continuer = 0;
                    break;
                }
            }
            break;






        }





















        SDL_BlitSurface(imgFond,NULL,ecran,&position);
        SDL_BlitSurface(Texte,NULL,ecran,&posTexte);

        for(i =0; i < nombre_niveau; i++)
        {
            SDL_FreeSurface(chiffre);
            positionChiffre.x = i * longueur_chiffre + (longueur_chiffre * 2);
            sprintf(chaineChiffre,"%d",i +1);
            if(zoom[i + 1] == 1)
            {
                chiffre = TTF_RenderText_Blended(policezoom,chaineChiffre,couleurRouge);
            }
            else
            {


                chiffre = TTF_RenderText_Blended(police,chaineChiffre,couleurRouge);
            }
            SDL_BlitSurface(chiffre,NULL,ecran,&positionChiffre);
        }

        SDL_FreeSurface(texteRetour);
        if(zoomRetour ==1 )
        {
            texteRetour = TTF_RenderText_Blended(policezoom,"Retour",couleurNoire);
        }

        else
        {
            texteRetour = TTF_RenderText_Blended(police,"Retour",couleurNoire);
        }

        SDL_BlitSurface(texteRetour,NULL,ecran,&posRetour);

        SDL_Flip(ecran);

    }



    SDL_FreeSurface(imgFond);
    SDL_FreeSurface(Texte);
    SDL_FreeSurface(chiffre);
    SDL_FreeSurface(texteRetour);

    TTF_CloseFont(policezoom);
    TTF_CloseFont(policeTitre);
    TTF_CloseFont(police);
    TTF_Quit();

}
