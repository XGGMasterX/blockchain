#include "sha256.h"
#include <iostream>
#include <string>

// Vectores de prueba oficiales de SHA-256 (FIPS 180-4 / NIST).
using namespace std;

static int fallos = 0;

static void comprobar(const string& nombre, const string& obtenido, const string& esperado) {
    if (obtenido == esperado) {
        cout << "[OK]    " << nombre << endl;
    } else {
        cout << "[FALLO] " << nombre << endl;
        cout << "        obtenido: " << obtenido << endl;
        cout << "        esperado: " << esperado << endl;
        fallos++;
    }
}

int main() {
    comprobar("cadena vacia (FIPS 180-4)",
              SHA256::cifrar(""),
              "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");

    comprobar("abc (FIPS 180-4)",
              SHA256::cifrar("abc"),
              "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");

    comprobar("pangrama clasico",
              SHA256::cifrar("The quick brown fox jumps over the lazy dog"),
              "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592");

    // Mensaje de 64 bytes: exige dos bloques de 512 bits (padding completo).
    comprobar("64 x 'a' (dos bloques de 512 bits)",
              SHA256::cifrar(string(64, 'a')),
              "ffe054fe7ae0cb6dc65c3af9b61d5209f439851db43d0ba5997337df154668eb");

    // Determinismo: dos llamadas sobre la misma entrada producen el mismo hash.
    comprobar("determinismo",
              SHA256::cifrar("AwesomeCoin"),
              SHA256::cifrar("AwesomeCoin"));

    cout << (fallos == 0 ? "\nTODOS LOS TESTS PASARON" : "\nHAY TESTS FALLIDOS") << endl;
    return fallos == 0 ? 0 : 1;
}
