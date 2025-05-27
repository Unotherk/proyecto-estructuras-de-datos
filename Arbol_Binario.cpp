#include "Arbol_Binario.h"
#include <iostream>
#include <queue>
#include <limits>

using namespace std;

NodoArbolBinario::NodoArbolBinario(int value) : data(value), left(nullptr), right(nullptr) {}

ArbolBinario::ArbolBinario() : root(nullptr) {}

void ArbolBinario::insertNode(int value) {
    NodoArbolBinario* nuevoNodo = new NodoArbolBinario(value);

    if (root == nullptr) {
        root = nuevoNodo;
        return;
    }

    queue<NodoArbolBinario*> q;
    q.push(root);

    while (!q.empty()) {
        NodoArbolBinario* current = q.front();
        q.pop();

        if (current->left == nullptr) {
            current->left = nuevoNodo;
            return;
        } else {
            q.push(current->left);
        }

        if (current->right == nullptr) {
            current->right = nuevoNodo;
            return;
        } else {
            q.push(current->right);
        }
    }
}

NodoArbolBinario* ArbolBinario::deleteRecursive(NodoArbolBinario* current, int value) {
    if (current == nullptr)
        return nullptr;

    if (current->data == value) {
        if (current->left == nullptr && current->right == nullptr) {
            delete current;
            return nullptr;
        }
        if (current->left == nullptr) {
            NodoArbolBinario* temp = current->right;
            delete current;
            return temp;
        }
        if (current->right == nullptr) {
            NodoArbolBinario* temp = current->left;
            delete current;
            return temp;
        }

        NodoArbolBinario* sucesor = findMin(current->right);
        current->data = sucesor->data;
        current->right = deleteRecursive(current->right, sucesor->data);
    } else {
        current->left = deleteRecursive(current->left, value);
        current->right = deleteRecursive(current->right, value);
    }
    return current;
}

NodoArbolBinario* ArbolBinario::findMin(NodoArbolBinario* nodo) {
    while (nodo->left != nullptr) {
        nodo = nodo->left;
    }
    return nodo;
}

void ArbolBinario::deleteNode(int value) {
    root = deleteRecursive(root, value);
}

bool ArbolBinario::search(int value) {
    return searchRecursive(root, value);
}

bool ArbolBinario::searchRecursive(NodoArbolBinario* current, int value) {
    if (current == nullptr)
        return false;

    if (current->data == value)
        return true;

    return searchRecursive(current->left, value) || searchRecursive(current->right, value);
}

void ArbolBinario::inorder() {
    inorderRecursive(root);
    cout << endl;
}

void ArbolBinario::inorderRecursive(NodoArbolBinario* nodo) {
    if (nodo != nullptr) {
        inorderRecursive(nodo->left);
        cout << nodo->data << " ";
        inorderRecursive(nodo->right);
    }
}

void ArbolBinario::preorder() {
    preorderRecursive(root);
    cout << endl;
}

void ArbolBinario::preorderRecursive(NodoArbolBinario* nodo) {
    if (nodo != nullptr) {
        cout << nodo->data << " ";
        preorderRecursive(nodo->left);
        preorderRecursive(nodo->right);
    }
}

void ArbolBinario::postorder() {
    postorderRecursive(root);
    cout << endl;
}

void ArbolBinario::postorderRecursive(NodoArbolBinario* nodo) {
    if (nodo != nullptr) {
        postorderRecursive(nodo->left);
        postorderRecursive(nodo->right);
        cout << nodo->data << " ";
    }
}

void ArbolBinario::levelOrder() {
    if (root == nullptr) return;

    queue<NodoArbolBinario*> q;
    q.push(root);

    while (!q.empty()) {
        NodoArbolBinario* current = q.front();
        q.pop();

        cout << current->data << " ";

        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
    cout << endl;
}

void ArbolBinario::printTree() {
    printTreeVisual(root, 0, 5);
}

void ArbolBinario::printTreeVisual(NodoArbolBinario* root, int space, int level) {
    if (root == nullptr) return;

    space += level;

    printTreeVisual(root->right, space, level);

    cout << endl;
    for (int i = level; i < space; i++)
        cout << " ";
    cout << root->data << "\n";

    printTreeVisual(root->left, space, level);
}

void menuArbolBinario() {
    ArbolBinario tree;
    int opcion, nodoBinario;

    do {
        system("cls");
        cout << "MENU ARBOL BINARIO\n"
             << "1. Insertar nodo al arbol\n"
             << "2. Eliminar nodo del arbol\n"
             << "3. Recorrer arbol (in-orden)\n"
             << "4. Recorrer arbol (pre-orden)\n"
             << "5. Recorrer arbol (post-orden)\n"
             << "6. Recorrer arbol (amplitud)\n"
             << "7. Buscar nodo\n"
             << "8. Visualizar arbol\n"
             << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Ingrese el numero para el nodo: ";
                cin >> nodoBinario;
                if (cin.fail()) {
                    cout << "Dato invalido, no es un numero\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    tree.insertNode(nodoBinario);
                    cout << "Numero valido ingresado: " << nodoBinario << endl;
                }
                system("pause");
                break;
            case 2:
                cout << "Ingrese el nodo que quiere eliminar: ";
                cin >> nodoBinario;
                if (cin.fail()) {
                    cout << "Dato invalido, no es un numero\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    tree.deleteNode(nodoBinario);
                    cout << "Nodo eliminado exitosamente: " << nodoBinario << endl;
                }
                system("pause");
                break;
            case 3:
                tree.inorder();
                system("pause");
                break;
            case 4:
                tree.preorder();
                system("pause");
                break;
            case 5:
                tree.postorder();
                system("pause");
                break;
            case 6:
                tree.levelOrder();
                system("pause");
                break;
            case 7:
                cout << "Ingrese el nodo que quiere buscar: ";
                cin >> nodoBinario;
                if (cin.fail()) {
                    cout << "Dato invalido, no es un numero\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    if (tree.search(nodoBinario))
                        cout << "Nodo encontrado: " << nodoBinario << endl;
                    else
                        cout << "Nodo no encontrado\n";
                }
                system("pause");
                break;
            case 8:
                tree.printTree();
                system("pause");
                break;
            default:
                cout << "Opcion no valida!\n";
                system("pause");
        }
    } while (true);
}
