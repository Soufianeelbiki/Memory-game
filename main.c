#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <SDL.h>
#include<time.h>
#include<SDL_mixer.h>

#include "game_sdl.h"
#include "authentif.h"

int main( int argc, char * argv[] )
{
/*--------------------------------------PARTIE CONSOLE ---------------------------------------------------*/
    int score[5]={0};
    int grp;int sec=5,f=0;
    char liste_username[5][80];
    logo();
    encadrant();
    membres();
    effacer();
    logo();
    grp=choisir_grp_non();
    joueur_joue(liste_username,grp,&f);

    sleep(1);
    effacer();
    ready();
    while(sec>=0)
    {
        printf("\r\t\t\t\t\t\t\t\t\t Le jeu sera lancer dans %02ds ",sec);
        sleep(1);
        sec--;

    }
/*--------------------------------------------------------------------------------------------------------*/

    srand(time(NULL));
    SDL_Window *window=NULL;
    SDL_Renderer *renderer=NULL;
    SDL_Surface *picture=NULL;

    SDL_Rect dest_rect={0,0,800,800};
    if(SDL_Init(SDL_INIT_VIDEO)!=0)  // initialiser le sdl
    {
        SDL_Log("ERREUR %s\n",SDL_GetError());
        clean_resources(NULL,NULL,NULL);
    }
    window= SDL_CreateWindow("game window",100,100,800,800,0); // creer une fenetre sur le sdl  avec gestion d'erreur
    if (window==NULL)
    {
        SDL_Log("erreur > %s\n",SDL_GetError());
        clean_resources(NULL,NULL,NULL);
        }
   if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
      clean_resources(window,NULL,NULL);
   }

    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // creer le renderer avec gestion d'erreur
    if (renderer==NULL)
    {
        SDL_Log("erreur %s\n",SDL_GetError());
        clean_resources(window,NULL,NULL);

    }

    SDL_SetRenderDrawColor(renderer,0,162,232,SDL_ALPHA_OPAQUE); // donner une couleur au renderer
    picture=SDL_LoadBMP("affichage/memory_game.bmp");
    if (picture==NULL)
        {
            SDL_Log("erreur %s\n",SDL_GetError());
            clean_resources(window,renderer,NULL);
        }

    SDL_Texture *texture=NULL;
    charger(window,renderer,picture,dest_rect,texture);
     SDL_RenderPresent(renderer);
    SDL_Delay(1000);
load_image(window,renderer,picture,texture,0,0,800,800,"affichage/level.bmp",1);
 SDL_Event choisir_niveau;

 int finish=0,x,y,x1,y1,i,j,max=0;
 while(!finish)
 {

     while(SDL_PollEvent(&choisir_niveau))
     {  SDL_GetMouseState(&x1,&y1);
         if( x1>276 && x1<524 && y1>296 && y1<386) // donner des animations pour le jeu .
         {
             load_image(window,renderer,picture,texture,0,0,800,800,"affichage/facile_1.bmp",1);
         }
        else if (x1>276 && x1<524 && y1>429 && y1<519)
                {
            load_image(window,renderer,picture,texture,0,0,800,800,"affichage/normale_1.bmp",1);
                }

        else if(x1>276 && x1<524 && y1>562  && y1<651)
        {
            load_image(window,renderer,picture,texture,0,0,800,800,"affichage/difficile_1.bmp",1);
        }
        else if(x1>27 && x1<77 && y1<782 && y1>732)
        {
            load_image(window,renderer,picture,texture,0,0,800,800,"affichage/aide.bmp",1);
        }
        else
            load_image(window,renderer,picture,texture,0,0,800,800,"affichage/level.bmp",1);

         switch(choisir_niveau.type)
         {
             case SDL_QUIT:
                finish=1;
                clean_resources(window,renderer,texture);
                break;
             case SDL_MOUSEBUTTONDOWN:
                 SDL_GetMouseState(&x,&y);
                SDL_RenderClear(renderer);

                 if( x>276 && x<524 && y>296 && y<386) // l'utilisateur a cliqué sur niveau facile .
                   {
                    system("cls");
                    for(i=0;i<grp;i++)  // initialiser le score lorsque l'utilisateur decide de jouer plusieurs parties .
                    {
                        score[i]=0;
                    }
                    facile(window,renderer,texture,&finish,grp,liste_username,score,f);
                          if (!finish)
                    {  for(i=0;i<grp;i++)
                    {                           enregistrement_score(liste_username[i],score[i]);
                        if (score[i]>max)
                        {
                        max=score[i];
                                j=i;}

                    }

                        joueur_gagnant(window,renderer,picture,texture,j);
                        end_game(window,renderer,picture,texture,&finish);
                   }

                   }
                 if (x>276 && x<524 && y>429 && y<519)
                   {
                    system("cls");
                    for(i=0;i<grp;i++)
                    {
                        score[i]=0;
                    }
                    normale(window,renderer,texture,&finish,grp,liste_username,score,f);
                    if (!finish)
                     {  for(i=0;i<grp;i++)
                    {                           enregistrement_score(liste_username[i],score[i]);
                        if (score[i]>max)
                        {


                        max=score[i];
                                j=i;}

                    }

                        joueur_gagnant(window,renderer,picture,texture,j);
                        end_game(window,renderer,picture,texture,&finish);
                   }

                   }
                 if(x>276 && x<524 && y>562  && y<651)
                   {
                    system("cls");
                    for(i=0;i<grp;i++)
                    {
                        score[i]=0;
                    }
                    difficile(window,renderer,texture,&finish,grp,liste_username,score,f);
                   if (!finish)
                     {  for(i=0;i<grp;i++)
                    {                           enregistrement_score(liste_username[i],score[i]);
                        if (score[i]>max)
                        {


                        max=score[i];
                                j=i;}

                    }

                        joueur_gagnant(window,renderer,picture,texture,j);
                        end_game(window,renderer,picture,texture,&finish);
                   }

                   }
                if(x1>27 && x1<77 && y1<782 && y1>732)
                {
                     system("cls");
                    aide(window,renderer,picture,texture,&finish);
                }
            break;
         }
     }
 }
    return 0;
}





