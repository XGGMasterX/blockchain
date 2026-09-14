#include <iostream>
#include <ctime>
#include <vector>
#include <limits>
#include <cstdlib>
#include "Usuario.h" 
#include "Blockchain.h" 

using namespace std;

//AGREGAR==============
//USUARIOS
//CARTERA
Usuario* registerAcount();
void ingresoCuenta();
void loginAcount(Usuario*& x, ListTransactions *& lista);
void inAcoint();
void Transaction(ListTransactions *& lista);
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

void loginAcount(Usuario *&x,ListTransactions *& lista) {
    if (x != NULL) {
        limpiarPantalla();
        do {
            inAcoint();
            switch (orden)
            {
            case 1:  Transaction(lista);
                break; 
            default:
                break;
            }

            limpiarPantalla();
             
        } while (orden != 2);
    }
}

//EL ULTIMO INGRESO NO SE ASIGNA
//MAS PERSONALIZACION DE TRANSACTIONS
void Transaction(ListTransactions *&lista) {

    double amount;
    double fee;

    cout << "Cuanto dinero desea enviar ?:"; cin >> amount;
    cout << endl;
    cout << "Cuanta Comision desea darle al minero ?:"; cin >> fee;
    cout << endl;

    if (true) {
        //COMENZAMOS BLOQUE///////////////
        time_t data1Time;
        TransactionData* data1 = NULL;
        data1  =  data1->_ComprobationKey(amount, fee, "Joe", "Sally", time(&data1Time), 0);
        lista->setTransactionLista(data1);
    }

    pausar();
}

void closeBlockChain(Blockchain awesomeCoin,ListTransactions *& lista){
    //TERMINAMOS BOQUE///////////////
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

    //HACER Intentamos alterar la cadena 
    pausar();

}

int main()
{
    //Creamos la cadena
    //Bloque genesis
    //cout << "GENESIS" << endl;
    Blockchain awesomeCoin;

    //cout << "Cadena" << endl;
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
