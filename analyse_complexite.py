import csv
import sys
from collections import defaultdict
import matplotlib.pyplot as plt
import matplotlib.lines as mlines
import numpy as np

CSV_FILE = "mesures.csv"

def lire_csv(fichier):
    """Retourne les données sous la forme d'un dict imbriqué :
       donnees[morphologie][methode] = {"tailles": [...], "nb_visites": [...], "temps": [...]}
    """
    donnees = defaultdict(lambda: defaultdict(lambda: {"tailles": [], "nb_visites": [], "temps": []}))
    try:
        with open(fichier, newline="", encoding="utf-8") as f:
            reader = csv.DictReader(f, delimiter=";")
            for row in reader:
                morpho  = row["Morphologie"]
                methode = row["Methode"]
                taille  = int(row["Taille"])
                nb      = int(row["Nb_visites"])
                temps   = float(row["Temps"])
                donnees[morpho][methode]["tailles"].append(taille)
                donnees[morpho][methode]["nb_visites"].append(nb)
                donnees[morpho][methode]["temps"].append(temps)
    except FileNotFoundError:
        print(f"Erreur : fichier '{fichier}' introuvable.", file=sys.stderr)
        sys.exit(1)
    return donnees


def moyenne_par_taille(tailles, valeurs):
    """Agrège plusieurs mesures pour la même taille en calculant la moyenne."""
    agregat = defaultdict(list)
    for t, v in zip(tailles, valeurs):
        agregat[t].append(v)
    tailles_moy = sorted(agregat.keys())
    valeurs_moy = [np.mean(agregat[t]) for t in tailles_moy]
    return tailles_moy, valeurs_moy

COULEURS_METHODES = {
    "Naif":       "#e74c3c",
    "Definition": "#2980b9",
    "Infixe":     "#27ae60",
}
STYLES_METHODES = {
    "Naif":       "-o",
    "Definition": "--s",
    "Infixe":     "-.^",
}

MORPHOLOGIES_ABR     = ["ABR_presque_complet",     "ABR_filiforme",     "ABR_quelconque"]
MORPHOLOGIES_NON_ABR = ["non_ABR_presque_complet", "non_ABR_filiforme", "non_ABR_quelconque"]

TITRES = {
    "ABR_presque_complet":     "ABR presque complet",
    "non_ABR_presque_complet": "non-ABR presque complet",
    "ABR_filiforme":           "ABR filiforme",
    "non_ABR_filiforme":       "non-ABR filiforme",
    "ABR_quelconque":          "ABR quelconque",
    "non_ABR_quelconque":      "non-ABR quelconque",
}


def plot_methodes(ax, donnees_morpho, metrique, echelle, titre):
    """Trace sur un axe ax les trois méthodes pour une morphologie donnée."""
    for methode in ["Naif", "Definition", "Infixe"]:
        if methode not in donnees_morpho:
            continue
        t, v = moyenne_par_taille(
            donnees_morpho[methode]["tailles"],
            donnees_morpho[methode][metrique]
        )
        ax.plot(t, v,
                STYLES_METHODES[methode],
                color=COULEURS_METHODES[methode],
                label=methode,
                linewidth=1.8,
                markersize=5)

    ax.set_title(titre, fontsize=10, fontweight="bold")
    ax.set_xlabel("Taille (n)")
    ax.set_ylabel("Nœuds visités" if metrique == "nb_visites" else "Temps (s)")
    if echelle == "log":
        ax.set_xscale("log")
        ax.set_yscale("log")
    ax.grid(True, which="both", linestyle=":", alpha=0.5)
    ax.legend(fontsize=8)
    
def figure_toutes_morphologies(donnees, metrique, echelle, nom_fichier):
    """6 sous-graphes (une par morphologie) pour une métrique et une échelle."""
    fig, axes = plt.subplots(2, 3, figsize=(16, 9))
    morphologies = MORPHOLOGIES_ABR + MORPHOLOGIES_NON_ABR
    for ax, morpho in zip(axes.flat, morphologies):
        if morpho in donnees:
            plot_methodes(ax, donnees[morpho], metrique, echelle, TITRES[morpho])
        else:
            ax.set_visible(False)

    unite = "nœuds visités" if metrique == "nb_visites" else "temps d'exécution"
    sup = fig.suptitle(
        f"Comparaison des méthodes – {unite} ({echelle})",
        fontsize=13, fontweight="bold"
    )
    plt.tight_layout(rect=[0, 0, 1, 0.95])
    plt.savefig(nom_fichier, dpi=150, bbox_inches="tight")
    print(f"Figure enregistrée : {nom_fichier}")
    plt.close(fig)

def figure_comparaison_morphologies(donnees, methode, metrique, echelle, nom_fichier):
    """Compare toutes les morphologies pour une seule méthode."""
    fig, ax = plt.subplots(figsize=(10, 6))
    cmap = plt.get_cmap("tab10")
    morphologies = MORPHOLOGIES_ABR + MORPHOLOGIES_NON_ABR
    styles = ["-o", "--s", "-.^", "-D", "--x", ":P"]
    for i, morpho in enumerate(morphologies):
        if morpho not in donnees or methode not in donnees[morpho]:
            continue
        t, v = moyenne_par_taille(
            donnees[morpho][methode]["tailles"],
            donnees[morpho][methode][metrique]
        )
        ax.plot(t, v, styles[i % len(styles)],
                color=cmap(i),
                label=TITRES[morpho],
                linewidth=1.8, markersize=5)
    if echelle == "log":
        ax.set_xscale("log")
        ax.set_yscale("log")
    ax.set_title(f"Méthode '{methode}' – toutes morphologies ({echelle})",
                 fontsize=12, fontweight="bold")
    ax.set_xlabel("Taille (n)")
    ax.set_ylabel("Nœuds visités" if metrique == "nb_visites" else "Temps (s)")
    ax.grid(True, which="both", linestyle=":", alpha=0.5)
    ax.legend(fontsize=8)
    plt.tight_layout()
    plt.savefig(nom_fichier, dpi=150, bbox_inches="tight")
    print(f"Figure enregistrée : {nom_fichier}")
    plt.close(fig)

def main():
    donnees = lire_csv(CSV_FILE)
    if not donnees:
        print("Aucune donnée trouvée dans le CSV.")
        return
    figure_toutes_morphologies(donnees, "nb_visites", "linear", "visites_lineaire.png")
    figure_toutes_morphologies(donnees, "nb_visites", "log", "visites_log.png")
    figure_toutes_morphologies(donnees, "temps", "linear", "temps_lineaire.png")
    figure_toutes_morphologies(donnees, "temps", "log", "temps_log.png")
    for methode in ["Naif", "Definition", "Infixe"]:
        figure_comparaison_morphologies(donnees, methode, "nb_visites", "log", f"morphologies_{methode.lower()}_log.png")
        figure_comparaison_morphologies(donnees, methode, "nb_visites", "linear", f"morphologies_{methode.lower()}_lineaire.png")
    print("\nAnalyse terminée. Fichiers PNG générés dans le répertoire courant.")

if __name__ == "__main__":
    main()