#include "lista.h"
#include "pila.h"
#include "cola.h"
#include "Arbol_B.h"
#include "arbol_binario.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void mostrarMenuPrincipal();
void manejarMenuPrincipal();

bool confirmarSalida() {
    string respuesta;
    cout << "\n\t¡ADVERTENCIA!\n"
         << "Todos los cambios realizados seran eliminados.\n"
         << "¿Esta seguro que desea salir? (S/N): ";
    getline(cin, respuesta);
    return (respuesta == "S" || respuesta == "s");
}

int main() {
    manejarMenuPrincipal();
    return 0;
}

void mostrarMenuPrincipal() {
    system("cls");
    cout << "SISTEMA DE ESTRUCTURAS DE DATOS\n"
         << "1. Trabajar con Lista Enlazada\n"
         << "2. Trabajar con Cola\n"
         << "3. Trabajar con Pila\n"
         << "4. Trabajar con Arbol Binario\n"
         << "5. Trabajar con Arbol AVL\n"
         << "6. Trabajar con Arbol B\n"
         << "7. Trabajar con Tabla Hash\n"
         << "8. Salir del sistema\n\n"
         << "Seleccione una opcion: ";
}

void manejarMenuPrincipal() {
    string entrada;
    int opcion;

    do {
        mostrarMenuPrincipal();
        getline(cin, entrada);

        try {
            opcion = stoi(entrada);
        } catch(...) {
            opcion = -1;
        }

        system("cls");
        
        switch(opcion) {
            case 1:
                manejarMenuLista();
                break;
                
            case 2:
                menuCola(); 
                break;
            case 3:
                menuPila();
                break;
            case 4:
                menuArbolBinario();
                break;
            case 5:
            case 6:
                menuArbolB();
                break;
            case 7:
                cout << "\n\t¡Funcionalidad no implementada!\n"
                     << "Todavia no se ha implementado esta caracteristica\n\n";
                system("pause");
                break;
                
            case 8: {
                if (confirmarSalida()) {
                    cout << "\nSaliendo del sistema...\n\n";
                    return;
                }
                break;
            }
                
            default:
                cout << "\nOpcion no valida!\n\n";
                system("pause");
        }
        
    } while(true);
}