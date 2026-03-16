#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arbre_binaire.h"
#include "est_ABR.h"

Arbre insere_abr(Arbre a, int val) {
    if (a == NULL) return alloue_noeud(val);
    if (val < a->valeur)
        a->fg = insere_abr(a->fg, val);
    else
        a->fd = insere_abr(a->fd, val);
    return a;
}

Arbre insere_aleat(Arbre a, int val) {
    if (a == NULL) return alloue_noeud(val);
    if (rand() % 2 == 0)
        a->fg = insere_aleat(a->fg, val);
    else
        a->fd = insere_aleat(a->fd, val);
    return a;
}

int main() {
    int n = 100000;
    srand(time(NULL));

    Arbre mon_abr = NULL;
    Arbre mon_arbre_aleat = NULL;
    long long visites_abr_naif = 0, visites_abr_def = 0;
    long long visites_aleat_naif = 0, visites_aleat_def = 0;

    for (int i = 0; i < n; i++) {
        int val = rand() % 10000;
        mon_abr = insere_abr(mon_abr, val);
        mon_arbre_aleat = insere_aleat(mon_arbre_aleat, val);
    }

    printf("Statistiques pour n = %d\n\n", n);
    int res1 = est_abr_naif(mon_abr, &visites_abr_naif);
    printf("Version naive : ABR valide ? %s. Nombre de noeuds visités : %lld\n",res1 ? "OUI" : "NON", visites_abr_naif);
    int res2 = est_abr_definition(mon_abr, &visites_abr_def);
    printf("Version definition : ABR valide ? %s. Nombre de noeuds visités : %lld\n",res2 ? "OUI" : "NON", visites_abr_def);
    printf("\n");
    int res3 = est_abr_naif(mon_arbre_aleat, &visites_aleat_naif);
    printf("Version naive : ABR valide ? %s. Nombre de noeuds visités : %lld\n",res3 ? "OUI" : "NON", visites_aleat_naif);
    int res4 = est_abr_definition(mon_arbre_aleat, &visites_aleat_def);
    printf("Version definition : ABR valide ? %s. Nombre de noeuds visités : %lld\n",res4 ? "OUI" : "NON", visites_aleat_def);
    return 0;
}