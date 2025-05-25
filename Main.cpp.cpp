#include "Lista.h"
#include "Avl.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

void mostrarMenuPrincipal() {
    system("cls");
    cout << "SISTEMA DE ESTRUCTURAS DE DATOS\n\n"
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

bool confirmarSalida() {
    string r;
    cout << "ADVERTENCIA: se perderan todos los datos no guardados.\n"
         << "Seguro que desea salir? (S/N): ";
    getline(cin, r);
    return (r == "S" || r == "s");
}

void manejarMenuPrincipal() {
    string entrada;
    int opcion;
    do {
        mostrarMenuPrincipal();
        getline(cin, entrada);
        try { opcion = stoi(entrada); }
        catch(...) { opcion = -1; }
        system("cls");
        switch(opcion) {
            case 1: manejarMenuLista(); break;
            case 2: case 3: case 4:
                cout << "Funcion no implementada aun.\n\n";
                system("pause"); break;
            case 5: manejarMenuAVL(); break;
            case 6: case 7:
                cout << "Funcion no implementada aun.\n\n";
                system("pause"); break;
            case 8:
                if (confirmarSalida()) {
                    cout << "\nSaliendo...\n\n";
                    return;
                }
                break;
            default:
                cout << "Opcion no valida!\n\n";
                system("pause");
        }
    } while(true);
}

void manejarMenuAVL() {
    int opcion;
    string entrada;
    do {
        system("cls");
        cout << "SUBMENU - ARBOL AVL\n\n"
             << "1. Insertar elemento\n"
             << "2. Eliminar elemento\n"
             << "3. Buscar elemento\n"
             << "4. Mostrar como imagen (PNG)\n"
             << "5. Recorrido Inorder\n"
             << "6. Recorrido Preorder\n"
             << "7. Recorrido Postorder\n"
             << "8. Volver al menu principal\n\n"
             << "Seleccione opcion: ";
        getline(cin, entrada);
        try { opcion = stoi(entrada); }
        catch(...) { opcion = -1; }
        system("cls");

        InputResult res;
        switch(opcion) {
            case 1:
                res = leerEntrada("Valor a insertar (C cancelar): ");
                if (!res.cancelado) {
                    avl.insertar(res.valor);
                    cout << "\nInsertado!\n\n";
                }
                break;
            case 2:
                avl.eliminar(0);  // llama al método que maneja vacío y mensajes
                break;
            case 3:
                avl.buscar(0);    // igual, el método imprime mensaje
                break;
            case 4:
                avl.mostrarGraphviz();
                break;
            case 5:
                avl.recorridoInorder();
                break;
            case 6:
                avl.recorridoPreorder();
                break;
            case 7:
                avl.recorridoPostorder();
                break;
            case 8:
                cout << "Volviendo al menu principal...\n\n";
                break;
            default:
                cout << "Opcion no valida!\n\n";
        }
        if (opcion != 8) system("pause");
    } while (opcion != 8);
}

int main() {
    manejarMenuPrincipal();
    return 0;
}
