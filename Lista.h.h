#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <string>

struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo(int d);
};

class Lista {
private:
    Nodo* cabeza;

public:
    Lista();
    bool estaVacia();
    void insertar(int valor);
    void eliminar(int valor);
    bool buscar(int valor);
    void mostrar();
};

struct InputResult {
    int valor;
    bool cancelado;
};

// Declaración de la lista global
extern Lista lista;

// Funciones del menú de listas
void manejarMenuLista();
InputResult leerEntrada(const std::string& mensaje);

#endif
