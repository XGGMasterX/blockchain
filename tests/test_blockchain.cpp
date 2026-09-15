#include "Blockchain.h"
#include <iostream>
#include <string>

using namespace std;

static int fallos = 0;

static void comprobar(const string& nombre, const string& obtenido, const string& esperado) {
    if (obtenido == esperado) {
        cout << "[OK]    " << nombre << endl;
    } else {
        cout << "[FALLO] " << nombre << endl;
        cout << "        obtenido: " << obtenido << endl;
        cout << "        esperado: " << esperado << endl;
        fallos++;
    }
}

int main() {
    // 1. La cadena arranca con el genesis y es valida
    Blockchain bc;
    comprobar("genesis: la cadena arranca valida", std::to_string(bc.isChainValid()), "1");
    comprobar("genesis: la cadena tiene un bloque", std::to_string(bc.getChain().size()), "1");
    comprobar("genesis: previousHash = 0", bc.getChain()[0]->getPreviousHash(), "0");

    // 2. addBlock: PoW con prefijo de dificultad, encadenado y comisiones
    ListTransactions* lista = new ListTransactions();
    lista->setTransactionLista(TransactionData::_ComprobationKey(150, 5, "Sally", "Joe", 1700000000, 1));
    bc.addBlock(lista);
    Block* b = bc.getLatestBlock();
    comprobar("PoW: el hash minado lleva el prefijo de dificultad (00)", b->getHash().substr(0, 2), "00");
    comprobar("encadenado: previousHash = hash del bloque anterior", b->getPreviousHash(), bc.getChain()[0]->getHash());
    comprobar("fee: el bloque acumula las comisiones", std::to_string(b->getFeeBlock()), "5.000000");
    comprobar("cadena valida tras minar", std::to_string(bc.isChainValid()), "1");

    // 3. EFECTUAR INTERCAMBIO DE MONTOS: el bloque liquida los saldos al minar
    NodoTransaction* n = b->listTransactions->getLista();
    comprobar("balance emisor: debito liquidado", std::to_string(n->getData()->getSenderAmount()), "-150.000000");
    comprobar("balance receptor: credito liquidado", std::to_string(n->getData()->getReceiverAmount()), "150.000000");

    // 4. COMPROBAR PRIVADA: firma invalida -> emisor marcado con LLAVE_FALLIDA
    TransactionData* mala = TransactionData::_ComprobationKey(10, 1, "Joe", "Sally", 1700000001, 0);
    comprobar("firma invalida marcada", mala->senderKey, TransactionData::LLAVE_FALLIDA);

    // 5. Inmutabilidad: mutar un bloque invalida la cadena
    b->listTransactions->getLista()->getData()->amount = 999;
    comprobar("mutacion de monto detectada", std::to_string(bc.isChainValid()), "0");

    cout << (fallos == 0 ? "\nTODOS LOS TESTS PASARON" : "\\nHAY TESTS FALLIDOS") << endl;
    return fallos == 0 ? 0 : 1;
}
