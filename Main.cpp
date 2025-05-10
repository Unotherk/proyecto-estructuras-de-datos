#include <iostream>
#include <string>
#include <cstdlib>
#include "lista.h"

using namespace std;

void mostrarMenuPrincipal();
void manejarMenuPrincipal();
void mostrarMenuLista(Lista& lista);
void manejarMenuLista();

bool confirmarSalida() {
    string respuesta;
    cout << "\nADVERTENCIA\n"
         << "Todos los cambios realizados seran eliminados.\n"
         << "Esta seguro que desea salir? (S/N): ";
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
    Lista lista; // Solo para el ejemplo de lista
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

        switch(opcion) {
            case 1:
                manejarMenuLista();
                break;
                
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                system("cls");
                cout << "Todavia no se ha implementado esta caracteristica\n\n";
                system("pause");
                break;
                
            case 8:{
                if (confirmarSalida()) {
                    cout << "\nSaliendo del sistema...\n\n";
                    return;  // Salir inmediatamente de la función
                }
                opcion = -1;  // Resetear opción para continuar en el bucle
                break;
            }
                
            default:
                cout << "\nOpcion no valida!\n";
                system("pause");
        }
        
    } while(true);  // Bucle infinito controlado por el case 8
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
    Lista lista;
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
        
        switch (opcion) {
            case 1: {
                 system("cls");
                InputResult res = leerEntrada("Ingresa el valor a insertar (C para cancelar): ");
                if (!res.cancelado) {
                    lista.insertar(res.valor);
                    cout << "\nElemento " << res.valor << " insertado!\n\n";
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
                            cout << "\nElemento " << res.valor << " eliminado!\n\n";
                        } else {
                            cout << "\nElemento no encontrado!\n\n";
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
                cout << "\nElemento " << res.valor << " encontrado!\n\n";
                } else {
                cout << "\nElemento no encontrado\n\n";
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
                cout << "Volviendo al menu principal...\n\n";
                break;
            
            default:
                cout << "Opcion no valida!\n\n";
        }

        if(opcion != 5) {
            system("pause");
            system("cls");
        }
        
    } while(opcion != 5);
}