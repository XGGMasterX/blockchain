#ifndef Block_h
#define Block_h

#include <iostream>
#include "TransactionData.h"
using namespace std;
//Clase de blockes
class Block
{
private:
    int index;
    string blockHash;
    string previousHash;
    int64_t _nNonce;
    int transacciones = 0;
    //AGREGAR LISTA DE TRANSACCIONES
    //AGREGAR FEE (RECONPENSA)
    //AGREGAR KEY PUBLICA DE MINERO
    
public:
    //Constuctor
    Block(int idx, TransactionData d, string prevHash, int nonce);
    
    int getIndex() const;

    int64_t getNonce() const;
    
    //Obtenemos hash principal
    string getHash() const;
    
    void MineBlock(uint32_t nDifficulty);
    string _CalculateHash() const;
    //Obtenemos hash de transaccion anterior
    string getPreviousHash() const;
    
    TransactionData data;
    
    //Validacion de hash
    bool isHashValid() const;
};

#endif /* Block_h */
