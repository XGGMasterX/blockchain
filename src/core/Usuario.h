#ifndef Usuarios_h
#define Usuarios_h
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
using namespace std;

class Usuario {
  public:
	  Usuario();
	  string publicKey;
	  double amount;

	  void reciveAmount(int r);
	  void enviarAmount(int r, string key);
  private:
	int privateKey;

};
#endif
