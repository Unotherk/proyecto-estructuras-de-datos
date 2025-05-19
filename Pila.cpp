#include <iostream>
using namespace std;

struct pilas {
	int valor;
	pilas* direccionA;
};
pilas* pilao, * pilaaux;
void ingreso();
void mostrar();
void eliminar();
void buscar();
int main() {
	int opcion;
	while (true) {
		cout << "1. Ingreso de datos a la pila" << endl;
		cout << "2. Leer datos de la pila" << endl;
		cout << "3. Eliminar datos de la pila" << endl;
		cout << "4. Buscar datos en la pila" << endl;
		cin >> opcion;
		switch (opcion)
		{
		case 1:
			ingreso();
			break;
		case 2:
			mostrar();
			break;
		case 3:
			eliminar();
			break;
		case 4:
			buscar();
			break;
		default:
			break;
		}
	}
}
void ingreso() {
	if (pilao == NULL)
	{
		pilao = new(pilas);
		cout << "Ingrese el primer dato a la pila" << endl;
		cin >> pilao->valor;
		cout << "(Dato ingresado correctamente)" << endl;
		pilao->direccionA = NULL;
		return;
	}
	pilaaux = new(pilas);

	cout << "Ingrese un dato a la pila" << endl;
	cin >> pilaaux->valor;
	cout << "(Dato ingresado correctamente)" << endl;
	pilaaux->direccionA = pilao;
	pilao = pilaaux;
}

void mostrar() {
	if (pilao == NULL)
	{
		cout << "La pila está vacía!" << endl;
	}
	pilaaux = pilao;
	cout << "Los datos de la pila son: " << endl;
	while(pilaaux != NULL) {
		cout << pilaaux->valor << endl;
		pilaaux = pilaaux->direccionA;
	}
	cout << "FIN MF" << endl;
}

void eliminar() {
	if (pilao == NULL)
	{
		cout << "La pila está vacía!" << endl;
		return;
	}
	pilaaux = new(pilas);
	pilaaux = pilao;
	cout << "Elemento eliminado: " << pilaaux->valor << endl;
	pilao = pilaaux->direccionA;
	delete(pilaaux);
}

void buscar() {
	if (pilao == NULL)
	{
		cout << "La pila está vacía!" << endl;
		return;
	}
	int buscarDatos;
	bool datoEncontrado = false;
	pilaaux = pilao;
	cout << "Ingrese el dato a buscar: " << endl;
	cin >> buscarDatos;
	while (pilaaux != NULL) {
		if (buscarDatos == pilaaux->valor) {
			cout << "Dato encontrado exitosamente, el valor es: " << pilaaux->valor << endl;
			datoEncontrado = true;
			break;
		}
		pilaaux = pilaaux->direccionA;
	}
	if (datoEncontrado == false) {
		cout << "El dato no se encuentra en la pila." << endl;
	}
}