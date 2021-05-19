

#include "authentif.h"

/*----------------------------------------------------  Afficher les mots en Asci ART -------------------------------------------*/
void logo()
{
    FILE *fic=fopen("asci art/jeudememoire.txt","r");
    int c;
    while (1) // boucle qui se termine a la fin de fichier "càd feof(fic)=1"
    {

        c=fgetc(fic);
        if (feof(fic))
                break;
        printf("%c",c);

    }
    fclose(fic);
}

// pour afficher l'encadrant *****meme pricipe que logo*****
void encadrant()
{
    FILE *fic=fopen("asci art/encadrant.txt","r");
    int c;
    while (1)
    {

        c=fgetc(fic);
        if (feof(fic))
                break;
        printf("%c",c);

    }
    fclose(fic);
}

// pour afficher les memberes  *****meme pricipe que logo*****
void membres()
{
    FILE *fic=fopen("asci art/memberes.txt","r");
    int c;
    while (1)
    {

        c=fgetc(fic);
        if (feof(fic))
                break;
        printf("%c",c);

    }
    fclose(fic);
}
// pour afficher READY *****meme pricipe que logo*****
void ready()
{
    FILE *fic=fopen("asci art/ready.txt","r");
    int c;
    while (1)
    {

        c=fgetc(fic);
        if (feof(fic))
                break;
        printf("%c",c);

    }
    fclose(fic);
}

// effacer l'écran par une click
void effacer()
{
    getchar();
    system ("cls");
}
/*----------------------------------------------------------------------------------------------------------------------------------*/



/*----------------------------------------------- La parie d'inscription et d'identification -----------------------------------------*/


// savoir le nombre du groupe des joueures
int choisir_grp_non()
{
    int grp;
    printf("%c vous pr%cf%crez :\n",254,130,138);
    printf("\t  1-Jouer Seule.\n");
    printf("\t  2-Jouer en groupe (MAX 4).\n");
    scanf("%d",&grp);
    if (grp==2) {printf(" %c D%cterminer le nombre du groupe : ",254,130); scanf("%d",&grp);}
    return grp;
}
// recherche un username dans un fichier texte " s'il existe i vaut à 1 sinon vaut à 0"
int rech(char name1[80])
{
    int existe=0; char username[80];
   FILE *fic=fopen("joueur_data.txt","r+");
   while (!feof(fic)) // boucle qui se termine a la fin de fichier "càd feof(fic)=1"
    {

        fscanf(fic,"%s ",username);

        if(strcmp(name1,username)==0) {existe=1;break;} // si on trouve le username existe vaut a 1 on sort de la boucle

    }
    fclose(fic);
    return existe;
}
// retourne les informations d'un joueur
joueur inscrire()
{
    joueur jr;
    printf("\n-----------------Entrer vos informations !!!!-------------\n ");
    printf("\n%c Username :",254);scanf("%s",jr.username);
    while(rech(jr.username)!=0) //cette boucle sert a verifier l'unicité de username "si il est déja existé  il demande a nouveau d'entrer un nouveau usernmae "
    {
        printf("\n%c Entrer un nouveau username (deja utilise) :",254);scanf("%s",jr.username);
    }
    printf("\n%c Password :",254);scanf("%s",jr.password);
    printf("\n%c Prenom :",254);scanf("%s",jr.prenom);
    printf("\n%c Nom :",254);scanf("%s",jr.nom);
    return(jr);

}
// ajouter le joueur inscris dans le fichier texte des joueurs
void ajouter_joueur(joueur jr)
{
    FILE *fic=fopen("joueur_data.txt","a");
    fprintf(fic,"%s |%s |%s |%s |\n",jr.username,jr.password,jr.prenom,jr.nom);
    fclose(fic);

}
// cette fonction sert soit a supprimer les infos s'il n'a pas entrer ses propres infos pour acceder a son compte d'un joueur ou soit a modifier son password
void mise_a_jour(char username1[80],char password1[80],char choix[20])
{
    FILE * fic=fopen("joueur_data.txt","r");
    FILE * fic1=fopen("teeeest.txt","a");// ouvrir un fichier texte pour conserver les donnés des joueurs apres la mise a jour
    joueur jr;
    char str_score[100];// on stocke la liste des score dans une chaine de caractere
    while(!feof(fic))   // boucle qui se termine a la fin de fichier "càd feof(fic)=1"
    {

        fscanf(fic,"%s |%s |%s |%s %s\n",jr.username,jr.password,jr.prenom,jr.nom,str_score);
        if(strcmp(jr.username,username1)==0) // recherche l'username
        {
            if (strcmp(choix,"supprimer")==0) continue; // si le choix est de supprimer les infos de joueur on saute l'instrution "fprinf" dans le nouveau fichier texte
            else
                strcpy(jr.password,password1); // si le choix est de modifier le password , on copie le nouveau password


        }
        fprintf(fic1,"%s |%s |%s |%s %s\n",jr.username,jr.password,jr.prenom,jr.nom,str_score);


    }


    fclose(fic1);
    fclose(fic);
    remove("joueur_data.txt"); // supprimer l'ancien fichier texte
    rename("teeeest.txt","joueur_data.txt"); // renommer le nouveau fichier texte par le nom de l'ancien
}
// cette fonction sert a verifier le login "1 si on a le succes accéder a le compte du joueur sinon retourne 0"
int login (char username[80],char password[80])
{
    FILE *fic=fopen("joueur_data.txt","r");
    joueur jr;
    int c=0,existe=0;
    char new_password[80],nom1[80],prenom1[80],str_score[100];
    while(!feof(fic)) // boucle qui se termine a la fin de fichier "càd feof(fic)=1"
    {
        fscanf(fic,"%s |%s |%s |%s %s\n",jr.username,jr.password,jr.prenom,jr.nom,str_score);
        if (strcmp(username,jr.username)==0) //cherche le username si on lr trouve existe=1 sinon exite reste nulle
        {
            existe=1;
         if(strcmp(password,jr.password)==0) //apres on trouve l' username on passe a verifier le password
            {printf("\n********** L'acces a votre pseudo-joueur est fait avec succes !!! **************");
            fclose(fic);return 1;}
         else // si le password est incorrect
         {

             while(strcmp(password,jr.password)!=0 && c!=3) // on donne a l'utilisateur 3 tentative d'entrer son password
             {
                printf("\n passeword eronee !! ressayez une autre fois \n%c Password : ",254);
                scanf("%s",new_password);
                strcpy(password,new_password);

                c++;
             }
                if (c<3) // si le cas ou il entre le password correct
                    {printf("\n********** L'acces a votre pseudo-joueur est fait avec succes !!! **************");fclose(fic);return 1;}

                else // si le passwort reste encore inccorrect , on lui demande son nom et son prenom pour renitialiser son password
                {
                  printf("\n renitialiser votre mot de passe !!! entrez votre nom et prenom afin de confirmer");
                  printf("\n%c Nom : ",254);scanf("%s",nom1);
                  printf("\n%c Prenom : ",254);scanf("%s",prenom1);
                  if(strcmp(nom1,jr.nom)==0 && strcmp(prenom1,jr.prenom)==0) // si le nom et le prenom sont correctes , on demande un nouveau password
                  {
                      fclose(fic);// on ferme le fichier pour le modifier
                      printf("\n%c Entrez un nouveau password : ",254);scanf("%s",new_password);
                      mise_a_jour(username,new_password,"modifier"); // on remplace l'ancian password par le nouveau dans le fichier texte de joueur
                      return 1; //  successful
                  }
                  else // si le nom et le prenom sont incorrectes, on supprime les donnés de ce joueur définitivement
                  {
                      fclose(fic);// on ferme le fichier pour le modifier
                      mise_a_jour(username,password,"supprimer");//supprission les donnés du joueur  dans le fichier texte.
                      printf("\n**************** l'acces de votre pseudo-joueur est supprime !!! ******************");
                      return 0; // failed

                  }

              }
          }
        }


    }
    fclose(fic);
    if (existe==0) // si username entrée par l'utilisateur n'existe pas ====> failed login
    {
        printf("\n vous devez s'inscrire !!! username : '%s' n'existe pas !",username);
        return 0; // failed
    }


}
// on demande au groupe du joueurs de s'inscrire ou de s'identifier , on enregistre ses username dans "liste_username[10][80]"


void joueur_joue(char liste_username[10][80],int grp,int *f)
{
    int i,choix,login_statut;
    joueur jr;
    for (i=0;i<grp;i++) // tous les joueurs doit soit s'inscrire soi s'identifier
    {
        printf("\n\n******************** le joueur N: %d ******************\n",i+1);
        printf("\n%c Entrer :\n1- pour s'identifier        2- pour s'inscrire   : \n",254);scanf("%d",&choix);
        switch(choix) // s'identifier ou s'inscrire
        {
        case 1 : printf("\n%c Username : ",254);scanf("%s",jr.username);
                 printf("\n%c Password : ",254);scanf("%s",jr.password);
                 login_statut=login(jr.username,jr.password);
                 if (login_statut==1)
                 {
                     if(strcmp(jr.username,"admin")==0)
                     {
                         printf("\n %c voulez-vous charger le pack des images? \n 1)oui              2) non \n ",254);
                         scanf("%d",f);

                     }

                        break; //si le login ça marche on sort de switch pour passer au joueur suivant
                 }
                 else {sleep(2);system("cls");logo();} // sinon il doit s'inscrire au nouveau

        case 2 : jr=inscrire(); // la partie d'inscription
                 ajouter_joueur(jr);
                 break;


        }
        strcpy(liste_username[i],jr.username);
        if (i==(grp-1)) break; // ctte condition a une relation avec l'animation de l'etape d'inscription
        effacer();// effacer l'écran de console
        logo();

    }
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------enregistrer le nouveau score dans un fichier ----------------------------------------------------------------------------------------------*/



// cette fonction consiste à ajouter le score a la liste des scores dans un fichier texte des joueurs
void enregistrement_score(char username1[80],int score1)
{
    FILE *fic=fopen("joueur_data.txt","r+");
    FILE*fic1=fopen("teeeest.txt","a");
    joueur jr;
    char str_score[100]="\0",ch[3]="\0";
    int n=0;
    while(!feof(fic)) // boucle qui se termine a la fin de fichier "càd feof(fic)=1"
    {

        fscanf(fic,"%s |%s |%s |%s %s\n",jr.username,jr.password,jr.prenom,jr.nom,str_score);
        fflush(stdin);
        if(strcmp(jr.username,username1)==0) // chercher l'username
        {
            int i=strlen(str_score);

            itoa(score1,ch,10); // convertir le score entier en score char
if (score1 > 9) // si le score est de 2 chiffres , on mémorise le premier chiffre puis le deuxième puis on ajoute une virgule
            {
                str_score[i]=ch[0];str_score[i+1]=ch[1];
            }
            else //si le score est d'un chiffres , on mémorise le premier chiffre puis on ajoute une virgule
            {
                str_score[i]=ch[0];
            }
            strcat(str_score,"--");

        }
        fprintf(fic1,"%s |%s |%s |%s %s\n",jr.username,jr.password,jr.prenom,jr.nom,str_score);
        fflush(stdout);


    }


    fclose(fic1);
    fclose(fic);

    remove("joueur_data.txt") ;       // supprimer l'ancien fichier texte
                    rename("teeeest.txt","joueur_data.txt"); // renommer le nouveau fichier texte par le nom de l'ancien

}




