#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <SDL.h>
#include<time.h>
#include<SDL_mixer.h>
#ifndef game_sdl_H
#define game_sdl_H

void tableau_de_bord(char nom_joueur[80],char player[80],int score);

int passer_tour(int tour,int nb_grp);

// le max non inclus
int posy ( int y, int n);

int posx (int x);

int position (int x, int y,int n);

void aleatoire_non_repete(int a[], int n, int max);


void fonc_image_aleatoire(char scr_img_aleatoire[24][50],char src_img[24][50],int niveau);


void clean_resources(SDL_Window *w,SDL_Renderer *r,SDL_Texture *t);

void charger(SDL_Window *window,SDL_Renderer *renderer,SDL_Surface *surface,SDL_Rect dest,SDL_Texture *t);

 void load_image(SDL_Window *window,SDL_Renderer *renderer,SDL_Surface *image,SDL_Texture *texture,int x1,int y1,int h,int w,char source[30],int level);

 void intialiser(SDL_Window *window,SDL_Renderer *renderer,SDL_Surface *image,SDL_Texture *texture,int x1,int y1,int h,int w,int level);


void joueur_gagnant(SDL_Window *window,SDL_Renderer *renderer,SDL_Surface *image,SDL_Texture *texture,int j);

  void difficile(SDL_Window *window,SDL_Renderer *renderer,SDL_Texture *texture,int *finish,int groupe,char nom_joueur[5][80],int score[5],int f );


 void normale(SDL_Window *window,SDL_Renderer *renderer,SDL_Texture *texture,int *finish,int groupe,char nom_joueur[5][80],int score[5],int f);
 void facile(SDL_Window *window,SDL_Renderer *renderer,SDL_Texture *texture,int *finish,int groupe, char nom_joueur[5][80],int score[5],int f);

void aide(SDL_Window *window,SDL_Renderer *renderer,SDL_Surface *picture,SDL_Texture *texture,int *finish);

void end_game(SDL_Window *window,SDL_Renderer *renderer,SDL_Surface *image,SDL_Texture *texture,int *finish);

#endif

