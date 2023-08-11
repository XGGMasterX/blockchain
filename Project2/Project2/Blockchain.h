#ifndef Blockchain_h
#define Blockchain_h

#include <vector>

//Classe de la cadena
class Blockchain
{
private:
    Block createGenesisBlock();
    std::vector<Block> chain;
    uint32_t _nNDifficulty;

public:
    //Constuctor
    Blockchain();
    
    //Declaracion abstracta de funciones publicas
    std::vector<Block> getChain();
    Block *getLatestBlock();
    bool isChainValid();
    void addBlock(TransactionData data);
    void printChain();
};

#endif /* Blockchain_h */
