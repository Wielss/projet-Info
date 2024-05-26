#include "repertoire.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Athlete athletes[MAX_ATHLETES];

// Fonction pour dupliquer un fichier en changeant son nom trouvée sur internet
void dupliquerFichier(FILE *fichierSource, const char *nomDestination) {
  if (fichierSource == NULL) {
    perror("Erreur: le fichier source est NULL");
    exit(EXIT_FAILURE);
  }
  fseek(fichierSource, 0, SEEK_SET);
  char chemin[50] = "./donnees/";
  strcat(chemin, nomDestination); // on ecrite le chemin complet
  strcat(chemin, ".txt");         // on ecrite le chemin complet
  FILE *fichierDestination = fopen(chemin, "wb");
  if (fichierDestination == NULL) {
    perror("Erreur lors de l'ouverture du fichier destination");
    exit(EXIT_FAILURE);
  }

  char chaine[300];
  while (fgets(chaine, 300, fichierSource) != NULL) {
    fprintf(fichierDestination, "%s", chaine);
  }

  fclose(fichierDestination);
  return;
}

// Fonction pour renvoyer le maximum de deux entiers copié sur internet mais pas
// compris
int max(int a, int b) { return (a > b) ? a : b; }

char *delimiter(const char *chaine, int indice,
                char *champ) { // renvoie la colonne numéro indice
  // dans champ
  char inputCopy[strlen(chaine) + 1]; // sera une copie de l'entrée
  strcpy(inputCopy, chaine);          // copie l'entrée

  char *inter;
  int i = 0;

  // On utilise strtok pour séparer les champs délimités par ";" cette fonction
  // passe de colonne en colonne
  inter = strtok(inputCopy, ";");
  while (inter != NULL) {
    if (i == indice) {
      strncpy(champ, inter, 15 - 1);
      champ[15 - 1] =
          '\0'; // Assurez-vous que le champ est terminé par un caractère nul
      return champ; // retourne le champ correspondant
    }
    inter = strtok(
        NULL, ";"); // mettre null comme argument passe à la colonne suivante
    i++;
  }

  // Si l'indice demandé est hors des limites, retourne NULL
  return NULL;
}

int comptelignefichier(FILE *param) {

  char chaine[300];
  if (param != NULL) {
    int i = -1; // on ne compte pas la première ligne qui est juste une
                // indication du format
    fseek(param, 0, SEEK_SET); // on se place au début du fichier
    while (fgets(chaine, 300, param) != NULL) {
      i++;
    }
    return i;
  } else {
    printf(" erreur fichier invalide appel comptelignefichier");
    exit(3);
  }
}

void viderBuffer() // efface les caractères deja écrit dans le clavier
{
  int c = 0;
  while (c != '\n' && c != EOF) // boucle qui les suprrimes un à un
  {
    c = getchar();
  }
}

int supprimerFichierDansDossier(const char *dossier, const char *nomFichier) {
  // les paramètres const char ne peuvent pas etre modifiés, cette fonction
  // supprime lefichier dans le dossier
  DIR *d;
  struct dirent *entree;
  char cheminFichier[1024]; // le chemin

  // Ouvre le répertoire spécifié
  d = opendir(dossier);
  if (d == NULL) {
    perror("Erreur lors de l'ouverture du répertoire");
    return -1;
  }

  // Parcourir les fichiers du répertoire
  while ((entree = readdir(d)) != NULL) {
    // Comparer le nom du fichier avec celui spécifié
    if (strcmp(entree->d_name, nomFichier) == 0) {
      // Construire le chemin complet du fichier
      snprintf(cheminFichier, sizeof(cheminFichier), "%s/%s", dossier,
               nomFichier);
      // Supprimer le fichier
      if (remove(cheminFichier) == 0) {
        printf("Fichier %s supprimé avec succès.\n", cheminFichier);
        closedir(d);
        return 0; // Renvoie 0 pour indiquer le succès
      } else {
        perror("Erreur lors de la suppression du fichier");
        closedir(d);
        return -1;
      }
    }
  }

  printf("Fichier %s non trouvé dans le répertoire %s.\n", nomFichier, dossier);
  closedir(d);
  return -1; // Ren,voie -1 si le fichier n'est pas trouvé
}

int supprimerFichierDansDossierMuet(const char *dossier,
                                    const char *nomFichier) {
  // comme la fonction ci dessus mais sans printf
  DIR *d;
  struct dirent *entree;
  char cheminFichier[1024]; // le chemin

  // Ouvre le répertoire spécifié
  d = opendir(dossier);
  if (d == NULL) {
    // perror("Erreur lors de l'ouverture du répertoire");
    return -1;
  }

  // Parcourir les fichiers du répertoire
  while ((entree = readdir(d)) != NULL) {
    // Comparer le nom du fichier avec celui spécifié
    if (strcmp(entree->d_name, nomFichier) == 0) {
      // Construire le chemin complet du fichier
      snprintf(cheminFichier, sizeof(cheminFichier), "%s/%s", dossier,
               nomFichier);
      // Supprimer le fichier
      if (remove(cheminFichier) == 0) {
        // printf("Fichier %s supprimé avec succès.\n", cheminFichier);
        closedir(d);
        return 0; // Renvoie 0 pour indiquer le succès
      } else {
        // perror("Erreur lors de la suppression du fichier");
        closedir(d);
        return -1;
      }
    }
  }

  // printf("Fichier %s non trouvé dans le répertoire %s.\n", nomFichier,
  // dossier);
  closedir(d);
  return -1; // Ren,voie -1 si le fichier n'est pas trouvé
}

int charToDigit(char c) { // fonctrion trouvée sur internet
  if (c >= '0' && c <= '9') {
    return c - '0';
  } else {
    return -1; // Retourne -1 pour indiquer que le caractère n'est pas un
               // chiffre valide
  }
}

void traduirelais(int num,
                  char chaine[15]) { // prend un numero entre 1 et 5 et
                                     // renvoie l'épreuve associée.
  switch (num) {
  case 1:
    strcpy(chaine, "100 mètres\0");
    return;
  case 2:
    strcpy(chaine, "400 mètres\0");
    return;
  case 3:
    strcpy(chaine, "5000 mètres\0");
    return;
  case 4:
    strcpy(chaine, "Marathon\0");
    return;
  case 5:
    strcpy(chaine, "Relais\0");
    return;
  default:
    printf("erreur numéro d'épreuve invalide");
    strcpy(chaine, "ERREUR\0");
    return;
  }
}

int lire(char *chaine, int longueur) // fonction copiée sur open classroooms
                                     // scanf amélioré renvoie 0 si erreur
{
  char *positionEntree = NULL;

  if (fgets(chaine, longueur, stdin) != NULL) {
    positionEntree = strchr(chaine, '\n');
    if (positionEntree != NULL) {
      *positionEntree = '\0';
    } else {
      viderBuffer();
    }
    return 1;
  } else {
    viderBuffer();
    return 0;
  }
}

int date_valide(int jour, int mois,
                int annee) { // prend des entiers en params renvoie 1 si bon
  int nombreDeJours;
  switch (mois) {
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:
  case 12:
    nombreDeJours = 31;
    break;
  case 4:
  case 6:
  case 9:
  case 11:
    nombreDeJours = 30;
    break;
  case 2:
    if (((annee % 4 == 0) && (annee % 100 != 0)) || (annee % 400 == 0)) {
      nombreDeJours = 29;
    } else {
      nombreDeJours = 28;
    }
    break;
  default:
    printf("\nNuméro de mois invalide!\nAppuyez sur entrée pour revenir à la "
           "saisie.\n");
    return 0;
  }
  if ((jour < 1) || (jour > nombreDeJours)) {
    printf("\nNuméro de jour invalide!\nAppuyez sur entrée pour revenir à la "
           "saisie.\n");
    return 0;
  }
  return 1;
}

int estbonnedate(char chaine[11]) { // vérifie si la date passé est au bon
                                    // format renvoie 0 si erreur
  int jour = 0;
  int mois = 0;
  int annee = 0;
  char jourc[3] = "11"; // champ texte qui seront convertis en entiers
  char moisc[3] = "11";
  char anneec[5] = "1111";
  for (int i = 0; i < 4; i++) {
    if ((chaine[i] < '0') ||
        (chaine[i] >
         '9')) { // un des quatres premiers cractères n'est pas un chiffre

      printf("Format de la date invalide : \nun des quatres premiers "
             "caractères n'est pas un chiffre!\n");
      return 0;
    }
    anneec[i] = chaine[i];
  }
  if (chaine[4] != '-') { // il manque un tiret
    printf("Format de la date invalide :\nIl manque un trait d'union!\n");
    return 0;
  }
  for (int i = 5; i < 7; i++) {
    if ((chaine[i] < '0') ||
        (chaine[i] >
         '9')) { // un des quatres premiers cractères n'est pas un chiffre
      printf("Format de la date invalide : \nle 6ème ou le 7ème "
             "caractère n'est pas un chiffre!\n");
      return 0;
    }
    moisc[i - 5] = chaine[i];
  }
  if (chaine[7] != '-') { // il manque un tiret
    printf("Format de la date invalide :\nIl manque un trait d'union!\n");
    return 0;
  }
  for (int i = 8; i < 10; i++) {
    if ((chaine[i] < '0') ||
        (chaine[i] >
         '9')) { // un des deux derniers caractères n'est pas un chiffre
      printf("Format de la date invalide : \nun des deux derniers caractères "
             "n'est pas un chiffre!\n");
      return 0;
    }
    jourc[i - 8] = chaine[i];
  }
  // printf("%s %s %s", jourc, moisc, anneec);
  // printf("%d %d %d", atoi(jourc), atoi(moisc), atoi(anneec));
  return date_valide(
      atoi(jourc), atoi(moisc),
      atoi(anneec)); // atoi transforme les chaines de caracteres en entier
}

void Afficherstat(FILE *fichier) {
  if (fichier != NULL) {
    int continu = 1;
    int epreuve = 0;
    while (continu) {
      printf("Quel type d'épreuve?\n(format : 1=100m 2=400m 3=5000m 4=marathon "
             "5=relais4*400m)");
      scanf("%d", &epreuve);
      if ((epreuve < 1) ||
          (epreuve > 5)) { // on vérifie la validité de l'entrée
        printf("\nVous n'avez pas respecté le format\n");
        viderBuffer(); // empeche des erreurs
      } else {
        continu = 0; // on sort de la boucle
      }
    }

    continu = 1;
    char daterecente[11];    // Date la plus récente, utile pour la progression
    char daterecentebis[11]; // 2ème date la plus récente
    float tpsrecent;         // temps associé à la date récente
    float tpsrecentbis;      // temps associé à la 2ème date la plus récente
    float piretps;
    float meilleurtps;
    float moyenne; // on va additionner chaque temps et les diviser par le
                   // compteur à la fin
    char chaine[300];
    fseek(fichier, 0, SEEK_SET); // on se place au début du fichier
    fgets(chaine, 300, fichier); // on enlève la première ligne
    if (fgets(chaine, 300,
              fichier) == NULL) // on prend la 2nde ligne pour initialiser les
                                // stats , on vérifie ausis qu'elle existe
    {
      printf("Cet athlète n'a aucun entrainements !");
      return;
    }
    char nomepreuve[16];
    traduirelais(epreuve, nomepreuve); // pour l'affichage
    int compteur = 1;                  // pour diviser la moyenne après
    char colonne[16];
    char colonned[16]; // colonne pour la date
    if (delimiter(chaine, 2,
                  colonne)) { // si le delimitage du temps se passe bien

      if (delimiter(chaine, 0,
                    colonned)) { // si le delimitage de la date se passe bien
        strcpy(daterecente, colonned); // on initilise la date récente
      } else {
        printf("Erreur dans l'affichage date\n");
        return;
      }
      float tps = 0;
      tps = atof(colonne); // converti le champ en nombre réel
      piretps = tps;       // on initalise les stats
      meilleurtps = tps;
      moyenne = tps;
      tpsrecent = tps;

    } else {
      printf("Erreur dans l'affichage1\n");
      return;
    }

    if (fgets(chaine, 300,
              fichier) ==
        NULL) // on prend la 3eme ligne pour trouver la date récente
              // stats , on vérifie ausis qu'elle existe
    {         // il n'y a qu'un seul entrainement

      printf("\nStatistiques au %s :\n", nomepreuve);
      printf("Meilleur temps : %f\n", meilleurtps);
      printf("Pire temps : %f\n", piretps);
      printf("Moyenne des temps : %f\n", (moyenne / compteur));
      printf("Progression inexistante puisqu'il n'y a qu'un entrainement\n");
      return;
    }
    if (delimiter(chaine, 2,
                  colonne)) { // si le delimitage du temps se passe bien
      float tps;
      tps = atof(colonne); // converti le champ en nombre réel
      if (delimiter(chaine, 0,
                    colonned)) { // si le delimitage de la date se passe bien
        if (strcmp(colonned, daterecente) >
            0) { // on rencontre une date plus grande : la date de la ligne
                 // est la nouvelle date recente
          strcpy(daterecentebis,
                 daterecente); // on initialise date recn,te bis qui prend la
                               // valeur de date recente
          tpsrecentbis = tpsrecent;      // on change le temps associé
          strcpy(daterecente, colonned); // on change la date récente
          tpsrecent = tps;               // on change le temps associé
        } else {
          strcpy(daterecentebis,
                 colonned);   // on initilise la date récente bis
          tpsrecentbis = tps; // on associe le temps
        }
      } else {
        printf("Erreur dans l'affichage date\n");
        return;
      }

      if (tps > piretps) { // un nouveau pire temps est détécté
        piretps = tps;     // on modifie le pire tps
      }
      if (tps < meilleurtps) {
        meilleurtps = tps; // un nouveau meilleur temps
      }
      moyenne += tps;
      compteur += 1;

    } else {
      printf("Erreur dans l'affichage2\n");
      return;
    }

    while (fgets(chaine, 300, fichier) != NULL) { // parcours fichier
      if (delimiter(chaine, 2, colonne)) { // si le delimitage se passe bien
        float tps;
        tps = atof(colonne); // converti le champ en nombre réel

        if (delimiter(chaine, 0,
                      colonned)) { // si le delimitage de la date se passe bien
          if (strcmp(colonned, daterecente) >
              0) { // on rencontre une date plus grande, la date de la ligne
                   // est la nouvelle date recente
            strcpy(daterecentebis,
                   daterecente);           // datrecnte bis  prend la
                                           // valeur de date recente
            tpsrecentbis = tpsrecent;      // on change le temps associé
            strcpy(daterecente, colonned); // on change la date récente
            tpsrecent = tps;               // on change le temps associé
          } else {
            if (strcmp(colonned, daterecentebis) >
                0) { // on rencontre une date plus grande, la date de la ligne
                     // est la nouvelle date recentebis
              strcpy(daterecentebis,
                     colonned);   // on initilise la date récente bis
              tpsrecentbis = tps; // on associe le temps
            }
          }
        } else {
          printf("Erreur dans l'affichage date\n");
          return;
        }

        if (tps > piretps) { // un nouveau pire temps est détécté
          piretps = tps;     // on modifie le pire tps
        }
        if (tps < meilleurtps) {
          meilleurtps = tps; // un nouveau meilleur temps
        }
        moyenne += tps;
        compteur += 1;

      } else {
        printf("Erreur dans le parcours du fichier\n");
        return;
      }
    }

    printf("\nStatistiques au %s :\n", nomepreuve);
    printf("Meilleur temps : %f\n", meilleurtps);
    printf("Pire temps : %f\n", piretps);
    printf("Moyenne des temps : %f\n", (moyenne / compteur));
    printf("Progression depuis la dernière séance : %f\n",
           (tpsrecentbis - tpsrecent));
    return;
  } else {
    printf(" erreur fichier invalide appel afficherstat");
    exit(3);
  }
}

void afficher_menu() {
  printf("\n-------------------------------------\n");
  printf("|             Menu:                 |\n");
  printf("-------------------------------------\n");
  printf("| 1. Afficher la liste des athlètes |\n");
  printf("| 2. Ajouter un nouvel athlète      |\n");
  printf("| 3. Rechercher un athlète          |\n");
  printf("| 4. Ajouter un entraînement        |\n");
  printf("| 5. Consulter les entrainements    |\n");
  printf("| 6. Qui envoyer aux JO             |\n");
  printf("| 7. Quitter                        |\n");
  printf("-------------------------------------\n");
  printf("| Choix:                            |\n");
  printf("-------------------------------------\n");
}

void afficher_filtrat(FILE *fich) { // assez similaire à afficher performances
  if (fich == NULL) {
    printf("\nerreur ouverture filtrat!\n");
    return;
  }
  int nbligne = comptelignefichier(fich);
  printf("%d", nbligne);
  if (nbligne < 2) {
    printf("\n\nAucun résultat avec tous ces filtres!\n");
    return;
  }
  printf("\n\nFiltrat :\n");

  char chaine[300];                  // on va inscrire la ligne dedans
  char colonne[16];                  // pour delimiter chaque champs
  fseek(fich, 0, SEEK_SET);          // on se place au début du fichier
  while (fgets(chaine, 300, fich)) { // parcours du fichier
    if (delimiter(chaine, 0,
                  colonne)) { // si le delimitage du nom se passe bien
      printf("Athlète : %s\n", colonne);   // on affiche le nom
      if (delimiter(chaine, 1, colonne)) { // si le delimitage se passe bien
        printf("Entrainement du %s :\n", colonne);
        if (delimiter(chaine, 2, colonne)) { // si le delimitage se passe bien
          int ent = 0;
          int estrelais = 0;
          ent = charToDigit(colonne[0]); // on traduit le cractère de
                                         // l'épreuve en un chiffre
          if (ent == 5) {
            estrelais = 1;
          }
          traduirelais(ent, colonne); // on utilise ce chiffre qu'on traduit
                                      // en le nom de l'épreuve
          printf("Épreuve : %s\n", colonne);
          if (delimiter(chaine, 3,
                        colonne)) { // si le delimitage se passe bien
            float tps = 0;
            tps = atof(colonne); // converti le champ en nombre réel
            printf("Temps : %f\n", tps);
            if (delimiter(chaine, 4,
                          colonne)) { // si le delimitage se passe bien
              if (estrelais) {        // cas du relais
                int pos = 0;
                pos = charToDigit(colonne[0]); // converti le champ en entier

                printf("Position dans le relais : %d\n", pos);
              }

            } else {

              printf("Erreur dans l'affichage 545\n");
              return;
            }

          } else {
            printf("Erreur dans l'affichage 550\n");
            return;
          }
        } else {
          printf("Erreur dans l'affichage 554\n");
          return;
        }
      } else {
        printf("Erreur dans l'affichage 558\n");
        return;
      }
    } else {
      printf("Erreur dans l'affichage 565\n");
      return;
    }
  }
  return;
}

int compter_tout() {
  int i = 0;
  struct dirent *dir; // on déclare une structure dir grâce à la bibliotheque
                      // dirent.h utile pour naviguer dans les fichiers
  DIR *d = opendir("./donnees");         // on ouvre le répertoire donnees
  if (d) {                               // ouvre le dossier s'il existe
    while ((dir = readdir(d)) != NULL) { // on parcours les fichiers

      if (dir->d_name[0] == '.' &&
          (dir->d_name[1] == '\0' ||
           (dir->d_name[1] == '.' && dir->d_name[2] == '\0'))) {
        continue;
      } // Ignore les entrées "." et ".." pour que le compte sois bon
      i++;
    }
    closedir(d); // on ferme
  }

  return i;
}

int tout_entrainement() {
  char tmps[256];
  FILE *tout_entrainement = fopen("tout_entrainement.txt", "r");
  if (tout_entrainement == NULL) {
    printf("Erreur lors de l'ouverture de tout_entrainement.txt\n");
    return 0;
  }
  int comptee = 0;

  while (fscanf(tout_entrainement, "%s\n", tmps) == 1) {
    printf("|%s| \n", tmps);
    comptee++;
  }
  fclose(tout_entrainement);
  return comptee;
}

// Fonction pour vider le contenu du ficxhier t.txt
FILE *viderFichierTemp(FILE *temp) {
  fclose(temp);
  FILE *fichier = fopen("./donnees/t.txt", "wb+"); //écrase le fichier t.txt
  if (fichier == NULL) {
    perror("Erreur lors de l'ouverture du fichier t.txt");
    return NULL;
  }
  return fichier;
}

void refiltrer(FILE *fichtemp) {    // permet de filtrer d'avantage
  dupliquerFichier(fichtemp, "tp"); // duplique fichtemp sous le nom "tp"
  FILE *tp = fopen("./donnees/tp.txt",
                   "r+"); // r+ ouverture + ecriture place le curseur au début
  // le fichiertp est celui dans qu'on parcourera on va vider fichtemp pour le
  // reremplir avec le sresultats du traitement
  char chaine[300];
  char colonne[50];                      // pour le délimitage
  fichtemp = viderFichierTemp(fichtemp); // vide t.txt
  fseek(fichtemp, 0, SEEK_SET);          // on se met au debut du fichier t
  fseek(tp, 0, SEEK_SET); // on se met au debut du fichier tp ligne un peu
                          // inutile car on ouvre en r+
  int choix = 0;
  while (1) {
    printf("\n\nSelon quel champ filtrer?");
    printf("\n1 : filtrer selon une épreuve\n");
    printf("2 : filtrer selon une date\n");
    printf("3 : filtrer selon un nom\n");
    printf("4 : Quitter\n");
    if (scanf("%d", &choix) != 1) {
      while (getchar() != '\n')
        ;
      printf("Entrée invalide. Veuillez entrer un nombre valide.\n");
      continue;
    }

    if (choix == 1) { // cas epreuve
      viderBuffer();
      int epreuve = 0;   // numero de l'épreuve
      char chaineep[11]; // chaine ou on stockera le caractyère de l'épreuve

      viderBuffer();
      int continu = 1;
      while (continu) {
        printf(
            "Quel type d'épreuve?\n(format : 1=100m 2=400m 3=5000m 4=marathon "
            "5=relais4*400m)");
        scanf("%d", &epreuve);
        if ((epreuve < 1) ||
            (epreuve > 5)) { // on vérifie la validité de l'entrée
          printf("\nVous n'avez pas respecté le format\n");
          viderBuffer(); // empeche des erreurs
        } else {
          continu = 0; // on sort de la boucle
        }
      }
      while (fgets(chaine, 300, tp) != NULL) { // on parcours tp.txt
        if (delimiter(chaine, 2, colonne)) {   // si delimitage se passe bien
          int numep = 0;
          numep = charToDigit(colonne[0]); // on convertit l'épreuve en chiffre
          if (numep == epreuve) { // les epreuves correspondent donc on filtre
            fprintf(fichtemp, "%s",
                    chaine); // on modifie t.txt avec les reusltat du filtre
          }

        } else {
          printf("Erreur delimitage refiltrer epreuve");
          return;
        }
      }
      afficher_filtrat(fichtemp);
      refiltrer(fichtemp);
      return;

    } else if (choix == 2) { // cas date
      viderBuffer();
      int continu = 1;
      char date[11];
      while (continu) {
        date[0] = '\0'; // vide la chaine
        printf("Quelle est la date de la performance?\n(format :YYYY-MM-DD)");
        // scanf("% s", p.date);
        if ((!(lire(date, 11))) ||
            (!(estbonnedate(date)))) { // si la lecture se passe mal :

          viderBuffer(); // empeche des erreurs
        } else {
          continu = 0; // on sort de la boucle
        }
      }
      while (fgets(chaine, 300, tp) != NULL) { // on parcours tp.txt
        if (delimiter(chaine, 1,
                      colonne)) { // si delimitage de la date se passe bien

          if (strcmp(date, colonne) ==
              0) { // les dates correspondent donc on filtre
            fprintf(fichtemp, "%s",
                    chaine); // on modifie t.txt avec les reusltat du filtre
          }

        } else {
          printf("Erreur delimitage refiltrer epreuve");
          return;
        }
      }
      afficher_filtrat(fichtemp);

      refiltrer(fichtemp);
      return;
    } else if (choix == 3) { // cas nom
      viderBuffer();
      char nom[60];
      while (1) {
        nom[0] = '\0'; // vide la chaine
        printf("Entrez le nom de l'athlète à ajouter (minimum 3 caractères)\n");

        lire(nom, 50);
        if (strlen(nom) < 3) {
          printf("\n ERREUR il faut plus de 2 caractères\n");
          continue;
        }
        break;
      }
      while (fgets(chaine, 300, tp) != NULL) { // on parcours tp.txt
        if (delimiter(chaine, 0,
                      colonne)) { // si delimitage de la date se passe bien

          if (strcmp(nom, colonne) ==
              0) { // les noms correspondent donc on filtre
            fprintf(fichtemp, "%s",
                    chaine); // on modifie t.txt avec les reusltat du filtre
          }

        } else {
          printf("Erreur delimitage refiltrer epreuve");
          return;
        }
      }
      afficher_filtrat(fichtemp);

      refiltrer(fichtemp);
      return;
    } else if (choix == 4) { // cas quitter
      viderBuffer();
      return;
    } else {
      printf("Entrée invalide. Veuillez entrer un nombre valide.\n");
      continue;
    }
  }
  return;
}

void afficher_performances_athlete(
    FILE *fichierparam,
    char nomsanstxt[60]) { // similaire à compteligne fichier

  char chaine[300]; // on va inscrire la ligne dedans
  char colonne[16];
  if (fichierparam != NULL) {
    FILE *fichbis =
        fopen("./donnees/t.txt",
              "wb+"); // on cree le fichier temporaire "t.txt" à filtrer
                      // //wb+ écrase les fichiers existants il sera utile pour
                      // des traitements suppls

    fseek(fichierparam, 0, SEEK_SET); // on se place au début du fichier
    fgets(chaine, 300, fichierparam); // on extrait la première ligne
    while (fgets(chaine, 300, fichierparam) != NULL) {
      fprintf(fichbis, "%s;%s", nomsanstxt,
              chaine); // on met le traitement dans le fichier temporaire
                       // en rajoutant le nom en tant que colonn n°0, cela
                       // décalera les autres colonnes

      if (delimiter(chaine, 0, colonne)) { // si le delimitage se passe bien
        printf("\n\nEntrainement du %s :\n", colonne);
        if (delimiter(chaine, 1, colonne)) { // si le delimitage se passe bien
          int ent = 0;
          int estrelais = 0;
          ent = charToDigit(colonne[0]); // on traduit le cractère de
                                         // l'épreuve en un chiffre
          if (ent == 5) {
            estrelais = 1;
          }
          traduirelais(ent, colonne); // on utilise ce chiffre qu'on traduit
                                      // en le nom de l'épreuve
          printf("Épreuve : %s\n", colonne);
          if (delimiter(chaine, 2,
                        colonne)) { // si le delimitage se passe bien
            float tps = 0;
            tps = atof(colonne); // converti le champ en nombre réel
            printf("Temps : %f\n", tps);
            if (delimiter(chaine, 3,
                          colonne)) { // si le delimitage se passe bien
              if (estrelais) {        // cas du relais
                int pos = 0;
                pos = charToDigit(colonne[0]); // converti le champ en entier

                printf("Position dans le relais : %d\n", pos);
              }

            } else {

              printf("Erreur dans l'affichage 537\n");
              return;
            }

          } else {
            printf("Erreur dans l'affichage 542\n");
            return;
          }
        } else {
          printf("Erreur dans l'affichage 546\n");
          return;
        }
      } else {
        printf("Erreur dans l'affichage 550\n");
        return;
      }
    }
    int choix = 0;
    while (1) {
      printf("\n\nVoulez vous affiner d'avantage la recherche avec d'autres "
             "filtres ?");
      printf("\nTapez 1 pour refiltrer\n");
      printf("Tapez 2 pour quitter\n");
      if (scanf("%d", &choix) != 1) {
        while (getchar() != '\n')
          ;
        printf("Entrée invalide. Veuillez entrer un nombre valide.\n");
        continue;
      }

      if (choix == 1) { // cas refiltrage
        viderBuffer();

        refiltrer(fichbis);
        return;

      } else if (choix == 2) { // cas quitter
        viderBuffer();
        return;
      } else {
        printf("Entrée invalide. Veuillez entrer un nombre valide.\n");
        continue;
      }
    }
    return; // on fini le parcours du fichier on revient
  } else {
    printf(" erreur fichier invalide appel afficherperformances");
    exit(3);
  }
}

void saisir_et_sauvegarder_entrainement(FILE *fichierparam) {

  Entrainement p;

  int continu = 1;
  while (continu) {
    printf("Quelle est la date de la performance?\n(format :YYYY-MM-DD)");
    // scanf("% s", p.date);
    if ((!(lire(p.date, 11))) ||
        (!(estbonnedate(p.date)))) { // si la lecture se passe mal :

      viderBuffer(); // empeche des erreurs
    } else {
      continu = 0; // on sort de la boucle
    }
  }
  continu = 1;
  while (continu) {
    printf("Quel type d'épreuve?\n(format : 1=100m 2=400m 3=5000m 4=marathon "
           "5=relais4*400m)");
    scanf("%d", &p.epreuve);
    if ((p.epreuve < 1) ||
        (p.epreuve > 5)) { // on vérifie la validité de l'entrée
      printf("\nVous n'avez pas respecté le format\n");
      viderBuffer(); // empeche des erreurs
    } else {
      continu = 0; // on sort de la boucle
    }
  }

  continu = 1;

  p.temps = -1.0;
  while (continu) {
    printf("Temps de l'épreuve en secondes?");
    scanf("%f", &p.temps);

    if (p.temps < 0) { // on vérifie la validité de l'entrée
      printf("\nVous n'avez pas respecté le format\n");
      viderBuffer(); // empeche des erreurs
    } else {
      continu = 0; // on sort de la boucle
    }
  }
  continu = 1;

  int vrairep = 1; // postion dans le relai

  if (p.epreuve == 5) { // cas du relais : on previent l'utilisateur

    while (continu) {

      printf("L'athlète occupera la position 1 du relais.\nAppuyez sur 1 pour "
             "valider.\nAppuyez sur 2 pour recommencer la saisie (il faut "
             "commencer par le premier athlète du relais)\n");
      int repe = 0;

      scanf("%d", &repe);
      if ((repe < 3) && (repe > 0)) { // format valide
        if (repe == 1) {
          continu = 0;
        } else {
          return;
        }
      } else {
        printf("Format invalide\n");
        viderBuffer();
      }
    }
  }
  continu = 1;

  if ((comptelignefichier(fichierparam) - 1 < MAX_ENTRAINEMENTS) &&
      ((p.epreuve != 5) ||
       (comptelignefichier(fichierparam) - 4 <
        MAX_ENTRAINEMENTS))) {        // il n'y a pas trop d'entrainements
    fseek(fichierparam, 0, SEEK_END); // on se place à la fin du fichier
    fprintf(fichierparam, "%s;%d;%.2f;%d\n", p.date, p.epreuve, p.temps,
            vrairep);
    printf("Entrainement ajouté.\n");
    if (p.epreuve == 5) { // cas du relais : on s'occupe des autres particpants
      int i = 2;
      int resu = 0;
      while (i < 5) { // indice du numéro des athlètes

        resu = ajouter_relais(i, p.date);
        if (resu == 0) { // cas erreur
          printf("\nErreur lors de l'ajout au relais du %s\n", p.date);
          exit(283);

        } else if (resu == 1) { // bon cas
          i += 1;

        } else if (resu == -1) { // choisir un autre athlète on ne fait rien
        }
      }
      printf("Entrainements ajoutés.\n");
    }
    viderBuffer();
  } else {
    printf("Erreur: Nombre maximum d'entraînements atteint.\n");
    return;
  }

  /* FILE *f = fopen(a->nomfichier, "a");
   if (f == NULL) {
     printf("Erreur lors de l'ouverture du fichier de l'athlète\n");
     exit(1);
   }
   fprintf(f, "%s %s %.2f\n", p.date, p.epreuve, p.temps);
   fclose(f);
  */
}

int rechercher_athlete() { // plus ou moins une copie du début de ajouter
                           // entrainement
  char nom[55];
  printf("Entrez le nom de l'athlète à rechercher: ");
  viderBuffer();
  fgets(nom, 50, stdin); // comme unscanf on lit les 50 premiers caracère
                         // stdin (le nom du clavier en c)
  for (int i = 0; i < 50;
       i++) { // cette boucle enlève le \n stocké dans nom après la saisie
    if (nom[i] == '\n') {
      nom[i] = '\0';
    }
  }
  char nomsanstxt[60] = "";
  strcpy(nomsanstxt, nom); // on copie le nom sans l'extension.txt
  strcat(nom, ".txt");     // on rajoute .txt pour trouver le fichier

  struct dirent *dir; // on déclare une structure dir grâce à la bibliotheque
                      // dirent.h utile pour naviguer dans les fichiers
  DIR *d = opendir("./donnees"); // on ouvre le répertoire donnees
  if (d) {                       // ouvre le dossier s'il existe

    while ((dir = readdir(d)) != NULL) { // on parcours les fichiers

      if (strcmp(dir->d_name, nom) == 0) { // si l'athlète existe
        int choix = 0;
        printf("| 1. Afficher ses performances      |\n");
        printf("| 2. Saisir Entraînement            |\n");
        printf("| 3. Consulter ses statistiques     |\n");
        printf("| 4. Supprimer cette athlète        |\n");

        if (scanf("%d", &choix) != 1) {
          while (getchar() != '\n')
            ;
          printf("Entrée invalide. Veuillez entrer un nombre valide.\n");
          continue;
        }
        char nfich[70] = "./donnees/";
        strcat(nfich, nom); // on ecrit le chemin du fichier

        FILE *fich = fopen(nfich, "r+"); // on ouvre le fichier de l'athlète
        if (fich) {
          switch (choix) {

          case 1:
            viderBuffer(); //évite une erreur
            afficher_performances_athlete(fich, nomsanstxt);
            fclose(fich);

            return 1;

            break;
          case 2:

            viderBuffer(); //évite une erreur
            saisir_et_sauvegarder_entrainement(fich);
            fclose(fich);
            return 1;
            break;
          case 3:

            viderBuffer(); //évite une erreur
            printf("Statistiques de %s\n", nom);
            Afficherstat(fich);
            fclose(fich);
            return 1;
            break;
          case 4:
            viderBuffer(); //évite une erreur
            supprimerFichierDansDossier("donnees", nom);
            fclose(fich);
            return 1;
            break;
          default:
            printf(
                "Choix invalide. Veuillez sélectionner une option valide.\n");
          }
        } else {
          printf("erreur dans l'ouverture du fichier %s", nom);
          exit(2);
        }
      }
    }
    printf("Athlète non trouvé.\n");
    return 0;
  }

  printf("Erreur lors de l'ouverture du dossier donnees\nAppuyez sur entrée "
         "pour revenir au menu.\n");
  viderBuffer(); // au cas ou l'utilisateur écrit plus de 50 caractères
  return 0;
}

void afficher_liste_athletes() {
  struct dirent *dir; // on déclare une structure dir grâce à la bibliotheque
                      // dirent.h utile pour naviguer dans les fichiers
  DIR *d = opendir("./donnees");         // on ouvre le répertoire donnees
  if (d) {                               // ouvre le dossier s'il existe
    while ((dir = readdir(d)) != NULL) { // on parcours les fichiers

      if (dir->d_name[0] == '.' &&
          (dir->d_name[1] == '\0' ||
           (dir->d_name[1] == '.' && dir->d_name[2] == '\0'))) {
        continue;
      } // Ignore les entrées "." et ".." pour un affichage plus lisible
      printf("%s\n", dir->d_name); // on affiche les noms des fichiers
    }
    closedir(d); // on ferme
  }

  return;
}

void ajouter_athlete() {

  if (compter_tout() >= MAX_ATHLETES) {
    printf("Erreur: Nombre maximum d'athlètes atteint.\n");
    return;
  }
  char nom[55];
  char nomsanstxt[55]; // le nom sans .txt
  viderBuffer();
  while (1) {
    nom[0] = '\0'; // vide la chaine
    printf("Entrez le nom de l'athlète à ajouter (minimum 3 caractères)\n");

    lire(nom, 50);
    if (strlen(nom) < 3) {
      printf("\n ERREUR il faut plus de 2 caractères\n");
      continue;
    }
    break;
  }
  /*viderBuffer();
  fgets(nom, 50, stdin); // comme unscanf on lit les 50 premiers caracère
                         // stdin (le nom du clavier en c)
  for (int i = 0; i < 50;
       i++) { // cette boucle enlève le \n stocké dans nom après la saisie
    if (nom[i] == '\n') {
      nom[i] = '\0';
    }
  }*/
  strcpy(nomsanstxt, nom); // on met le nom dans nomsanstxt
  strcat(nom, ".txt");     // on rajoute .txt pour trouver le fichier
  char nfich[70] = "./donnees/";
  struct dirent *dir; // on déclare une structure dir grâce à la bibliotheque
                      // dirent.h utile pour naviguer dans les fichiers
  DIR *d = opendir("./donnees");           // on ouvre le répertoire donnees
  if (d) {                                 // ouvre le dossier s'il existe
    while ((dir = readdir(d)) != NULL) {   // on parcours les fichiers
      if (strcmp(dir->d_name, nom) == 0) { // si l'athlète existe
        printf("%s existe déjà!\n", nomsanstxt);
        closedir(d); // on ferme le dossier donnees
        return;
      }
    }
    viderBuffer();
    FILE *ficha = NULL;
    int choix;
    // on crée l'athlète

    strcat(nfich, nom); // on ecrit le chemin du fichier
    ficha = fopen(nfich,
                  "w+"); // W+ créee les fichiers inexistants et
                         // écrase les existants
    fprintf(ficha,
            "Date format YYYY-MM-JJ;type epreuve 1=100m 2=400m "
            "3=5000m 4=marathon 5=relais4*400;performance temps en "
            "secondes;position au relais (=0si pas un relais)\n"); // phrase
                                                                   // pour
                                                                   // comprendre
                                                                   // les
                                                                   // donnees
    fclose(ficha);
    printf("%s ajouté!", nomsanstxt);
    closedir(d); // on ferme le dossier donnees
    viderBuffer();
    return;
  } else {
    printf("Erreur lors de l'ouverture du dossier donnees\nAppuyez sur "
           "entrée pour revenir au menu.\n");

    viderBuffer(); // au cas ou l'utilisateur écrit plus de 50 caractères
    return;
  }
}

void ajouter_entrainement() {
  char nom[55];
  printf("Entrez le nom de l'athlète pour ajouter un entraînement: ");
  viderBuffer();
  fgets(nom, 50, stdin); // comme unscanf on lit les 50 premiers caracère
                         // stdin (le nom du clavier en c)
  for (int i = 0; i < 50;
       i++) { // cette boucle enlève le \n stocké dans nom après la saisie
    if (nom[i] == '\n') {
      nom[i] = '\0';
    }
  }

  strcat(nom, ".txt"); // on rajoute .txt pour trouver le fichier

  struct dirent *dir; // on déclare une structure dir grâce à la bibliotheque
                      // dirent.h utile pour naviguer dans les fichiers
  DIR *d = opendir("./donnees");           // on ouvre le répertoire donnees
  if (d) {                                 // ouvre le dossier s'il existe
    while ((dir = readdir(d)) != NULL) {   // on parcours les fichiers
      if (strcmp(dir->d_name, nom) == 0) { // si l'athlète existe
        char nfich[70] = "./donnees/";
        strcat(nfich, nom);              // on ecrit le chemin du fichier
        FILE *fich = fopen(nfich, "r+"); // on ouvre le fichier de l'athlète
        if (fich) { // si l'ouverture du fichier s'est bien passée
          saisir_et_sauvegarder_entrainement(fich);
          fclose(fich);

        } else {
          printf("erreur dans l'ouverture du fichier %s", nom);
          exit(2);
        }
        closedir(d); // on ferme le dossier donnees
        return;
      }
    }
    closedir(d); // on ferme le dossier donnees
    printf("Athlète non trouvé.\nAppuyez sur entrée pour revenir au "
           "menu.\n");
    viderBuffer(); // au cas ou l'utilisateur écrit plus de 50 caractères
    return;
  }
  printf("Erreur lors de l'ouverture du dossier donnees\nAppuyez sur entrée "
         "pour revenir au menu.\n");
  viderBuffer(); // au cas ou l'utilisateur écrit plus de 50 caractères
  closedir(d);   // on ferme le dossier donnees
  return;
}

int ajouter_relais(int numero, char date[11]) {
  char nom[55];
  char nomsanstxt[55]; // le nom sans .txt
  viderBuffer();
  while (1) {
    nom[0] = '\0'; // vide la chaine
    printf("Entrez le nom de l'athlète à ajouter (minimum 3 caractères)\n");

    lire(nom, 50);
    if (strlen(nom) < 3) {
      printf("\n ERREUR il faut plus de 2 caractères\n");
      continue;
    }
    break;
  }
  strcpy(nomsanstxt, nom); // on met le nom dans nomsanstxt
  strcat(nom, ".txt");     // on rajoute .txt pour trouver le fichier
  char nfich[70] = "./donnees/";
  struct dirent *dir; // on déclare une structure dir grâce à la bibliotheque
                      // dirent.h utile pour naviguer dans les fichiers
  DIR *d = opendir("./donnees");           // on ouvre le répertoire donnees
  if (d) {                                 // ouvre le dossier s'il existe
    while ((dir = readdir(d)) != NULL) {   // on parcours les fichiers
      if (strcmp(dir->d_name, nom) == 0) { // si l'athlète existe
        char nfich[70] = "./donnees/";
        strcat(nfich, nom);              // on ecrit le chemin du fichier
        FILE *fich = fopen(nfich, "r+"); // on ouvre le fichier de l'athlète
        if (fich) { // si l'ouverture du fichier s'est bien passée
          float temps = -1.0;
          int continuer = 1;
          while (continuer) {
            printf("Temps de l'épreuve en secondes?");
            scanf("%f", &temps);

            if (temps < 0) { // on vérifie la validité de l'entrée
              printf("\nVous n'avez pas respecté le format\n");
              viderBuffer(); // empeche des erreurs
            } else {
              continuer = 0; // on sort de la boucle
            }
          }
          fseek(fich, 0, SEEK_END);
          fprintf(fich, "%s;5;%.2f;%d\n", date, temps, numero);
          fclose(fich);
          closedir(d); // on ferme le dossier donnees
          return 1;
        } else {
          printf("erreur dans l'ouverture du fichier %s", nom);
          exit(2);
        }
        closedir(d); // on ferme le dossier donnees
        return 0;
      }
    }
    viderBuffer();
    int choix;
    int continu = 1; // pour la boucle
    while (continu) {
      printf("Athlète non trouvé.\nAppuyez sur 1 le créer.\nAppuyez sur 2 "
             "pour "
             "séléctionner un autre athlète\n");

      if (scanf("%d", &choix) != 1) { // erreur de lecture
        while (getchar() != '\n')     // vide la chaine
          ;
        printf("Entrée invalide. Veuillez entrer un nombre valide.\n");

        continue;
      }

      FILE *ficha = NULL;

      switch (choix) {
      case 1: // on crée l'athlète
        if (compter_tout() >= MAX_ATHLETES) {
          printf("Erreur: Nombre maximum d'athlètes atteint.\n");
          return 0;
        }

        strcat(nfich, nom); // on ecrit le chemin du fichier
        ficha = fopen(nfich,
                      "w+"); // W+ créee les fichiers inexistants et
                             // écrase les existants
        fprintf(ficha, "Date format YYYY-MM-JJ;type epreuve 1=100m 2=400m "
                       "3=5000m 4=marathon 5=relais4*400;performance temps en "
                       "secondes;position au relais (=0si pas un relais)\n");

        int continuer = 1;

        float temps = -1.0;
        while (continuer) {
          printf("Temps de l'épreuve en secondes?");
          scanf("%f", &temps);

          if (temps < 0) { // on vérifie la validité de l'entrée
            printf("\nVous n'avez pas respecté le format\n");
            viderBuffer(); // empeche des erreurs
          } else {
            continuer = 0; // on sort de la boucle
          }
        }

        fprintf(ficha, "%s;5;%.2f;%d\n", date, temps, numero);
        fclose(ficha);
        closedir(d); // on ferme le dossier donnees
        return 1;
        break;
      case 2:
        continu = 0;
        closedir(d); // on ferme le dossier donnees
        return -1;
        break;

      default:
        printf("Choix invalide. Veuillez sélectionner une option valide.\n");

        break;
      }
    }
    closedir(d); // on ferme le dossier donnees
  } else {
    printf("Erreur lors de l'ouverture du dossier donnees\nAppuyez sur "
           "entrée pour revenir au menu.\n");

    viderBuffer(); // au cas ou l'utilisateur écrit plus de 50 caractères
    return 0;
  }
}

// Fonction pour tronquer .txt à la fin d'une chaîne de caractères et stocker
// le résultat dans une autre chaîne
void tronquerTxt(const char *chaine, char *chaineModifiee) {
  size_t longueur = strlen(chaine);
  const char *extension = ".txt";
  size_t longueurExtension = strlen(extension);

  // Copier la chaîne d'origine dans la chaîne de sortie
  strcpy(chaineModifiee, chaine);

  // Vérifier si la chaîne se termine par ".txt"
  if (longueur >= longueurExtension &&
      strcmp(chaine + longueur - longueurExtension, extension) == 0) {
    // Tronquer l'extension en ajoutant un caractère de fin de chaîne ('\0')
    // plus tôt
    chaineModifiee[longueur - longueurExtension] = '\0';
  }
}

void trierathletejo(athletejo tab[3]) {
  int i, j, minIndex;
  athletejo temp;

  for (i = 0; i < 2; i++) {
    minIndex = i;
    for (j = i + 1; j < 3; j++) {
      if (tab[j].tpsmoyen < tab[minIndex].tpsmoyen) {
        minIndex = j;
      }
    }
    if (minIndex != i) {
      // Échanger les éléments
      temp = tab[i];
      tab[i] = tab[minIndex];
      tab[minIndex] = temp;
    }
  }
}

float temps_moyen(FILE *fichier, int epreuve) {
  if (fichier == NULL) {
    printf("erreur temps moyen ouverture fichier");
    exit(5);
  }
  char chaine[300];
  float somme = 0;
  int compteur = 0;
  fseek(fichier, 0, SEEK_SET); // on se met au debut du fichier
  fgets(chaine, 300, fichier); // on enlève la 1ère ligne
  int epligne = 0;             // epreuve de la ligne
  char colonne[16];
  while (fgets(chaine, 300, fichier) != NULL) { // parcours fichier
    if (delimiter(chaine, 1, colonne)) { // on sors l'épreuve avec succès
      epligne = charToDigit(colonne[0]); // transforme lepreuve en un chiffre
      if (epligne == epreuve) {          // l'épreuve nous intéresse
        char colonnebis[16];
        if (delimiter(chaine, 2, colonne)) { // on sors le temps avec succès
          float tps = 0;
          tps = atof(colonne); // converti le champ en nombre réel
          somme += tps;
          compteur++;
        } else {
          printf("erreur temps moyen delimitationdu temps");
          exit(7);
        }
      }
    }

    else {
      printf("erreur temps moyen delimitation epreuve");
      exit(6);
    }
  }

  if (compteur == 0) {
    compteur = 1; // evite une erreur maths si le fichier est vide
  }
  return (somme / compteur);
}

void envoyer_jo() {
  int comptour = 0; // compte les tours de la boucle

  athletejo tab[3] = {
      {"Element1", 0.0},
      {"Element2", 0.0},
      {"Element3",
       0.0}}; // tableau de 3 athlètesjo une structure avec tempsmoyen et nom
  int continu = 1;
  int epreuve = 0;
  while (continu) {
    printf("Quel type d'épreuve?\n(format : 1=100m 2=400m 3=5000m 4=marathon "
           "5=relais4*400m)");
    scanf("%d", &epreuve);
    if ((epreuve < 1) || (epreuve > 5)) { // on vérifie la validité de l'entrée
      printf("\nVous n'avez pas respecté le format\n");
      viderBuffer(); // empeche des erreurs
    } else {
      continu = 0; // on sort de la boucle
    }
  }
  struct dirent *dir; // on déclare une structure dir grâce à la bibliotheque
                      // dirent.h utile pour naviguer dans les fichiers
  DIR *d = opendir("./donnees"); // on ouvre le répertoire donnees

  if (d) {                               // ouvre le dossier s'il existe
    while ((dir = readdir(d)) != NULL) { // on parcours les fichiers
      char chemin[70] = "./donnees/\0";
      char nomsanstxt[56];
      tronquerTxt(
          dir->d_name,
          nomsanstxt); // ecri le nom du fichier qu'on examine sans le .txt
      if (dir->d_name[0] == '.' &&
          (dir->d_name[1] == '\0' ||
           (dir->d_name[1] == '.' && dir->d_name[2] == '\0'))) {
        continue;
      }                            // Ignore les entrées "." et ".."
      strcat(chemin, dir->d_name); // on rajoute .txt pour trouver le fichier
      FILE *fich = NULL;
      // printf("%s", chemin);
      fich = fopen(chemin, "r");
      comptour += 1;
      float tempscur = temps_moyen(fich, epreuve);
      // printf("%d %f\n", comptour, tempscur);
      if (tempscur ==
          0) { // cas où l'athlète ne s'est jamais entrainé sur cette érpeuve
        comptour -= 1; // on incrémente pas pour éviter un bug où quelqu'un qui
                       // n'avait pas couru était traité parmi les 3 premiers
        // printf("comptour %d\n",comptour);
        continue;
      }
      if (comptour < 4) { // lors des 3 premières éxécutions on remplit le
                          // tableau petit à petit
        athletejo meloud;
        strcpy(meloud.nom, nomsanstxt); // on met le nom de l'athlete
        meloud.tpsmoyen = tempscur;
        tab[comptour - 1] =
            meloud; //-1 car comptour vaut 1 lors du premier sparcours
      } else if (comptour == 4) { // cas particulier de l'excution n°4 on va
                                  // trier le tableau

        trierathletejo(tab); // trie les athletes selon le temps
        for (int i = 0; i < 3; i++) {
          // printf("%s %f\n", tab[i].nom, tab[i].tpsmoyen);
        }
      } else { // cas suivant : on va regarder si l'athlète a sa place sur le
               // podium
        for (int i = 0; i < 3; i++) {
          if (tab[2 - i].tpsmoyen >
              tempscur) { // on met 2-i pour aller dans l'ordre decroissant
                          // car un meilleur temps est un  temps inférieur
            // cas ou l'athlete actuel est meilleur donc on remplace l'ancien
            // par le nouveau
            athletejo meloud;
            strcpy(meloud.nom, nomsanstxt); // on met le nom de l'athlete
            meloud.tpsmoyen = tempscur;     // on change le temps
            if (tab[max((1 - i), 0)].tpsmoyen >
                tempscur) { // on regarde si éventuellement le temps merite
                            // une place supérieure et on met max dans la
                            // comparaison pour éviter une segfault
              if (tab[0].tpsmoyen >
                  tempscur) { // on regarde si éventuellement le temps merite
                              // la place ultime
                tab[0] = meloud;
                break; // pour éviter que le tableau sois rempli que de la
                       // même personne
              }
              tab[max((1 - i), 0)] = meloud;
              break; // pour éviter que le tableau sois rempli que de la même
                     // personne
            }
            tab[2 - i] = meloud;
            break; // pour éviter que le tableau sois rempli que de la même
                   // personne
          }
        }
      }
      fclose(fich);
    }
    closedir(d); // on ferme
    char nep[16];
    traduirelais(epreuve, nep);
    printf("\n\nSont convoqués aux Jeux Olympiques pour l'épreuve du %s :\n",
           nep);
    if (tab[0].tpsmoyen > 0) { // ces conditions masquent les fantômes
      printf("-%s avec un temps moyen de %f\n", tab[0].nom, tab[0].tpsmoyen);
    }
    if (tab[1].tpsmoyen > 0) {
      printf("-%s avec un temps moyen de %f\n", tab[1].nom, tab[1].tpsmoyen);
    }
    if (tab[2].tpsmoyen > 0) {
      printf("-%s avec un temps moyen de %f\n", tab[2].nom, tab[2].tpsmoyen);
    }
  } else {
    printf("erreur le dossier donnees n'existe pas");
    return;
  }
}

void afficher_entrainement_date() {
  viderBuffer();
  int continu = 1;
  int epreuve = 0;
  char date[20];
  while (continu) {
    date[0] = '\0';
    printf("Quelle est la date de la performance?\n(format :YYYY-MM-DD)");
    if ((!(lire(date, 11))) ||
        (!(estbonnedate(date)))) { // si la lecture se passe mal :

      viderBuffer(); // empeche des erreurs
    } else {
      continu = 0; // on sort de la boucle
    }
  }
  struct dirent *dir; // on déclare une structure dir grâce à la bibliotheque
                      // dirent.h utile pour naviguer dans les fichiers
  DIR *d = opendir("./donnees"); // on ouvre le répertoire donnees

  if (d) { // ouvre le dossier s'il existe
    FILE *fichbis =
        fopen("./donnees/t.txt",
              "wb+"); // on cree le fichier temporaire "t.txt" à filtrer
                      // //wb+ écrase les fichiers existants il sera utile pour
                      // des traitements suppls

    printf("Tous les entrainements du %s trouvés :\n\n", date);
    while ((dir = readdir(d)) != NULL) { // on parcours les fichiers
      char chemin[70] = "./donnees/\0";
      char nomsanstxt[56];
      tronquerTxt(
          dir->d_name,
          nomsanstxt); // ecri le nom du fichier qu'on examine sans le .txt
      if (dir->d_name[0] == '.' &&
          (dir->d_name[1] == '\0' ||
           (dir->d_name[1] == '.' && dir->d_name[2] == '\0'))) {
        continue;
      }                            // Ignore les entrées "." et ".."
      strcat(chemin, dir->d_name); // on rajoute .txt pour trouver le fichier
      FILE *fich = NULL;
      // printf("%s", chemin);
      fich = fopen(chemin, "r");
      char chaine[300];
      fseek(fich, 0, SEEK_SET); // on se met au debut du fichier
      fgets(chaine, 300, fich); // on enlève la 1ère ligne
      int epligne = 0;          // epreuve de la ligne
      char colonne[20];
      while (fgets(chaine, 300, fich) != NULL) { // parcours fichier
        if (delimiter(chaine, 0, colonne)) {
          if (strcmp(date, colonne) == 0) { // les dates correspondent
            fprintf(fichbis, "%s;%s", nomsanstxt,
                    chaine); // on met le traitement dans le fichier temporaire
                             // en rajoutant le nom en tant que colonn n°0, cela
                             // décalera les autres colonnes
            printf("Athlète : %s\n", nomsanstxt);

            char epreuve[20];
            if (delimiter(chaine, 1, epreuve)) {
              int numep = 0;
              numep = charToDigit(epreuve[0]); // on convertit
              char nomep[20];
              traduirelais(numep, nomep);
              printf("Épreuve : %s\n", nomep);
              float tps = 0;
              char colonnet[16];

              if (delimiter(chaine, 2, colonnet)) {
                tps = atof(colonnet); // conversion
                printf("Temps: %f\n", tps);
                if (numep == 5) { // cas du relais
                  char colonnep[20];
                  if (delimiter(chaine, 3, colonnep)) {
                    printf("Position dans le relais: %s\n", colonnep);

                  } else {
                    printf("erreur delimitage position relais\n");
                    return;
                  }
                } else {
                  printf("\n");
                }
              } else {
                printf("erreur delimitage temps\n");
                return;
              }
            } else {
              printf("erreur delimitage date\n");
              return;
            }
          }

        } else {
          printf("ECHEC DU DELIMITAGE date\n");
          return;
        }
      }
    }
    int choix = 0;
    while (1) {
      printf("\n\nVoulez vous affiner d'avantage la recherche avec d'autres "
             "filtres ?");
      printf("\nTapez 1 pour refiltrer\n");
      printf("Tapez 2 pour quitter\n");
      if (scanf("%d", &choix) != 1) {
        while (getchar() != '\n')
          ;
        printf("Entrée invalide. Veuillez entrer un nombre valide.\n");
        continue;
      }

      if (choix == 1) { // cas refiltrage
        viderBuffer();

        refiltrer(fichbis);
        return;

      } else if (choix == 2) { // cas quitter
        viderBuffer();
        return;
      } else {
        printf("Entrée invalide. Veuillez entrer un nombre valide.\n");
        continue;
      }
    }
  } else {
    printf("erreur le dossier donnees n'existe pas");
    return;
  }
}

void afficher_entrainement_epreuve() { // similaire à afficher_entrainement_date
  int continu = 1;
  int epreuve = 0;
  while (continu) {
    printf("Quel type d'épreuve?\n(format : 1=100m 2=400m 3=5000m 4=marathon "
           "5=relais4*400m)");
    scanf("%d", &epreuve);
    if ((epreuve < 1) || (epreuve > 5)) { // on vérifie la validité de l'entrée
      printf("\nVous n'avez pas respecté le format\n");
      viderBuffer(); // empeche des erreurs
    } else {
      continu = 0; // on sort de la boucle
    }
  }
  struct dirent *dir; // on déclare une structure dir grâce à la bibliotheque
                      // dirent.h utile pour naviguer dans les fichiers
  DIR *d = opendir("./donnees"); // on ouvre le répertoire donnees

  if (d) { // ouvre le dossier s'il existe
    FILE *fichbis =
        fopen("./donnees/t.txt",
              "wb+"); // on cree le fichier temporaire "t.txt" à filtrer
                      // //wb+ écrase les fichiers existants il sera utile pour
                      // des traitements suppls
    char nomep[16];
    traduirelais(epreuve, nomep);
    printf("Tous les entrainements de %s trouvés :\n\n", nomep);
    while ((dir = readdir(d)) != NULL) { // on parcours les fichiers
      char chemin[70] = "./donnees/\0";
      char nomsanstxt[56];
      tronquerTxt(
          dir->d_name,
          nomsanstxt); // ecri le nom du fichier qu'on examine sans le .txt
      if (dir->d_name[0] == '.' &&
          (dir->d_name[1] == '\0' ||
           (dir->d_name[1] == '.' && dir->d_name[2] == '\0'))) {
        continue;
      }                            // Ignore les entrées "." et ".."
      strcat(chemin, dir->d_name); // on rajoute .txt pour trouver le fichier
      FILE *fich = NULL;
      // printf("%s", chemin);
      fich = fopen(chemin, "r");
      char chaine[300];
      fseek(fich, 0, SEEK_SET); // on se met au debut du fichier
      fgets(chaine, 300, fich); // on enlève la 1ère ligne
      int epligne = 0;          // epreuve de la ligne
      char colonne[16];
      while (fgets(chaine, 300, fich) != NULL) { // parcours fichier
        if (delimiter(chaine, 1, colonne)) {
          if (charToDigit(colonne[0]) ==
              epreuve) { // la ligne est celle de lepreuve
            fprintf(fichbis, "%s;%s", nomsanstxt,
                    chaine); // on met le traitement dans le fichier temporaire
                             // en rajoutant le nom en tant que colonn n°0, cela
                             // décalera les autres colonnes
            printf("Athlète : %s\n", nomsanstxt);
            char date[20];
            if (delimiter(chaine, 0, date)) {
              printf("Date : %s\n", date);
              float tps = 0;
              char colonnet[16];

              if (delimiter(chaine, 2, colonnet)) {
                tps = atof(colonnet); // conversion
                printf("Temps: %f\n", tps);
                if (epreuve == 5) { // cas du relais
                  char colonnep[20];
                  if (delimiter(chaine, 3, colonnep)) {
                    printf("Position dans le relais: %s\n", colonnep);
                  } else {
                    printf("erreur delimitage position relais\n");
                    return;
                  }
                }
              } else {
                printf("erreur delimitage temps\n");
                return;
              }
            } else {
              printf("erreur delimitage date\n");
              return;
            }
          }

        } else {
          printf("ECHEC DU DELIMITAGE\n");
          return;
        }
      }
    }

    int choix = 0;
    while (1) {
      printf("\n\nVoulez vous affiner d'avantage la recherche avec d'autres "
             "filtres ?");
      printf("\nTapez 1 pour refiltrer\n");
      printf("Tapez 2 pour quitter\n");
      if (scanf("%d", &choix) != 1) {
        while (getchar() != '\n')
          ;
        printf("Entrée invalide. Veuillez entrer un nombre valide.\n");
        continue;
      }

      if (choix == 1) { // cas refiltrage
        viderBuffer();

        refiltrer(fichbis);
        return;

      } else if (choix == 2) { // cas quitter
        viderBuffer();
        return;
      } else {
        printf("Entrée invalide. Veuillez entrer un nombre valide.\n");
        continue;
      }
    }
  } else {
    printf("erreur le dossier donnees n'existe pas");
    return;
  }
}

void consulter_entrainements() {
  printf("Pour afficher les entrainements d'un athlète veuillez séléctionner \n"
         "rechercher athlète dans le menu principal puis affichez ses "
         "performances\n");
  printf("Pour afficher les entrainements selon la date écrivez 1\n");
  printf("Pour afficher les entrainements selon l'épreuve écrivez 2\n");
  int choix = 0;
  while (1) {
    if (scanf("%d", &choix) != 1) {
      while (getchar() != '\n')
        ;
      printf("Entrée invalide. Veuillez entrer un nombre valide.\n");
      continue;
    }

    switch (choix) {
    case 1:
      afficher_entrainement_date();
      return;
      break;
    case 2:
      afficher_entrainement_epreuve();
      return;

      break;
    default:
      printf("Saisie invalide \n");
      break;
    }
  }
}
