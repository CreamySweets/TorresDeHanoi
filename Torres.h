#pragma once
class Torres
{
	private:
		int* tablero;
		int filas, columnas;
	public:
		Torres();
		void iniciarJuego();
		void empezar();
		void imprimir(int);
		void moverDisco(int, int, int );
		void jugar(int, int, int, int, int);
};


