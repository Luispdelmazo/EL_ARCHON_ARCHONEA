#pragma once
#include "Casillas.h"
#include "Pieza.h"

const int FILAS = 9;
const int COLS = 9;
const int TAM_CASILLA = 60;
const int MARGEN = 50;

// clase que gestiona todo el tablero del juego
// tiene dos matrices: una de casillas y otra de punteros a piezas
// las casillas son el fondo del tablero (color, tipo, puntos de poder)
// los punteros apuntan a las piezas que hay en cada casilla
// si el puntero es nullptr significa que la casilla esta vacia
class Tablero {
private:
    Casilla casillas[9][9];   // el fondo del tablero con sus tipos
    Pieza* piezas[9][9];      // punteros a las piezas, nullptr = vacio

    bool faseClaraOscura;     // controla el ciclo de oscilacion
    int tiempoOscilacion;     // contador para saber cuando cambiar

public:
    Tablero();
    ~Tablero();

    // dibuja primero las casillas y luego las piezas encima
    void dibujar();

    // coloca una pieza en una casilla concreta
    void colocarPieza(Pieza* p, int fila, int col);

    // mueve una pieza de una casilla a otra
    // si en el destino hay una pieza rival se abre el combate
    void moverPieza(int filaOrigen, int colOrigen,
        int filaDestino, int colDestino);

    // devuelve la pieza que hay en una casilla (o nullptr si esta vacia)
    Pieza* getPieza(int fila, int col);

    // elimina una pieza del tablero y libera su memoria
    void eliminarPieza(int fila, int col);

    // actualiza el ciclo de oscilacion de las casillas
    void actualizarOscilacion();

    // convierte coordenadas de pantalla a casilla del tablero
    // lo usamos para saber donde ha hecho clic el raton
    bool pantallaToCasilla(int x, int y, int& fila, int& col);
};