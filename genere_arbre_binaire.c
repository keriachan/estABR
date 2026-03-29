#include "genere_arbre_binaire.h"
#include <stdlib.h>

static void genere_trie(int * tab, int taille) {
    if (taille <= 0) 
        return;
    tab[0] = rand() % 100;
    for (int i = 1; i < taille; i++)
        tab[i] = tab[i-1] + 1 + rand() % 10;
}

static int prefixe_presque_complet_vers_codage(int * codage, int * prefixe, int n) {
    if (n == 0) { 
        codage[0] = -1; 
        return 1; 
    }
    int gauche = nb_noeuds_gauche(n);
    codage[0] = prefixe[0];
    int ecriture = 1;
    ecriture += prefixe_presque_complet_vers_codage(codage + ecriture, prefixe + 1, gauche);
    ecriture += prefixe_presque_complet_vers_codage(codage + ecriture, prefixe + 1 + gauche, n - gauche - 1);
    return ecriture;
}

static int prefixe_filiforme_vers_codage(int * codage, int * prefixe, int * infixe, int n) {
    if (n == 0) { 
        codage[0] = -1; 
        return 1; 
    }
    if (n == 1) {
        codage[0] = prefixe[0];
        codage[1] = -1;
        codage[2] = -1;
        return 3;
    }
    codage[0] = prefixe[0];
    int ecriture = 1;
 
    if (prefixe[0] == infixe[0]) {
        codage[ecriture++] = -1;
        ecriture += prefixe_filiforme_vers_codage(codage + ecriture, prefixe + 1, infixe + 1, n - 1);
    } else {
        ecriture += prefixe_filiforme_vers_codage(codage + ecriture, prefixe + 1, infixe, n - 1);
        codage[ecriture++] = -1;
    }
    return ecriture;
}

static int infixe_vers_codage_quelconque(int * codage, int * infixe, int n) {
    if (n == 0) {
        codage[0] = -1;
        return 1;
    }
    int k = rand() % n;
    codage[0] = infixe[k];
    int gauche = infixe_vers_codage_quelconque(codage + 1, infixe, k);
    int droite = infixe_vers_codage_quelconque(codage + 1 + gauche, infixe + k + 1, n - k - 1);
    return 1 + gauche + droite;
}

int construit_quelconque(Arbre * a, int ** codage, int n) {
    if (n <= 0)
        return 0;
    if (**codage == -1) {
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

int nb_noeuds_gauche(int n) {
    if (n <= 1) 
        return 0;
    int h = 0;
    while ((1 << (h + 1)) <= n) {
        h++;
    }
    int avant_der_gauche = (1 << (h - 1)) - 1;
    int dernier = n - ((1 << h) - 1);
    int max_dernier_gauche = 1 << (h - 1);
    int dernier_gauche = dernier < max_dernier_gauche ? dernier : max_dernier_gauche;
    return avant_der_gauche + dernier_gauche;
}

void parcours_infixe_2_prefixe_presque_complet(int * prefixe, int * infixe, int n) {
    if (n == 0) 
        return;
    int gauche = nb_noeuds_gauche(n);
    prefixe[0] = infixe[gauche];
    parcours_infixe_2_prefixe_presque_complet(prefixe + 1, infixe, gauche);
    parcours_infixe_2_prefixe_presque_complet(prefixe + 1 + gauche, infixe + gauche + 1, n - gauche - 1);
}

void parcours_infixe_2_prefixe_filiforme_aleatoire(int * prefixe, int * infixe, int n) {
    if (n == 0) 
        return;
    if (n == 1) { 
        prefixe[0] = infixe[0]; 
        return; 
    }
    if (rand() % 2 == 0) {
        prefixe[0] = infixe[0];
        parcours_infixe_2_prefixe_filiforme_aleatoire(prefixe + 1, infixe + 1, n - 1);
    } else {
        prefixe[0] = infixe[n - 1];
        parcours_infixe_2_prefixe_filiforme_aleatoire(prefixe + 1, infixe, n - 1);
    }
}

void parcours_infixe_2_prefixe_quelconque_aleatoire(int * codage, int * infixe, int n) {
    infixe_vers_codage_quelconque(codage, infixe, n);
}

int ABR_presque_complet_alea(Arbre * a, int taille) {
    if (taille <= 0) { 
        *a = NULL; 
        return 1; 
    }
    int * infixe  = malloc(taille * sizeof(int));
    int * prefixe = malloc(taille * sizeof(int));
    int * codage  = malloc((2 * taille + 1) * sizeof(int));
    if (!infixe || !prefixe || !codage) {
        free(infixe); 
        free(prefixe); 
        free(codage); 
        return 0;
    }
    genere_trie(infixe, taille);
    parcours_infixe_2_prefixe_presque_complet(prefixe, infixe, taille);
    prefixe_presque_complet_vers_codage(codage, prefixe, taille);
    free(infixe); 
    free(prefixe);
    int * ptr = codage;
    int res = construit_quelconque(a, &ptr, 2 * taille + 1);
    free(codage);
    return res;
}

int non_ABR_presque_complet_alea(Arbre * a, int taille) {
    if (taille < 2) { *a = NULL; return 0; }
    int * infixe  = malloc(taille * sizeof(int));
    int * prefixe = malloc(taille * sizeof(int));
    int * codage  = malloc((2 * taille + 1) * sizeof(int));
    if (!infixe || !prefixe || !codage) {
        free(infixe); 
        free(prefixe); 
        free(codage); 
        return 0;
    }
    genere_trie(infixe, taille);
    int tmp = infixe[0];
    infixe[0] = infixe[taille - 1];
    infixe[taille - 1] = tmp;
    parcours_infixe_2_prefixe_presque_complet(prefixe, infixe, taille);
    prefixe_presque_complet_vers_codage(codage, prefixe, taille);
    free(infixe); 
    free(prefixe);
    int * ptr = codage;
    int res = construit_quelconque(a, &ptr, 2 * taille + 1);
    free(codage);
    return res;
}

int ABR_filiforme_alea(Arbre * a, int taille) {
    if (taille <= 0) { *a = NULL; return 1; }
    int * infixe  = malloc(taille * sizeof(int));
    int * prefixe = malloc(taille * sizeof(int));
    int * codage  = malloc((2 * taille + 1) * sizeof(int));
    if (!infixe || !prefixe || !codage) {
        free(infixe); 
        free(prefixe); 
        free(codage); 
        return 0;
    }
    genere_trie(infixe, taille);
    int * infixe_orig = malloc(taille * sizeof(int));
    if (!infixe_orig) { 
        free(infixe); 
        free(prefixe); 
        free(codage); 
        return 0; 
    }
    for (int i = 0; i < taille; i++) infixe_orig[i] = infixe[i];
    parcours_infixe_2_prefixe_filiforme_aleatoire(prefixe, infixe, taille);
    prefixe_filiforme_vers_codage(codage, prefixe, infixe_orig, taille);
    free(infixe); 
    free(prefixe); 
    free(infixe_orig);
    int * ptr = codage;
    int res = construit_quelconque(a, &ptr, 2 * taille + 1);
    free(codage);
    return res;
}

int non_ABR_filiforme_alea(Arbre * a, int taille) {
    if (taille < 2) { 
        *a = NULL; 
        return 0; 
    }
    int * infixe  = malloc(taille * sizeof(int));
    int * prefixe = malloc(taille * sizeof(int));
    int * codage  = malloc((2 * taille + 1) * sizeof(int));
    if (!infixe || !prefixe || !codage) {
        free(infixe); 
        free(prefixe); 
        free(codage); 
        return 0;
    }
    genere_trie(infixe, taille);
    int tmp = infixe[0];
    infixe[0] = infixe[taille - 1];
    infixe[taille - 1] = tmp;
    int * infixe_orig = malloc(taille * sizeof(int));
    if (!infixe_orig) { 
        free(infixe); 
        free(prefixe); 
        free(codage); 
        return 0; 
    }
    for (int i = 0; i < taille; i++) 
        infixe_orig[i] = infixe[i];
    parcours_infixe_2_prefixe_filiforme_aleatoire(prefixe, infixe, taille);
    prefixe_filiforme_vers_codage(codage, prefixe, infixe_orig, taille);
    free(infixe); 
    free(prefixe); 
    free(infixe_orig);
    int * ptr = codage;
    int res = construit_quelconque(a, &ptr, 2 * taille + 1);
    free(codage);
    return res;
}

int ABR_quelconque_alea(Arbre * a, int taille) {
    if (taille <= 0) { 
        *a = NULL; 
        return 1; 
    }
    int * infixe = malloc(taille * sizeof(int));
    int * codage = malloc((2 * taille + 1) * sizeof(int));
    if (!infixe || !codage) { 
        free(infixe); 
        free(codage); 
        return 0; 
    }
    genere_trie(infixe, taille);
    parcours_infixe_2_prefixe_quelconque_aleatoire(codage, infixe, taille);
    free(infixe);
    int * ptr = codage;
    int res = construit_quelconque(a, &ptr, 2 * taille + 1);
    free(codage);
    return res;
}

int non_ABR_quelconque_alea(Arbre * a, int taille) {
    if (taille < 2) { 
        *a = NULL; 
        return 0; 
    }
    int * infixe = malloc(taille * sizeof(int));
    int * codage = malloc((2 * taille + 1) * sizeof(int));
    if (!infixe || !codage) { 
        free(infixe); 
        free(codage); 
        return 0; 
    }
    genere_trie(infixe, taille);
    int tmp = infixe[0];
    infixe[0] = infixe[taille - 1];
    infixe[taille - 1] = tmp;
    parcours_infixe_2_prefixe_quelconque_aleatoire(codage, infixe, taille);
    free(infixe);
    int * ptr = codage;
    int res = construit_quelconque(a, &ptr, 2 * taille + 1);
    free(codage);
    return res;
}