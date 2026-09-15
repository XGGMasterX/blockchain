#include <iostream>
#include <ctime>
#include <vector>
#include <limits>
#include <cstdlib>
#include "Usuario.h"
#include "Blockchain.h"

using namespace std;

Usuario* registerAcount();
void ingresoCuenta();
void loginAcount(Usuario*& x, ListTransactions *& lista);
void inAcoint();
void Transaction(Usuario* emisor, ListTransactions *& lista);
void closeBlockChain(Blockchain awesomeCoin, ListTransactions *& lista);

//Limpieza de pantalla portable (Windows/Linux)
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//Pausa portable (sustituye a _getch() de conio.h de Windows)
void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

int orden;

void ingresoCuenta(){
    std::cout << "Que desea realizar ?";
    std::cout << endl;
    std::cout << "Crear Cuenta--(1)";
    std::cout << endl;
    std::cout << "Ingresar en Cuenta--(2)";
    std::cout << endl;
    std::cout << "Salir--(3)";
    std::cout << endl;
    cin >> orden;
}

void inAcoint() {
    std::cout << "Que desea realizar ?";
    std::cout << endl;
    std::cout << "Realizar Transferencia--(1)";
    std::cout << endl;
    std::cout << "Salir--(2)";
    std::cout << endl;
    cin >> orden;
}

Usuario* registerAcount() {
    return new Usuario();
}

void loginAcount(Usuario*& x, ListTransactions *& lista) {
    if (x != NULL) {
        // COMPROBAR PRIVADA: la sesion se abre con la clave privada; el hash
        // debe reproducir la clave publica de la cuenta. Sin sesion no hay
        // cartera (y las transferencias se consignarian con firma invalida).
        string privKey;
        cout << "Ingresa tu clave privada: ";
        cin >> privKey;

        if (x->login(privKey)) {
            cout << "Sesion abierta. Bienvenido de vuelta." << endl;
            pausar();
            limpiarPantalla();
            do {
                inAcoint();
                switch (orden)
                {
                case 1:  Transaction(x, lista);
                    break;
                default:
                    break;
                }

                limpiarPantalla();

            } while (orden != 2);
        }
        else {
            cout << "Clave privada incorrecta. Acceso denegado." << endl;
            pausar();
        }
    }
    else {
        cout << "Primero debes crear una cuenta (opcion 1)." << endl;
        pausar();
    }
}

void Transaction(Usuario* emisor, ListTransactions *&lista) {

    double amount;
    double fee;
    string receiver;

    cout << "Direccion del receptor (clave publica): ";
    cin >> receiver;
    cout << endl;
    cout << "Cuanto dinero desea enviar ?:"; cin >> amount;
    cout << endl;
    cout << "Cuanta Comision desea darle al minero ?:"; cin >> fee;
    cout << endl;

    if (emisor != NULL) {
        //COMENZAMOS BLOQUE///////////////
        time_t data1Time;
        TransactionData* data1 = NULL;
        // COMPROBAR PRIVADA: la sesion ya verifico la clave; el emisor firma
        // con su clave publica (identidad on-chain). El receptor es el que
        // indico el usuario.
        data1 = data1->_ComprobationKey(amount, fee, emisor->publicKey, receiver, time(&data1Time), 1);
        // EFECTUAR INTERCAMBIO DE MONTOS: los saldos (sender/receiver) los
        // liquida el bloque al minar; aqui solo se emite la transferencia.
        lista->setTransactionLista(data1);
        cout << "Transferencia emitida de " << amount << " a " << receiver
             << " (comision: " << fee << ")." << endl;
    }

    pausar();
}

void closeBlockChain(Blockchain awesomeCoin, ListTransactions *& lista){
    //TERMINAMOS BLOQUE///////////////
    awesomeCoin.addBlock(lista);

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

    pausar();
}

int main()
{
    //Creamos la cadena
    //Bloque genesis (ancla de la cadena: indice 0, previousHash "0")
    Blockchain awesomeCoin;

    //Agregamos Primer Bloque

    ListTransactions* lista = new ListTransactions();
    Usuario* miCuenta = NULL;
    do {
        ingresoCuenta();
        switch (orden)
        {
        case 1: miCuenta = registerAcount();
            break;
        case 2: loginAcount(miCuenta,lista);
            break;
        default:
            break;
        }

        limpiarPantalla();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (orden != 3);
    closeBlockChain(awesomeCoin, lista);

    pausar();
    return 0;
}
