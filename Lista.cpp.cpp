#include "Lista.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Definición de la lista global (ya declarada en Lista.h)
Lista lista;

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
        cout << "La lista esta vacia\n\n";
        return;
    }

    Nodo* actual = cabeza;
    while (actual != nullptr) {
        cout << actual->dato << " ";
        actual = actual->siguiente;
    }
    cout << "\n\n";
}

// Funciones del menú de listas
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
            cout << "\nEntrada invalida! Intenta nuevamente\n\n";
            system("pause");
            system("cls");
        }
    }
}

void mostrarMenuLista() {
    system("cls");
    cout << "SUBMENU - LISTA ENLAZADA\n\n"
         << "1. Insertar elemento\n"
         << "2. Eliminar elemento\n"
         << "3. Buscar elemento\n"
         << "4. Mostrar lista\n"
         << "5. Volver al menu principal\n\n"
         << "Seleccione operacion: ";
}

void manejarMenuLista() {
    string entrada;
    int opcion;

    do {
        mostrarMenuLista();
        getline(cin, entrada);

        try {
            opcion = stoi(entrada);
        } catch (...) {
            opcion = -1;
        }

        system("cls");
        
        switch(opcion) {
            case 1: {
                InputResult res = leerEntrada("Ingrese valor a insertar (C para cancelar): ");
                if (!res.cancelado) {
                    lista.insertar(res.valor);
                    cout << "\nElemento " << res.valor << " insertado exitosamente!\n\n";
                }
                break;
            }
            
            case 2: {
                if (lista.estaVacia()) {
                    cout << "La lista esta vacia!\n\n";
                } else {
                    InputResult res = leerEntrada("Ingrese valor a eliminar (C para cancelar): ");
                    if (!res.cancelado) {
                        if (lista.buscar(res.valor)) {
                            lista.eliminar(res.valor);
                            cout << "\nElemento " << res.valor << " eliminado!\n\n";
                        } else {
                            cout << "\nEl valor no existe en la lista\n\n";
                        }
                    }
                }
                break;
            }
            
            case 3: {
                if (lista.estaVacia()) {
                    cout << "La lista esta vacia!\n\n";
                } else {
                    InputResult res = leerEntrada("Ingrese valor a buscar (C para cancelar): ");
                    if (!res.cancelado) {
                        string resultado = lista.buscar(res.valor) ? "SI" : "NO";
                        cout << "\nEl elemento " << res.valor << " " << resultado << " esta en la lista\n\n";
                    }
                }
                break;
            }
            
            case 4: {
                lista.mostrar();
                break;
            }
            
            case 5:
                cout << "Volviendo al menu principal...\n\n";
                break;
            
            default:
                cout << "Opcion no valida!\n\n";
        }

        if (opcion != 5) {
            system("pause");
        }
        
    } while (opcion != 5);
}
