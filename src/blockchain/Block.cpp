#include <stdio.h>
#include <string>
#include <sstream>
#include "Block.h"
#include <vector>
#include "sha256.h"

using namespace std;

//Constructor
Block::Block(int idx, ListTransactions* list, string prevHash,int nonce)
{
    index = idx;
    listTransactions->setLista(list);
    previousHash = prevHash;
    _nNonce = nonce;
    transactions = 0;
    //EFECTUAR INTERCAMBIO DE MONTOS AL MINAR BLOQUE: el bloque liquida los
    //montos de sus transacciones (sender/receiver) al consolidarse en cadena.
    listTransactions->liquidarMontos();
    _CalculateFee();
    this->blockHash = _CalculateHash();
}

//Funciones de acceso privado
string Block::_CalculateHash() const {

    stringstream ss;
    NodoTransaction* aux = listTransactions->getLista();

    //Recorremos TODAS las transacciones (protegido contra lista vacia)
    while (aux != NULL && aux->getData() != NULL)
    {
        TransactionData* data = aux->getData();
        ss << std::to_string(data->amount) + data->receiverKey + data->senderKey + std::to_string(data->timestamp);
        aux = aux->getSiguiente();
    }

    ss << std::to_string(fee) << std::to_string(_nNonce);
    std::string toHashS = ss.str();

    // HASH DIRECTO: SHA-256 sobre previousHash + datos del bloque. Se elimina
    // el std::hash intermedio: no era portable entre plataformas (su algoritmo
    // no esta especificado por el estandar) ni criptograficamente solido.
    return SHA256::cifrar(previousHash + toHashS);
}
void Block::_CalculateFee(){
    NodoTransaction* aux = listTransactions->getLista();
    double totalFee = 0;
    while (aux != NULL && aux->getData() != NULL)
    {
        TransactionData* data = aux->getData();
        totalFee += data->fee;
        aux = aux->getSiguiente();
    }
    this->fee = totalFee;
}

//Funciones de acceso publico
void Block::MineBlock(uint32_t nDifficulty) {
    stringstream ss;
    for (uint32_t i = 0; i < nDifficulty; ++i)
    {
        ss << "0";
    }
    string str(ss.str());

    do {
        _nNonce+= 1;
        blockHash = _CalculateHash();
        cout << blockHash << "++++++++++++++++" << _nNonce << endl;
    } while (blockHash.substr(0, nDifficulty) != str);
    transactions++;
    cout << "Block mined: " << blockHash << endl;
}




string Block::getHash() const
{
    return blockHash;
}

string Block::getPreviousHash() const
{
    return previousHash;
}

//Validamos el hash
bool Block::isHashValid() const
{
    return _CalculateHash() == getHash();
}

int Block::getIndex()const
{
    return index;
}

int64_t Block::getNonce() const
{
    return _nNonce;
}

double Block::getFeeBlock() {
    return fee;
}