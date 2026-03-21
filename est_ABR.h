#ifndef EST_ABR_H
#define EST_ABR_H

#include "arbre_binaire.h"

/* Renvoie la plus petite valeur de l'arbre non vide a. */
int abr_min(Arbre a, long long * nb_visites);

/* Renvoie la plus grande valeur de l'arbre non vide a. */
int abr_max(Arbre a, long long * nb_visites);

/* Renvoie 1 si l’arbre binaire a est bien un arbre binaire de recherche,
 * 0 sinon. */
int est_abr_naif(Arbre a, long long * nb_visites);

/* Fonction auxilaire qui parcours l'arbre qu'une seul fois
 * en faisant remonter le min et le max de chaque sous arbres.
 * Elle renvoie 1 si l’arbre binaire a est bien un arbre binaire de recherche,
 * 0 sinon. */
int est_abr_definition_aux(Arbre a, int *min, int *max, long long * nb_visites);

/* Cette fonction utilise la fonction auxiliaire est_abr_definition_aux.
 * Elle renvoie 1 si l’arbre binaire a est bien un arbre binaire de recherche,
 * 0 sinon. */
int est_abr_definition(Arbre a, long long * nb_visites);

/* Détermine si parcours infixe de a est strictement croissant.
 */
int infixe_croissant(Arbre a, Noeud ** dernier_noeud, long long * nb_visites);

/* Cette fonction utilise la fonction auxiliaire infixe_croissant.
 * Elle renvoie 1 si l’arbre binaire a est bien un arbre binaire de recherche,
 * 0 sinon. 
 */
int est_abr_infixe(Arbre a, long long * nb_visites);

#endif
