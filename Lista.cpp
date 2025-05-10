#include "lista.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Implementación de Nodo
Nodo::Nodo(int d) : dato(d), siguiente(nullptr) {}

// Implementación de Lista
Lista::Lista() : cabeza(nullptr) {}

bool Lista::estaVacia() {
    return cabeza == nullptr;
}

void Lista::insertar(int valor) {
    Nodo* nuevo = new Nodo(valor);
    if (cabeza == nullptr) {
        cabeza = nuevo;
    } else {
        Nodo* actual = cabeza;
        while (actual->siguiente != nullptr)
            actual = actual->siguiente;
        actual->siguiente = nuevo;
    }
}

void Lista::eliminar(int valor) {
    if (cabeza == nullptr) return;

    if (cabeza->dato == valor) {
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        return;
    }

    Nodo* actual = cabeza;
    while (actual->siguiente != nullptr) {
        if (actual->siguiente->dato == valor) {
            Nodo* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
            return;
        }
        actual = actual->siguiente;
    }
}

bool Lista::buscar(int valor) {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->dato == valor) return true;
        actual = actual->siguiente;
    }
    return false;
}

void Lista::mostrar() {
    if (estaVacia()) {
        cout << "La lista esta vacia\n";
        return;
    }

    Nodo* actual = cabeza;
    while (actual != nullptr) {
        cout << actual->dato << " ";
        actual = actual->siguiente;
    }
    cout << "\n";
}

// Implementación de funciones auxiliares
InputResult leerEntrada(const string& mensaje) {
    string entrada;
    while (true) {
        cout << mensaje;
        getline(cin, entrada);

        if (entrada == "C" || entrada == "c") {
            return {0, true};
        }

        try {
            size_t pos;
            int valor = stoi(entrada, &pos);
            if (pos == entrada.size()) return {valor, false};
            throw invalid_argument("");
        } catch (...) {
            cout << "\nElemento invalido, intenta nuevamente.\n\n";
            system("pause");
            system("cls");
        }
    }
}

void mostrarMenu() {
    cout << "MENU PRINCIPAL\n"
         << "1. Insertar elemento\n"
         << "2. Eliminar elemento\n"
         << "3. Buscar elemento\n"
         << "4. Mostrar lista\n"
         << "5. Salir\n"
         << "Selecciona una opcion: ";
}
/*
// Función principal
int main() {
    Lista lista;
    string entrada;
    int opcion;

    while (true) {
        mostrarMenu();
        getline(cin, entrada);

        try {
            opcion = stoi(entrada);
        } catch (...) {
            opcion = -1;
        }

        switch (opcion) {
            case 1: {
                system("cls");
                InputResult res = leerEntrada("Ingresa el valor a insertar (C para cancelar): ");
                if (!res.cancelado) {
                    lista.insertar(res.valor);
                    cout << "\nElemento " << res.valor << " insertado!\n";
                }
                break;
            }

            case 2: {
                system("cls");
                if (lista.estaVacia()) {
                    cout << "La lista esta vacia!\n\n";
                } else {
                    InputResult res = leerEntrada("Ingresa el valor a eliminar (C para cancelar): ");
                    if (!res.cancelado) {
                        if (lista.buscar(res.valor)) {
                            lista.eliminar(res.valor);
                            cout << "\nElemento " << res.valor << " eliminado!\n";
                        } else {
                            cout << "\nElemento no encontrado!\n";
                        }
                    }
                }
                break;
            }

            case 3: {
                system("cls");
                if (lista.estaVacia()) {
                    cout << "La lista esta vacia!\n\n";
                } else {
                    InputResult res = leerEntrada("Ingresa el valor a buscar (C para cancelar): ");
                    if (!res.cancelado) {
                        if (lista.buscar(res.valor)) {
                            cout << "\nElemento " << res.valor << " encontrado!\n";
                        } else {
                            cout << "\nElemento no encontrado\n";
                        }
                    }
                }
                break;
            }

            case 4: {
                system("cls");
                if (!lista.estaVacia()) {
                    cout << "Elementos en la lista:\n\n";
                }
                lista.mostrar();
                cout << "\n";
                break;
            }

            case 5:
                return 0;

            default:
                cout << "\nOpcion invalida!\n";
                break;
        }

        system("pause");
        system("cls");
    }

    return 0;
    */
