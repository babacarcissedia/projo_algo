#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#define NMAX 100

typedef char Chaine[32];
typedef struct Mot
{
    Chaine LeMot;
    struct Mot *next;
}Mot;

typedef Mot *pMot;

typedef struct Arbre
{
   char* Element;
   struct Arbre *sag;
   struct Arbre *sad;
}Arbre;

typedef Arbre *pArbre;

typedef struct FA
{
   pArbre A;
   struct FA *suiv;
}FA;

typedef FA *pFA;

typedef struct FileArbre
{
   pFA Tete;
   pFA Queue;
   int taille;
}FileArbre;

//
typedef struct personne
{
  char* prenom;
  struct personne* suiv;
} Personne;

typedef struct inputs
{
  GtkWidget* prenom;
  Personne* liste;
} Inputs;

enum
{
  BMP_COLUMN,
  TEXT_COLUMN,
  N_COLUMN
};


pMot creer_maillon(char*);
pMot saisieliste();
//void afficher_liste(pMot);
pArbre creer_maillon_Arbre(char*);
pArbre saisieArbre(pArbre,Personne*);
//pArbre rechercher_Place(pArbre,Chaine);
void AfficherArbre_Largeur(pArbre);
pArbre ajout_noeud(pArbre,char*);
pArbre tete(FileArbre);
pFA creer_maillon_FA(pArbre);
FileArbre enfiler(FileArbre,pArbre);
FileArbre defiler(FileArbre);
int EstVide(pArbre);
void Insertion(pArbre, gchar *,GtkTreeStore *,GdkPixbuf *,GtkTreeIter );

//
void presentation(GtkWidget* win);
void print_info (GtkWidget* win, gchar* msg);
void print_error (GtkWidget* win, gchar* msg);
void print_warning (GtkWidget* win, gchar* msg);
Personne* ajouter_personne(Personne* liste, Personne* a_ajouter);
Personne* saisir_liste(GtkWidget* wid, Personne* ma_liste);
void submit_form(GtkWidget* wid, Inputs* datas);
Personne* create_cell_personne(char* prenom);
Personne* ajouter_personne(Personne* liste, Personne* a_ajouter);
void afficher_liste_cons(Personne* liste);
void afficher_liste(GtkWidget* wid, Personne* liste);
void afficher_sama_arbre(GtkWidget* wid, Personne* ma_liste);
void afficher_arbre_largeur(GtkWidget* wid, Personne* ma_liste);

