#include "Tabla_hash.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>  // Para system()

using namespace std;

// Constructor
TablaHash::TablaHash() : tabla(TAMANO_TABLA) {}

// Función para limpiar pantalla
void TablaHash::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Función hash simple (módulo)
int TablaHash::funcionHash(int clave) {
    return abs(clave) % TAMANO_TABLA;
}

// Validar si una cadena es un numero valido
bool TablaHash::esNumeroValido(const string& str) {
    if (str.empty()) return false;

    size_t inicio = 0;
    if (str[0] == '-' || str[0] == '+') {
        if (str.length() == 1) return false;
        inicio = 1;
    }

    for (size_t i = inicio; i < str.length(); i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

// Obtener un entero valido del usuario
int TablaHash::obtenerEnteroValido(const string& mensaje) {
    string entrada;
    int numero;

    while (true) {
        cout << mensaje;
        getline(cin, entrada);

        if (esNumeroValido(entrada)) {
            stringstream ss(entrada);
            ss >> numero;
            return numero;
        }
        else {
            cout << "Error: Debe ingresar un numero valido. Intente nuevamente.\n";
        }
    }
}

// Obtener una opcion valida del menu
char TablaHash::obtenerOpcionValida(const string& opciones) {
    string entrada;
    char opcion;

    while (true) {
        cout << "Ingrese su opcion: ";
        getline(cin, entrada);

        if (entrada.length() == 1) {
            opcion = tolower(entrada[0]);
            if (opciones.find(opcion) != string::npos) {
                return opcion;
            }
        }

        cout << "Error: Opcion no valida. Por favor, ingrese una de las opciones mostradas.\n";
    }
}

// Limpiar buffer de entrada
void TablaHash::limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Pausar para que el usuario pueda leer
void TablaHash::pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.get();
}

// Insertar un elemento en la tabla hash
void TablaHash::insertar(int clave) {
    int indice = funcionHash(clave);

    // Verificar si ya existe
    for (const int& elemento : tabla[indice]) {
        if (elemento == clave) {
            cout << "El numero " << clave << " ya existe en la tabla.\n";
            return;
        }
    }

    tabla[indice].push_back(clave);
    cout << "Numero " << clave << " insertado exitosamente.\n";
}

// Eliminar un elemento de la tabla hash
bool TablaHash::eliminar(int clave) {
    int indice = funcionHash(clave);

    auto& lista = tabla[indice];
    auto it = find(lista.begin(), lista.end(), clave);

    if (it != lista.end()) {
        lista.erase(it);
        cout << "Numero " << clave << " eliminado exitosamente.\n";
        return true;
    }
    else {
        cout << "El numero " << clave << " no se encontro en la tabla.\n";
        return false;
    }
}

// Buscar un elemento en la tabla hash
bool TablaHash::buscar(int clave) {
    int indice = funcionHash(clave);

    for (const int& elemento : tabla[indice]) {
        if (elemento == clave) {
            cout << "El numero " << clave << " SI se encuentra en la tabla (Indice: " << indice << ").\n";
            return true;
        }
    }

    cout << "El numero " << clave << " NO se encuentra en la tabla.\n";
    return false;
}

// Visualizar toda la tabla hash
void TablaHash::visualizar() {
    cout << "\nCONTENIDO DE LA TABLA HASH \n";
    cout << "================================\n";
    bool tablaVacia = true;

    for (int i = 0; i < TAMANO_TABLA; i++) {
        cout << "Indice " << i << ": ";
        if (tabla[i].empty()) {
            cout << "[vacio]";
        }
        else {
            tablaVacia = false;
            cout << "[ ";
            for (auto it = tabla[i].begin(); it != tabla[i].end(); ++it) {
                if (it != tabla[i].begin()) std::cout << " -> ";
                cout << *it;
            }
            cout << " ]";
        }
        cout << "\n";
    }

    if (tablaVacia) {
        cout << "\nLa tabla hash esta completamente vacia.\n";
    }
    cout << "================================\n";
}

// Mostrar menu principal
void TablaHash::mostrarMenuPrincipal() {
    limpiarPantalla();
    cout << "================================\n";
    cout << "        MENU TABLA HASH         \n";
    cout << "================================\n";
    cout << " 1. Agregar numero              \n";
    cout << " 2. Borrar numero               \n";
    cout << " 3. Encontrar numero            \n";
    cout << " 4. Mostrar tabla completa      \n";
    cout << " 5. Salir                       \n";
    cout << " 6. Regresar al menu principal  \n";
    cout << "================================\n";
}

// Menu para agregar
void TablaHash::menuAgregar() {
    char opcion;

    do {
        limpiarPantalla();
        cout << "================================\n";
        cout << "        AGREGAR NUMEROS         \n";
        cout << "================================\n";

        int numero = obtenerEnteroValido("Ingrese el numero a agregar: ");
        insertar(numero);

        cout << "\nDesea agregar otro numero? (s/n) o regresar al menu principal (r): ";
        opcion = obtenerOpcionValida("snr");

    } while (opcion == 's');

    if (opcion == 'r') {
        cout << "Regresando al menu principal...\n";
        pausar();
    }
}

// Menu para borrar
void TablaHash::menuBorrar() {
    char opcion;

    do {
        limpiarPantalla();
        cout << "================================\n";
        cout << "        BORRAR NUMEROS          \n";
        cout << "================================\n";

        int numero = obtenerEnteroValido("Ingrese el numero a borrar: ");
        eliminar(numero);

        cout << "\nDesea borrar otro numero (s/n) o regresar al menu principal (r): ";
        opcion = obtenerOpcionValida("snr");

    } while (opcion == 's');

    if (opcion == 'r') {
        cout << "Regresando al menu principal...\n";
        pausar();
    }
}

// Menu para encontrar
void TablaHash::menuEncontrar() {
    char opcion;

    do {
        limpiarPantalla();
        cout << "================================\n";
        cout << "       ENCONTRAR NUMEROS        \n";
        cout << "================================\n";

        int numero = obtenerEnteroValido("Ingrese el numero a encontrar: ");
        buscar(numero);

        cout << "\nDesea encontrar otro numero (s/n) o regresar al menu principal (r): ";
        opcion = obtenerOpcionValida("snr");

    } while (opcion == 's');

    if (opcion == 'r') {
        cout << "Regresando al menu principal...\n";
        pausar();
    }
}

// Menu para mostrar
void TablaHash::menuMostrar() {
    char opcion;

    do {
        limpiarPantalla();
        visualizar();

        cout << "\nDesea ver la tabla nuevamente? (s/n) o regresar al menu principal (r): ";
        opcion = obtenerOpcionValida("snr");

    } while (opcion == 's');

    if (opcion == 'r') {
        cout << "Regresando al menu principal...\n";
        pausar();
    }
}

// Confirmar salida del programa
bool TablaHash::confirmarSalida() {
    limpiarPantalla();
    cout << "================================\n";
    cout << "       CONFIRMAR SALIDA         \n";
    cout << "================================\n";
    cout << "Todos los datos almacenados se perderan.\n";
    cout << "Esta seguro de que desea salir del programa (s/n): ";
    char opcion = obtenerOpcionValida("sn");
    return (opcion == 's');
}

// Mostrar el menu principal del sistema de estructuras de datos
void TablaHash::mostrarMenuSistema() {
    limpiarPantalla();
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

// Función principal para ejecutar el programa
void TablaHash::ejecutar() {
    char opcion;

    // Mostrar mensaje de bienvenida
    limpiarPantalla();

    do {
        mostrarMenuPrincipal();
        opcion = obtenerOpcionValida("123456");

        switch (opcion) {
        case '1':
            menuAgregar();
            break;
        case '2':
            menuBorrar();
            break;
        case '3':
            menuEncontrar();
            break;
        case '4':
            menuMostrar();
            break;
        case '5':
            if (confirmarSalida()) {
                limpiarPantalla();
                cout << "================================\n";
                cout << "Gracias por usar el Sistema   \n";
                cout << "       de Tabla Hash          \n";
                cout << "================================\n";
                return;
            }
            else {
                cout << "Operacion cancelada. Regresando al menu principal...\n";
                pausar();
            }
            break;
        case '6':
            cout << "Regresando al menu del sistema de estructuras de datos...\n";
            pausar();
            mostrarMenuSistema();
            cout << "Presione Enter para volver al menu de Tabla Hash...";
            cin.get();
            break;
        }
    } while (true);
}

// Función main
int main() {
    TablaHash tabla;
    tabla.ejecutar();
    return 0;
}