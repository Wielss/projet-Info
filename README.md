Participants au projet : Matteo Roccia			
Gabriel Zahramane
Francisco Tornos Lloret 
MI4
					
Ce projet vise à développer une application de gestion pour permettre aux entraîneurs de suivre les performances des athlètes en vue des JO. Les performances des athlètes sont stockées dans des fichiers et peuvent être mises à jour, consultées et analysées pour produire des statistiques.

# Fonctionnalités :
Gestion des épreuves : 
100m, 400m, 5000m, marathon, relais 4x400m.

Suivi des performances : 
Stockage des performances individuelles dans des fichiers.

Entrée des données : 
Ajout de nouvelles performances.

Consultation des résultats : 
Historique des entraînements par athlète, épreuve ou date.

Statistiques :
Meilleur, pire et temps moyen par athlète et épreuve.
Sélection des trois meilleurs athlètes par épreuve.
Progression des athlètes entre deux dates.

Améliorations possibles : 
Calcul de la régression linéaire pour l'évolution des performances, tri des historiques par date ou nom.

# Modules du programme :

repertoire.c : contient le corps de chque fonction

repertoire.h : contient le prototype de chaque fonction

main.c : contient la fonction main qui lance le programme principal

# Utilisation:
Compiler le programme :
```bash
make
```

Executer le programme :
```bash
./main
```

# RAPPORT DE PROJET :

Nous avons décidé de choisir le projet CER-J-O car c’était le plus parlant pour nous parmi ceux proposés, en raison de notre affinité avec les fichiers. Pour communiquer, nous avons créé un groupe sur Discord et sur Whatsapp.
Tout d’abord, nous avons regardé une vidéo pour comprendre l’utilisation de GitHub. Gabriel a créé un menu qui nous a servi de base pour le projet. En cours, notre proffesseur de TD d'informattique Romuald Grignon nous a donné des pistes pour bien démarrer, notamment en créant un fichier nommé toux.txt regroupant les noms de tous les athlètes. Au début, nous avons suivi cette méthode, mais Matteo s'est rendu compte que cela compliquerait les choses. Après des discussions et des recherches, nous avons décidé d'utiliser des dossiers pour stocker les noms des athlètes. Bien que nous ayons initialement douté, nous avons rapidement appris à les utiliser grâce à leur grande similitude avec les fichiers. Francisco s’est chargé de sécuriser les saisies des utilisateurs. En effet, le programme plantait lorsque des caractères spéciaux étaient entrés. Après s’être documenté, il a trouvé une solution sur un forum. Les premières fonctions pour afficher la liste des athlètes ou ajouter un athlète étaient relativement simples. Les fonctionnalités liées aux relais et aux statistiques, avec leurs filtres multiples, nous ont pris plus de temps.Pour afficher les performances des athlètes, nous avions prévu de créer un fichier contenant toutes les valeurs pour chaque épreuve, mais cette solution présentait trop de failles. Nous nous sommes donc tournés vers une solution meilleure en créant un fichier temporaire avec l’ensemble des performances des relais renseignés.Francisco, n’ayant pas de PC chez lui, travaillait seul sur les PC du lycée et nous envoyait ses avancées. Quant à Matteo et Gabriel, ils programmaient ensemble via des appels Discord, en mettant en commun leurs idées respectives.
Il faut aussi reconnaître que à certain moment chatGPT nous a bien aidé comme par exemple pour la fonction qui convertit des caractères en entier.
Lorsque l'un de nous avait une idée, il l'expliquait aux autres pour que nous soyons tous sur la même longueur d’onde. En effet, nous avons rapidement compris qu'il est très difficile de se mettre à la place de l’autre pour comprendre ce qu'il veut faire. Il est donc crucial d'extérioriser nos pensées, que ce soit par des dessins ou par la parole.

