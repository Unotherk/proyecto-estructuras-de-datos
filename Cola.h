#ifndef COLA_H
#define COLA_H

struct datosCola {
    int dato;
    datosCola* dir_next;
};

void ingresarDatosCola();
void mostrarDatosCola();
void eliminarDatosCola();
void buscarDatosCola();
void menuCola();

#endif