#ifndef COLA_H
#define COLA_H

#include <string>

struct ColaInputResult {
    int valor;
    bool cancelado;
};

struct datosCola {
    int dato;
    datosCola* dir_next;
};

extern datosCola* first;
extern datosCola* last;

void ingresarDatosCola(int dato);
void mostrarDatosCola();
void eliminarDatosCola();
void buscarDatosCola(int dato);
void cargarDesdeArchivoCola(const std::string& nombreArchivo);
void guardarEnArchivoCola(const std::string& nombreArchivo);
void menuCola();

#endif // COLA_H