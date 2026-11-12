#include <iostream>
using namespace std;

// Exercice 2 : File d'attente (FIFO) implementee avec une liste chainee

class Noeud {
public:
    int valeur;
    Noeud* suivant;

    Noeud(int v) {
        valeur = v;
        suivant = nullptr;
    }
};

class File {
private:
    Noeud* tete;   // element le plus ancien (sortie)
    Noeud* queue;  // element le plus recent (entree)
    int nbElements;

public:
    File() {
        tete = nullptr;
        queue = nullptr;
        nbElements = 0;
    }

    // Enfiler : ajout en fin de file
    void enfiler(int valeur) {
        Noeud* nouveau = new Noeud(valeur);

        if (estVide()) {
            tete = queue = nouveau;
        } else {
            queue->suivant = nouveau;
            queue = nouveau;
        }

        nbElements++;
    }

    // Defiler : retrait du premier element (FIFO)
    int defiler() {
        if (estVide()) {
            cout << "Erreur : la file est vide !" << endl;
            return -1;
        }

        Noeud* temp = tete;
        int valeur = temp->valeur;
        tete = tete->suivant;

        if (tete == nullptr)
            queue = nullptr;

        delete temp;
        nbElements--;
        return valeur;
    }

    // Consulter le premier element sans le retirer
    int premier() const {
        if (estVide()) {
            cout << "Erreur : la file est vide !" << endl;
            return -1;
        }
        return tete->valeur;
    }

    bool estVide() const {
        return tete == nullptr;
    }

    int taille() const {
        return nbElements;
    }

    void afficher() const {
        cout << "Tete -> ";
        Noeud* courant = tete;
        while (courant != nullptr) {
            cout << courant->valeur << " -> ";
            courant = courant->suivant;
        }
        cout << "NULL" << endl;
    }

    ~File() {
        while (!estVide())
            defiler();
    }
};

int main() {
    File f;

    f.enfiler(10);
    f.enfiler(20);
    f.enfiler(30);
    f.enfiler(40);

    cout << "File initiale : ";
    f.afficher();
    cout << "Taille : " << f.taille() << endl;
    cout << "Premier element : " << f.premier() << endl;

    cout << "Defiler : " << f.defiler() << endl;
    cout << "Defiler : " << f.defiler() << endl;

    cout << "Apres 2 defilements : ";
    f.afficher();
    cout << "Taille : " << f.taille() << endl;

    f.enfiler(50);
    cout << "Apres enfiler(50) : ";
    f.afficher();

    // Vider la file pour tester le cas file vide
    while (!f.estVide())
        cout << "Defiler : " << f.defiler() << endl;

    f.defiler(); // test file vide

    return 0;
}
