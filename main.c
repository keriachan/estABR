#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arbre_binaire.h"
#include "est_ABR.h"
#include "genere_arbre_binaire.h"

#define NB_MORPHOLOGIES 6
#define NB_METHODES     3
#define NB_REPETITIONS  5 

static const char * MORPHOLOGIES[NB_MORPHOLOGIES] = {
    "ABR_presque_complet",
    "non_ABR_presque_complet",
    "ABR_filiforme",
    "non_ABR_filiforme",
    "ABR_quelconque",
    "non_ABR_quelconque"
};

static const char * METHODES[NB_METHODES] = {
    "Naif",
    "Definition",
    "Infixe"
};

static const int TAILLES[] = {
    50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000
};
static const int NB_TAILLES = 9;
static const int TAILLE_MAX_FILIFORME = 2000;
typedef int (*fonc_gen)(Arbre *, int);

static fonc_gen GENERATEURS[NB_MORPHOLOGIES] = {
    ABR_presque_complet_alea,
    non_ABR_presque_complet_alea,
    ABR_filiforme_alea,
    non_ABR_filiforme_alea,
    ABR_quelconque_alea,
    non_ABR_quelconque_alea
};

static int est_filiforme(int m) {
    return (m == 2 || m == 3);
}

int main(void) {
    srand((unsigned int)time(NULL));

    FILE * csv = fopen("mesures.csv", "w");
    if (!csv) {
        fprintf(stderr, "Impossible d'ouvrir mesures.csv en écriture.\n");
        return EXIT_FAILURE;
    }
    fprintf(csv, "Taille;Morphologie;Methode;Nb_visites;Temps\n");
    printf("Génération des mesures en cours...\n");

    for (int ti = 0; ti < NB_TAILLES; ti++) {
        int n = TAILLES[ti];
        printf("  taille = %d\n", n);

        for (int m = 0; m < NB_MORPHOLOGIES; m++) {
            if (est_filiforme(m) && n > TAILLE_MAX_FILIFORME)
                continue;
            for (int rep = 0; rep < NB_REPETITIONS; rep++) {
                Arbre a = NULL;
                if (!GENERATEURS[m](&a, n)) {
                    fprintf(stderr, "  [WARN] Echec de génération pour %s, taille=%d, rep=%d\n", MORPHOLOGIES[m], n, rep);
                    continue;
                }

                /* --- Méthode 0 : Naïf --- */
                {
                    long long nb = 0;
                    clock_t t0 = clock();
                    est_abr_naif(a, &nb);
                    clock_t t1 = clock();
                    double temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
                    fprintf(csv, "%d;%s;%s;%lld;%.9f\n",
                            n, MORPHOLOGIES[m], METHODES[0], nb, temps);
                }

                /* --- Méthode 1 : Définition --- */
                {
                    long long nb = 0;
                    clock_t t0 = clock();
                    est_abr_definition(a, &nb);
                    clock_t t1 = clock();
                    double temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
                    fprintf(csv, "%d;%s;%s;%lld;%.9f\n",
                            n, MORPHOLOGIES[m], METHODES[1], nb, temps);
                }

                /* --- Méthode 2 : Infixe --- */
                {
                    long long nb = 0;
                    clock_t t0 = clock();
                    est_abr_infixe(a, &nb);
                    clock_t t1 = clock();
                    double temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
                    fprintf(csv, "%d;%s;%s;%lld;%.9f\n",
                            n, MORPHOLOGIES[m], METHODES[2], nb, temps);
                }

                liberer_arbre(a);
            }
        }
    }
    fclose(csv);
    printf("Mesures enregistrées dans mesures.csv\n");
    return EXIT_SUCCESS;
}