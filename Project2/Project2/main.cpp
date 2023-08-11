#include <iostream>
#include <ctime>
#include <vector>


#include "Block.h"
#include "Blockchain.h"
#include "TransactionData.h"

using namespace std;

//AGREGAR==============
//USUARIOS
//CARTERA
//TRANSACCIONES

int main()
{
    //Creamos la cadena
    //Bloque genesis
    Blockchain awesomeCoin;
    
    //Agregamos Primer Bloque
    time_t data1Time;
    TransactionData data1(1.5, "Joe", "Sally", time(&data1Time));
    cout << "Se bloquea" << endl;
    awesomeCoin.addBlock(data1);
    
    time_t data2Time;
    TransactionData data2(34, "Martha", "Fred", time(&data2Time));
    awesomeCoin.addBlock(data2);

    time_t data6Time;
    TransactionData data6(275, "pedro", "fernandez", time(&data6Time));
    awesomeCoin.addBlock(data6);

    time_t data7Time;
    TransactionData data7(0.2345, "franco", "milei", time(&data7Time));
    awesomeCoin.addBlock(data7);
    
    //Pintamos Cadena
    awesomeCoin.printChain();
    
    //Verificamos valides
    printf("\nIs chain still valid? %d\n", awesomeCoin.isChainValid());
    if (awesomeCoin.isChainValid() == 0) {
        cout << "ESTA CADENA NO ES VALIDA" << endl;
    }
    else if (awesomeCoin.isChainValid() == 1) {
        cout << "ESTA CADENA ES VALIDA" << endl;
    }
    
    //Intentamos alterar la cadena
    Block *hackBlock = awesomeCoin.getLatestBlock();
    hackBlock->data.amount = 10000; 
    hackBlock->data.receiverKey = "Jon"; //CAMBIAMOS EL DESTINATARIO

    //Pintamos Cadena
    awesomeCoin.printChain();

    //Verificamos valides de la Corrupcion y de la nueva cadena
    printf("\nIs chain still valid? %d\n", awesomeCoin.isChainValid());
    if (awesomeCoin.isChainValid() == 0) {
        cout << "ESTA CADENA NO ES VALIDA" << endl;
    }
    else if (awesomeCoin.isChainValid() == 1) {
        cout << "ESTA CADENA ES VALIDA" << endl;
    }
    
    return 0;
}
