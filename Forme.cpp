
#include <iostream>
using namespace std;

// Classe abstraite
class Forme {
public:
    // Méthode virtuelle pure
    virtual double aire() const = 0;

    // Destructeur virtuel
    virtual ~Forme() {}
};

// Classe Cercle
class Cercle : public Forme {
private:
    double rayon;

public:
    Cercle(double r) {
        rayon = r;
    }

    double aire() const override {
        return 3.14 * rayon * rayon;
    }
};

// Classe Rectangle
class Rectangle : public Forme {
private:
    double longueur;
    double largeur;

public:
    Rectangle(double l, double w) {
        longueur = l;
        largeur = w;
    }

    double aire() const override {
        return longueur * largeur;
    }
};

int main() {

    int n;
    cout << "Combien de formes voulez-vous creer ? ";
    cin >> n;

    // Tableau de pointeurs vers Forme
    Forme** tab = new Forme*[n];

    for (int i = 0; i < n; i++) {

        int choix;

        cout << "\n1. Cercle";
        cout << "\n2. Rectangle";
        cout << "\nVotre choix : ";
        cin >> choix;

        if (choix == 1) {
            double rayon;

            cout << "Donner le rayon : ";
            cin >> rayon;

            tab[i] = new Cercle(rayon);
        }
        else if (choix == 2) {
            double longueur, largeur;

            cout << "Donner la longueur : ";
            cin >> longueur;

            cout << "Donner la largeur : ";
            cin >> largeur;

            tab[i] = new Rectangle(longueur, largeur);
        }
        else {
            cout << "Choix invalide !" << endl;
            i--;
        }
    }

    // Affichage des aires
    cout << "\n===== LES AIRES DES FORMES =====\n";

    for (int i = 0; i < n; i++) {
        cout << "Aire de la forme " << i + 1
             << " = " << tab[i]->aire() << endl;
    }

    // Liberation de la memoire
    for (int i = 0; i < n; i++) {
        delete tab[i];
    }

    delete[] tab;

    return 0;
}
