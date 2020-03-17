#include <iostream>
#include <string.h>
#ifndef TorresH 
#define TorresH
#pragma once
class Torres
{
	private:
		int* tablero;
		int filas, columnas;
		int movimiento;
	public:
		Torres();
		void menu();
		void reglas();
		void imprimirEspacios(int, int);
		void imprimirDiscos(int, int);
		void iniciarJuego();
		void empezar();
		void imprimir(int);
		void moverDisco(int, int, int );
		void jugar(int, int, int, int, int);
};
#endif


