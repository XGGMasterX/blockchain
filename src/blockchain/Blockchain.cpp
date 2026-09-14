#include <stdio.h>
#include <ctime>
#include <string>
#include "Blockchain.h"
#include <vector>

//Constructor de la cadena de blockes (blockchain)
Blockchain::Blockchain()
{
    Block* genesis = createGenesisBlock();
    chain.push_back(genesis);
    _nNDifficulty = 2;
}

// Public Chain Getter
std::vector<Block*> Blockchain::getChain() {
    return chain;
}

//Creacion del bloque genesis
Block* Blockchain::createGenesisBlock()
{
    //Obtenemos el tiempo
    std::time_t current;
    
    ListTransactions* genesisTransactionList = new ListTransactions();
    TransactionData* d = NULL;
    d = d->_ComprobationKey(0, 0, "Genesis", "Genesis", time(&current), 0);
    genesisTransactionList->setTransactionLista(d);

    Block* genesis = new Block(0, genesisTransactionList, "0",0);
    return genesis;
}


Block* Blockchain::getLatestBlock()
{
    return chain.back();
}

//Funcion para agregar nuevos bloques a la cadena
//VERIFICAR MONTO DE LA DIRECCION
void Blockchain::addBlock(ListTransactions* list)
{
    std::string previousHash;
    int index = (int)chain.size();
    if (chain.size() > 0) {
        previousHash = getLatestBlock()->getHash();
    }
    else if (chain.size() == 0) {
        previousHash = "0";
    }
    Block* newBlock = new Block(index, list, previousHash, 0);
    newBlock->MineBlock(_nNDifficulty);
    chain.push_back(newBlock);
    //EFECTUAR INTERCAMBIO DE MONTOS ALL MINAR BLOQUE
}

bool Blockchain::isChainValid()
{
    std::vector<Block*>::iterator it;
    
    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block* currentBlock = *it;
        if (!currentBlock->isHashValid())
        {
            return false;
        }
        
        
        if (it != chain.begin())
        {
            Block* previousBlock = *(it - 1);
            if (currentBlock->getPreviousHash() != previousBlock->getHash())
            {
                return false;
            }
        }
    }
    
    return true;
}

//Pintamos cadena completa
void Blockchain::printChain() {
    std::vector<Block*>::iterator it;

    for (it = chain.begin(); it != chain.end(); ++it)
    {   
        printf("\n\nBlock ===================================");
        //ARREGLAR ESCRITURA DE LOS DATOS PRINCIPALES DEL BLOQUE
        Block* currentBlock = *it;
        printf("\nIndex: %d", currentBlock->getIndex());
        if (currentBlock->listTransactions->getLista()->getData()->senderKey != "Genesis") {
            currentBlock->listTransactions->writeLista();
        }
        printf("\nNonce: %lld", (long long)currentBlock->getNonce());
        std::cout << endl;
        std::cout << "FeeBlock: " << currentBlock->getFeeBlock() << endl;
        std::cout << "Hash: " << currentBlock->getHash() << endl;
        std::cout << "Previous Hash: " << currentBlock->getPreviousHash() << endl;
        std::cout << "Is Block Valid?: " << currentBlock->isHashValid() << endl;

    }
}

