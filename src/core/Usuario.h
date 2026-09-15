#ifndef Usuarios_h
#define Usuarios_h
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
using namespace std;

// ============================================================================
// Usuario — identidad y sesion: claves publica/privada y saldo disponible.
// ============================================================================
// La clave privada es un entero aleatorio de 6 digitos; la publica se deriva
// con SHA-256 (src/crypto/sha256.h) y hace de direccion on-chain. La sesion
// se abre con login(privKey) contra una instancia ya creada en el registro.
// ============================================================================
class Usuario {
  public:
	  Usuario();
	  string publicKey;
	  double amount;

	  void reciveAmount(int r);
	  void enviarAmount(int r, string key);
	  double getAmount() const;
	  bool login(const string& privKey) const;

  private:
	int privateKey;
};
#endif
