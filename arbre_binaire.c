#include "arbre_binaire.h"

Arbre alloue_noeud(int val){
    Noeud * A = malloc(sizeof(Noeud));
    if (A){
        A->valeur = val;
        A->fg = NULL;
        A->fd = NULL;
    }
    return A;
}

void liberer_arbre(Arbre a){
    if (!a)
        return;
    liberer_arbre(a->fg);
    liberer_arbre(a->fd);
    free(a);
}

int hauteur(Arbre A){
    if (!A)
        return -1;
    else {
        int h1 = hauteur(A->fg), h2 = hauteur(A->fd);
        return 1 + ((h1 > h2) ? h1 : h2);
    }
}

int nb_noeud(Arbre A){
    if (!A)
        return 0;
    else
        return 1 + nb_noeud(A->fg) + nb_noeud(A->fd);
}

int nb_feuille(Arbre A){
    if (!A)
        return 0;
    if (!(A->fg) && !(A->fd))
        return 1;
    return nb_feuille(A->fg) + nb_feuille(A->fd);
}

int nb_noeud_interne(Arbre A){
    return nb_noeud(A) - nb_feuille(A);
}

int nb_noeud_interne_ex(Arbre A){
    if (!A)
        return 0;
    if (!(A->fg) || !(A->fd))
        return nb_noeud_interne_ex(A->fg) + nb_noeud_interne_ex(A->fd);
    return 1 + nb_noeud_interne_ex(A->fg) + nb_noeud_interne_ex(A->fd);
}