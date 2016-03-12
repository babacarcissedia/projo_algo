#include "Headers.h"

pArbre tete(FileArbre file)
{
	if (file.taille != 0)
		return (file.Tete)->A;
	else return NULL;
}

pFA creer_maillon_FA(pArbre A)
 {
	 pFA p;
	 p = (pFA)malloc(sizeof(FA));
	 while (p==NULL)
     {
         p=(pFA)malloc(sizeof(FA));
     }
	 p->A=A;
	 p->suiv = NULL;
	 return p;
 }

FileArbre enfiler(FileArbre file, pArbre nom)
{

	pFA maillon=creer_maillon_FA(nom);
	if (file.taille!=0)
	{
	    file.Queue-> suiv =  maillon;
	    file.Queue = maillon;
	    file.taille++;
	}
	else
    {
        file.Tete=file.Queue=maillon;
        file.taille++;
    }
	return file;
}

FileArbre defiler(FileArbre file)
{
	pFA tete;
	if (file.taille != 0)
	{
		tete = file.Tete;
		file.Tete = tete->suiv;
		free(tete);
		file.taille--;
		if (file.taille == 0)
			file.Queue = NULL;
		return file;
	}
	else
		return file;
}
