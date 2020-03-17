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
		void menu(); //Mariano
		void reglas(); //Cuevas
		void imprimirEspacios(int, int); //Mariano
		void imprimirDiscos(int, int); //Mariano
		void iniciarJuego(); //Cuevas
		void empezar();//Cuevas
		void imprimir(int); //Cuevas
		void moverDisco(int, int, int ); //
		void jugar(int, int, int, int, int); //carlos
};
#endif


