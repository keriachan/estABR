#ifndef ARBRE_BINAIRE_H
#define ARBRE_BINAIRE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct noeud {
    int valeur;
    struct noeud *fg, *fd;
} Noeud, *Arbre;

/* Alloue un nouveau noeud en mémoire 
 */
Arbre alloue_noeud(int val);

/* Libere la mémoire utilisé par l'arbre a;
 */
void liberer_arbre(Arbre a);

/* Renvoie la hauteur de l'arbre 
 * (-1 pour un arbre vide) 
 */
int hauteur(Arbre A);

/* Renvoie le nombre total de noeuds dans l'arbre 
 */
int nb_noeud(Arbre A);

/* Renvoie le nombre de feuilles 
 */
int nb_feuille(Arbre A);

/* Renvoie le nombre de noeuds internes (non-feuilles) 
 */
int nb_noeud_interne(Arbre A);

/* Renvoie le nombre de noeuds internes ayant exactement deux fils 
 */
int nb_noeud_interne_ex(Arbre A);

#endif