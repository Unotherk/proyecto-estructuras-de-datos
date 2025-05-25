#include "Tabla_hash.h"
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

// Funcion de hash
int HashTable::hashFunction(int key) {
    return key % tableSize;
}

// Funcion para comprobar si es numero
bool HashTable::isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// Funcion para encontrar el siguiente numero 
int HashTable::nextPrime(int n) {
    if (n <= 1) return 2;

    bool found = false;
    while (!found) {
        n++;
        if (isPrime(n))
            found = true;
    }
    return n;
}

// Redimensionar la tabla hash
void HashTable::resize() {
    int oldSize = tableSize;
    tableSize = nextPrime(tableSize * 2);
    vector<list<KeyValuePair>> oldTable = table;

    // Crear nueva tabla
    table.clear();
    table.resize(tableSize);
    itemCount = 0;

    // Reinsertar todos los elementos
    for (int i = 0; i < oldSize; i++) {
        for (auto& pair : oldTable[i]) {
            insert(pair.key, pair.value);
        }
    }
}

// Constructor
HashTable::HashTable(int size) {
    tableSize = size;
    table.resize(tableSize);
    itemCount = 0;
}

// Insertar un elemento en la tabla hash
void HashTable::insert(int key, string value) {
    // Verificar factor de carga y redimensionar si es necesario
    float loadFactor = static_cast<float>(itemCount) / tableSize;
    if (loadFactor > 0.7) {
        resize();
    }

    int index = hashFunction(key);

    // Comprobar si la clave ya existe
    for (auto& pair : table[index]) {
        if (pair.key == key) {
            pair.value = value; // Actualizar valor
            return;
        }
    }

    // Si no existe, insertar nuevo par clave-valor
    table[index].push_back(KeyValuePair(key, value));
    itemCount++;
}

// Buscar un elemento por clave
string HashTable::search(int key) {
    int index = hashFunction(key);

    for (auto& pair : table[index]) {
        if (pair.key == key) {
            return pair.value;
        }
    }

    return ""; // Retornar cadena vacia si no se encuentra
}

// Eliminar un elemento por clave
bool HashTable::remove(int key) {
    int index = hashFunction(key);

    auto& bucket = table[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->key == key) {
            bucket.erase(it);
            itemCount--;
            return true;
        }
    }

    return false; // Elemento no encontrado
}

// Mostrar todos los elementos de la tabla hash
void HashTable::display() {
    if (itemCount == 0) {
        cout << "La tabla hash esta vacia." << endl;
        return;
    }

    cout << "Contenido de la tabla hash:" << endl;
    cout << "-------------------------" << endl;
    for (int i = 0; i < tableSize; i++) {
        if (!table[i].empty()) {
            cout << "Índice " << i << ": ";
            for (auto& pair : table[i]) {
                cout << "[" << pair.key << ":" << pair.value << "] ";
            }
            cout << endl;
        }
    }
    cout << "-------------------------" << endl;
    cout << "Total de elementos: " << itemCount << endl;
    cout << "Tamaño de la tabla: " << tableSize << endl;
    cout << "Factor de carga: " << static_cast<float>(itemCount) / tableSize << endl;
}

// Obtener el tamaño de la tabla
int HashTable::size() {
    return itemCount;
}

// Verificar si la tabla esta vacia
bool HashTable::isEmpty() {
    return itemCount == 0;
}

// Limpiar la tabla hash
void HashTable::clear() {
    for (auto& bucket : table) {
        bucket.clear();
    }
    itemCount = 0;
}

// Funcion para mostrar el menu de la Tabla Hash
void showHashTableMenu() {
    HashTable hashTable;
    int option = 0;
    bool exit = false;

    while (!exit) {
        cout << "\n=== MENU TABLA HASH ===" << endl;
        cout << "1. Insertar elemento" << endl;
        cout << "2. Buscar elemento" << endl;
        cout << "3. Eliminar elemento" << endl;
        cout << "4. Mostrar tabla" << endl;
        cout << "5. Limpiar tabla" << endl;
        cout << "6. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";

        // Validar entrada
        if (!(cin >> option)) {
            cin.clear(); // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar entrada invalida
            cout << "\nEntrada invalida. Por favor ingrese un numero." << endl;
            continue;
        }

        // Limpiar buffer de entrada
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (option) {
        case 1: { // Insertar elemento
            int key;
            string value;

            cout << "\n--- Insertar Elemento ---" << endl;
            cout << "Ingrese la clave (numero): ";

            // Validar entrada de clave
            if (!(cin >> key)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada invalida. La clave debe ser un numero." << endl;
                break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Ingrese el valor: ";
            getline(cin, value);

            hashTable.insert(key, value);
            cout << "Elemento insertado correctamente." << endl;
            break;
        }
        case 2: { // Buscar elemento
            int key;

            cout << "\n--- Buscar Elemento ---" << endl;
            cout << "Ingrese la clave a buscar: ";

            // Validar entrada de clave
            if (!(cin >> key)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada invalida. La clave debe ser un numero." << endl;
                break;
            }

            string result = hashTable.search(key);
            if (result.empty()) {
                cout << "Elemento con clave " << key << " no encontrado." << endl;
            }
            else {
                cout << "Valor encontrado: " << result << endl;
            }
            break;
        }
        case 3: { // Eliminar elemento
            int key;

            cout << "\n--- Eliminar Elemento ---" << endl;
            cout << "Ingrese la clave a eliminar: ";

            // Validar entrada de clave
            if (!(cin >> key)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada invalida. La clave debe ser un numero entero." << endl;
                break;
            }

            if (hashTable.remove(key)) {
                cout << "Elemento con clave " << key << " eliminado correctamente." << endl;
            }
            else {
                cout << "Elemento con clave " << key << " no encontrado." << endl;
            }
            break;
        }
        case 4: // Mostrar tabla
            cout << "\n--- Mostrar Tabla Hash ---" << endl;
            hashTable.display();
            break;
        case 5: // Limpiar tabla
            cout << "\n--- Limpiar Tabla Hash ---" << endl;
            cout << "¿Esta seguro que desea limpiar la tabla? (s/n): ";
            char confirm;
            cin >> confirm;

            if (tolower(confirm) == 's') {
                hashTable.clear();
                cout << "Tabla hash limpiada correctamente." << endl;
            }
            break;
        case 6: { // Volver al menú principal
            cout << "\n¿Esta seguro que desea volver al menu principal? Todos los cambios se perderan. (s/n): ";
            char confirm;
            cin >> confirm;

            if (tolower(confirm) == 's') {
                exit = true;
                cout << "Volviendo al menu principal..." << endl;
            }
            break;
        }
        default:
            cout << "\nOpcion invalida. Por favor seleccione una opcion valida." << endl;
        }
    }
}