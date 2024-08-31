#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int code;
    char nom[50];
    int quantite;
    int quantiteInitiale; // Quantité initiale ajoutée
    float prix;
    float prixTTC;
    time_t dateAchat;
} Produit;
// Tableau pour stocker les produits
Produit produits[1000];
int nbProduits = 0;

void ajouterProduit() {
    // déclare une variable p de type Produit
     Produit p;
    // Ajouter le produit au tableau
   
                printf("Entrez le code du produit : ");
                scanf("%d", &p.code);
                printf("Entrez le nom du produit : ");
                scanf(" %[^\n]s",&p.nom);
                printf("Entrez la quantité : ");
                scanf("%d", &p.quantite);
                p.quantiteInitiale = p.quantite; // Stocker la quantité initiale
                printf("Entrez le prix : ");
                scanf("%f", &p.prix);
                p.prixTTC = p.prix + (p.prix * 0.15);
                 produits[nbProduits]=p;
    nbProduits++;
}

void ajouterPlusieursProduits() {
    // Demander à l'utilisateur de saisir plusieurs produits
    int n;
    printf("Entrez le nombre de produits à ajouter : ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
       
        ajouterProduit();
    }
}
void modifierProduit() {
    int code;
    printf("Entrez le code du produit à modifier : ");
    scanf("%d", &code);
    
    for (int i = 0; i < nbProduits; i++) {
        if (produits[i].code == code) {
            printf("Modification du produit '%s'\n", produits[i].nom);

            // Modifier le nom
            printf("Entrez le nouveau nom du produit (ou appuyez sur Entrée pour conserver l'actuel) : ");
            scanf(" %[^\n]s", produits[i].nom); // Lire la nouvelle entrée

            // Modifier la quantité
            printf("Entrez la nouvelle quantité (actuelle : %d) : ", produits[i].quantite);
            int nouvelleQuantite;
            scanf("%d", &nouvelleQuantite);
            produits[i].quantite = nouvelleQuantite;

            // Modifier le prix
            printf("Entrez le nouveau prix (actuel : %.2f) : ", produits[i].prix);
            float nouveauPrix;
            scanf("%f", &nouveauPrix);
            produits[i].prix = nouveauPrix;
            produits[i].prixTTC = nouveauPrix + (nouveauPrix * 0.15);

            printf("Produit modifié avec succès !\n");
            return;
        }
    }
    printf("Produit avec code %d non trouvé.\n", code);
}

void listerProduits() {
    int choix;
    printf("Trier par (1) Nom ou (2) Prix ou (3) Afficher tous : ");
    scanf("%d", &choix);
    if (choix == 3){
    /* Afficher les produits
    for (int i = 0; i < nbProduits; i++) {
        printf("Nom : %s, Prix : %.2f, Prix TTC : %.2f\n", produits[i].nom, produits[i].prix, produits[i].prixTTC);
    }*/
}
   else if (choix == 1) {
        // Trier par nom
        for (int i = 0; i < nbProduits - 1; i++) {
            for (int j = i + 1; j < nbProduits; j++) {
                if (strcmp(produits[i].nom, produits[j].nom) > 0) {
                    Produit temp = produits[i];
                    produits[i] = produits[j];
                    produits[j] = temp;
                }
            }
        }
    } else if (choix == 2) {
        // Trier par prix
        for (int i = 0; i < nbProduits - 1; i++) {
            for (int j = i + 1; j < nbProduits; j++) {
                if (produits[i].prix > produits[j].prix) {
                    Produit temp = produits[i];
                    produits[i] = produits[j];
                    produits[j] = temp;
                }
            }
        }
    }

    // Afficher les produits après le tri
    printf("Liste des produits :\n");
    for (int i = 0; i < nbProduits; i++) {
        printf("Nom : %s, Prix : %.2f, Prix TTC : %.2f\n", produits[i].nom, produits[i].prix, produits[i].prixTTC);
    }
}



void acheterProduit() {
    // Demander à l'utilisateur de saisir le code du produit et la quantité à déduire
    int code;
    int quantite;
    printf("Entrez le code du produit : ");
    scanf("%d", &code);
    printf("Entrez la quantité à déduire : ");
    scanf("%d", &quantite);
    // Mettre à jour la quantité du produit
    for (int i = 0; i < nbProduits; i++) {
        if (produits[i].code == code) {
            if (produits[i].quantite >= quantite) {
                produits[i].quantite -= quantite;
                 // Enregistrer la date d'achat
                produits[i].dateAchat = time(NULL); // Obtient le temps actuel en secondes
                printf("Achat réussi !\n");
                 printf("Prix TTC : %.2f\n", produits[i].prixTTC);
                printf("Date d'achat : %s", ctime(&produits[i].dateAchat));
            } else {
                printf("Erreur : quantité insuffisante en stock.\n");
            }
            break;
        }
    }
}

void rechercherProduits() {
    // Demander à l'utilisateur de saisir le code ou la quantité du produit à rechercher
    int choix;
    printf("Rechercher par (1) Code ou (2) Quantité : ");
    scanf("%d", &choix);
    if (choix == 1) {
        int code;
        printf("Entrez le code du produit : ");
        scanf("%d", &code);
        // Rechercher le produit par code
        for (int i = 0; i < nbProduits; i++) {
            if (produits[i].code == code) {
                printf("Nom : %s, Prix : %.2f, Prix TTC : %.2f, Quantité : %d\n", produits[i].nom, produits[i].prix, produits[i].prixTTC, produits[i].quantite);
                break;
            }
        }
    } else if (choix == 2) {
        int quantite;
        printf("Entrez la quantité du produit : ");
        scanf("%d", &quantite);
        // Rechercher les produits par quantité
        for (int i = 0; i < nbProduits; i++) {
            if (produits[i].quantite == quantite) {
                printf("Nom : %s, Prix : %.2f, Prix TTC : %.2f, Code : %d\n", produits[i].nom, produits[i].prix, produits[i].prixTTC, produits[i].code);
            }
        }
    }
}

void etatDuStock() {
    // Afficher les produits dont la quantité est inférieure à 3
    for (int i = 0; i < nbProduits; i++) {
        if (produits[i].quantite < 3) {
            printf("Nom : %s, Prix : %.2f, Prix TTC : %.2f, Quantité : %d\n", produits[i].nom, produits[i].prix, produits[i].prixTTC, produits[i].quantite);
        }
    }
}

void alimenterStock() {
    // Demander à l'utilisateur de saisir le code du produit et la quantité à ajouter
    int code;
    int quantite;
    printf("Entrez le code du produit : ");
    scanf("%d", &code);
    printf("Entrez la quantité à ajouter : ");
    scanf("%d", &quantite);
    // Mettre à jour la quantité du produit
    for (int i = 0; i < nbProduits; i++) {
        if (produits[i].code == code) {
            produits[i].quantite += quantite;
            printf("Stock mis à jour !\n");
            break;
        }
    }
}

void supprimerProduit() {
    int code;
    printf("Entrez le code du produit à supprimer : ");
    scanf("%d", &code);

    // Rechercher le produit par code
    int index = -1;
    for (int i = 0; i < nbProduits; i++) {
        if (produits[i].code == code) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Produit avec code %d non trouvé.\n", code);
        return;
    }

    // Déplacer les produits suivants
    for (int i = index; i < nbProduits - 1; i++) {
        produits[i] = produits[i + 1];
    }

    // Réduire le nombre de produits
    nbProduits--;

    printf("Produit supprimé avec succès !\n");
}

void statistiqueVente() {
    float total = 0.0;
    float prixMax = 0.0;
    float prixMin = 100000.0;  // Initialisé à une valeur élevée
    int nombreVentes = 0;

    // Obtenir la date actuelle
    time_t maintenant = time(NULL);
    struct tm *infoTemps = localtime(&maintenant);

    // Parcourir les produits
    for (int i = 0; i < nbProduits; i++) {
        if (produits[i].quantite < produits[i].quantiteInitiale) { // Si le produit a été vendu
            
            // Comparer la date d'achat avec la date actuelle
            struct tm *dateAchat = localtime(&produits[i].dateAchat);

            if (infoTemps->tm_year == dateAchat->tm_year &&
                infoTemps->tm_mon == dateAchat->tm_mon &&
                infoTemps->tm_mday == dateAchat->tm_mday) {
                
                float montantVente = produits[i].prixTTC * (produits[i].quantiteInitiale - produits[i].quantite);
                total += montantVente;
                nombreVentes++;

                if (produits[i].prixTTC > prixMax) {
                    prixMax = produits[i].prixTTC;
                }
                if (produits[i].prixTTC < prixMin) {
                    prixMin = produits[i].prixTTC;
                }
            }
        }
    }

    // Afficher les statistiques
    printf("Total des ventes (aujourd'hui) : %.2f\n", total);
    if (nombreVentes > 0) {
        printf("Moyenne des prix vendus (aujourd'hui) : %.2f\n", total / nombreVentes);
        printf("Prix max vendu (aujourd'hui) : %.2f\n", prixMax);
        printf("Prix min vendu (aujourd'hui) : %.2f\n", prixMin);
    } else {
        printf("Aucune vente n'a été enregistrée aujourd'hui.\n");
    }
}
int main() {
    int choix;

    do {
        printf("1. Ajouter un produit\n");
        printf("2. Ajouter plusieurs produits\n");
        printf("3. Lister les produits\n");
        printf("4. Acheter un produit\n");
        printf("5. Rechercher des produits\n");
        printf("6. État du stock\n");
        printf("7. Alimenter le stock\n");
        printf("8. Supprimer un produit\n");
        printf("9. Statistique des ventes\n");
        printf("10. modifier\n");
        printf("10. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterProduit();
                break;
            case 2:
                ajouterPlusieursProduits();
                break;
            case 3:
                listerProduits();
                break;
            case 4:
                acheterProduit();
                break;
            case 5:
                rechercherProduits();
                break;
            case 6:
                etatDuStock();
                break;
            case 7:
                alimenterStock();
                break;
            case 8:
                supprimerProduit();
                break;
            case 9:
                statistiqueVente();
                break;
            case 10:
                modifierProduit();
                break;
            case 11:
                return 0;
            default:
                printf("Choix invalide\n");
        }
    } while (1);

    return 0;
}
