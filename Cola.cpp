#include <iostream>
#include "cola.h"
using namespace std;

datosCola* first = nullptr;
datosCola* last = nullptr;
datosCola* cola = nullptr;

void ingresarDatosCola() {
    cola = new datosCola;
    cout << "Ingrese un dato a la cola: ";
    cin >> cola->dato;
    cola->dir_next = nullptr;

    if (last != nullptr) {
        last->dir_next = cola;
        last = cola;
        cout << "Dato ingresado!" << endl;
    } else {
        first = last = cola;
        cout << "Primer dato ingresado!" << endl;
    }
}

void mostrarDatosCola() {
    if (first == nullptr) {
        cout << "La cola esta vacia!" << endl;
        return;
    }

    datosCola* temp = first;
    cout << "Los datos de la cola son: " << endl;
    while (temp != nullptr) {
        cout << temp->dato << endl;
        temp = temp->dir_next;
    }
}

void eliminarDatosCola() {
    if (first != nullptr) {
        datosCola* temp = first;
        cout << "Eliminado: " << temp->dato << endl;
        first = first->dir_next;
        delete temp;

        if (first == nullptr) {
            last = nullptr;
        }
    } else {
        cout << "La cola esta vacia!" << endl;
    }
}

void buscarDatosCola() {
    if (first == nullptr) {
        cout << "La cola esta vacia!" << endl;
        return;
    }

    int buscarDatos;
    cout << "Ingrese el dato a buscar: ";
    cin >> buscarDatos;

    datosCola* temp = first;
    while (temp != nullptr) {
        if (temp->dato == buscarDatos) {
            cout << "Dato encontrado! El dato es: " << temp->dato << endl;
            return;
        }
        temp = temp->dir_next;
    }

    cout << "No se encontro el dato!" << endl;
}

void menuCola() {
    int opcion;
    do {
        system("cls");
        cout << "MENU COLA\n"
             << "1. Ingresar datos a la cola\n"
             << "2. Mostrar datos de la cola\n"
             << "3. Eliminar datos de la cola\n"
             << "4. Buscar datos en la cola\n"
             << "5. Volver al menu principal\n"
             << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                ingresarDatosCola();
                system("pause");
                break;
            case 2:
                mostrarDatosCola();
                system("pause");
                break;
            case 3:
                eliminarDatosCola();
                system("pause");
                break;
            case 4:
                buscarDatosCola();
                system("pause");
                break;
            case 5:
                return;
            default:
                cout << "Opcion no valida!" << endl;
                system("pause");
        }
    } while (true);
}