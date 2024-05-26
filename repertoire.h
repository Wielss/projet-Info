#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entrainement {
  char date[11];
  int epreuve;
  float temps;
} Entrainement;

#define MAX_ATHLETES 100
#define MAX_ENTRAINEMENTS 100

typedef struct Athlete {
  char nom[50];
  char nomfichier[50];
  Entrainement entrainements[MAX_ENTRAINEMENTS];
  int nb_entrainements;
} Athlete;

typedef struct athletejo {
  char nom[56];
  float tpsmoyen;

} athletejo;

void dupliquerFichier(FILE *fichierSource, const char *nomDestination);

int max(int a, int b);

char *delimiter(const char *chaine, int indice,
                char *champ); // renvoie la colonne numéro indice dans champ

int comptelignefichier(FILE *param);

void viderBuffer();

int supprimerFichierDansDossier(
    const char *dossier,
    const char
        *nomFichier); // les paramètres const char ne peuvent pas etre modifiés,
                      // cette fonction supprime lefichier dans le dossier

int supprimerFichierDansDossierMuet(const char *dossier,
                                    const char *nomFichier);

int charToDigit(char c); // merci chatgpt

void traduirelais(int num,
                  char chaine[15]); // prend un numéro entre 1 et 5 et
                                    // renvoie l'épreuve associée.

int lire(char *chaine,
         int longueur); // fonction copiée sur open classroooms scanf amélioré

int date_valide(int jour, int mois, int annee); // prend des entiers en params

int estbonnedate(char chaine[11]); // vérifie si la date passé est au bon
                                   // format renvoie 0 si erreur
// Fonction pour trouver 2 dates récentes
void trouverDatesLesPlusRecentes(FILE *fichier, char *dateLaPlusRecente,
                                 char *deuxiemeDateLaPlusRecente);

void Afficherstat(
    FILE *fichier); // affiche les statistqieus d'un athlètye selon l'épreuev

void afficher_menu();

void afficher_filtrat(FILE*fich);//est appelée depuis refiltrer pour un affichage propre

int compter_tout();

int tout_entrainement();

FILE *viderFichierTemp(FILE *temp); // vvide le fichiers T.txt

void refiltrer(FILE *fichtemp); // permet de filtrer d'avantage

void afficher_performances_athlete(FILE *fichierparam, char nomsanstxt[60]);

void saisir_et_sauvegarder_entrainement(FILE *fichierparam);

void saisir_et_sauvegarder_relais(
    FILE *fichierparam); // est appélée lors d'un relais

int rechercher_athlete(); // renvoie 0 si erreur 1 sinon

void afficher_liste_athletes();

void ajouter_athlete();

void supprimer_athlete();

void ajouter_entrainement();

int ajouter_relais(int numero,
                   char date[11]); // est appélée lors d'un relais le numero
                                   // est 2 au début et s'arrete à 4
                                   // renvoie 1 si bien passé 0 si erreur
//-1 s'il faut choisir un nouvel athlète

void tronquerTxt(const char *chaine, char *chaineModifiee);

void trierathletejo(athletejo tab[3]); // algo primitif

float temps_moyen(
    FILE *fichier,
    int epreuve); // renvoie le temps moyen de l'thlète sur l'épreuve

void envoyer_jo(); // affihce les 3 meilleurs athlètes pour une épreuve

void afficher_entrainement_date();

void afficher_entrainement_epreuve();

void consulter_entrainements();
