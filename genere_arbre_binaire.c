#include "genere_arbre_binaire.h"

int construit_quelconque(Arbre * a, int ** codage, int n){
    if (n <= 0)
        return 0;
    if (**codage == -1){
        *a = NULL;
        (*codage)++;
        return 1;
    }
    *a = alloue_noeud(**codage);
    if (!*a)
        return 0;
    (*codage)++;
    n--;
    if (!construit_quelconque(&(*a)->fg, codage, n)) {
        free(*a);
        *a = NULL;
        return 0;
    }
    if (!construit_quelconque(&(*a)->fd, codage, n)) {
        liberer_arbre((*a)->fg);
        free(*a);
        *a = NULL;
        return 0;
    }
    return 1;
}