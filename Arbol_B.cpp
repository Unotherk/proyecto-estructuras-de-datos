#include "Arbol_B.h"
#include <iostream>
using namespace std;

NodoArbolB::NodoArbolB(int _t, bool _leaf) {
    t = _t;
    leaf = _leaf;
    key = new int[2 * t - 1];
    child = new NodoArbolB * [2 * t];
    n = 0;
}

int NodoArbolB::findKey(int k) {
    int idx = 0;
    while (idx < n && key[idx] < k) ++idx;
    return idx;
}

ArbolB::ArbolB(int _t) {
    t = _t;
    root = new NodoArbolB(t, true);
}

void ArbolB::split(NodoArbolB* x, int i, NodoArbolB* y) {
    NodoArbolB* z = new NodoArbolB(t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++) z->key[j] = y->key[j + t];
    if (!y->leaf) for (int j = 0; j < t; j++) z->child[j] = y->child[j + t];
    y->n = t - 1;
    for (int j = x->n; j > i; j--) x->child[j + 1] = x->child[j];
    x->child[i + 1] = z;
    for (int j = x->n - 1; j >= i; j--) x->key[j + 1] = x->key[j];
    x->key[i] = y->key[t - 1];
    x->n++;
}

void ArbolB::nonFullInsert(NodoArbolB* x, int key) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && key < x->key[i]) {
            x->key[i + 1] = x->key[i];
            i--;
        }
        x->key[i + 1] = key;
        x->n++;
    }
    else {
        while (i >= 0 && key < x->key[i]) i--;
        i++;
        if (x->child[i]->n == (2 * t - 1)) {
            split(x, i, x->child[i]);
            if (key > x->key[i]) i++;
        }
        nonFullInsert(x->child[i], key);
    }
}

NodoArbolB* ArbolB::search(NodoArbolB* actual, int key) {
    int i = 0;
    while (i < actual->n && key > actual->key[i]) i++;
    if (i < actual->n && key == actual->key[i]) return actual;
    if (actual->leaf) return nullptr;
    return search(actual->child[i], key);
}

void ArbolB::print(NodoArbolB* n) {
    for (int i = 0; i < n->n; i++) cout << n->key[i] << " ";
    cout << endl;
    if (!n->leaf) for (int i = 0; i <= n->n; i++) print(n->child[i]);
}

void ArbolB::insertar(int key) {
    NodoArbolB* r = root;
    if (r->n == (2 * t - 1)) {
        NodoArbolB* s = new NodoArbolB(t, false);
        s->child[0] = r;
        root = s;
        split(s, 0, r);
        nonFullInsert(s, key);
    }
    else {
        nonFullInsert(r, key);
    }
}

void ArbolB::eliminar(int key) {
    if (!root) return;
    remove(root, key);
    if (root->n == 0) {
        NodoArbolB* tmp = root;
        if (root->leaf) root = nullptr;
        else root = root->child[0];
        delete tmp;
    }
}

void ArbolB::remove(NodoArbolB* node, int key) {
    int idx = node->findKey(key);
    if (idx < node->n && node->key[idx] == key) {
        if (node->leaf) removeFromLeaf(node, idx);
        else removeFromNonLeaf(node, idx);
    }
    else {
        if (node->leaf) return;
        bool flag = (idx == node->n);
        if (node->child[idx]->n < t) fill(node, idx);
        if (flag && idx > node->n) remove(node->child[idx - 1], key);
        else remove(node->child[idx], key);
    }
}

void ArbolB::removeFromLeaf(NodoArbolB* node, int idx) {
    for (int i = idx + 1; i < node->n; ++i) node->key[i - 1] = node->key[i];
    node->n--;
}

void ArbolB::removeFromNonLeaf(NodoArbolB* node, int idx) {
    int k = node->key[idx];
    if (node->child[idx]->n >= t) {
        int pred = getPred(node, idx);
        node->key[idx] = pred;
        remove(node->child[idx], pred);
    }
    else if (node->child[idx + 1]->n >= t) {
        int succ = getSucc(node, idx);
        node->key[idx] = succ;
        remove(node->child[idx + 1], succ);
    }
    else {
        merge(node, idx);
        remove(node->child[idx], k);
    }
}

int ArbolB::getPred(NodoArbolB* node, int idx) {
    NodoArbolB* cur = node->child[idx];
    while (!cur->leaf) cur = cur->child[cur->n];
    return cur->key[cur->n - 1];
}

int ArbolB::getSucc(NodoArbolB* node, int idx) {
    NodoArbolB* cur = node->child[idx + 1];
    while (!cur->leaf) cur = cur->child[0];
    return cur->key[0];
}

void ArbolB::fill(NodoArbolB* node, int idx) {
    if (idx != 0 && node->child[idx - 1]->n >= t) borrowFromPrev(node, idx);
    else if (idx != node->n && node->child[idx + 1]->n >= t) borrowFromNext(node, idx);
    else {
        if (idx != node->n) merge(node, idx);
        else merge(node, idx - 1);
    }
}

void ArbolB::borrowFromPrev(NodoArbolB* node, int idx) {
    NodoArbolB* child = node->child[idx];
    NodoArbolB* sibling = node->child[idx - 1];
    for (int i = child->n - 1; i >= 0; --i) child->key[i + 1] = child->key[i];
    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i) child->child[i + 1] = child->child[i];
    }
    child->key[0] = node->key[idx - 1];
    if (!child->leaf) child->child[0] = sibling->child[sibling->n];
    node->key[idx - 1] = sibling->key[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
}

void ArbolB::borrowFromNext(NodoArbolB* node, int idx) {
    NodoArbolB* child = node->child[idx];
    NodoArbolB* sibling = node->child[idx + 1];
    child->key[child->n] = node->key[idx];
    if (!child->leaf) child->child[child->n + 1] = sibling->child[0];
    node->key[idx] = sibling->key[0];
    for (int i = 1; i < sibling->n; ++i) sibling->key[i - 1] = sibling->key[i];
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i) sibling->child[i - 1] = sibling->child[i];
    }
    child->n += 1;
    sibling->n -= 1;
}

void ArbolB::merge(NodoArbolB* node, int idx) {
    NodoArbolB* child = node->child[idx];
    NodoArbolB* sibling = node->child[idx + 1];
    child->key[t - 1] = node->key[idx];
    for (int i = 0; i < sibling->n; ++i) child->key[i + t] = sibling->key[i];
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i) child->child[i + t] = sibling->child[i];
    }
    for (int i = idx + 1; i < node->n; ++i) node->key[i - 1] = node->key[i];
    for (int i = idx + 2; i <= node->n; ++i) node->child[i - 1] = node->child[i];
    child->n += sibling->n + 1;
    node->n--;
    delete sibling;
}

void ArbolB::buscar(int key) {
    NodoArbolB* result = search(root, key);
    if (result != nullptr) cout << "Clave encontrada.\n";
    else cout << "Clave no encontrada.\n";
}

void ArbolB::mostrarClavesNodoMinimo() {
    NodoArbolB* current = root;
    while (!current->leaf) current = current->child[0];
    cout << "Claves en el nodo mas a la izquierda: ";
    for (int i = 0; i < current->n; ++i) cout << current->key[i] << " ";
    cout << endl;
}

void ArbolB::mostrarClavesNodoMaximo() {
    NodoArbolB* current = root;
    while (!current->leaf) current = current->child[current->n];
    cout << "claves en el nodo mas a la derecha: ";
    for (int i = 0; i < current->n; ++i) cout << current->key[i] << " ";
    cout << endl;
}

void ArbolB::showBTree() {
    cout << "arbol B en preorden:\n";
    print(root);
}

void menuArbolB() {
    ArbolB arbol(2);
    int opcion, clave;

    do {
        system("cls");
        cout << "----- MENU ARBOL B -----\n"
             << "1. Insertar clave\n"
             << "2. Eliminar clave\n"
             << "3. Buscar clave\n"
             << "4. Mostrar arbol (preorden)\n"
             << "5. Mostrar claves nodo minimo\n"
             << "6. Mostrar claves nodo maximo\n"
             << "7. Volver al menu principal\n"
             << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Clave a insertar: ";
                cin >> clave;
                cin.ignore();
                arbol.insertar(clave);
                break;
            case 2:
                cout << "Clave a eliminar: ";
                cin >> clave;
                cin.ignore();
                arbol.eliminar(clave);
                break;
            case 3:
                cout << "Clave a buscar: ";
                cin >> clave;
                cin.ignore();
                arbol.buscar(clave);
                break;
            case 4:
                arbol.showBTree();
                break;
            case 5:
                arbol.mostrarClavesNodoMinimo();
                break;
            case 6:
                arbol.mostrarClavesNodoMaximo();
                break;
        }
        if (opcion != 7) system("pause");
    } while (opcion != 7);
}