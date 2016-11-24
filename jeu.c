#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "file.h"
#include "constantes.h"



int partieJeu(SDL_Surface* ecran, int niveau) {

SDL_Surface *imgFond = NULL, *imgMur = NULL, *imgCaisse = NULL, *imgZeldaBAS = NULL, *imgZeldaHAUT = NULL, *imgZeldaGAUCHE = NULL, *imgZeldaDROITE = NULL, *imgObjectif = NULL, *imgCaisseOk = NULL, *imgBarre = NULL;
SDL_Surface *imgBravo = NULL,*texteRetour = NULL, *texteRecommencer, *textePerdue = NULL, *texteNiveau = NULL, *texteAuteur = NULL, *texteCompteur = NULL, *neige = NULL;
SDL_Surface *imgPorte_ferme = NULL, *imgPorte_ouverte = NULL;
SDL_Event event;
TTF_Init();
SDL_Rect positionFond, position, positionZelda, positionBarre, positionBravo,positionCompteur, positionTexteRetour, positionTexteRecommencer,positionPerdue;
SDL_Rect positionTexteNiveau, positionTexteAuteur;
int continuer = 1;
int porte_passe  = 0;
int carte[Longueur_Bloc][Largeur_Bloc] = {0};
char chaineNiv[10] = {0};
char chaineCompteur[10] = {0};

TTF_Font *policeTexte = NULL;
TTF_Font *policePerdue = NULL;
TTF_Font *policeAuteur = NULL;
TTF_Font *policeCompteur = NULL;

policeTexte = TTF_OpenFont("font.ttf",10);
policePerdue = TTF_OpenFont("NEIGE.ttf",50);
policeAuteur = TTF_OpenFont("font.ttf",10);
policeCompteur = TTF_OpenFont("NEIGE.ttf",15);
SDL_Color couleurNoire = {0, 0, 0};
SDL_Color couleurRouge = {237,28,36};
SDL_Color Cyan = {0, 163, 232};
TTF_SetFontStyle(policeCompteur, TTF_STYLE_NORMAL);
TTF_SetFontStyle(policeAuteur,TTF_STYLE_ITALIC);
texteRetour = TTF_RenderText_Shaded(policeTexte, "Echap : Retourner au menu", couleurNoire,Cyan);
texteRecommencer = TTF_RenderText_Shaded(policeTexte, "R : Recommencer", couleurNoire,Cyan);
textePerdue = TTF_RenderText_Blended(policePerdue," PERDU(E)",couleurRouge);
texteAuteur = TTF_RenderText_Shaded(policeAuteur,"Auteur : Mikael",couleurNoire,Cyan);
int i = 0;
int j = 0;


int max = 150;
int bravo = 0;
int perdue = 0;
int caisse_restant = 0;
int ZeldaActuel = BAS;
int temps1 = 0, temps2 = 0;
int tempsActuel = 0, precedent = 0;
int rebours = 0;
int reboursInt = 0;
int compteur = 0;

imgMur = IMG_Load("DATA/mur.png");
neige = IMG_Load("DATA/neige.png");
imgCaisse = IMG_Load("DATA/caisse.png");
imgObjectif = IMG_Load("DATA/objectif.png");
imgZeldaBAS = IMG_Load("DATA/zelda_bas.gif");
imgZeldaHAUT = IMG_Load("DATA/zelda_haut.gif");
imgZeldaGAUCHE = IMG_Load("DATA/zelda_gauche.gif");
imgZeldaDROITE = IMG_Load("DATA/zelda_droite.gif");
imgCaisseOk = IMG_Load("DATA/caisse_ok.png");
imgPorte_ferme = IMG_Load("DATA/porte_ferme.png");
imgPorte_ouverte = IMG_Load("DATA/porte_ouverte.png");
imgBarre = SDL_CreateRGBSurface(SDL_HWSURFACE, 408, 40, 32, 0, 0, 0, 0);
SDL_FillRect(imgBarre, NULL, SDL_MapRGB(ecran->format, 0, 163, 232));

SDL_SetColorKey(imgPorte_ferme, SDL_SRCCOLORKEY, SDL_MapRGB(imgPorte_ferme->format, 255, 255, 255));
SDL_SetColorKey(imgZeldaHAUT, SDL_SRCCOLORKEY, SDL_MapRGB(imgZeldaHAUT->format, 255, 255, 255));
SDL_SetColorKey(imgZeldaBAS, SDL_SRCCOLORKEY, SDL_MapRGB(imgZeldaBAS->format, 255, 255, 255));
SDL_SetColorKey(imgZeldaGAUCHE, SDL_SRCCOLORKEY, SDL_MapRGB(imgZeldaGAUCHE->format, 255, 255, 255));
SDL_SetColorKey(imgZeldaDROITE, SDL_SRCCOLORKEY, SDL_MapRGB(imgZeldaDROITE->format, 255, 255, 255));
imgBravo = IMG_Load("DATA/bravo.jpg");

    positionFond.x = (Longueur/2) - (310/2) ;
    positionFond.y = 0;
    position.x = 0;
    position.y = 0;
    positionBarre.y = 408;
    positionBarre.x =0;
    positionCompteur.x = 300;
    positionCompteur.y = 415;
    positionTexteRetour.x = 0;
    positionTexteRetour.y = 408;
    positionTexteRecommencer.x = 0;
    positionTexteRecommencer.y = 425;
    positionBravo.x = (Longueur/2) - (268/2);
    positionBravo.y = (Largeur /2) - (84/2);
    positionPerdue.x = ( ecran->w /2) - (textePerdue->w / 2);
    positionPerdue.y = ecran->h / 2;
    positionTexteNiveau.x = 150;
    positionTexteNiveau.y = 410;
    positionTexteAuteur.x = 150;
    positionTexteAuteur.y = 430;
debut:

niveau = niveau + 1;
sprintf(chaineNiv,"Niveau : %d",niveau);
texteNiveau = TTF_RenderText_Shaded(policeCompteur,chaineNiv,couleurRouge,Cyan);
debut3:
rebours = CompteRebours(niveau); // Fonction pour savoir combien de secondes il y a dans le niveau

debut2:
bravo = 0;

chargerPartie(carte,niveau);





// Recherche de la position de Zelda au départ
for (i = 0 ; i < Longueur_Bloc ; i++)
{
    for (j = 0 ; j < Largeur_Bloc ; j++)
    {
        if (carte[i][j] == ZELDA) // Si Zelda se trouve à cette position
        {
            positionZelda.x = i*34;
            positionZelda.y = j*34;
            carte[i][j] = VIDE;
        }
    }
}




 SDL_EnableKeyRepeat(10, 80);

while(continuer)
{







    if(SDL_PollEvent(&event))
    {


    switch(event.type)
    {


        case SDL_QUIT:
                return 0;
                break;
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {

         case SDL_BUTTON_LEFT:


                if(perdue == 1) { perdue = 0; goto debut3;}
            break;

            }
            break;
        case SDL_KEYDOWN:


  switch (event.key.keysym.sym)
                {

                case SDLK_ESCAPE:
                    continuer = 0;



                    break;
                case SDLK_r:
                    goto debut3;

                    break;
                case SDLK_UP:

                    if(perdue == 1) { perdue = 0; goto debut3;}

                    if(!perdue)
                    {




                    ZeldaActuel = HAUT;
                   porte_passe = deplacerJoueur(carte,&positionZelda,HAUT,bravo);
                    if(porte_passe == 1) {  porte_passe = 0; goto debut;}


                    }
                    break;
                case SDLK_DOWN:
                    if(perdue == 1) { perdue = 0; goto debut3;}

                    if(!perdue)
                    {
                      ZeldaActuel = BAS;
                   porte_passe = deplacerJoueur(carte, &positionZelda, BAS,bravo);
                    if(porte_passe == 1) {  porte_passe = 0; goto debut;}
                    }
                    break;
                case SDLK_LEFT:

                    if(perdue == 1) { perdue = 0; goto debut3;}

                         if(!perdue)
                    {



                    ZeldaActuel = GAUCHE;
                  porte_passe = deplacerJoueur(carte,&positionZelda,GAUCHE,bravo);
                  if(porte_passe == 1) {  porte_passe = 0; goto debut;}

                    }
                    break;
                case SDLK_RIGHT:
                if(perdue == 1) { perdue = 0; goto debut3;}

                     if(!perdue)
                    {

                    ZeldaActuel = DROITE;
                    porte_passe = deplacerJoueur(carte,&positionZelda,DROITE,bravo);
                    if(porte_passe == 1) {  porte_passe = 0; goto debut;}


                    }

                    break;

                }





                    break;



                case SDL_KEYUP:

                    switch(event.key.keysym.sym)
                    {


                case SDLK_UP:



                    case SDLK_LEFT:



                        break;
                    case SDLK_RIGHT:

                        break;

                    }
                 break;
    }


    } // Fin du poll
else { SDL_Delay(20 - (tempsActuel - precedent));}


    if(!bravo && !perdue)
    {



    tempsActuel = SDL_GetTicks();
    if(tempsActuel - precedent > 20) {
        SDL_FreeSurface(texteCompteur);
        rebours -= 20;
        reboursInt = rebours / 1000;
        sprintf(chaineCompteur,"Temps : %d",reboursInt);

        texteCompteur = TTF_RenderText_Blended(policeCompteur,chaineCompteur,couleurNoire);
        precedent = SDL_GetTicks();


    }

    }

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
                SDL_BlitSurface(imgZeldaBAS,NULL,ecran,&position);
                break;
            case CAISSE_OK:
                SDL_BlitSurface(imgCaisseOk,NULL,ecran, &position);
                break;
            case VIDE:
                SDL_BlitSurface(neige,NULL,ecran, &position);

                break;
            case PORTE:
                SDL_BlitSurface(neige,NULL,ecran, &position);
                position.x = position.x + 16;
                if(bravo != 1)
                {


                 SDL_BlitSurface(imgPorte_ferme,NULL,ecran, &position);
                }
                else
                {
                    SDL_BlitSurface(imgPorte_ouverte,NULL,ecran, &position);
                }
                 break;

        }
    }
}





switch(ZeldaActuel)
{

case BAS:
    SDL_BlitSurface(imgZeldaBAS,NULL,ecran, &positionZelda);
    break;
case HAUT:
    SDL_BlitSurface(imgZeldaHAUT,NULL,ecran, &positionZelda);
    break;
case DROITE:
    SDL_BlitSurface(imgZeldaDROITE,NULL,ecran, &positionZelda);
    break;
case GAUCHE:
    SDL_BlitSurface(imgZeldaGAUCHE,NULL,ecran, &positionZelda);
    break;
}




    SDL_BlitSurface(imgBarre,NULL,ecran,&positionBarre);

    SDL_BlitSurface(texteRetour, NULL, ecran, &positionTexteRetour); /* Blit du texte */
    SDL_BlitSurface(texteRecommencer, NULL, ecran, &positionTexteRecommencer); /* Blit du texte */
    SDL_BlitSurface(texteNiveau, NULL, ecran, &positionTexteNiveau); /* Blit du texte */
    SDL_BlitSurface(texteAuteur, NULL, ecran, &positionTexteAuteur); /* Blit du texte */
    SDL_BlitSurface(texteCompteur,NULL,ecran,&positionCompteur);
    if (rebours <= 0){SDL_BlitSurface(textePerdue,NULL,ecran,&positionPerdue); perdue = 1; }
caisse_restant = 0;
    for (i = 0 ; i < Longueur_Bloc ; i++)
{
    for (j = 0 ; j < Largeur_Bloc ; j++)
    {
        if (carte[i][j] == OBJECTIF)
        {
            caisse_restant = 1;

        }

    }
}

if(caisse_restant == 0) {

    bravo = 1;
}






SDL_Flip(ecran);


}


SDL_FreeSurface(ecran);
SDL_FreeSurface(imgMur);
SDL_FreeSurface(imgCaisse);
SDL_FreeSurface(imgObjectif);
SDL_FreeSurface(imgCaisseOk);
SDL_FreeSurface(imgZeldaBAS);
SDL_FreeSurface(imgZeldaHAUT);
SDL_FreeSurface(imgZeldaGAUCHE);
SDL_FreeSurface(imgZeldaDROITE);
SDL_FreeSurface(imgBarre);
SDL_FreeSurface(imgBravo);
SDL_FreeSurface(texteRecommencer);
SDL_FreeSurface(texteRetour);
SDL_FreeSurface(textePerdue);
SDL_FreeSurface(texteNiveau);
SDL_FreeSurface(texteAuteur);
SDL_FreeSurface(texteCompteur);
SDL_FreeSurface(neige);
SDL_FreeSurface(imgPorte_ferme);
SDL_FreeSurface(imgPorte_ouverte);
TTF_CloseFont(policeTexte); /* Doit être avant TTF_Quit() */
TTF_CloseFont(policePerdue);
TTF_CloseFont(policeCompteur);
TTF_Quit();
}


int deplacerJoueur(int carte[Longueur_Bloc][Largeur_Bloc], SDL_Rect *pos, int direction, int bravo)
{
    int caisse = 0;
    int porte_passe = 0;
    switch(direction)
    {
    case HAUT:
        if(pos->y - 34 < 0)
            break;


    if((carte[pos->x / 34][pos->y / 34 -1] == MUR || (carte[pos->x /34][pos->y /34 - 1] == PORTE) && bravo != 1 ) || ((carte[pos->x /34][pos->y / 34 - 1] == CAISSE || carte[pos->x /34][pos->y / 34 - 1] == CAISSE_OK) && carte[pos->x /34][pos->y /34 - 2] != VIDE && carte[pos->x / 34][pos->y / 34 - 2] != OBJECTIF)   )
            break;

      caisse = deplacerBloc(&carte[pos->x / 34][pos->y /34 - 1],&carte[pos->x / 34][pos->y /34 - 2]);

    pos->y = pos->y - 34;
    if(carte[pos->x / 34][pos->y / 34 ] == PORTE ) {porte_passe = 1;}
        break;

    case BAS:
        if (pos->y +34 >= Largeur_Bloc *34)
            break;
        if((carte[pos->x / 34][pos->y / 34 +1] == MUR || (carte[pos->x /34][pos->y /34 +1] == PORTE) && bravo != 1   ) || ((carte[pos->x /34][pos->y / 34 + 1] == CAISSE || carte[pos->x /34][pos->y / 34 + 1] == CAISSE_OK) && carte[pos->x /34][pos->y /34 + 2] != VIDE && carte[pos->x / 34][pos->y / 34 + 2] != OBJECTIF)   )
            break;

        deplacerBloc(&carte[pos->x / 34][pos->y /34 + 1],&carte[pos->x / 34][pos->y /34 + 2]);

        pos->y = pos->y + 34;
        if(carte[pos->x / 34][pos->y / 34] == PORTE ) { porte_passe = 1; }

        break;



    case GAUCHE:
        if(pos->x - 34 < 0)
            break;
        if((carte[pos->x / 34 -1][pos->y / 34] == MUR || (carte[pos->x /34 -1][pos->y /34] == PORTE)&& bravo != 1    ) || ((carte[pos->x /34 - 1][pos->y / 34] == CAISSE || carte[pos->x /34 - 1][pos->y / 34] == CAISSE_OK) && carte[pos->x /34 - 2][pos->y /34] != VIDE && carte[pos->x / 34 - 2][pos->y / 34] != OBJECTIF) )
            break;
       deplacerBloc(&carte[pos->x / 34 - 1][pos->y /34],&carte[pos->x / 34 - 2][pos->y /34]);

        pos->x = pos->x - 34;
        if(carte[pos->x / 34][pos->y / 34] == PORTE ) {porte_passe = 1; }
        break;

    case DROITE:
        if(pos->x + 34 >= Largeur_Bloc * 34)
        break;
        if((carte[pos->x / 34 + 1][pos->y / 34] == MUR || (carte[pos->x /34 +1][pos->y /34] == PORTE) && bravo != 1    ) || ((carte[pos->x /34 + 1][pos->y / 34] == CAISSE || carte[pos->x /34 + 1][pos->y / 34] == CAISSE_OK) && carte[pos->x /34 + 2][pos->y /34] != VIDE && carte[pos->x / 34 + 2][pos->y / 34] != OBJECTIF) )
            break;
       deplacerBloc(&carte[pos->x / 34 + 1][pos->y /34],&carte[pos->x / 34 + 2][pos->y /34]);

        pos->x = pos->x + 34;
        if(carte[pos->x / 34][pos->y / 34] == PORTE) {porte_passe = 1; }
        break;
    }





return porte_passe;



}




void deplacerBloc(int *premierCase, int *secondeCase)
{
    int caisse = 0;
   {
    if (*premierCase == CAISSE || *premierCase == CAISSE_OK)
    {
        if (*secondeCase == OBJECTIF)
        {


            *secondeCase = CAISSE_OK;

        }
        else
        {


            *secondeCase = CAISSE;

        }
        if (*premierCase == CAISSE_OK)
        {


            *premierCase = OBJECTIF;


        }
        else
        {


            *premierCase = VIDE;

        }
    }
}

}

int CompteRebours(int niv)
{
    int compte = 0;
    if(niv == 1) {compte = 5; }
    else if(niv == 2) { compte = 120;}
    else if(niv == 3) { compte = 120;}
    else if(niv == 4) { compte = 120;}
    else if(niv == 5) { compte = 120;}
    else if(niv == 6) { compte = 120;}
    else if(niv == 7) { compte = 120;}
    else if(niv == 8) { compte = 120;}
    else if(niv == 9) { compte = 120;}
    else if(niv == 10) { compte = 120;}
    compte = compte *1000 + 1000;
    return compte;


}
