
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Classe abstraite NoeudFichier
class NoeudFichier {
protected:
    string nomFichier;

public:
    NoeudFichier(string nom) {
        nomFichier = nom;
    }

    // Methode normale : retourne le nom
    string nom() const {
        return nomFichier;
    }

    // Methode virtuelle pure
    virtual int taille() const = 0;

    // Destructeur virtuel
    virtual ~NoeudFichier() {}
};

// Classe Fichier
class Fichier : public NoeudFichier {
private:
    int tailleFichier;

public:
    Fichier(string nom, int taille)
        : NoeudFichier(nom) {
        tailleFichier = taille;
    }

    // Implementation de la methode pure
    int taille() const override {
        return tailleFichier;
    }
};

// Classe Dossier
class Dossier : public NoeudFichier {
private:
    vector<NoeudFichier*> enfants;

public:
    Dossier(string nom) : NoeudFichier(nom) {}

    // Ajouter un fichier ou un sous-dossier
    void ajouter(NoeudFichier* noeud) {
        enfants.push_back(noeud);
    }

    // Calculer la taille totale du dossier
    int taille() const override {
        int total = 0;

        for (int i = 0; i < enfants.size(); i++) {
            total += enfants[i]->taille();
        }

        return total;
    }

    // Acceder aux enfants
    const vector<NoeudFichier*>& getEnfants() const {
        return enfants;
    }

    // Destructeur : liberer les enfants
    ~Dossier() {
        for (int i = 0; i < enfants.size(); i++) {
            delete enfants[i];
        }
    }
};

// Creation recursive d'un fichier ou dossier
NoeudFichier* creerNoeud(vector<Dossier*>& dossiers) {

    int choix;
    string nom;

    cout << "\n1. Fichier";
    cout << "\n2. Dossier";
    cout << "\nVotre choix : ";
    cin >> choix;

    cout << "Donner le nom : ";
    cin >> nom;

    if (choix == 1) {

        int taille;

        cout << "Donner la taille (Ko) : ";
        cin >> taille;

        return new Fichier(nom, taille);
    }
    else if (choix == 2) {

        Dossier* d = new Dossier(nom);

        // Enregistrer le dossier pour le selectionner plus tard
        dossiers.push_back(d);

        int n;

        cout << "Combien d'elements dans ce dossier ? ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "\nElement " << i + 1 << " : ";
            d->ajouter(creerNoeud(dossiers));
        }

        return d;
    }

    cout << "Choix invalide !" << endl;
    return nullptr;
}

// Afficher la structure hierarchique
void afficherStructure(const NoeudFichier* noeud, int niveau = 0) {

    for (int i = 0; i < niveau; i++) {
        cout << "  ";
    }

    cout << "- " << noeud->nom();

    const Dossier* d = dynamic_cast<const Dossier*>(noeud);

    if (d != nullptr) {
        cout << " (Dossier, " << d->taille() << " Ko)" << endl;

        for (int i = 0; i < d->getEnfants().size(); i++) {
            afficherStructure(d->getEnfants()[i], niveau + 1);
        }
    }
    else {
        cout << " (Fichier, " << noeud->taille() << " Ko)" << endl;
    }
}

int main() {

    vector<Dossier*> dossiers;

    // Creation du dossier racine
    string nomRacine;

    cout << "Nom du dossier principal : ";
    cin >> nomRacine;

    Dossier* racine = new Dossier(nomRacine);

    dossiers.push_back(racine);

    int n;

    cout << "Combien d'elements dans le dossier principal ? ";
    cin >> n;

    // Creation des elements
    for (int i = 0; i < n; i++) {
        cout << "\nElement " << i + 1 << " : ";
        racine->ajouter(creerNoeud(dossiers));
    }

    // Afficher toute la structure
    cout << "\n===== STRUCTURE DES FICHIERS =====\n";
    afficherStructure(racine);

    // Selection d'un dossier
    cout << "\n===== SELECTION D'UN DOSSIER =====\n";

    for (int i = 0; i < dossiers.size(); i++) {
        cout << i + 1 << ". " << dossiers[i]->nom() << endl;
    }

    int choix;

    cout << "Choisir un dossier : ";
    cin >> choix;

    if (choix >= 1 && choix <= dossiers.size()) {

        cout << "\nDossier : " << dossiers[choix - 1]->nom() << endl;

        cout << "Taille totale : "
             << dossiers[choix - 1]->taille()
             << " Ko" << endl;
    }
    else {
        cout << "Selection invalide !" << endl;
    }

    // Liberation de toute la structure
    delete racine;

    return 0;
}
