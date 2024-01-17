#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct intrare {
    char element;
    int aparitii;
};

struct nod {
    intrare info;
    nod* next;
};

struct lista {
    nod* primul_element;
    lista() {
        primul_element = NULL;
    }
    ~lista() {
        nod* current = primul_element;
        while (current != NULL) {
            nod* next = current->next;
            delete current;
            current = next;
        }
    }
    void insert_la_inceput(long long cheie, int valoare) {
        nod* nou = new nod;
        nou->info.element = cheie;
        nou->info.aparitii = valoare;
        nou->next = primul_element;
        primul_element = nou;
    }
    intrare* cauta_dupa_cheie(long long cheie) {
        nod* curent = primul_element;
        while (curent != NULL && curent->info.element != cheie)
            curent = curent->next;
        if (curent == NULL)
            return NULL;
        return &(curent->info);
    }
    void afisare() {
        nod* pointer;
        if (primul_element == NULL)
            cout << "prim=NULL";
        else
            for (pointer = primul_element; pointer != NULL; pointer = pointer->next)
                cout << "[" << pointer->info.element << ", " << pointer->info.aparitii << "] -> ";
        cout << endl;
    }
};

int hash_diviziune(long long cheie) {
    return cheie % 19;
}

struct hashtable_chaining {
    lista* T;
    int n;
    int (*hashfunc)(long long);
    hashtable_chaining(int N, int (*H)(long long)) {
        n = N;
        hashfunc = H;
        T = new lista[n];
    }
    // Copy constructor
    hashtable_chaining(const hashtable_chaining& other) : n(other.n), hashfunc(other.hashfunc) {
        T = new lista[n];
        for (int i = 0; i < n; ++i) {
            T[i] = other.T[i];
        }
    }
    // Assignment operator
    hashtable_chaining& operator=(const hashtable_chaining& other) {
        if (this != &other) {
            delete[] T;
            n = other.n;
            hashfunc = other.hashfunc;
            T = new lista[n];
            for (int i = 0; i < n; ++i) {
                T[i] = other.T[i];
            }
        }
        return *this;
    }
    ~hashtable_chaining() {
        delete[] T;
    }
    void put(long long cheie, int valoare) {
        int hash = hashfunc(cheie);
        int index = hash % n;
        intrare* gasit = T[index].cauta_dupa_cheie(cheie);
        if (gasit == NULL)
            T[index].insert_la_inceput(cheie, valoare);
        else
            gasit->aparitii = abs(gasit->aparitii - valoare);
    }

    void afisare() {
        for (int i = 0; i < n; i++)
            T[i].afisare();
    }
};

int main(){
    int n;
    cout << "Primul multiset" << endl;
    cout << "Numarul de perechi:";
    cin>> n;
    vector<char> elemente1;
    vector<int> aparitii1;
    for(int i = 1; i <= n; i++)
    {
        cout << "Perechea " << i << endl;
        int aparitie;
        cin >> aparitie;
        aparitii1.push_back(aparitie);
        char element;
        cin >> element;
        elemente1.push_back(element);
    }
    int m;
    cout << "Al doilea multiset" << endl;
    cout << "Numarul de perechi:";
    cin >> m;
    vector<char> elemente2;
    vector<int> aparitii2;
    for(int i = 1; i <= m; i++)
    {
        cout << "Perechea " << i << endl;
        int aparitie;
        cin >> aparitie;
        aparitii2.push_back(aparitie);
        char element;
        cin >> element;
        elemente2.push_back(element);
    }
    int max = 0;
    if(n > m)
        max = n;
    else
        max = m;
    hashtable_chaining H(max,hash_diviziune);
    for(int i = 0; i < n; i++)
        H.put(elemente1[i], aparitii1[i]);
    for(int i = 0; i < m; i++)
        H.put(elemente2[i], aparitii2[i]);
    H.afisare();
    return 0;
}
