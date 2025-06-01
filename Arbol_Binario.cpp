#include "Arbol_Binario.h"
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

struct ArbolBinarioInputResult { int valor; bool cancelado; };
static ArbolBinarioInputResult leerEntrada(const string& mensaje) {
    string line;
    while (true) {
        cout << mensaje;
        if (!getline(cin, line)) return {0, true};
        if (line == "C" || line == "c") return {0, true};
        try {
            size_t pos;
            int v = stoi(line, &pos);
            if (pos == line.size()) return {v, false};
        } catch (...) {}
        cout << "Entrada inválida! (número o C)\n";
    }
}

NodoArbolBinario::NodoArbolBinario(int value)
    : data(value), left(nullptr), right(nullptr) {}

ArbolBinario::ArbolBinario() : root(nullptr) {}

ArbolBinario::~ArbolBinario() {
    if (!root) return;
    vector<NodoArbolBinario*> stack;
    stack.push_back(root);
    while (!stack.empty()) {
        NodoArbolBinario* n = stack.back();
        stack.pop_back();
        if (n->left)  stack.push_back(n->left);
        if (n->right) stack.push_back(n->right);
        delete n;
    }
}

bool ArbolBinario::isEmpty() const {
    return root == nullptr;
}

void ArbolBinario::insertNode(int value) {
    NodoArbolBinario* node = new NodoArbolBinario(value);
    if (!root) { root = node; return; }
    queue<NodoArbolBinario*> q;
    q.push(root);
    while (!q.empty()) {
        NodoArbolBinario* cur = q.front(); q.pop();
        if (!cur->left) { cur->left = node; return; }
        q.push(cur->left);
        if (!cur->right) { cur->right = node; return; }
        q.push(cur->right);
    }
}

void ArbolBinario::deleteNode(int value) {
    if (isEmpty()) { cout << "El arbol esta vacio\n"; return; }
    if (root->data == value && !root->left && !root->right) {
        delete root;
        root = nullptr;
        return;
    }
    queue<NodoArbolBinario*> q;
    q.push(root);
    NodoArbolBinario *target = nullptr, *last = nullptr;
    vector<NodoArbolBinario*> nodes;
    while (!q.empty()) {
        last = q.front(); nodes.push_back(last); q.pop();
        if (last->data == value) target = last;
        if (last->left)  q.push(last->left);
        if (last->right) q.push(last->right);
    }
    if (!target) { cout << "Valor no encontrado\n"; return; }
    target->data = last->data;
    for (auto n : nodes) {
        if (n->left == last) {
            delete last;
            n->left = nullptr;
            return;
        }
        if (n->right == last) {
            delete last;
            n->right = nullptr;
            return;
        }
    }
}

bool ArbolBinario::search(int value) {
    if (isEmpty()) { cout << "El arbol esta vacio\n"; return false; }
    queue<NodoArbolBinario*> q;
    q.push(root);
    while (!q.empty()) {
        NodoArbolBinario* cur = q.front(); q.pop();
        if (cur->data == value) return true;
        if (cur->left)  q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    return false;
}

void ArbolBinario::inorderRecursive(NodoArbolBinario* n) {
    if (!n) return;
    inorderRecursive(n->left);
    cout << n->data << " ";
    inorderRecursive(n->right);
}

void ArbolBinario::inorder() {
    if (isEmpty()) { cout << "El arbol esta vacio\n"; return; }
    inorderRecursive(root);
    cout << "\n";
}

void ArbolBinario::preorderRecursive(NodoArbolBinario* n) {
    if (!n) return;
    cout << n->data << " ";
    preorderRecursive(n->left);
    preorderRecursive(n->right);
}

void ArbolBinario::preorder() {
    if (isEmpty()) { cout << "El arbol esta vacio\n"; return; }
    preorderRecursive(root);
    cout << "\n";
}

void ArbolBinario::postorderRecursive(NodoArbolBinario* n) {
    if (!n) return;
    postorderRecursive(n->left);
    postorderRecursive(n->right);
    cout << n->data << " ";
}

void ArbolBinario::postorder() {
    if (isEmpty()) { cout << "El arbol esta vacio\n"; return; }
    postorderRecursive(root);
    cout << "\n";
}

void ArbolBinario::levelOrder() {
    if (isEmpty()) { cout << "El arbol esta vacio\n"; return; }
    queue<NodoArbolBinario*> q;
    q.push(root);
    while (!q.empty()) {
        NodoArbolBinario* cur = q.front(); q.pop();
        cout << cur->data << " ";
        if (cur->left)  q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    cout << "\n";
}

void ArbolBinario::printTreeVisual(NodoArbolBinario* n, int space, int level) {
    if (!n) return;
    space += level;
    printTreeVisual(n->right, space, level);
    cout << string(space, ' ') << n->data << "\n";
    printTreeVisual(n->left, space, level);
}

void ArbolBinario::printTree() {
    if (isEmpty()) { cout << "El arbol esta vacio\n"; return; }
    printTreeVisual(root, 0, 4);
}

void ArbolBinario::graphvizRec(NodoArbolBinario* n, ofstream& out) {
    if (!n) return;
    auto id = reinterpret_cast<uintptr_t>(n);
    out << "  \"" << id << "\" [label=\"" << n->data << "\"];\n";
    if (n->left) {
        auto lid = reinterpret_cast<uintptr_t>(n->left);
        out << "  \"" << id << "\" -> \"" << lid << "\";\n";
        graphvizRec(n->left, out);
    }
    if (n->right) {
        auto rid = reinterpret_cast<uintptr_t>(n->right);
        out << "  \"" << id << "\" -> \"" << rid << "\";\n";
        graphvizRec(n->right, out);
    }
}

void ArbolBinario::mostrarGraphviz() {
    if (isEmpty()) { cout << "El arbol esta vacio\n"; return; }
    ofstream f("arbol.dot");
    f << "digraph G {\n";
    graphvizRec(root, f);
    f << "}\n";
    f.close();
    system("dot -Tpng arbol.dot -o arbol.png");
    system("start arbol.png");
}

void ArbolBinario::cargarDesdeArchivo(const std::string& nombreArchivo) {
    if (root) {
        std::vector<NodoArbolBinario*> stk{root};
        while (!stk.empty()) {
            auto n = stk.back(); stk.pop_back();
            if (n->left)  stk.push_back(n->left);
            if (n->right) stk.push_back(n->right);
            delete n;
        }
        root = nullptr;
    }
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    int valor;
    std::vector<int> vals;
    while (archivo >> valor) vals.push_back(valor);
    archivo.close();
    for (int v : vals) insertNode(v);
}

void ArbolBinario::guardarEnArchivo(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    if (isEmpty()) return;
    queue<NodoArbolBinario*> q;
    q.push(root);
    while (!q.empty()) {
        NodoArbolBinario* cur = q.front(); q.pop();
        archivo << cur->data << "\n";
        if (cur->left)  q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    archivo.close();
}

void menuArbolBinario() {
    ArbolBinario tree;
    tree.cargarDesdeArchivo("arbol.txt");
    int opcion;
    do {
        system("cls");
        cout << "MENU ARBOL BINARIO\n"
             << "1. Insertar nodo\n"
             << "2. Eliminar nodo\n"
             << "3. Recorrer in-orden\n"
             << "4. Recorrer pre-orden\n"
             << "5. Recorrer post-orden\n"
             << "6. Recorrer amplitud\n"
             << "7. Buscar nodo\n"
             << "8. Mostrar Graphviz\n"
             << "9. Volver\n"
             << "Seleccione una opcion: ";
        string op; getline(cin, op);
        try { opcion = stoi(op); } catch(...) { opcion = -1; }
        system("cls");
        ArbolBinarioInputResult res;
        switch (opcion) {
            case 1:
                res = leerEntrada("Valor nodo (C cancelar): ");
                if (!res.cancelado) tree.insertNode(res.valor);
                break;
            case 2:
                res = leerEntrada("Valor a eliminar (C cancelar): ");
                if (!res.cancelado) tree.deleteNode(res.valor);
                break;
            case 3:
                tree.inorder();
                break;
            case 4:
                tree.preorder();
                break;
            case 5:
                tree.postorder();
                break;
            case 6:
                tree.levelOrder();
                break;
            case 7:
                res = leerEntrada("Valor a buscar (C cancelar): ");
                if (!res.cancelado) {
                    bool found = tree.search(res.valor);
                    cout << (found ? "Encontrado\n" : "No encontrado\n");
                }
                break;
            case 8:
                tree.mostrarGraphviz();
                break;
            case 9:
                tree.guardarEnArchivo("arbol.txt");
                return;
            default:
                cout << "Opcion invalida\n";
        }
        cout << "\n"; system("pause");
    } while (true);
}
