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

            // Imprime espacios
            for (i = 0; i < espacios; i++) {
                std::cout << " ";
            }

            // Imprime los discos
            for (i = 0; i < tablero[columnas * contadorFilas + contadorColumnas]; i++) {
                std::cout << "*";
            }

            // Imprime espacios
            for (i = 0; i < espacios; i++) {
                std::cout << " ";
            }
          
            std::cout << "\t";
        }

        std::cout <<"\n";
    }


};


void Torres::moverDisco(int ultimoNumero, int filaOrigen, int filaDestino)
{
    int cO = columnas - 1, cD = columnas - 1;


    // Se busca el tope de la fila origen
    while (cO >= 0 && tablero[columnas * filaOrigen + cO] == 0)
    {
        cO--;
    };
    if (cO < 0)
        cO = 0;

    // Se calcula la posición de la fila destino
    while (cD >= 0 && tablero[columnas * filaDestino + cD] == 0)
    {
        cD--;
    };

    // Se mueve el disco a esa fila
    tablero[columnas * filaDestino + cD + 1] = tablero[columnas * filaOrigen + cO];
    tablero[columnas * filaOrigen + cO] = 0;

    // Se imprime el tablero de juego:
    imprimir(ultimoNumero);
};


void Torres::jugar(int disco, int ultimoNumero, int O, int A, int D)
{
    if (disco == 1)
    {
        // Se limpia la pantalla, imprime y toma pausa entre impresiones
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