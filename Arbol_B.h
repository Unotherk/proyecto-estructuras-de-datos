#ifndef ARBOL_B_H
#define ARBOL_B_H

class NodoArbolB {
public:
    int* key;
    NodoArbolB** child;
    int t;
    int n;
    bool leaf;

    NodoArbolB(int _t, bool _leaf);
    int findKey(int k);
};

class ArbolB {
private:
    NodoArbolB* root;
    int t;

    void split(NodoArbolB* x, int i, NodoArbolB* y);
    void nonFullInsert(NodoArbolB* x, int key);
    NodoArbolB* search(NodoArbolB* actual, int key);
    void print(NodoArbolB* n);
    void remove(NodoArbolB* node, int key);
    void removeFromLeaf(NodoArbolB* node, int idx);
    void removeFromNonLeaf(NodoArbolB* node, int idx);
    int getPred(NodoArbolB* node, int idx);
    int getSucc(NodoArbolB* node, int idx);
    void fill(NodoArbolB* node, int idx);
    void borrowFromPrev(NodoArbolB* node, int idx);
    void borrowFromNext(NodoArbolB* node, int idx);
    void merge(NodoArbolB* node, int idx);

public:
    ArbolB(int _t);
    void insertar(int key);
    void eliminar(int key);
    void buscar(int key);
    void mostrarClavesNodoMinimo();
    void mostrarClavesNodoMaximo();
    void showBTree();
};

void menuArbolB();

#endif