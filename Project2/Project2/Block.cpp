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
    if (previousHash == "0") {
        this->blockHash = _CalculateHash();
    }
    _CalculateFee();
}

//Funciones de acceso privado
inline string Block::_CalculateHash() const {

    std::string toHashS;
    stringstream ss;
    NodoTransaction* lista = listTransactions->getLista();
    NodoTransaction* aux = new NodoTransaction();

    if (lista->getData() != NULL) {
        aux = lista;
        while (aux->getData() != NULL)
        {
            TransactionData* data = aux->getData();
            ss << std::to_string(data->amount) + data->receiverKey + data->senderKey + std::to_string(data->timestamp);

            if (aux->getSiguiente() != NULL) {
                aux = aux->getSiguiente();
            }
            else if (aux->getSiguiente() == NULL) {
                break;
            }
        }
        ss << std::to_string(fee) << std::to_string(_nNonce);
        std::string toHashS = ss.str();

        std::hash<std::string> tDataHash;
        std::hash<std::string> prevHash;

        string limitHash = to_string(tDataHash(toHashS) ^ (prevHash(previousHash)) << 1);
        string sha256 = SHA256::cifrar(limitHash);
        return sha256;
    }

    return "NULL";
}

void Block::_CalculateFee(){
    NodoTransaction* lista = listTransactions->getLista();
    NodoTransaction* aux = new NodoTransaction();
    double totalFee = 0;
    if (lista->getData() != NULL) {
        aux = lista;
        while (aux->getData() != NULL)
        {
            TransactionData* data = aux->getData();
            totalFee += data->fee;
            if (aux->getSiguiente() != NULL) {
                aux = aux->getSiguiente();
            }
            else if (aux->getSiguiente() == NULL) {
                break;
            }
        }
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
    ss << "\0";
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