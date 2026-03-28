#include "arbre_binaire.h"

int abr_min(Arbre a){
    if(!(a->fg))
        return a->valeur;
    return abr_min(a->fg);
}

int abr_max(Arbre a){
    if(!(a->fd))
        return a->valeur;
    return abr_max(a->fd);  
}

int est_abr_naif(Arbre a){
    int M, m;
    if (!a)
        return 1;
    if (!est_abr_naif(a->fg) || !est_abr_naif(a->fd))
        return 0;
    if (a->fg){
        M = abr_max(a->fg);
        if (M > a->valeur)
            return 0;
    }
    if (a->fd){
        m = abr_min(a->fd);
        if (m < a->valeur)
            return 0;
    }
    return 1;
}

int est_abr_definition_aux(Arbre a, int *min, int *max){
    int min_tmp, max_tmp;
    if (!a)
        return 1;
    if (a->fg){
        if (!est_abr_definition_aux(a->fg, &min_tmp, &max_tmp) || a->valeur < max_tmp)
            return 0;
        *min = min_tmp;
    } else
        *min = a->valeur;
    if (a->fd){
        if (!est_abr_definition_aux(a->fd, &min_tmp, &max_tmp) || a->valeur > min_tmp)
            return 0;
        *max = max_tmp;
    } else
        *max = a->valeur;
    return 1;
}

int est_abr_definition(Arbre a){
    int min, max;
    return est_abr_definition_aux(a, &min, &max);
}

int infixe_croissant(Arbre a, Noeud ** dernier_noeud){
    if (!a)
        return 1;
    if (!infixe_croissant(a->fg, dernier_noeud))
        return 0;
    if (*dernier_noeud && (*dernier_noeud)->valeur >= a->valeur)
        return 0;
    *dernier_noeud = a;
    return infixe_croissant(a->fd, dernier_noeud);
}

int est_abr_infixe(Arbre a){
    Noeud *tmp = NULL;
    return infixe_croissant(a, &tmp);
}
