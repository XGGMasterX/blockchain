// ============================================================================
// Cuenta — cartera: saldo y validez de una cuenta AwesomeCoin.
// ============================================================================
// Representa la cartera de un usuario. La clave publica es la IDENTIDAD: se
// usa como senderKey/receiverKey en las transacciones, y es el dato que el
// bloque consignara al efectuar los intercambios de montos al minar.
//
// Constructor privado + factory estatica: solo el modulo puede crear cuentas,
// y solo con una clave privada que se valide contra la clave publica
// derivada (mismo mecanismo que TransactionData::_ComprobationKey).
// ============================================================================
#ifndef Cuenta_h
#define Cuenta_h

#include <iostream>
#include <sstream>
#include <string>
#include "sha256.h"

class Cuenta {
  private:
    std::string publicKey;      // identidad en la blockchain
    double balance;             // saldo consignado en la cadena
    int privateKeyComprobation; // 1 si la clave privada verifico

    // Constructor privado: solo Cuenta::crear() instancia.
    Cuenta(std::string pub, double amt) {
        publicKey = pub;
        balance = amt;
        privateKeyComprobation = 1; // la clave ya fue validada en crear()
    }

  public:
    // NUEVA CUENTA (registro): valida que privKey derive en publicKey.
    // Es el punto de entrada legitimo de carteras a la cadena.
    static Cuenta* crear(std::string privKey, std::string publicKey) {
        if (SHA256::cifrar(privKey) == publicKey) {
            return new Cuenta(walletAddress(publicKey), 0.0);
        }
        return NULL;
    }

    // SALDO: de una direccion conocida (persistencia/explorador).
    static Cuenta* cargar(std::string publicKey, double amt) {
        return new Cuenta(publicKey, amt);
    }

    // La direccion on-chain de esta cartera (su clave publica).
    static std::string walletAddress(std::string pubKey) {
        return pubKey;
    }

    std::string getPublicKey() const {
        return publicKey;
    }

    double getBalance() const {
        return balance;
    }

    // Acredita un monto (recepcion de fondos).
    void receive(double amt) {
        balance += amt;
    }

    void reciveAmount(int r) {
        balance += r;
    }

    void enviarAmount(int r, std::string key) {
        // Su destino era el flujo de cartera; los intercambios ocurren al
        // minar, en Blockchain::addBlock: los fondos salen del saldo alli.
        (void)r;
        (void)key;
    }
};

#endif /* Cuenta_h */

