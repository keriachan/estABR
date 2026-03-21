#include "est_ABR.h"

int abr_min(Arbre a, long long * nb_visites){
    (*nb_visites)++;
    if(!(a->fg))
        return a->valeur;
    return abr_min(a->fg, nb_visites);  
}

int abr_max(Arbre a, long long * nb_visites){
    (*nb_visites)++;
    if(!(a->fd))
        return a->valeur;
    return abr_max(a->fd, nb_visites);  
}

int est_abr_naif(Arbre a, long long * nb_visites){
    int M, m;
    if (!a)
        return 1;
    (*nb_visites)++;
    if (!est_abr_naif(a->fg, nb_visites) || !est_abr_naif(a->fd, nb_visites))
        return 0;
    if (a->fg){
        M = abr_max(a->fg, nb_visites);
        if (M > a->valeur)
            return 0;
    }
    if (a->fd){
        m = abr_min(a->fd, nb_visites);
        if (m < a->valeur)
            return 0;
    }
    return 1;
}

int est_abr_definition_aux(Arbre a, int *min, int *max, long long * nb_visites){
    int min_tmp, max_tmp;
    if (!a)
        return 1;
    (*nb_visites)++;
    if (a->fg){
        if (!est_abr_definition_aux(a->fg, &min_tmp, &max_tmp, nb_visites) || a->valeur < max_tmp)
            return 0;
        *min = min_tmp;
    } else
        *min = a->valeur;
    if (a->fd){
        if (!est_abr_definition_aux(a->fd, &min_tmp, &max_tmp, nb_visites) || a->valeur > min_tmp)
            return 0;
        *max = max_tmp;
    } else
        *max = a->valeur;
    return 1;
}

int est_abr_definition(Arbre a, long long * nb_visites){
    int min, max;
    return est_abr_definition_aux(a, &min, &max, nb_visites);
}

int infixe_croissant(Arbre a, Noeud ** dernier_noeud, long long * nb_visites){
    if (!a)
        return 1;
    (*nb_visites)++;
    if (!infixe_croissant(a->fg, dernier_noeud, nb_visites))
        return 0;
    if (*dernier_noeud && (*dernier_noeud)->valeur >= a->valeur)
        return 0;
    *dernier_noeud = a;
    return infixe_croissant(a->fd, dernier_noeud, nb_visites);
}

int est_abr_infixe(Arbre a, long long * nb_visites){
    Noeud *tmp = NULL;
    return infixe_croissant(a, &tmp, nb_visites);
}