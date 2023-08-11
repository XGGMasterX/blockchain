#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "Block.h"
#include "TransactionData.h"
#include <vector>
#include "sha256.h"
#include <conio.h>

using namespace std;

//Constructor
Block::Block(int idx, TransactionData d, string prevHash,int nonce)
{
    index = idx;
    data = d;
    previousHash = prevHash;
    _nNonce = nonce;
    blockHash = _CalculateHash();
}

//Funciones de acceso privado
int Block::getIndex()const
{
    return index;
}

int64_t Block::getNonce() const
{
    return _nNonce;
}

//Minado de Blocke
//ESTUDIAR PORQUE SE VUELVE ETERNO EL BUCCLE
void Block::MineBlock(uint32_t nDifficulty) {
    stringstream ss;
    for (uint32_t i = 0; i < nDifficulty; ++i)
    {
        ss << "0";
    }
    ss << "\0";
    string str(ss.str());
   
    if (data.receiverKey != "genesis") {
        do {
            _nNonce+= 1;
            blockHash = _CalculateHash();
            cout << blockHash << "++++++++++++++++" << _nNonce << endl;
        } while (blockHash.substr(0, nDifficulty) != str);
        transacciones++;
        cout << "Block mined: " << blockHash << endl;
    }
    else if (data.receiverKey == "genesis") {
        blockHash = _CalculateHash();
    }
}

inline string Block::_CalculateHash() const {

    std::string toHashS = std::to_string(data.amount) + data.receiverKey + data.senderKey + std::to_string(data.timestamp) + std::to_string(_nNonce);
    std::hash<std::string> tDataHash;
    std::hash<std::string> prevHash;

    string limitHash = to_string(tDataHash(toHashS) ^ (prevHash(previousHash)) << 1);
    string sha256 = SHA256::cifrar(limitHash);
    return sha256;
}

//Funciones de acceso publico
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
