#include <stdio.h>
#include <ctime>
#include <string>

#include "Block.h"
#include "Blockchain.h"

#include <vector>

//Constructor de la cadena de blockes (blockchain)
Blockchain::Blockchain()
{
    Block genesis = createGenesisBlock();
    chain.push_back(genesis);
    _nNDifficulty = 5;
}

// Public Chain Getter
std::vector<Block> Blockchain::getChain() {
    return chain;
}

//Creacion del bloque genesis
Block Blockchain::createGenesisBlock()
{
    //Obtenemos el tiempo
    std::time_t current;
    
    TransactionData d(0, "Genesis", "Genesis", time(&current));
    
    Block genesis(0, d, "0",0);
    return genesis;
}


Block *Blockchain::getLatestBlock()
{
    return &chain.back();
}

//Funcion para agregar nuevos bloques a la cadena
//MODIFICAR PARA TRANSACCION INDIVIDUAL
//VERIFICAR MONTO DE LA DIRECCION
void Blockchain::addBlock(TransactionData d)
{
    
    int index = (int)chain.size();
    string previousHash = (int)chain.size() > 0 ? getLatestBlock()->getHash() : 0;
    Block newBlock(index, d, previousHash, 0);
    newBlock.MineBlock(_nNDifficulty);
    chain.push_back(newBlock);
}

bool Blockchain::isChainValid()
{
    std::vector<Block>::iterator it;
    
    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        if (!currentBlock.isHashValid())
        {
            return false;
        }
        
        
        if (it != chain.begin())
        {
            Block previousBlock = *(it - 1);
            if (currentBlock.getPreviousHash() != previousBlock.getHash())
            {
                return false;
            }
        }
    }
    
    return true;
}

//Pintamos cadena completa
void Blockchain::printChain() {
    std::vector<Block>::iterator it;
    
    for (it = chain.begin(); it != chain.end(); ++it)
    {   
        //ARREGLAR ESCRITURA DE LOS DATOS PRINCIPALES DEL BLOQUE
        Block currentBlock = *it;
        printf("\n\nBlock ===================================");
        printf("\nIndex: %d", currentBlock.getIndex());
        printf("\nAmount: %f", currentBlock.data.amount);
        printf("\nSenderKey: %s", currentBlock.data.senderKey.c_str());
        printf("\nReceiverKey: %s", currentBlock.data.receiverKey.c_str());
        printf("\nTimestamp: %d", (int)currentBlock.data.timestamp);
        printf("\nHash: %zu", currentBlock.getHash());
        printf("\nPrevious Hash: %zu", currentBlock.getPreviousHash());
        printf("\nIs Block Valid?: %d", currentBlock.isHashValid());
        printf("\nNonce: %zu", currentBlock.getNonce());
    }
}

