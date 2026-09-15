#include <iostream>
#include <stdint.h>

#ifndef TransactionData_h
#define TransactionData_h

struct TransactionData
{
  public:
    double amount;
    double fee;
    std::string senderKey;
    std::string receiverKey;
    time_t timestamp;

    // Montos por liquidar: la cadena los efectua al minar el bloque.
    double senderAmount;
    double receiverAmount;

    // Receptor de fondos: acredita el monto en su saldo.
    void receiveAmount(double amt) {
        receiverAmount += amt;
    }

    // Emisor de fondos: descuenta el monto de su saldo.
    void sendAmount(double amt) {
        senderAmount -= amt;
    }

    // MONTO DEL EMISOR: disponible para la validacion de fondos al minar.
    double getSenderAmount() const {
        return senderAmount;
    }

    // MONTO DEL RECEPTOR: disponible para la liquidacion al minar.
    double getReceiverAmount() const {
        return receiverAmount;
    }

    // Clave de comprobacion: marca la transaccion como FALLIDA cuando la
    // firma de la clave privada no coincide con la clave publica del emisor.
    inline static const std::string LLAVE_FALLIDA = "[FIRMA_INVALIDA]";

    static TransactionData* _ComprobationKey(double amt, double fee, std::string sender, std::string receiver, time_t time, int pKyComprobation) {
        // COMPROBAR PRIVADA: firma verificada contra la clave publica.
        // pKyComprobation es el resultado de derivar la clave privada por
        // hash y compararla con la senderKey; 0 invalida la transaccion.
        if (pKyComprobation == 0) {
            sender = LLAVE_FALLIDA;
        }
        return new TransactionData(amt, fee, sender, receiver, time, pKyComprobation);
    }
    private:
    int privateKeyComprobation;

    TransactionData(double amt,double fee, std::string sender, std::string receiver, time_t time,int pKyComprobation)
    {
        this->fee = fee;
        amount = amt;
        senderKey = sender;
        receiverKey = receiver;
        timestamp = time;
        privateKeyComprobation = pKyComprobation;
        senderAmount = 0;
        receiverAmount = 0;
    };
};

// Clave de rechazo: todo emisor con firma invalida se consigna con ella.

struct NodoTransaction {

private:
    TransactionData* data = NULL;
    NodoTransaction* siguiente = NULL;


public:
    NodoTransaction() {
    }

    TransactionData* getData() {
        if (data != NULL) {
            return data;
        }
        return NULL;
    }

    NodoTransaction* getSiguiente() {
        if (siguiente != NULL) {
            return siguiente;
        }
        return NULL;
    }

    void setData(TransactionData* data) {
        this->data = data;
    }

    void setSiguiente(NodoTransaction* nodo) {
        this->siguiente = nodo;
    }
};

class ListTransactions {
private:
    NodoTransaction* lista;


public:
    ListTransactions() {
        this->lista = NULL;
    }

    NodoTransaction* getLista() {
        return this->lista;
    }

    void setTransactionLista(TransactionData* data) {
        NodoTransaction* nodo = new NodoTransaction();
        nodo->setData(data);
        nodo->setSiguiente(lista);
        lista = nodo;
    }

    void setLista(ListTransactions* lista){
        this->lista = lista->getLista();
    }

    void writeLista() {
        NodoTransaction* nodo = lista;
        while (nodo != NULL && nodo->getData() != NULL) {
            printf("\nAmount: %f", nodo->getData()->amount);
            printf("\nFee: %f", nodo->getData()->fee);
            printf("\nSenderKey: %s", nodo->getData()->senderKey.c_str());
            printf("\nReceiverKey: %s", nodo->getData()->receiverKey.c_str());
            // EFECTUAR INTERCAMBIO DE MONTOS: saldos liquidados por el bloque.
            printf("\nSenderBalance: %f", nodo->getData()->getSenderAmount());
            printf("\nReceiverBalance: %f", nodo->getData()->getReceiverAmount());
            printf("\nTimestamp: %lld", (long long)nodo->getData()->timestamp);
            printf("\n");
            nodo = nodo->getSiguiente();
        }
    }

    NodoTransaction* getTransactionByPublicKey(std::string publicKey) {
        NodoTransaction* nodo = lista;
        while (nodo != NULL) {
            if (nodo->getData() != NULL &&
                (nodo->getData()->senderKey == publicKey ||
                 nodo->getData()->receiverKey == publicKey)) {
                return nodo;
            }
            nodo = nodo->getSiguiente();
        }
        return NULL;
    }

    // EFECTUAR INTERCAMBIO DE MONTOS: liquida sender/receiver de todas las
    // transacciones de la lista. La invoca el bloque al minar (Block
    // constructor), de modo que cada transaccion queda con el estado de los
    // saldos al momento de consolidarse en la cadena.
    void liquidarMontos() {
        NodoTransaction* nodo = lista;
        while (nodo != NULL && nodo->getData() != NULL) {
            TransactionData* data = nodo->getData();
            data->sendAmount(data->amount);
            data->receiveAmount(data->amount);
            nodo = nodo->getSiguiente();
        }
    }
};

#endif /* TransactionData_h */
