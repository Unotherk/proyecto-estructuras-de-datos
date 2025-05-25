#ifndef PILA_H
#define PILA_H

struct NodoPila {
    int valor;
    NodoPila* siguiente;
};

// Funciones de la pila
void ingresarDatoPila();
void mostrarPila();
void eliminarDatoPila();
void buscarDatoPila();
void menuPila();

#endif