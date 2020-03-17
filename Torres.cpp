#include "Torres.h"
#include <iostream>
#include <windows.h>

Torres::Torres() {
    filas = 3;
    columnas = 0;
    tablero = nullptr;
}

void Torres::empezar() {
    std::cout << "Con cuantos discos va a jugar?: ";
    std::cin >> columnas;
    tablero = (int*)malloc(sizeof(int) * filas * columnas);
    iniciarJuego();
}

void Torres::menu() {
    int Op, disc;
    while (true) {
        system("cls");
        std::cout << "\t Torres de Hanoi" << std::endl
            << "1.Jugar" << std::endl
            << "2.Reglas" << std::endl
            << "3.Calcular movimientos" << std::endl
            << "4.Salir" << std::endl
            << "Opcion: ";
        std::cin >> Op;
        switch (Op) {
        case 1:
            empezar();
            system("pause");
            break;
        case 2:
            reglas();
            system("pause");
            break;
        case 3:
            std::cout << "Ingrese el numero de discos-> ";
            std::cin >> disc;
            std::cout << "El numero de movimientos es " << pow(2, disc) - 1 << std::endl;
            system("pause");
            break;
        case 4:
            exit(true);
        }
    }
}

void Torres::iniciarJuego() {
    // Reinicia las torres poniendo todos los discos en la primera y vaciándolas
    int i, j, disco = 1, ultimoNumero;
    for (i = 0; i < filas; i++)
    {
        for (j = columnas - 1; j >= 0; j--)
        {
            if (i == 0)
            {
                tablero[columnas * i + j] = disco;
                disco += 2;
            }
            else
            {
                tablero[columnas * i + j] = 0;
            }
        }
    }
    ultimoNumero = disco;

    // Se imprimen las tres columnas (el tablero) antes de hacer cualquier cosa
    system("cls");
    imprimir(ultimoNumero);
    system("pause");

    // Se llama al método jugar para comenzar el juego
    jugar(columnas, ultimoNumero, 0, 1, 2);
}

void Torres::imprimir(int ultimoNumero)
{
    int contadorFilas, contadorColumnas;
    int i = 0, espacios;
    for (contadorColumnas = columnas - 1; contadorColumnas >= 0; contadorColumnas--)
    {
        for (contadorFilas = 0; contadorFilas < filas; contadorFilas++)
        {
            espacios = (ultimoNumero - tablero[columnas * contadorFilas + contadorColumnas]) / 2;

            // Espacios que están en la izquierda
            imprimirEspaciosAnteriores(0, espacios);

            // Imprime los comodines
            /*for (i = 0; i < tablero[columnas * contadorFilas + contadorColumnas]; i++) {
                std::cout << "*";
            }*/
            imprimirDiscos(0, tablero[columnas * contadorFilas + contadorColumnas]);


            // Espacios a la derecha
            /*for (i = 0; i < espacios; i++) {
                std::cout << " ";
            }*/
            imprimirEspaciosPosteriores(0, espacios);
            std::cout << "\t";
        }

        std::cout << "\n";
    }


};

void Torres::reglas() {
    std::cout << "\t\t**Reglas**" << std::endl
        << "1. Solo se puede mover un disco cada vez y para mover otro los demás tienen que estar en postes." << std::endl
        << "2. Un disco de mayor tamaño no puede estar sobre uno más pequeño que él mismo." << std::endl
        << "3. Solo se puede desplazar el disco que se encuentre arriba en cada poste." << std::endl;
}


void Torres::moverDisco(int ultimoNumero, int filaOrigen, int filaDestino)
{
    int cO = columnas - 1, cD = columnas - 1;


    // Se busca el disco que se encuentre mas arriba y por lo tanto el mas pequeño de la fila de origen.
    while (cO >= 0 && tablero[columnas * filaOrigen + cO] == 0)
    {
        cO--;
    };
    if (cO < 0)
        cO = 0;

    // Ahora se calcula cual es la posición libre mas arriba de la fila de destino
    while (cD >= 0 && tablero[columnas * filaDestino + cD] == 0)
    {
        cD--;
    };

    // Se mueve el disco de la fila de origen a la de destino:
    tablero[columnas * filaDestino + cD + 1] = tablero[columnas * filaOrigen + cO];
    tablero[columnas * filaOrigen + cO] = 0;

    // Se imprime el tablero:
    imprimir(ultimoNumero);
};


void Torres::jugar(int disco, int ultimoNumero, int O, int A, int D)
{
    if (disco == 1)
    {
        // Se borra la pantalla, se imprime la tabla y se hace una pausa que varia dependiendo del numero de discos:
        system("cls");
        moverDisco(ultimoNumero, O, D);
        if (columnas <= 5) Sleep(80); else if (columnas <= 10) Sleep(30); else if (columnas <= 15) Sleep(6); else if (columnas > 15) Sleep(20);
    }
    else
    {
        jugar(disco - 1, ultimoNumero, O, D, A);

        system("cls");
        moverDisco(ultimoNumero, O, D);
        if (columnas <= 5) Sleep(80); else if (columnas <= 10) Sleep(30); else if (columnas <= 15) Sleep(6); else if (columnas > 15) Sleep(20);

        jugar(disco - 1, ultimoNumero, A, O, D);
    };

};


void Torres::imprimirEspaciosAnteriores(int i, int espacios) {
    if (i == espacios) {
    }
    else {
        std::cout << " ";
        imprimirEspaciosAnteriores(i + 1, espacios);
    }
}

void Torres::imprimirDiscos(int i, int asteriscos) {
    if (i == asteriscos) {
    }
    else {
        std::cout << "*";
        imprimirDiscos(i + 1, asteriscos);
    }
}

void Torres::imprimirEspaciosPosteriores(int i, int espacios) {
    if (i == espacios) {
    }
    else {
        std::cout << " ";
        imprimirEspaciosPosteriores(i + 1, espacios);
    }
}