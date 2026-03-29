#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arbre_binaire.h"
#include "est_ABR.h"
#include "genere_arbre_binaire.h"

int tailles[] = {50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000};
int nb_tailles = 9;

int nb_rep = 5;

int taille_max_filiforme = 2000;

int main(void) {
    srand((unsigned int)time(NULL));
    FILE *csv = fopen("mesures.csv", "w");
    if (!csv) {
        printf("erreur ouverture fichier\n");
        return 1;
    }
    fprintf(csv, "Taille;Morphologie;Methode;Nb_visites;Temps\n");
    for (int i = 0; i < nb_tailles; i++) {
        int n = tailles[i];
        printf("taille = %d\n", n);
        for (int rep = 0; rep < nb_rep; rep++) {
            Arbre a = NULL;
            long long nb_visites;
            clock_t t0, t1;
            double temps;
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
            if (n <= taille_max_filiforme) {
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
