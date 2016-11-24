#include "constantes.h"
int partieJeu(SDL_Surface* ecran, int niveau);
int deplacerJoueur(int carte[][Largeur_Bloc], SDL_Rect *pos, int direction, int bravo);
void deplacerBloc(int *premierCase, int *secondeCase);
int CompteRebours(int niv);
