#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#ifndef authentif_H
#define authentif_H


typedef struct _joueur{

    char username[80];
    char password[80];
    char prenom[80];
    char nom[80];
    int score[100];

}joueur;
/*----------------------------------------------------  Afficher les mots en Asci ART -------------------------------------------*/
/*----------------------------------------------------  Afficher les mots en Asci ART -------------------------------------------*/

// pour afficher "JEU DE MEMOIRE" ****lire un fichier ou le mot  "JEU DE MEMOIRE" est dessiné*****
void logo();


// pour afficher l'encadrant *****meme pricipe que logo*****
void encadrant();


// pour afficher les memberes  *****meme pricipe que logo*****
void membres();

// pour afficher READY *****meme pricipe que logo*****
void ready();

// effacer l'écran par une click
void effacer();
/*----------------------------------------------------------------------------------------------------------------------------------*/



/*----------------------------------------------- La parie d'inscription et d'identification -----------------------------------------*/


// savoir le nombre du groupe des joueures
int choisir_grp_non();

// recherche un username dans un fichier texte " s'il existe i vaut à 1 sinon vaut à 0"
int rech(char name1[80]);

// ajouter le joueur inscris dans le fichier texte des joueurs
void ajouter_joueur(joueur jr);

// cette fonction sert soit a supprimer les infos s'il n'a pas entrer ses propres infos pour acceder a son compte d'un joueur ou soit a modifier son password
void mise_a_jour(char username1[80],char password1[80],char choix[20]);

// cette fonction sert a verifier le login "1 si on a le succes accéder a le compte du joueur sinon retourne 0"
int login (char username[80],char password[80]);

// on demande au groupe du joueurs de s'inscrire ou de s'identifier , on enregistre ses username dans "liste_username[10][80]"


void joueur_joue(char liste_username[10][80],int grp,int *f);

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------- lire liste_score & enregistrer le nouveau score dans un fichier ----------------------------------------------------------------------------------------------*/


// cette fonction convert un liste score de caractere en liste score des entiers , on enregistre dans score[100] ett nous retourne le nombre des scores. NB!!: les scores sont composées de 1 à 2 chiffres max =20 min 0
int lire_score(int score[100],char username1[80]);


// cette fonction consiste à ajouter le score a la liste des scores dans un fichier texte des joueurs
void enregistrement_score(char username1[80],int score1);

// pour afficher "JEU DE MEMOIRE" ****lire un fichier ou le mot  "JEU DE MEMOIRE" est dessiné*****
#endif

