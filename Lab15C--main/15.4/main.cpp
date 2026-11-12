#include <iostream>
#include <string>
using namespace std;

// Exercice 4 : Pile generique (LIFO) avec les templates C++

template <typename T>
class Pile {
private:
    struct Noeud {
        T valeur;
        Noeud* suivant;

        Noeud(const T& v) : valeur(v), suivant(nullptr) {}
    };

    Noeud* sommet;
    int nbElements;

public:
    Pile() : sommet(nullptr), nbElements(0) {}

    // Empiler : ajout au sommet
    void empiler(const T& valeur) {
        Noeud* nouveau = new Noeud(valeur);
        nouveau->suivant = sommet;
        sommet = nouveau;
        nbElements++;
    }

    // Depiler : retrait du sommet (LIFO)
    T depiler() {
        if (estVide()) {
            cout << "Erreur : la pile est vide !" << endl;
            return T();
        }

        Noeud* temp = sommet;
        T valeur = temp->valeur;
        sommet = sommet->suivant;
        delete temp;
        nbElements--;
        return valeur;
    }

    // Consulter le sommet sans le retirer
    T haut() const {
        if (estVide()) {
            cout << "Erreur : la pile est vide !" << endl;
            return T();
        }
        return sommet->valeur;
    }

    bool estVide() const {
        return sommet == nullptr;
    }

    int taille() const {
        return nbElements;
    }

    void afficher() const {
        cout << "Sommet -> ";
        Noeud* courant = sommet;
        while (courant != nullptr) {
            cout << courant->valeur << " -> ";
            courant = courant->suivant;
        }
        cout << "NULL" << endl;
    }

    ~Pile() {
        while (!estVide())
            depiler();
    }
};

int main() {
    // Pile d'entiers
    Pile<int> pi;
    pi.empiler(10);
    pi.empiler(20);
    pi.empiler(30);

    cout << "Pile<int> : ";
    pi.afficher();
    cout << "Sommet : " << pi.haut() << endl;
    cout << "Depiler : " << pi.depiler() << endl;
    cout << "Apres depilement : ";
    pi.afficher();
    cout << "Taille : " << pi.taille() << endl;

    // Pile de chaines
    Pile<string> ps;
    ps.empiler("C++");
    ps.empiler("est");
    ps.empiler("genial");

    cout << "\nPile<string> : ";
    ps.afficher();
    while (!ps.estVide())
        cout << "Depiler : " << ps.depiler() << endl;
    ps.depiler(); // test pile vide

    // Pile de doubles
    Pile<double> pd;
    pd.empiler(3.14);
    pd.empiler(2.71);
    cout << "\nPile<double> : ";
    pd.afficher();

    return 0;
}
