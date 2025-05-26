#ifndef PILA_H
#define PILA_H

struct NodoPila {
    int valor;
    NodoPila* siguiente;
};

void ingresarDatoPila();
void mostrarPila();
void eliminarDatoPila();
void buscarDatoPila();
void menuPila();

#endif