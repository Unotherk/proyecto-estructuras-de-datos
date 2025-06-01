#ifndef ARBOL_BINARIO_H
#define ARBOL_BINARIO_H

#include <string>
#include <fstream>

struct NodoArbolBinario {
    int data;
    NodoArbolBinario* left;
    NodoArbolBinario* right;
    NodoArbolBinario(int value);
};

class ArbolBinario {
private:
    NodoArbolBinario* root;
    void inorderRecursive(NodoArbolBinario* node);
    void preorderRecursive(NodoArbolBinario* node);
    void postorderRecursive(NodoArbolBinario* node);
    void printTreeVisual(NodoArbolBinario* node, int space, int level);
    void graphvizRec(NodoArbolBinario* node, std::ofstream& out);
public:
    ArbolBinario();
    ~ArbolBinario();
    bool isEmpty() const;
    void insertNode(int value);
    void deleteNode(int value);
    bool search(int value);
    void inorder();
    void preorder();
    void postorder();
    void levelOrder();
    void printTree();
    void mostrarGraphviz();
    void cargarDesdeArchivo(const std::string& nombreArchivo);
    void guardarEnArchivo(const std::string& nombreArchivo);
};

void menuArbolBinario();

#endif 