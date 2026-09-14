#include "Usuario.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>

Usuario::Usuario() {
	srand((unsigned)time(nullptr));
	privateKey = 100000 + (rand() % 900000);
	stringstream ss;
	ss << privateKey;
	std::hash<std::string> tDataHash;
	publicKey = to_string(tDataHash(ss.str()));
	std::cout << "Tu clave privada es: " << privateKey << " Guardala en un lugar seguro" << endl;
	std::cout << "Tu clave publica es: " << publicKey << " Guardala para evitar errores" << endl;
}

