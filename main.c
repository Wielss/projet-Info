#include "repertoire.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  // Athlete athletes[MAX_ATHLETES];

  int choix;

  do {
    afficher_menu();
    supprimerFichierDansDossierMuet(
        "donnees", "t.txt"); // suprime le fichier temporaire t.txt qui contient
                             // des traitements
    supprimerFichierDansDossierMuet(
        "donnees", "tp.txt"); // suprime le fichier temporaire tp.txt qui
                              // contient des traitements

    if (scanf("%d", &choix) != 1) {
      while (getchar() != '\n')
        ;
      printf("Entrée invalide. Veuillez entrer un nombre valide.\n");
      continue;
    }

    switch (choix) {
    case 1:
      afficher_liste_athletes();
      break;
    case 2:
      ajouter_athlete();
      break;
    case 3:
      rechercher_athlete();
      break;
    case 4:
      ajouter_entrainement();
      break;
    case 5:
      consulter_entrainements();
      break;
    case 6:
      envoyer_jo();
      break;
    case 7:
      printf("Au revoir!\n");
      break;
    default:
      printf("Choix invalide. Veuillez sélectionner une option valide.\n");
    }
  } while (1);
  // while (choix != 7);

  return 0;
}