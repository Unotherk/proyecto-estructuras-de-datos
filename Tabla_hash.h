#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <string>

using namespace std;//

class TablaHash {
private:
    static const int TAMANO_TABLA = 10;
    vector<list<int>> tabla;

    // Función hash simple
    int funcionHash(int clave);

    // Funciones auxiliares para validacion
    bool esNumeroValido(const string& str);
    int obtenerEnteroValido(const string& mensaje);
    char obtenerOpcionValida(const string& opciones);

    // Funciones para limpiar entrada
    void limpiarBuffer();

    // Nuevas funciones agregadas
    void limpiarPantalla();
    void pausar();

public:
    // Constructor
    TablaHash();

    // Operaciones principales
    void insertar(int clave);
    bool eliminar(int clave);
    bool buscar(int clave);
    void visualizar();

    // Funciones del menu
    void mostrarMenuPrincipal();
    void mostrarMenuSistema();
    void menuAgregar();
    void menuBorrar();
    void menuEncontrar();
    void menuMostrar();
    void ejecutar();

    // Funcion para confirmar salida
    bool confirmarSalida();
};

#endif
