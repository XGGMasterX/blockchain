#ifndef Block_h
#define Block_h


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
    double fee;
    string publicKeyMinner;

    void _CalculateFee();
    string _CalculateHash() const;

public:
    Block(int idx, ListTransactions* d, string prevHash, int nonce);
    double getFeeBlock();
    int getIndex() const;
    int64_t getNonce() const;
    //Obtenemos hash principal
    string getHash() const;

    void MineBlock(uint32_t nDifficulty);

    //Obtenemos hash de transaccion anterior
    string getPreviousHash() const;

    //Validacion de hash
    bool isHashValid() const;

    //TODO TRANSACCIONES
    int transactions;
    ListTransactions* listTransactions = new ListTransactions();
};
#endif /* Block_h */
