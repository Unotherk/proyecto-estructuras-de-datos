#include "Avl.h"
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <fstream>

using namespace std;

// definición de la instancia global
AVL avl;

// --- Nodo ---
AVLNode::AVLNode(int k)
  : key(k), left(nullptr), right(nullptr), height(1) {}

// --- Auxiliares ---
int AVL::altura(AVLNode* nodo) {
    return nodo ? nodo->height : 0;
}

int AVL::balanceFactor(AVLNode* nodo) {
    return nodo ? altura(nodo->left) - altura(nodo->right) : 0;
}

AVLNode* AVL::rotarDerecha(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;  y->left = T2;
    y->height = max(altura(y->left), altura(y->right)) + 1;
    x->height = max(altura(x->left), altura(x->right)) + 1;
    return x;
}

AVLNode* AVL::rotarIzquierda(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;   x->right = T2;
    x->height = max(altura(x->left), altura(x->right)) + 1;
    y->height = max(altura(y->left), altura(y->right)) + 1;
    return y;
}

AVLNode* AVL::insertarNodo(AVLNode* nodo, int key) {
    if (!nodo) return new AVLNode(key);
    if (key < nodo->key)
        nodo->left = insertarNodo(nodo->left, key);
    else if (key > nodo->key)
        nodo->right = insertarNodo(nodo->right, key);
    else
        return nodo;  // no duplicados
    nodo->height = 1 + max(altura(nodo->left), altura(nodo->right));
    int bf = balanceFactor(nodo);
    if (bf > 1 && key < nodo->left->key)               return rotarDerecha(nodo);
    if (bf < -1 && key > nodo->right->key)             return rotarIzquierda(nodo);
    if (bf > 1 && key > nodo->left->key) {
        nodo->left = rotarIzquierda(nodo->left);
        return rotarDerecha(nodo);
    }
    if (bf < -1 && key < nodo->right->key) {
        nodo->right = rotarDerecha(nodo->right);
        return rotarIzquierda(nodo);
    }
    return nodo;
}

AVLNode* AVL::minValueNode(AVLNode* nodo) {
    AVLNode* actual = nodo;
    while (actual && actual->left) actual = actual->left;
    return actual;
}

// ahora eliminarNodo devuelve bool removed por referencia
AVLNode* AVL::eliminarNodo(AVLNode* nodo, int key, bool& removed) {
    if (!nodo) return nodo;
    if (key < nodo->key)
        nodo->left = eliminarNodo(nodo->left, key, removed);
    else if (key > nodo->key)
        nodo->right = eliminarNodo(nodo->right, key, removed);
    else {
        removed = true;
        if (!nodo->left || !nodo->right) {
            AVLNode* temp = nodo->left ? nodo->left : nodo->right;
            if (!temp) {
                delete nodo;
                return nullptr;
            } else {
                *nodo = *temp;
                delete temp;
            }
        } else {
            AVLNode* temp = minValueNode(nodo->right);
            nodo->key = temp->key;
            nodo->right = eliminarNodo(nodo->right, temp->key, removed);
        }
    }
    if (!nodo) return nodo;
    nodo->height = 1 + max(altura(nodo->left), altura(nodo->right));
    int bf = balanceFactor(nodo);
    if (bf > 1 && balanceFactor(nodo->left) >= 0)        return rotarDerecha(nodo);
    if (bf > 1 && balanceFactor(nodo->left) < 0)  {
        nodo->left = rotarIzquierda(nodo->left);
        return rotarDerecha(nodo);
    }
    if (bf < -1 && balanceFactor(nodo->right) <= 0)      return rotarIzquierda(nodo);
    if (bf < -1 && balanceFactor(nodo->right) > 0) {
        nodo->right = rotarDerecha(nodo->right);
        return rotarIzquierda(nodo);
    }
    return nodo;
}

bool AVL::buscarNodo(AVLNode* nodo, int key) {
    if (!nodo) return false;
    if (key == nodo->key) return true;
    return key < nodo->key
        ? buscarNodo(nodo->left, key)
        : buscarNodo(nodo->right, key);
}

void AVL::inorder(AVLNode* nodo) {
    if (!nodo) return;
    inorder(nodo->left);
    cout << nodo->key << " ";
    inorder(nodo->right);
}

void AVL::preorder(AVLNode* nodo) {
    if (!nodo) return;
    cout << nodo->key << " ";
    preorder(nodo->left);
    preorder(nodo->right);
}

void AVL::postorder(AVLNode* nodo) {
    if (!nodo) return;
    postorder(nodo->left);
    postorder(nodo->right);
    cout << nodo->key << " ";
}

// --- Graphviz output y apertura PNG ---
void AVL::mostrarGraphviz() {
    if (!root) {
        cout << "Arbol vacio\n\n";
        return;
    }
    ofstream f("arbol.dot");
    f << "digraph G {\n  node [shape=circle];\n";
    function<void(AVLNode*)> dump = [&](AVLNode* n){
        if (!n) return;
        f << "  " << n->key << ";\n";
        if (n->left)  f << "  " << n->key << " -> " << n->left->key  << ";\n";
        if (n->right) f << "  " << n->key << " -> " << n->right->key << ";\n";
        dump(n->left);
        dump(n->right);
    };
    dump(root);
    f << "}\n";
    f.close();
    system("dot -Tpng arbol.dot -o arbol.png");
    system("start arbol.png");
}

// --- Públicos ---
AVL::AVL() : root(nullptr) {}
void AVL::insertar(int key)    { root = insertarNodo(root, key); }
void AVL::eliminar(int key) {
    if (!root) {
        cout << "Arbol vacio\n\n";
        return;
    }
    bool removed = false;
    root = eliminarNodo(root, key, removed);
    cout << (removed ? "Elemento eliminado\n\n" : "No existe el valor en el arbol\n\n");
}
bool AVL::buscar(int key) {
    if (!root) {
        cout << "Arbol vacio\n\n";
        return false;
    }
    bool found = buscarNodo(root, key);
    cout << (found ? "Encontrado\n\n" : "No existe\n\n");
    return found;
}
void AVL::recorridoInorder() {
    if (!root) {
        cout << "Arbol vacio\n\n";
        return;
    }
    inorder(root);
    cout << "\n\n";
}
void AVL::recorridoPreorder() {
    if (!root) {
        cout << "Arbol vacio\n\n";
        return;
    }
    preorder(root);
    cout << "\n\n";
}
void AVL::recorridoPostorder() {
    if (!root) {
        cout << "Arbol vacio\n\n";
        return;
    }
    postorder(root);
    cout << "\n\n";
}
