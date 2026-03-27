#ifndef GENERE_ARBRE_BINAIRE_H
#define GENERE_ARBRE_BINAIRE_H

#include "arbre_binaire.h"

/* Construit un arbre binaire à partir de son codage préfixe (entiers >= 0
 * pour les noeuds, -1 pour les sous-arbres vides), de taille n.
 * codage est un double pointeur pour avancer dans le tableau au fil des
 * appels récursifs.
 * Renvoie 1 en cas de succès, 0 en cas d'échec d'allocation (la mémoire
 * allouée est libérée avant de renvoyer 0). 
 */
int construit_quelconque(Arbre * a, int ** codage, int n);

/* Renvoie le nombre de noeuds présents dans le sous-arbre gauche d'un
 * arbre presque complet à n noeuds. 
 */
int nb_noeuds_gauche(int n);

/* Transforme le parcours en profondeur infixe d'un arbre presque complet
 * à n noeuds en son parcours en profondeur préfixe.
 * prefixe et infixe sont des tableaux de taille n alloués par l'appelant. 
 */
void parcours_infixe_2_prefixe_presque_complet(int * prefixe, int * infixe, int n);

/* Sélectionne aléatoirement l'une des 2^(n-1) formes d'arbre filiforme à
 * n noeuds et transforme le parcours infixe passé en argument en le
 * parcours préfixe de l'arbre sélectionné.
 * prefixe et infixe sont des tableaux de taille n alloués par l'appelant. 
 */
void parcours_infixe_2_prefixe_filiforme_aleatoire(int * prefixe, int * infixe, int n);

/* Étant donné un parcours infixe d'un arbre à n noeuds, détermine
 * aléatoirement l'un des C_n parcours préfixe possibles et remplit le
 * tableau codage avec le codage (entiers >= 0 et -1 pour vide) de l'arbre
 * associé.
 * codage doit être de taille 2*n+1, alloué par l'appelant.
 */
void parcours_infixe_2_prefixe_quelconque_aleatoire(int * codage, int * infixe, int n);

/* Génère aléatoirement un ABR de forme presque complète à taille noeuds.
 * Renvoie 1 en cas de succès, 0 en cas d'échec d'allocation. 
 */
int ABR_presque_complet_alea(Arbre * a, int taille);

/* Génère aléatoirement un non-ABR de forme presque complète à taille noeuds.
 * Renvoie 1 en cas de succès, 0 en cas d'échec (taille < 2 ou allocation). 
 */
int non_ABR_presque_complet_alea(Arbre * a, int taille);

/* Génère aléatoirement un ABR filiforme à taille noeuds.
 * Renvoie 1 en cas de succès, 0 en cas d'échec d'allocation. 
 */
int ABR_filiforme_alea(Arbre * a, int taille);

/* Génère aléatoirement un non-ABR filiforme à taille noeuds.
 * Renvoie 1 en cas de succès, 0 en cas d'échec (taille < 2 ou allocation). 
 */
int non_ABR_filiforme_alea(Arbre * a, int taille);

/* Génère aléatoirement un ABR de forme quelconque à taille noeuds.
 * Renvoie 1 en cas de succès, 0 en cas d'échec d'allocation. 
 */
int ABR_quelconque_alea(Arbre * a, int taille);

/* Génère aléatoirement un non-ABR de forme quelconque à taille noeuds.
 * Renvoie 1 en cas de succès, 0 en cas d'échec (taille < 2 ou allocation). 
 */
int non_ABR_quelconque_alea(Arbre * a, int taille);

#endif