#include "Usuario.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include "sha256.h"

Usuario::Usuario() {
	srand((unsigned)time(nullptr));
	privateKey = 100000 + (rand() % 900000);
	stringstream ss;
	ss << privateKey;
	publicKey = SHA256::cifrar(ss.str());
	amount = 0.0;
	cout << "Cuenta creada con exito." << endl;
	cout << "Tu clave privada es: " << privateKey << " - Guardala en un lugar seguro, no se volvera a mostrar." << endl;
	cout << "Tu clave publica (direccion) es: " << publicKey << endl;
}

// Saldo disponible de la cuenta (se mantiene en memoria mientras corre el
// proceso; la cadena queda como registro auditable de los intercambios).
double Usuario::getAmount() const {
	return amount;
}

// Receptor de fondos: acredita el monto en el saldo del usuario.
void Usuario::reciveAmount(int r) {
	amount += r;
}

// Emisor de fondos: descuenta el monto (la validacion de fondos ocurre al
// minar el bloque, en Blockchain::addBlock, igual que en el flujo real).
void Usuario::enviarAmount(int r, string key) {
	if (key == publicKey) {
		amount -= r;
	}
}

// SESION: abre la cuenta comprobando la clave privada contra la publica
// derivada por hash. La clave incorrecta no da acceso a la cartera.
bool Usuario::login(const string& privKey) const {
	stringstream ss;
	ss << privKey;
	return SHA256::cifrar(ss.str()) == publicKey;
}

