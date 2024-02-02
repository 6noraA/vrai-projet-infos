// main.c

#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fichier_donnees>\n", argv[0]);
        return 1;
    }

    FILE* fichier = fopen(argv[1], "r");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    NoeudAVL* racine = NULL;

    // Ignorer la première ligne
    fscanf(fichier, "%*[^\n]\n");

    char ligne[500]; // Vous pouvez ajuster cette taille en fonction de vos besoins

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int trajet;
        char nom1[100], nom2[100];
        int etape;
        if (sscanf(ligne, "%d;%d;%99[^;];%99[^;];%*[^;];%*[^;]", &trajet, &etape, nom1, nom2) != 4) {
            fprintf(stderr, "Erreur de lecture de la ligne : %s\n", ligne);
            continue; // Ignorer la ligne incorrecte et passer à la suivante
        }

        if (strlen(nom1) == 0 || strlen(nom2) == 0) {
            fprintf(stderr, "Erreur : Nom1 ou Nom2 non lus correctement dans la ligne : %s\n", ligne);
            continue; // Ignorer la ligne incorrecte et passer à la suivante
        }

        int a = 1;
        racine = insertion(racine, nom1, trajet, etape, a);
        a = 2;
        racine = insertion(racine, nom2, trajet, etape, a);
    }

    parcoursEnOrdreDecroissant(racine);

    fclose(fichier);

    libererMemoire(racine);

    return 0;
}

