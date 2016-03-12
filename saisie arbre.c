#include "Headers.h"

pArbre creer_maillon_Arbre(char* unMot)
{
     pArbre p;
	 p = (pArbre)malloc(sizeof(Arbre));
	 if (p==NULL)
        printf("Espace insuffisant");
     p->Element = (char*)malloc(sizeof(char)*NMAX);
	 strcpy(p->Element, unMot);
	 p->sag = NULL;
	 p->sad = NULL;
	 return p;
}

pArbre ajout_noeud(pArbre a, char* nom)
{
    if (a==NULL)
        a=creer_maillon_Arbre(nom);
    else
    {
        if(strcmp(a->Element,nom)>0)
        {
            a->sag=ajout_noeud(a->sag,nom);
        }
        else
        {
            a->sad=ajout_noeud(a->sad,nom);
        }
    }
    return a;
}

pArbre saisieArbre(pArbre a ,Personne* M)
{
    Personne* courant=M;
    while(courant!=NULL)
    {
        a=ajout_noeud(a,courant->prenom);
        courant=courant->suiv;
    }
    return a;
}

void AfficherArbre_Largeur(pArbre A)
{
    pArbre x;
    FileArbre file;
    file.Tete=file.Queue=NULL;
    file.taille=0;
    file=enfiler(file,A);
    while(file.taille!=0)
    {
        x=tete(file);
        printf("%s\t",x->Element);
        if(EstVide(x->sag)!=0)
        {
           file=enfiler(file,x->sag);
        }
        if(EstVide(x->sad)!=0)
        {
            file=enfiler(file,x->sad);
    }
        file=defiler(file);
    }
}

int EstVide(pArbre a)
{
    if (a==NULL) return 0;
    return 1;
}


