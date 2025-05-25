#ifndef AVL_H
#define AVL_H

#include "Lista.h"    // para InputResult y leerEntrada
#include <iostream>
#include <string>
#include <functional>
#include <fstream>

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int k);
};

class AVL {
private:
    AVLNode* root;
    int altura(AVLNode* nodo);
    int balanceFactor(AVLNode* nodo);
    AVLNode* rotarDerecha(AVLNode* y);
    AVLNode* rotarIzquierda(AVLNode* x);
    AVLNode* insertarNodo(AVLNode* nodo, int key);
    AVLNode* minValueNode(AVLNode* nodo);
    AVLNode* eliminarNodo(AVLNode* nodo, int key, bool& removed);
    bool buscarNodo(AVLNode* nodo, int key);
    void inorder(AVLNode* nodo);
    void preorder(AVLNode* nodo);
    void postorder(AVLNode* nodo);

public:
    AVL();
    void insertar(int key);
    void eliminar(int key);
    bool buscar(int key);
    void mostrarGraphviz();    // genera arbol.png y lo abre
    void recorridoInorder();
    void recorridoPreorder();
    void recorridoPostorder();
};

// declaracion de la instancia global
extern AVL avl;

// prototipo del menú AVL
void manejarMenuAVL();

#endif // AVL_H
