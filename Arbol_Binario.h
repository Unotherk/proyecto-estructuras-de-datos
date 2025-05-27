#ifndef ARBOL_BINARIO_H
#define ARBOL_BINARIO_H

class NodoArbolBinario {
public:
    int data;
    NodoArbolBinario* left;
    NodoArbolBinario* right;

    NodoArbolBinario(int value);
};

class ArbolBinario {
private:
    NodoArbolBinario* root;

    NodoArbolBinario* deleteRecursive(NodoArbolBinario* current, int value);
    NodoArbolBinario* findMin(NodoArbolBinario* nodo);
    bool searchRecursive(NodoArbolBinario* current, int value);
    void inorderRecursive(NodoArbolBinario* nodo);
    void preorderRecursive(NodoArbolBinario* nodo);
    void postorderRecursive(NodoArbolBinario* nodo);
    void printTreeVisual(NodoArbolBinario* root, int space, int level);

public:
    ArbolBinario();

    void insertNode(int value);
    void deleteNode(int value);
    bool search(int value);
    void inorder();
    void preorder();
    void postorder();
    void levelOrder();
    void printTree();
};

void menuArbolBinario();

#endif
