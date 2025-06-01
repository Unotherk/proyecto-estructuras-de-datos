#include "Cola.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

datosCola* first = nullptr;
datosCola* last  = nullptr;

static ColaInputResult leerEntrada(const string& mensaje) {
    string line;
    while (true) {
        cout << mensaje;
        getline(cin, line);
        if (line == "C" || line == "c") return {0, true};
        try {
            size_t pos;
            int v = stoi(line, &pos);
            if (pos == line.size()) return {v, false};
        } catch (...) {}
        cout << "Entrada invalida! (numero o C)\n";
    }
}

void ingresarDatosCola(int dato) {
    auto* nodo = new datosCola{dato, nullptr};
    if (!first) first = last = nodo;
    else { last->dir_next = nodo; last = nodo; }
}

void mostrarDatosCola() {
    if (!first) { cout << "La cola esta vacia.\n"; return; }
    cout << "Cola: ";
    for (auto* cur = first; cur; cur = cur->dir_next)
        cout << cur->dato << " ";
    cout << "\n";
}

void eliminarDatosCola() {
    if (!first) { cout << "La cola esta vacia.\n"; return; }
    auto* temp = first;
    first = first->dir_next;
    if (!first) last = nullptr;
    delete temp;
}

void buscarDatosCola(int dato) {
    if (!first) { cout << "La cola esta vacia.\n"; return; }
    for (auto* cur = first; cur; cur = cur->dir_next) {
        if (cur->dato == dato) { cout << "Encontrado.\n"; return; }
    }
    cout << "No encontrado.\n";
}

void cargarDesdeArchivoCola(const std::string& nombreArchivo) {
    datosCola* cur = first;
    while (cur) {
        datosCola* tmp = cur;
        cur = cur->dir_next;
        delete tmp;
    }
    first = last = nullptr;
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    int valor;
    while (archivo >> valor) ingresarDatosCola(valor);
    archivo.close();
}

void guardarEnArchivoCola(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    for (auto* cur = first; cur; cur = cur->dir_next)
        archivo << cur->dato << "\n";
}

void menuCola() {
    cargarDesdeArchivoCola("cola.txt");
    int opcion;
    do {
        system("cls");
        cout << "=== MENU COLA ===\n"
             << "1. Ingresar dato\n"
             << "2. Mostrar cola\n"
             << "3. Eliminar dato\n"
             << "4. Buscar dato\n"
             << "5. Volver\n"
             << "Seleccione: ";
        string op; getline(cin, op);
        try { opcion = stoi(op); } catch (...) { opcion = -1; }
        system("cls");
        switch (opcion) {
            case 1: {
                auto res = leerEntrada("Valor (C cancelar): ");
                if (!res.cancelado) ingresarDatosCola(res.valor);
                break;
            }
            case 2: mostrarDatosCola(); break;
            case 3: eliminarDatosCola(); break;
            case 4: {
                auto res = leerEntrada("Valor a buscar (C cancelar): ");
                if (!res.cancelado) buscarDatosCola(res.valor);
                break;
            }
            case 5:
                guardarEnArchivoCola("cola.txt");
                return;
            default:
                cout << "Opción no válida.\n";
        }
        cout << "\n"; system("pause");
    } while (true);
}
