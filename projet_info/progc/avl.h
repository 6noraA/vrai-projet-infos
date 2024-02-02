// avl.h

#ifndef AVL_H
#define AVL_H

typedef struct NoeudAVL {
    char nom[100];
    int trajet;
    int compteur;
    int compteurt;
    struct NoeudAVL* gauche;
    struct NoeudAVL* droite;
    int hauteur;
} NoeudAVL;

int hauteur(NoeudAVL* noeud);
int max(int a, int b);
NoeudAVL* rotationGauche(NoeudAVL* y);
NoeudAVL* rotationDroite(NoeudAVL* x);
int getEquilibre(NoeudAVL* noeud);
NoeudAVL* insertion(NoeudAVL* racine, char* nom, int x, int y, int z);
void parcoursEnOrdreDecroissant(NoeudAVL* racine);
void libererMemoire(NoeudAVL* racine);

#endif

