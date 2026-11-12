#include <iostream>
#include <string>
using namespace std;

// Exercice 3 : Table de hachage (cle string -> valeur int)
// Gestion des collisions par chainage (liste chainee dans chaque case)

class Entree {
public:
    string cle;
    int valeur;
    Entree* suivant;

    Entree(const string& c, int v) {
        cle = c;
        valeur = v;
        suivant = nullptr;
    }
};

class TableHachage {
private:
    Entree** table;
    int capacite;
    int nbElements;

    // Fonction de hachage (polynomiale)
    int hacher(const string& cle) const {
        unsigned long h = 0;
        for (char c : cle)
            h = h * 31 + c;
        return h % capacite;
    }

public:
    TableHachage(int cap = 7) {
        capacite = cap;
        nbElements = 0;
        table = new Entree*[capacite];
        for (int i = 0; i < capacite; i++)
            table[i] = nullptr;
    }

    // Insertion (ou mise a jour si la cle existe deja)
    void inserer(const string& cle, int valeur) {
        int idx = hacher(cle);
        Entree* courant = table[idx];

        while (courant != nullptr) {
            if (courant->cle == cle) {
                courant->valeur = valeur;
                return;
            }
            courant = courant->suivant;
        }

        Entree* nouveau = new Entree(cle, valeur);
        nouveau->suivant = table[idx];
        table[idx] = nouveau;
        nbElements++;
    }

    // Recherche : retourne true et remplit 'valeur' si la cle existe
    bool rechercher(const string& cle, int& valeur) const {
        Entree* courant = table[hacher(cle)];

        while (courant != nullptr) {
            if (courant->cle == cle) {
                valeur = courant->valeur;
                return true;
            }
            courant = courant->suivant;
        }
        return false;
    }

    // Suppression d'une cle
    bool supprimer(const string& cle) {
        int idx = hacher(cle);
        Entree* courant = table[idx];
        Entree* precedent = nullptr;

        while (courant != nullptr) {
            if (courant->cle == cle) {
                if (precedent == nullptr)
                    table[idx] = courant->suivant;
                else
                    precedent->suivant = courant->suivant;

                delete courant;
                nbElements--;
                return true;
            }
            precedent = courant;
            courant = courant->suivant;
        }
        return false;
    }

    int taille() const {
        return nbElements;
    }

    void afficher() const {
        for (int i = 0; i < capacite; i++) {
            cout << "[" << i << "] ";
            Entree* courant = table[i];
            while (courant != nullptr) {
                cout << "(" << courant->cle << ", " << courant->valeur << ") -> ";
                courant = courant->suivant;
            }
            cout << "NULL" << endl;
        }
    }

    ~TableHachage() {
        for (int i = 0; i < capacite; i++) {
            Entree* courant = table[i];
            while (courant != nullptr) {
                Entree* temp = courant;
                courant = courant->suivant;
                delete temp;
            }
        }
        delete[] table;
    }
};

int main() {
    TableHachage t;

    t.inserer("Alice", 20);
    t.inserer("Bob", 15);
    t.inserer("Charlie", 18);
    t.inserer("David", 12);
    t.inserer("Eve", 17);

    cout << "Table de hachage :" << endl;
    t.afficher();
    cout << "Taille : " << t.taille() << endl;

    int v;
    if (t.rechercher("Bob", v))
        cout << "Bob trouve, valeur = " << v << endl;

    if (!t.rechercher("Zoe", v))
        cout << "Zoe introuvable" << endl;

    t.inserer("Bob", 19); // mise a jour
    t.rechercher("Bob", v);
    cout << "Bob apres mise a jour = " << v << endl;

    t.supprimer("Alice");
    cout << "Apres suppression de Alice :" << endl;
    t.afficher();
    cout << "Taille : " << t.taille() << endl;

    return 0;
}
