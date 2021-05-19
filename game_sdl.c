
#include "game_sdl.h"



/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void tableau_de_bord(char nom_joueur[80],char player[80],int score) // affichage de tableau de bord (score et le nom des joueur)
{
    int k;
            printf("\n   %c",201);
            for (k=0;k<80;k++) printf("%c",205);
            printf("%c\n",187);
           printf("\t\t      %s : %s                     Score: %d                  \n",player,nom_joueur,score);
            printf("   %c",200);
            for (k=0;k<80;k++) printf("%c",205);
            printf("%c\n\n",188);
}


int passer_tour(int tour,int nb_grp) // fonction pour passer le tour entre les joueurs
{
    if (tour<nb_grp-1) //incrementer le tour
        tour++;
    else        // réinitialiser le tour a 0 si il depasse le nombre de groupe-1
    {
        tour=0;
    }
return tour;
}

int posy ( int y, int n) // cette fonction permet si l'utilisateur clique sur une position qlq de l'image , il doit retourner la valeur de y pour definir not rectangle
{
    int Y1[]={0,200,400,600,800},i;     //
    int Y2[]={0,200,350,500,650,800};
    int Y3[]={0,200,320,440,560,680,800};  // chaque tableu se remplisse par raport a la taille de l'image
    switch(n)// n est le niveau
{case 1 :


        for (i=1;i<5;i++)
        {
            if((y-Y1[i])<0) //  on determine la borne inferieure plus proche de y
            break;
        }


    return Y1[i-1];

case 2 :

     for (i=1;i<6;i++)
        {
            if((y-Y2[i])<0)
            break;
        }


    return Y2[i-1];

case 3:
     for (i=1;i<7;i++)
        {
            if((y-Y3[i])<0)
            break;
        }


    return Y3[i-1];
}
}

int posx (int x) //cette fonction permet si l'utilisateur clique sur une position qlq de l'image , il doit retourner la valeur  de x pour definir not rectangle
{
    int X[]={0,200,400,600,800},i; //   NB! : la largeur de notre image reste constante pour tous les niveaux 200 px

        for (i=1;i<5;i++)
        {
            if((x-X[i])<0)  // on determine la borne inferieure plus proche de x
            break;
        }

      return X[i-1];
}
int position (int x, int y,int n) // le but de cette fonction est determiner la  position de l'image cliqué par l'utilisateur a partir de x et y dans la liste des sources des images
{
    int X[]={0,200,400,600,800};
    int Y1[]={200,400,600,800},colonne,ligne,i,pos;
    int Y2[]={200,350,500,650,800};
    int Y3[]={200,320,440,560,680,800};
    switch(n) // n est le niveau . pour chaque niveau  la largeur reste constante ( X est le meme ) mais la longuer varie selon la taille de l'image et le nombre d'image inséres.
{case 1:


        for (i=1;i<5;i++)
        {
            if((x-X[i])<0) {colonne=i-1;
            break;
        }
        }
        for (i=1;i<4;i++)
        {
            if((y-Y1[i])<0) {ligne=i-1;
            break;
        }
        }
    pos=ligne*4+colonne;
    return pos;


case 2 :
for (i=1;i<5;i++)
        {
            if((x-X[i])<0) {colonne=i-1;
            break;
        }
        }
        for (i=1;i<5;i++)
        {
            if((y-Y2[i])<0) {ligne=i-1;
            break;
        }
        }
    pos=ligne*4+colonne;
    return pos;

case 3 :
for (i=1;i<5;i++)
        {
            if((x-X[i])<0) {colonne=i-1;
            break;
        }
        }
        for (i=1;i<6;i++)
        {
            if((y-Y3[i])<0) {ligne=i-1;
            break;
        }
        }
    pos=ligne*4+colonne;
    return pos;


}
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------le but de cette partie est d'avoir une liste des sources des images pseudo aleatoires.--------------------------------------------------------------------------------------------------------------------------------*/


void aleatoire_non_repete(int a[], int n, int max) // cette fonction nous donne un tableau de taille n  chaque case est rempli par un entier aleatoire unique  de 0 a max-1
 {
    int i, j, again;
    srand(time(NULL)); // generateur des nombres pseudo aleatoires renouvlé par changement du temps
    for (i = 0; i < n; i++) {
        do {
            again = 0;
            a[i] = rand()%max; // generer un entier aleatoire entre 0 et max (non inclus)
            for (j = i - 1; j >= 0; j--) // cette boucle nous garantit qu'il n'ya pas de repition des entiers .
                {
                if (a[j] == a[i]) // si la repition existe . regenerer un nouveau entier .
                {
                    again = 1;
                    break;
                }
            }
        } while (again); // le programme sort de cette boucle lorsqu'on a aucune repition des entiers.
    }
}


void fonc_image_aleatoire(char scr_img_aleatoire[24][50],char src_img[24][50],int niveau)
// pour le bon fonctionnement du jeu . il faut que les images changent d'une partie a une autre . donc cette fonction nous permet d'avoir une liste de source image aleatoire en utlisant la fonction precedante .
{
srand(time(NULL));
int t[24],i,c;
  switch(niveau)
{
  case 1:
         aleatoire_non_repete(t,12,12); // niveau facile contient 12 images

        for(i=0;i<12;i++)
        {
            c=t[i];
            strcpy(scr_img_aleatoire[i],src_img[c]);

        }

        break;

    case 2:

            aleatoire_non_repete(t,16,16);  // niveau normale contient 16 images

            for(i=0;i<16;i++)
            {
            c=t[i];
            strcpy(scr_img_aleatoire[i],src_img[c]);

            }

            break;
    case 3:

            aleatoire_non_repete(t,20,20);  // niveau difficile contient 20 images

            for(i=0;i<20;i++)
            {
            c=t[i];
            strcpy(scr_img_aleatoire[i],src_img[c]);

            }
            break;

    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


void clean_resources(SDL_Window *w,SDL_Renderer *r,SDL_Texture *t) //cette fonction sert a sortir du SDL si il ya une erreur ou si on termine .
{
    if(t!=NULL)
        SDL_DestroyTexture(t);
    if(r!=NULL)
        SDL_DestroyRenderer(r);
    if(w!=NULL)
        SDL_DestroyWindow(w);
    SDL_Quit();

}

void charger(SDL_Window *window,SDL_Renderer *renderer,SDL_Surface *surface,SDL_Rect dest,SDL_Texture *t) // charger une image
 {

      if (surface==NULL)
        {
            SDL_Log("erreur %s\n",SDL_GetError());
            clean_resources(window,renderer,NULL);
        }
    t=SDL_CreateTextureFromSurface(renderer,surface);  // La texture t contient maintenant l'image importée
    SDL_FreeSurface(surface); // // libérer la mémoire du surface  , équivalent à destroyTexture pour les surface
    if (t==NULL)
    {
        SDL_Log("erreur %s\n",SDL_GetError());
        clean_resources(window,renderer,NULL);

    }
    if(SDL_QueryTexture(t,NULL,NULL,&dest.w,&dest.h)!=0) // application de la texture sur le rectangle dest
    {
        SDL_Log("erreur %s\n",SDL_GetError());
        clean_resources(window,renderer,t);

    }

    if(SDL_RenderCopy(renderer,t,NULL,&dest)!=0) // application de la texture sur le renderer
    {
        SDL_Log("erreur %s\n",SDL_GetError());
        clean_resources(window,renderer,t);
    }
 }
 void load_image(SDL_Window *window,SDL_Renderer *renderer,SDL_Surface *image,SDL_Texture *texture,int x1,int y1,int h,int w,char source[30],int level) // charger une image a partir de la source et et sa position et sa taille
 {
                    SDL_Rect det={0,0,h,w};
                    det.x=posx(x1);
                    det.y=posy(y1,level);
                    image=SDL_LoadBMP(source);
                    charger(window,renderer,image,det,texture);
                    SDL_RenderPresent(renderer); // afficher le renderer

 }
 void intialiser(SDL_Window *window,SDL_Renderer *renderer,SDL_Surface *image,SDL_Texture *texture,int x1,int y1,int h,int w,int level) // on utilise cette pour retourner les cartes qui a tourner l'utilisateur a leur etats intiales si ils ne sont pas identiques
 {
     switch (level)
     {
    case 1:

        load_image(window,renderer,image,texture,x1,y1,h,w,"facile/vide_facile.bmp",1);
        load_image(window,renderer,image,texture,x1,y1,h,w,"facile/Card_back.bmp",1);
        break;
    case 2:


        load_image(window,renderer,image,texture,x1,y1,h,w,"normale/vide_normal.bmp",2);
        load_image(window,renderer,image,texture,x1,y1,h,w,"normale/Card_back_normal.bmp",2);
        break;
    case 3 :
        load_image(window,renderer,image,texture,x1,y1,h,w,"difficile/vide_difficile.bmp",3);
        load_image(window,renderer,image,texture,x1,y1,h,w,"difficile/Card_back_difficile.bmp",3);
        break;
 }
 }

void joueur_gagnant(SDL_Window *window,SDL_Renderer *renderer,SDL_Surface *image,SDL_Texture *texture,int j) // cette fonction permet de feleciter le gagnant
 {
    switch(j)
     {


 case 0: // joueur n=1
    load_image(window,renderer,image,texture,0,0,800,800,"affichage/1.bmp",1);
    break;
 case 1:
    load_image(window,renderer,image,texture,0,0,800,800,"affichage/2.bmp",1);
    break;
 case 2:
    load_image(window,renderer,image,texture,0,0,800,800,"affichage/3.bmp",1);
    break;
 case 3:// joueur n=4
    load_image(window,renderer,image,texture,0,0,800,800,"affichage/4.bmp",1);
    break;
     }
 SDL_Delay(5000);
 }

  void facile(SDL_Window *window,SDL_Renderer *renderer,SDL_Texture *texture,int *finish,int groupe, char nom_joueur[5][80],int score[5],int f) // cette fonction represente le niveau facile du jeu

{


 Mix_Music *musique;
    SDL_Rect dest={0,200,200,200};
    SDL_Surface *picture;
    SDL_RenderClear(renderer);
    for (int i=0;i<12;i++) // cette boucle permet de creer le table de jeu 12 cartes
{
    picture=SDL_LoadBMP("facile/card_back.bmp");
charger(window,renderer,picture,dest,texture);
if(dest.x<600)

    dest.x+=200; // on charge ligne par ligne puisque au niveau facile chaque image a de taille (200,200)
else
  {dest.y+=200;
dest.x=0;
   }
   }


 SDL_RenderPresent(renderer);
 SDL_Delay(1000);

    int done=0;
SDL_Event event;
SDL_Rect det={0,200,200,200};
SDL_Surface *image=NULL;
char src_image_aleatoire[24][50];

if (f==1)  // le nouveau pack pour l'adminisrateur .
{
char src_image1[24][50]={"facile/eren.bmp","facile/overlord.bmp","facile/rem.bmp","facile/solo.bmp","facile/brook.bmp","facile/pikatchu.bmp","facile/eren.bmp","facile/overlord.bmp","facile/rem.bmp","facile/solo.bmp","facile/brook.bmp","facile/pikatchu.bmp"};
musique=Mix_LoadMUS("facile/aot2.mp3");
fonc_image_aleatoire(src_image_aleatoire,src_image1,1);

}
else // le pack des animeaux ordinaire
{
char src_image2[24][50]={"facile/a.bmp","facile/bomba.bmp","facile/lion.bmp","facile/monkey.bmp","facile/panda.bmp","facile/m.bmp","facile/a.bmp","facile/bomba.bmp","facile/lion.bmp","facile/monkey.bmp","facile/panda.bmp","facile/m.bmp"};;
musique=Mix_LoadMUS("facile/kid1.mp3"); // charger la musique
fonc_image_aleatoire(src_image_aleatoire,src_image2,1);

}
Mix_PlayMusic(musique,-1); // joueur de la musique , boucle infinie .
int x,y;
int j,i,x1[20],y1[20]; int t[20],tour=0;   SDL_Rect rectangle={0,0,800,200};
int k=0 ;  // ce variable represente le nombre de cartes tourné 0 ou 1 ou 2
int c=0; // variable designe combien d'images ont étes suppremes d'ou la gestion du partie  si c=6  donc tous les images sont suppriméés et remplacer par le vide d'ou la fin du jeu .
char source_player[5][50]={"affichage/player_1.bmp","affichage/player_2.bmp","affichage/player_3.bmp","affichage/player_4.bmp"};
char player[5][20]={"player 1","player 2","player 3","player 4"};
int temps_initial=SDL_GetTicks(); // prend le temps intial
int temps_actual,seconde=0;
for (j=0;j<groupe;j++) // affichage de tableau de bord pour chaque joueur .
{
    tableau_de_bord(nom_joueur[j],player[j],score[j]);

}

printf("\n\n\n");
load_image(window,renderer,image,texture,0,0,200,800,source_player[tour],1);
while (!done)
    {

                temps_actual=SDL_GetTicks(); // prend le temps actuelle depuis le lancement de programme
            if ((temps_actual-temps_initial)>1000) // on compte seconde par seconde
            {   seconde+=1;temps_initial=temps_actual;
                if (seconde==15) // chaque joueur a 15 seconde pour jouer son tour sinon le tour se passe .
                {
                    if (k==1)  // si le temps est terminé et une carte et tourné on l'initialise .
                    {
                        intialiser(window,renderer,image,texture,x1[0],y1[0],200,200,1);
                        k=0;

                    }
                    tour=passer_tour(tour,groupe);
                    load_image(window,renderer,image,texture,0,0,200,800,source_player[tour],1); // affiche le tour de chaque joueur .
                    seconde=0;
                }
            }
            printf("\r\t\t\t\tLe temps rest%c : %d sec",130,15-seconde);



        while (SDL_PollEvent(&event)) // creer un evenement sdl
        {

            switch(event.type)
            {

                case SDL_QUIT: // permet de sortir si l'utilisateur a cliqué sur la fermeture de la fenetre .
                 *finish=1; // pour sortir du jeu .
                 done=1;
                   break;
                case SDL_MOUSEBUTTONDOWN: // si l'utilisateur a cliqué sur une image .
                  if(k<2) // la fin du tour est realisé si k=2 (l'utilisateur a tourné deux images)
                  {

                    SDL_GetMouseState(&x,&y); // cette fonction permet d'obtenir les coordonnées du clique .
                    i=position(x,y,1); // determiner la position d'image
                    t[k]=i; // pour memoriser les deux positions d'image actuelle et precedente
                   if((k==1 && i==t[0]) ||(k==1 && strcmp("facile/vide_facile.bmp",src_image_aleatoire[i])==0) || y<200) // si l'utilisateur a cliqué sur une image deux fois ou si il a cliqué sur le vide le programme sort et aucune action n'est faite .
                        break;
                    if ((k==0 && strcmp("facile/vide_facile.bmp",src_image_aleatoire[i])==0 )|| y<200) // si l'utisateur a clique sur le vide pour la premiere clique aucune action est faite et k reste 0 . y< 200 est une condition parceque cette zone est prise par le joueur qui joue .
                    {
                        break;
                    }

                    det.x=posx(x);
                    det.y=posy(y,1);
                    x1[k]=posx(x);
                    y1[k]=posy(y,1);
                    load_image(window,renderer,image,texture,x,y,200,200,src_image_aleatoire[i],1); // afficher l'image cliqué .
                    SDL_Delay(500);
                     k++;
                    if (k==2)  // comparer les deux images cliquées
                    { k=0;
                      if(strcmp(src_image_aleatoire[t[0]],(src_image_aleatoire[i]))==0 ) // les deux images sont identiques et donc les supprimer et les remplisser par le vide
                        {
                            score[tour]+=1; // le score du joueur augmente par 1
                            load_image(window,renderer,image,texture,x1[0],y1[0],200,200,"facile/vide_facile.bmp",1);
                            load_image(window,renderer,image,texture,x1[1],y1[1],200,200,"facile/vide_facile.bmp",1);
                            strcpy(src_image_aleatoire[i],"facile/vide_facile.bmp");
                            strcpy(src_image_aleatoire[t[0]],"facile/vide_facile.bmp");
                            c++;
                            SDL_Delay(500);
                            system("cls");
                              for (j=0;j<groupe;j++)
                        {
                            tableau_de_bord(nom_joueur[j],player[j],score[j]);

                        }
                            seconde=0;
                    }
                     else //les deux images sont differents entre eux . donc les retourner à l'etat intiale .
                     {
                        intialiser(window,renderer,image,texture,x1[0],y1[0],200,200,1);
                        intialiser(window,renderer,image,texture,x1[1],y1[1],200,200,1);
                        tour=passer_tour(tour,groupe);
                        load_image(window,renderer,image,texture,0,0,200,800,source_player[tour],1);

                        SDL_Delay(1000);
                        seconde=0;
                     }
                   }

                }
                    if(c==6) // la fin du partie .
                      {

                        done=1;


                           Mix_FreeMusic(musique); //Libération de la musique

                        }
                   break;
            }

        }


    }


}


  void normale(SDL_Window *window,SDL_Renderer *renderer,SDL_Texture *texture,int *finish,int groupe,char nom_joueur[5][80],int score[5],int f) // cette fonction represente le niveau normale du jeu

{

    Mix_Music *musique;


    SDL_Rect dest={0,200,200,150};
    SDL_Surface *picture;

    for (int i=0;i<16;i++)
                        {
                picture=SDL_LoadBMP("normale/card_back_normal.bmp");
                charger(window,renderer,picture,dest,texture);
                    if(dest.x<600)

                        dest.x+=200;
                    else
                    {dest.y+=150;
                        dest.x=0;
                        }
                        }




                    SDL_RenderPresent(renderer);
                    SDL_Delay(1000);
     int done=0;
SDL_Event event;
SDL_Rect det={0,200,200,150};
SDL_Surface *image=NULL;
char src_image_aleatoire[24][50];
if (f==1)
{
char src_image1[24][50]={"normale/gara.bmp","normale/itachi.bmp","normale/madara.bmp","normale/naruto.bmp","normale/oruchimaro.bmp","normale/pain.bmp","normale/sakura.bmp","normale/sasuke.bmp","normale/gara.bmp","normale/itachi.bmp","normale/madara.bmp","normale/naruto.bmp","normale/oruchimaro.bmp","normale/pain.bmp","normale/sakura.bmp","normale/sasuke.bmp"};
 musique=Mix_LoadMUS("normale/aot.mp3");
fonc_image_aleatoire(src_image_aleatoire,src_image1,2);

}
else
{
char src_image2[24][50]={"normale/dog.bmp","normale/peng.bmp","normale/pachi.bmp","normale/ecureil.bmp","normale/paju.bmp","normale/pichi.bmp","normale/para.bmp","normale/penguin.bmp","normale/dog.bmp","normale/peng.bmp","normale/pachi.bmp","normale/ecureil.bmp","normale/paju.bmp","normale/pichi.bmp","normale/para.bmp","normale/penguin.bmp"};
musique=Mix_LoadMUS("normale/kid1.mp3");
fonc_image_aleatoire(src_image_aleatoire,src_image2,2);

}
Mix_PlayMusic(musique,-1);

int x,y;
int j,i,k=0,x1[20],y1[20],c=0; int t[20],tour=0;   SDL_Rect rectangle={0,0,800,200};
char source_player[5][50]={"affichage/player_1.bmp","affichage/player_2.bmp","affichage/player_3.bmp","affichage/player_4.bmp"};
char player[5][20]={"player 1","player 2","player 3","player 4"};
int temps_initial=SDL_GetTicks(),temps_actual,seconde=0;
for (j=0;j<groupe;j++)
{
    tableau_de_bord(nom_joueur[j],player[j],score[j]);

}

printf("\n\n\n");
load_image(window,renderer,image,texture,0,0,200,800,source_player[tour],1);
while (!done)
    {

                temps_actual=SDL_GetTicks();
            if ((temps_actual-temps_initial)>1000)
            {   seconde+=1;temps_initial=temps_actual;
                if (seconde==15)
                {
                     if (k==1)  // si le temps est terminé et une carte et tourné on l'initialise .
                    {
                        intialiser(window,renderer,image,texture,x1[0],y1[0],200,200,1);
                        k=0;

                    }
                    tour=passer_tour(tour,groupe);
                    load_image(window,renderer,image,texture,0,0,200,800,source_player[tour],1);
                    seconde=0;
                }
            }
            printf("\r\t\t\t\tLe temps rest%c : %d sec",130,15-seconde);



        while (SDL_PollEvent(&event))
        {

            switch(event.type)
            {


                case SDL_QUIT:
                  *finish=1;
                  done=1;
                clean_resources(window,renderer,texture);

                   break;
                case SDL_MOUSEBUTTONDOWN:
                  if(k<2)
                  {

                    SDL_GetMouseState(&x,&y);
                    i=position(x,y,2);
                    t[k]=i;
                   if((k==1 && i==t[0]) ||(k==1 && strcmp("normale/vide_normal.bmp",src_image_aleatoire[i])==0) || y<200)
                        break;
                    if ((k==0 && strcmp("normale/vide_normal.bmp",src_image_aleatoire[i])==0 )|| y<200)
                    {
                        break;
                    }

                    det.x=posx(x);
                    det.y=posy(y,2);
                    x1[k]=posx(x);
                    y1[k]=posy(y,2);
                    load_image(window,renderer,image,texture,x,y,200,150,src_image_aleatoire[i],2);
                    SDL_Delay(500);
                     k++;
                    if (k==2)
                    { k=0;
                      if(strcmp(src_image_aleatoire[t[0]],(src_image_aleatoire[i]))==0 )
                        {
                            score[tour]+=1;
                            load_image(window,renderer,image,texture,x1[0],y1[0],200,150,"normale/vide_normal.bmp",2);
                            load_image(window,renderer,image,texture,x1[1],y1[1],200,150,"normale/vide_normal.bmp",2);
                            strcpy(src_image_aleatoire[i],"normale/vide_normal.bmp");
                            strcpy(src_image_aleatoire[t[0]],"normale/vide_normal.bmp");
                            c++;
                            SDL_Delay(500);
                            system("cls");
                              for (j=0;j<groupe;j++)
                        {
                            tableau_de_bord(nom_joueur[j],player[j],score[j]);

                        }
                            seconde=0;
                    }
                     else
                     {
                        intialiser(window,renderer,image,texture,x1[0],y1[0],200,150,2);
                        intialiser(window,renderer,image,texture,x1[1],y1[1],200,150,2);
                        tour=passer_tour(tour,groupe);
                        load_image(window,renderer,image,texture,0,0,200,800,source_player[tour],1);

                        SDL_Delay(1000);
                        seconde=0;
                     }
                   }

                }
                    if(c==8)
                      {
                        done=1;
                        Mix_FreeMusic(musique); //Libération de la musique

                      }

                   break;
            }

        }


    }

}



 void difficile(SDL_Window *window,SDL_Renderer *renderer,SDL_Texture *texture,int *finish,int groupe,char nom_joueur[5][80],int score[5],int f )// cette fonction represente le niveau difficile du jeu

{

    Mix_Music *musique;
    SDL_Rect dest={0,200,200,120};
    SDL_Surface *picture;

    for (int i=0;i<20;i++)
                        {
                picture=SDL_LoadBMP("difficile/Card_back_difficile.bmp");
                charger(window,renderer,picture,dest,texture);
                    if(dest.x<600)

                        dest.x+=200;
                    else
                    {dest.y+=120;
                        dest.x=0;
                        }
                        }




                    SDL_RenderPresent(renderer);
                    SDL_Delay(1000);
     int done=0;
SDL_Event event;
SDL_Rect det={0,200,200,150};
SDL_Surface *image=NULL;
char src_image_aleatoire[24][50];
if(f==1)
{
char src_image1[24][50]={"difficile/1.bmp","difficile/2.bmp","difficile/3.bmp","difficile/4.bmp","difficile/5.bmp","difficile/6.bmp","difficile/7.bmp","difficile/8.bmp","difficile/9.bmp","difficile/10.bmp","difficile/1.bmp","difficile/2.bmp","difficile/3.bmp","difficile/4.bmp","difficile/5.bmp","difficile/6.bmp","difficile/7.bmp","difficile/8.bmp","difficile/9.bmp","difficile/10.bmp"};
musique=Mix_LoadMUS("difficile/overlord.mp3");
Mix_PlayMusic(musique,-1);
fonc_image_aleatoire(src_image_aleatoire,src_image1,3);


}
else {
char src_image2[24][50]={"difficile/a.bmp","difficile/b.bmp","difficile/c.bmp","difficile/d.bmp","difficile/e.bmp","difficile/f.bmp","difficile/g.bmp","difficile/h.bmp","difficile/i.bmp","difficile/k.bmp","difficile/a.bmp","difficile/b.bmp","difficile/c.bmp","difficile/d.bmp","difficile/e.bmp","difficile/f.bmp","difficile/g.bmp","difficile/h.bmp","difficile/i.bmp","difficile/k.bmp"};
musique=Mix_LoadMUS("difficile/kid.mp3");
fonc_image_aleatoire(src_image_aleatoire,src_image2,3);
Mix_PlayMusic(musique,-1);

}


int x,y;
int j,i,k=0,x1[20],y1[20],c=0; int t[20],tour=0;   SDL_Rect rectangle={0,0,800,200};
char source_player[5][50]={"affichage/player_1.bmp","affichage/player_2.bmp","affichage/player_3.bmp","affichage/player_4.bmp"};
char player[5][20]={"player 1","player 2","player 3","player 4"};
int temps_initial=SDL_GetTicks(),temps_actual,seconde=0;
for (j=0;j<groupe;j++)
{
    tableau_de_bord(nom_joueur[j],player[j],score[j]);

}

printf("\n\n\n");
load_image(window,renderer,image,texture,0,0,200,800,source_player[tour],1);
while (!done)
    {

                temps_actual=SDL_GetTicks();
            if ((temps_actual-temps_initial)>1000)
            {   seconde+=1;temps_initial=temps_actual;
                if (seconde==15)
                {
                    if (k==1)  // si le temps est terminé et une carte et tourné on l'initialise .
                    {
                        intialiser(window,renderer,image,texture,x1[0],y1[0],200,200,1);
                        k=0;

                    }
                    tour=passer_tour(tour,groupe);
                    load_image(window,renderer,image,texture,0,0,200,800,source_player[tour],1);
                    seconde=0;
                }
            }
            printf("\r\t\t\t\tLe temps rest%c : %d sec",130,15-seconde);



        while (SDL_PollEvent(&event))
        {

            switch(event.type)
            {


                case SDL_QUIT:
                  *finish=1;
                  done=1;
                   break;
                case SDL_MOUSEBUTTONDOWN:
                  if(k<2)
                  {

                    SDL_GetMouseState(&x,&y);
                    i=position(x,y,3);
                    t[k]=i;
                   if((k==1 && i==t[0]) ||(k==1 && strcmp("difficile/vide_difficile.bmp",src_image_aleatoire[i])==0) || y<200)
                        break;
                    if ((k==0 && strcmp("difficile/vide_difficile.bmp",src_image_aleatoire[i])==0 )|| y<200)
                    {
                        break;
                    }

                    det.x=posx(x);
                    det.y=posy(y,3);
                    x1[k]=posx(x);
                    y1[k]=posy(y,3);
                    load_image(window,renderer,image,texture,x,y,200,120,src_image_aleatoire[i],3);
                    SDL_Delay(500);
                     k++;
                    if (k==2)
                    { k=0;
                      if(strcmp(src_image_aleatoire[t[0]],(src_image_aleatoire[i]))==0 )
                        {
                            score[tour]+=1;
                            load_image(window,renderer,image,texture,x1[0],y1[0],200,120,"difficile/vide_difficile.bmp",3);
                            load_image(window,renderer,image,texture,x1[1],y1[1],200,120,"difficile/vide_difficile.bmp",3);
                            strcpy(src_image_aleatoire[i],"difficile/vide_difficile.bmp");
                            strcpy(src_image_aleatoire[t[0]],"difficile/vide_difficile.bmp");
                            c++;
                            SDL_Delay(500);
                            system("cls");
                              for (j=0;j<groupe;j++)
                        {
                            tableau_de_bord(nom_joueur[j],player[j],score[j]);

                        }
                            seconde=0;
                    }
                     else
                     {
                        intialiser(window,renderer,image,texture,x1[0],y1[0],200,120,3);
                        intialiser(window,renderer,image,texture,x1[1],y1[1],200,120,3);
                        tour=passer_tour(tour,groupe);
                        load_image(window,renderer,image,texture,0,0,200,800,source_player[tour],1);

                        SDL_Delay(1000);
                        seconde=0;
                     }
                   }

                }
                    if(c==10)
                      {

                        done=1;
                           Mix_FreeMusic(musique); //Libération de la musique

                        }
                   break;
            }

        }


    }

}


void aide(SDL_Window *window,SDL_Renderer *renderer,SDL_Surface *picture,SDL_Texture *texture,int *finish) // cette fonction permet de donner une description sur le jeu .
{
SDL_RenderClear(renderer);
load_image(window,renderer,picture,texture,0,0,800,800,"affichage/desc.bmp",1);
SDL_Delay(100);
int done=0,x,y ;
SDL_Event event;
while(!done)
{
    while(SDL_PollEvent(&event))
        {
            SDL_GetMouseState(&x,&y);
        if(x<100 && x>30 && y<777 && y>707) // cette condition est juste pour donner une animation pour le jeu
            load_image(window,renderer,picture,texture,0,0,800,800,"affichage/desc_1.bmp",1);
        else
            load_image(window,renderer,picture,texture,0,0,800,800,"affichage/desc.bmp",1);

        switch(event.type)
        {
            case SDL_QUIT:
                done=1;
                *finish=1;

                break;

            case SDL_MOUSEBUTTONDOWN :
                SDL_GetMouseState(&x,&y);
                if(x<100 && x>30 && y<777 && y>707) // si l'utilisateur a cliqué sur la fleche . il retourne vers choisir niveau .
                {
                    load_image(window,renderer,picture,texture,0,0,800,800,"affichage/level.bmp",1);
                    done=1;
                    break;
                }

        }

    }
}
}

void end_game(SDL_Window *window,SDL_Renderer *renderer,SDL_Surface *image,SDL_Texture *texture,int *finish) // l'utilisateur peut choisir si'il veut rejouer ou sortir du jeu
 {

    SDL_RenderClear(renderer);
    load_image(window,renderer,image,texture,0,0,800,800,"affichage/0.bmp",1);
    int done=0,x,y;
    SDL_Event fin_game;
    while(!done)
     {

        while(SDL_PollEvent(&fin_game))
        {   SDL_GetMouseState(&x,&y);
            if (x>155 && x<245 && y<662 && y>575)
                load_image(window,renderer,image,texture,0,0,800,800,"affichage/home.bmp",1);
            else if (x>510 && x<595 && y<662 && y>575)
                load_image(window,renderer,image,texture,0,0,800,800,"affichage/exit.bmp",1);
            else
                load_image(window,renderer,image,texture,0,0,800,800,"affichage/0.bmp",1);
            switch(fin_game.type)
            {
            case SDL_QUIT:
                done=1;
                *finish=1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x,&y);
                 if (x>155 && x<245 && y<662 && y>575) // l'utilisateur a cliqué sur rejouer donc sortir de cette boucle
                 {
                     done=1;
                     SDL_RenderClear(renderer);
                     break;

                 }
                 if (x>510 && x<595 && y<662 && y>575) // l'utilisateur a cliqué sur sortir  donc finish prend 1 pour sortir de tous le programme .
                 {
                     done=1;
                     *finish=1;
                     clean_resources(window,renderer,texture);

                     break;
                 }

            }

        }
     }
 }





