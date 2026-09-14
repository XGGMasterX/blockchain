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

    static TransactionData* _ComprobationKey(double amt, double fee, std::string sender, std::string receiver, time_t time, int pKyComprobation) {
        //COMPROBAR PRIVADA OBTENIDA HASHEANDO Y VERIFICANDO CON SENDERKEY

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
    };
};
;


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
            //ARREGLAR ESCRITURA DE LOS DATOS PRINCIPALES DEL BLOQUE
            printf("\nAmount: %f", nodo->getData()->amount);
            printf("\nFee: %f", nodo->getData()->fee);
            printf("\nSenderKey: %s", nodo->getData()->senderKey.c_str());
            printf("\nReceiverKey: %s", nodo->getData()->receiverKey.c_str());
            printf("\nTimestamp: %lld", (long long)nodo->getData()->timestamp);
            printf("\n");
            nodo = nodo->getSiguiente();
        }
    }

    NodoTransaction* getTransactionByPublicKey(std::string publicKey) {
        //MOSTAR TRANSACCION CORRESPONDIENTE
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
};

#endif /* TransactionData_h */
