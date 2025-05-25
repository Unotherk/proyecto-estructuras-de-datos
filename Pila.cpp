#include "pila.h"
#include <iostream>
using namespace std;

NodoPila* cima = nullptr;

void ingresarDatoPila() {
    NodoPila* nuevo = new NodoPila;
    cout << "Ingrese un dato a la pila: ";
    cin >> nuevo->valor;
    nuevo->siguiente = cima;
    cima = nuevo;
    cout << "(Dato ingresado correctamente)" << endl;
}

void mostrarPila() {
    if (!cima) {
        cout << "La pila está vacía!" << endl;
        return;
    }
    NodoPila* aux = cima;
    cout << "Los datos de la pila son:\n";
    while (aux) {
        cout << aux->valor << endl;
        aux = aux->siguiente;
    }
    cout << "FIN" << endl;
}

void eliminarDatoPila() {
    if (!cima) {
        cout << "La pila esta vacia!" << endl;
        return;
    }
    NodoPila* temp = cima;
    cout << "Elemento eliminado: " << temp->valor << endl;
    cima = cima->siguiente;
    delete temp;
}

void buscarDatoPila() {
    if (!cima) {
        cout << "La pila esta vacia!" << endl;
        return;
    }
    int dato;
    cout << "Ingrese el dato a buscar: ";
    cin >> dato;

    NodoPila* aux = cima;
    while (aux) {
        if (aux->valor == dato) {
            cout << "Dato encontrado exitosamente: " << aux->valor << endl;
            return;
        }
        aux = aux->siguiente;
    }
    cout << "El dato no se encuentra en la pila." << endl;
}

void menuPila() {
    int opcion;
    do {
        cout << "\n\t=== MENU PILA ===\n"
             << "1. Ingreso de datos a la pila\n"
             << "2. Mostrar pila\n"
             << "3. Eliminar dato\n"
             << "4. Buscar dato\n"
             << "5. Volver al menu principal\n"
             << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Limpia el buffer del salto de línea

        switch (opcion) {
            case 1: ingresarDatoPila(); break;
            case 2: mostrarPila(); break;
            case 3: eliminarDatoPila(); break;
            case 4: buscarDatoPila(); break;
            case 5: return;
            default: cout << "Opcion invalida!" << endl;
        }

        system("pause");
        system("cls");

    } while (true);
}