#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arbre_binaire.h"
#include "est_ABR.h"
#include "genere_arbre_binaire.h"

/* tailles qu'on va tester */
int tailles[] = {50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000};
int nb_tailles = 9;

/* on repete 5 fois chaque mesure pour avoir une moyenne */
int nb_rep = 5;

/* les filiformes on peut pas aller trop grand sinon stack overflow */
int taille_max_filiforme = 2000;

int main(void) {
    srand((unsigned int)time(NULL));

    /* ouverture du fichier csv */
    FILE *csv = fopen("mesures.csv", "w");
    if (!csv) {
        printf("erreur ouverture fichier\n");
        return 1;
    }

    /* premiere ligne du csv */
    fprintf(csv, "Taille;Morphologie;Methode;Nb_visites;Temps\n");

    for (int i = 0; i < nb_tailles; i++) {
        int n = tailles[i];
        printf("taille = %d\n", n);

        /* on repete nb_rep fois pour lisser les resultats */
        for (int rep = 0; rep < nb_rep; rep++) {

            Arbre a = NULL;
            long long nb_visites;
            clock_t t0, t1;
            double temps;

            /* --- ABR presque complet --- */
            ABR_presque_complet_alea(&a, n);

            nb_visites = 0;
            t0 = clock();
            est_abr_naif(a, &nb_visites);
            t1 = clock();
            temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
            fprintf(csv, "%d;ABR_presque_complet;Naif;%lld;%.9f\n", n, nb_visites, temps);

            nb_visites = 0;
            t0 = clock();
            est_abr_definition(a, &nb_visites);
            t1 = clock();
            temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
            fprintf(csv, "%d;ABR_presque_complet;Definition;%lld;%.9f\n", n, nb_visites, temps);

            nb_visites = 0;
            t0 = clock();
            est_abr_infixe(a, &nb_visites);
            t1 = clock();
            temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
            fprintf(csv, "%d;ABR_presque_complet;Infixe;%lld;%.9f\n", n, nb_visites, temps);

            liberer_arbre(a);
            a = NULL;

            /* --- non ABR presque complet --- */
            non_ABR_presque_complet_alea(&a, n);

            nb_visites = 0;
            t0 = clock();
            est_abr_naif(a, &nb_visites);
            t1 = clock();
            temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
            fprintf(csv, "%d;non_ABR_presque_complet;Naif;%lld;%.9f\n", n, nb_visites, temps);

            nb_visites = 0;
            t0 = clock();
            est_abr_definition(a, &nb_visites);
            t1 = clock();
            temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
            fprintf(csv, "%d;non_ABR_presque_complet;Definition;%lld;%.9f\n", n, nb_visites, temps);

            nb_visites = 0;
            t0 = clock();
            est_abr_infixe(a, &nb_visites);
            t1 = clock();
            temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
            fprintf(csv, "%d;non_ABR_presque_complet;Infixe;%lld;%.9f\n", n, nb_visites, temps);

            liberer_arbre(a);
            a = NULL;

            /* --- filiformes : seulement si n pas trop grand --- */
            if (n <= taille_max_filiforme) {

                /* ABR filiforme */
                ABR_filiforme_alea(&a, n);

                nb_visites = 0;
                t0 = clock();
                est_abr_naif(a, &nb_visites);
                t1 = clock();
                temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
                fprintf(csv, "%d;ABR_filiforme;Naif;%lld;%.9f\n", n, nb_visites, temps);

                nb_visites = 0;
                t0 = clock();
                est_abr_definition(a, &nb_visites);
                t1 = clock();
                temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
                fprintf(csv, "%d;ABR_filiforme;Definition;%lld;%.9f\n", n, nb_visites, temps);

                nb_visites = 0;
                t0 = clock();
                est_abr_infixe(a, &nb_visites);
                t1 = clock();
                temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
                fprintf(csv, "%d;ABR_filiforme;Infixe;%lld;%.9f\n", n, nb_visites, temps);

                liberer_arbre(a);
                a = NULL;

                /* non ABR filiforme */
                non_ABR_filiforme_alea(&a, n);

                nb_visites = 0;
                t0 = clock();
                est_abr_naif(a, &nb_visites);
                t1 = clock();
                temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
                fprintf(csv, "%d;non_ABR_filiforme;Naif;%lld;%.9f\n", n, nb_visites, temps);

                nb_visites = 0;
                t0 = clock();
                est_abr_definition(a, &nb_visites);
                t1 = clock();
                temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
                fprintf(csv, "%d;non_ABR_filiforme;Definition;%lld;%.9f\n", n, nb_visites, temps);

                nb_visites = 0;
                t0 = clock();
                est_abr_infixe(a, &nb_visites);
                t1 = clock();
                temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
                fprintf(csv, "%d;non_ABR_filiforme;Infixe;%lld;%.9f\n", n, nb_visites, temps);

                liberer_arbre(a);
                a = NULL;
            }

            /* --- ABR quelconque --- */
            ABR_quelconque_alea(&a, n);

            nb_visites = 0;
            t0 = clock();
            est_abr_naif(a, &nb_visites);
            t1 = clock();
            temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
            fprintf(csv, "%d;ABR_quelconque;Naif;%lld;%.9f\n", n, nb_visites, temps);

            nb_visites = 0;
            t0 = clock();
            est_abr_definition(a, &nb_visites);
            t1 = clock();
            temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
            fprintf(csv, "%d;ABR_quelconque;Definition;%lld;%.9f\n", n, nb_visites, temps);

            nb_visites = 0;
            t0 = clock();
            est_abr_infixe(a, &nb_visites);
            t1 = clock();
            temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
            fprintf(csv, "%d;ABR_quelconque;Infixe;%lld;%.9f\n", n, nb_visites, temps);

            liberer_arbre(a);
            a = NULL;

            /* --- non ABR quelconque --- */
            non_ABR_quelconque_alea(&a, n);

            nb_visites = 0;
            t0 = clock();
            est_abr_naif(a, &nb_visites);
            t1 = clock();
            temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
            fprintf(csv, "%d;non_ABR_quelconque;Naif;%lld;%.9f\n", n, nb_visites, temps);

            nb_visites = 0;
            t0 = clock();
            est_abr_definition(a, &nb_visites);
            t1 = clock();
            temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
            fprintf(csv, "%d;non_ABR_quelconque;Definition;%lld;%.9f\n", n, nb_visites, temps);

            nb_visites = 0;
            t0 = clock();
            est_abr_infixe(a, &nb_visites);
            t1 = clock();
            temps = (double)(t1 - t0) / CLOCKS_PER_SEC;
            fprintf(csv, "%d;non_ABR_quelconque;Infixe;%lld;%.9f\n", n, nb_visites, temps);

            liberer_arbre(a);
            a = NULL;
        }
    }

    fclose(csv);
    printf("mesures.csv genere\n");
    return 0;
}
