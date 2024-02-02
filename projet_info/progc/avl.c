// avl.c

#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hauteur(NoeudAVL* noeud) {
    return (noeud == NULL) ? 0 : noeud->hauteur;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

NoeudAVL* rotationGauche(NoeudAVL* y) {
    if (y == NULL || y->droite == NULL) {
        return y;
    }

    NoeudAVL* x = y->droite;
    NoeudAVL* T2 = x->gauche;

    x->gauche = y;
    y->droite = T2;

    y->hauteur = 1 + max(hauteur(y->gauche), hauteur(y->droite));
    x->hauteur = 1 + max(hauteur(x->gauche), hauteur(x->droite));

    return x;
}

NoeudAVL* rotationDroite(NoeudAVL* x) {
    if (x == NULL || x->gauche == NULL) {
        return x;
    }

    NoeudAVL* y = x->gauche;
    NoeudAVL* T2 = y->droite;

    y->droite = x;
    x->gauche = T2;

    x->hauteur = 1 + max(hauteur(x->gauche), hauteur(x->droite));
    y->hauteur = 1 + max(hauteur(y->gauche), hauteur(y->droite));

    return y;
}

int getEquilibre(NoeudAVL* noeud) {
    return (noeud == NULL) ? 0 : hauteur(noeud->gauche) - hauteur(noeud->droite);
}

NoeudAVL* insertion(NoeudAVL* racine, char* nom, int x, int y, int z) {
    if (racine == NULL) {
        NoeudAVL* nouveau_noeud = malloc(sizeof(NoeudAVL));
        if (nouveau_noeud == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire.\n");
            exit(EXIT_FAILURE);
        }

        strcpy(nouveau_noeud->nom, nom);
        nouveau_noeud->compteur = (y == 1) ? 1 : 0;
        nouveau_noeud->compteurt = 1;
        nouveau_noeud->trajet = x;
        nouveau_noeud->gauche = NULL;
        nouveau_noeud->droite = NULL;
        nouveau_noeud->hauteur = 1;
        return nouveau_noeud;
    }

    int comparaison = strcmp(nom, racine->nom);

    if (x != racine->trajet) {
        if (y == 1) {
            if (comparaison < 0) {
                racine->gauche = insertion(racine->gauche, nom, x, y, z);
            } else if (comparaison > 0) {
                racine->droite = insertion(racine->droite, nom, x, y, z);
            } else if (comparaison == 0) {
                if (z == 1) {
                    racine->compteurt = racine->compteurt + 1;
                    racine->compteur = racine->compteur + 1;
                } else {
                    racine->compteurt = racine->compteurt + 1;
                }
            }
        } else {
            if (comparaison < 0) {
                racine->gauche = insertion(racine->gauche, nom, x, y, z);
            } else if (comparaison > 0) {
                racine->droite = insertion(racine->droite, nom, x, y, z);
            } else if (comparaison == 0) {
                if (z == 2) {
                    racine->compteurt = racine->compteurt + 1;
                }
            }
        }
    }

    racine->hauteur = 1 + max(hauteur(racine->gauche), hauteur(racine->droite));

    int equilibre = getEquilibre(racine);

    // Cas de l'équilibre positif
    if (equilibre > 1) {
        if (comparaison < 0) {
            return rotationDroite(racine);
        } else {
            racine->gauche = rotationGauche(racine->gauche);
            return rotationDroite(racine);
        }
    }

    // Cas de l'équilibre négatif
    if (equilibre < -1) {
        if (comparaison > 0) {
            return rotationGauche(racine);
        } else {
            racine->droite = rotationDroite(racine->droite);
            return rotationGauche(racine);
        }
    }

    return racine;
}



void parcoursEnOrdreDecroissant(NoeudAVL* racine) {
    if (racine != NULL) {
        parcoursEnOrdreDecroissant(racine->droite);
        printf("%s; %d; %d\n", racine->nom, racine->compteur, racine->compteurt);
        parcoursEnOrdreDecroissant(racine->gauche);
    }
}












void libererMemoire(NoeudAVL* racine) {
    if (racine != NULL) {
        libererMemoire(racine->gauche);
        libererMemoire(racine->droite);
        free(racine);
    }
}







