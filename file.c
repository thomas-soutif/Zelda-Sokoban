#include <stdlib.h>
#include <stdio.h>
#include "constantes.h"

int chargerPartie(int niveau[Largeur_Bloc][Longueur_Bloc], int niv)
{
    char ligneFichier[Longueur_Bloc * Largeur_Bloc + 1] = {0};
    int i = 0, j = 0;
    FILE* fichier = NULL;
    if(niv == -1)
    {
        fichier = fopen("niveauxPerso.lvl","r");
        fgets(ligneFichier, Longueur_Bloc * Largeur_Bloc +2, fichier);
    }
    else
    {


        fichier = fopen("niveaux.lvl","r");





        for(i = 0; i < niv; i++)
        {


            fgets(ligneFichier, Longueur_Bloc * Largeur_Bloc +2, fichier);
        }
    }
    for (i = 0 ; i < Longueur_Bloc ; i++)
    {
        for (j = 0 ; j < Largeur_Bloc ; j++)
        {
            switch (ligneFichier[(i * Longueur_Bloc) + j])
            {
            case '0':
                niveau[j][i] = 0;
                break;
            case '1':
                niveau[j][i] = 1;
                break;
            case '2':
                niveau[j][i] = 2;
                break;
            case '3':
                niveau[j][i] = 3;
                break;
            case '4':
                niveau[j][i] = 4;
                break;
            case '5':
                niveau[j][i] = 5;
                break;
            case '6':
                niveau[j][i] = 6;
                break;
            }
        }
    }



    fclose(fichier);
    return 1;

}

void creerPartie(int carte[Longueur_Bloc][Largeur_Bloc])

{
    FILE* fichier = NULL;





    fichier = fopen("niveauxPerso.lvl","w+");
    int longueur = Longueur_Bloc * Largeur_Bloc;
    int i = 0;
    int j = 0;
    int objetActuel = VIDE;

    for (j = 0 ; j < Largeur_Bloc; j++)
    {
        for (i = 0 ; i < Longueur_Bloc; i++)
        {

            switch(carte[i][j])
            {
            case VIDE:
                objetActuel = 0;
                break;
            case MUR:
                objetActuel = 1;
                break;
            case CAISSE:
                objetActuel = 2;
                break;
            case OBJECTIF:
                objetActuel = 3;
                break;
            case ZELDA:
                objetActuel = 4;
                break;
            case CAISSE_OK:
                objetActuel = 5;
                break;
            case PORTE:
                objetActuel = 6;
                break;
            }

            fprintf(fichier,"%d",objetActuel);



        }



    }

    fclose(fichier);



}

void rename_fichier()
{

    rename("niveauPerso.lvl", "niveauPerso1.lvl");



}
