#include "Torres.h"
#include <iostream>
#include <windows.h>
#include <math.h>
Torres::Torres() {
    filas = 3; //Cantidad de palitos
    columnas = 0; // Cantidad de discos
    tablero = NULL; // Inicializa el tablero como puntero vac�o
}

void Torres::empezar() {
    std::cout << "Con cuantos discos va a jugar?: "; 
    std::cin >> columnas;
    tablero = (int*)malloc(sizeof(int) * filas * columnas); // A "tablero" lo vuelve un bloque de memoria bidimensional de tama�o filas * columnas
    iniciarJuego();
}

void Torres::menu() {
    int Op, disc; // "op" es la opci�n y "disc" es el n�mero de discos con el que se va a jugar
    while (true) { // Repetir� el ciclo de manera infinita 
    	system("cls");  // Limpia la pantalla antes de iniciar
        std::cout << "\t Torres de Hanoi" << std::endl // Muestra las opciones al usuario
            << "1.Jugar" << std::endl
            << "2.Reglas" << std::endl
            << "3.Calcular movimientos" << std::endl
            << "4.Salir" << std::endl
            << "Opcion: ";
        std::cin >> Op; // Recibe la opci�n que el usuario seleccion�
        switch (Op) { // Seg�n la opci�n introducida, ejecutar� el c�digo pertinente 
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
                std::cout << "El numero de movimientos es " << pow(2,disc)-1 << std::endl; // Utilizando la f�rmula de no. de movimientos = (2^n) - 1, calcula la cantidad m�nima de movimientos necesarios
                system("pause");
                break;
            case 4:
                exit(true);
			default:
				std::cout << "Opci�n inv�lida";
        }
    }
}

void Torres::reglas(){ // Muestra las reglas del juego al usuario.
	std::cout << "\t\t**Reglas**" << std::endl
			  << "1. Solo se puede mover un disco cada vez y para mover otro los dem�s tienen que estar en postes." << std::endl
			  << "2. Un disco de mayor tama�o no puede estar sobre uno m�s peque�o que �l mismo." 					<< std::endl
			  << "3. Solo se puede desplazar el disco que se encuentre arriba en cada poste." 						<< std::endl;
}

void Torres::iniciarJuego() {
    // Reinicia las torres poniendo todos los discos en la primera y vaci�ndolas
    int i, j, disco = 1, ultimoNumero;
    for (i = 0; i < filas; i++)
    {
        for (j = columnas - 1; j >= 0; j--)
        {
            if (i == 0) // Cuando se est� llenando el primer pivote, 
            {
                tablero[columnas * i + j] = disco; // En la posici�n columnas * i+j del tablero, se va a guardar el valor del ancho del disco. 
                disco += 2; // Se aumentan 2 al ancho del disco
            }
            else // En el resto de pivotes, 
            {
                tablero[columnas * i + j] = 0; // Todas sus posiciones se van a llenar con 0.
            }
        }
    }
    ultimoNumero = disco; // �ltimoNumero guarda el ancho del �ltimo disco.

    // Se imprimen las tres columnas (el tablero) antes de hacer cualquier cosa
    system("cls");
    imprimir(ultimoNumero);
    system("pause");

    // Se llama al m�todo jugar para comenzar el juego
    jugar(columnas, ultimoNumero, 0, 1, 2);
}

void Torres::imprimir(int ultimoNumero)
{
    int contadorFilas, contadorColumnas, i, espacios;
    for (contadorColumnas = columnas - 1; contadorColumnas >= 0; contadorColumnas--)
    {
        for (contadorFilas = 0; contadorFilas < filas; contadorFilas++)
        {
		espacios = (ultimoNumero - tablero[columnas * contadorFilas + contadorColumnas]) / 2; // Asigna la cantidad de espacios necesarios para imprimir una pir�mide y no un tri�ngulo rect�ngulo

            // Espacios que est�n en la izquierda
            imprimirEspacios(0, espacios);

            // Imprime los comodines
            imprimirDiscos(0, tablero[columnas * contadorFilas + contadorColumnas]);

            // Espacios a la derecha
			imprimirEspacios(0, espacios);
            std::cout << "\t";
        }
        std::cout <<"\n";
    }
};

void Torres::moverDisco(int ultimoNumero, int filaOrigen, int filaDestino)
{
    int cO = columnas - 1, cD = columnas - 1;

    while (cO >= 0 && tablero[columnas * filaOrigen + cO] == 0) // Comprueba que existan discos en el pivote origen, y que haya espacio libre en el pivote destino
    {
        cO--; // Y disminuye la columna de origen
    };
    if (cO < 0)	{ // Si la columna de origen es mayor a cero,
        cO = 0;
	}

    while (cD >= 0 && tablero[columnas * filaDestino + cD] == 0){ // Ahora se calcula cual es la posici�n libre mas arriba de la fila de destino
        cD--;
    };

    tablero[columnas * filaDestino + cD + 1] = tablero[columnas * filaOrigen + cO]; // Se mueve el disco de la fila de origen a la de destino:
    tablero[columnas * filaOrigen + cO] = 0;

    imprimir(ultimoNumero); // Se imprime el tablero
};


void Torres::jugar(int disco, int ultimoNumero, int O, int A, int D) // Como m�todo recursivo, recibe el disco (contador), ancho del �ltimo disco, el pivote de origen, el interino, y el de destino
{
    if (disco == 1) // Si se juega con un disco, o se alcanza el caso base, mueve el disco al pivote destino y finaliza la ejecuci�n
    {
        // Se borra la pantalla, se imprime la tabla y se hace una pausa que varia dependiendo del numero de discos:
        system("cls");
        moverDisco(ultimoNumero, O, D);
        if (columnas <= 5) Sleep(80); else if (columnas <= 10) Sleep(30); else if (columnas <= 15) Sleep(6); else if (columnas > 15) Sleep(20); // Cambia los intervalos de pausa seg�n la cantidad de discos 
    }
    else
    {
        jugar(disco - 1, ultimoNumero, O, D, A); // Disminuye disco en 1, y env�a los pivotes de origen, destino e interino

        system("cls");
        moverDisco(ultimoNumero, O, D); // Llama a "mover disco" para moverlo de su posici�n origen a la destino
        if (columnas <= 5) Sleep(80); else if (columnas <= 10) Sleep(30); else if (columnas <= 15) Sleep(6); else if (columnas > 15) Sleep(20);

        jugar(disco - 1, ultimoNumero, A, O, D); // Disminuye disco en 1, manda el �ltimo n�mero, reordena y manda interino como origen, origen como destino, y destino como interino
    };

};


void Torres::imprimirEspacios(int i, int espacios) { // M�todo recursivo para imprimir espacios
    if (i == espacios) { // En el caso base no hace nada :D
    }
    else {
        std::cout << " "; // Imprime un solo espacio
        imprimirEspacios(i + 1, espacios); // Y llama al m�todo
    }
}

void Torres::imprimirDiscos(int i, int asteriscos) { // Id�ntico a imprimir espacios, pero imprime un caracter en vez de un espacio.
    if (i == asteriscos) {
    }
    else {
        std::cout << "*";
        imprimirDiscos(i + 1, asteriscos);
    }
}