
#include <iostream>
using namespace std;

// Classe abstraite
class Paiement {
public:
    // Methode virtuelle pure
    virtual void effectuerPaiement(double montant) = 0;

    // Destructeur virtuel
    virtual ~Paiement() {}
};

// Classe PaiementCarte
class PaiementCarte : public Paiement {
public:
    void effectuerPaiement(double montant) override {
        cout << "Paiement de " << montant
             << " DH par carte bancaire." << endl;
    }
};

// Classe PaiementEspece
class PaiementEspece : public Paiement {
public:
    void effectuerPaiement(double montant) override {
        cout << "Paiement de " << montant
             << " DH en especes." << endl;
    }
};

int main() {

    // Tableau de pointeurs vers Paiement
    Paiement* tab[4];

    // Creation des objets
    tab[0] = new PaiementCarte();
    tab[1] = new PaiementEspece();
    tab[2] = new PaiementCarte();
    tab[3] = new PaiementEspece();

    // Montants des paiements
    double montants[4] = {250, 100, 500, 75};

    // Simulation des paiements
    cout << "===== SIMULATION DES PAIEMENTS =====" << endl;

    for (int i = 0; i < 4; i++) {
        tab[i]->effectuerPaiement(montants[i]);
    }

    // Liberation de la memoire
    for (int i = 0; i < 4; i++) {
        delete tab[i];
    }

    return 0;
}
