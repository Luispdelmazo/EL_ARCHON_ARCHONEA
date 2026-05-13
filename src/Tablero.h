#pragma once
#include "Pieza.h"
#include "Casillas.h"
#include <vector>

// CLASE: Tablero
// Miguel dijo: el tablero tiene DOS matrices:
//   1. Pieza* casillas[9][9]  -> donde esta cada pieza
//   2. Casilla tablero[9][9]  -> que tipo es cada casilla
// nullptr en la primera matriz = casilla vacia

class Tablero {
private:
    Pieza* casillas[9][9];      // Punteros a piezas (nullptr = vacio)
    Casilla tablero[9][9];      // Tipos y estados de cada casilla

    // Parametros graficos
    float tamCasilla;           // Tamano de cada casilla en pantalla
    float offsetX;              // Desplazamiento X del tablero
    float offsetY;              // Desplazamiento Y del tablero

    // Posiciones de los 5 puntos de poder
    int puntosPoder[5][2];

    // Para generar colores en cada turno
    float colorOscilanteR;
    float colorOscilanteG;
    float colorOscilanteB;

    // Seleccion de piezas (privado, se gestiona con metodos)
    int filaSeleccionada;
    int colSeleccionada;
    bool haySeleccion;

    // Casillas validas para moverse
    std::vector<Coord> casillasValidas;

public:
    // Constructor y destructor
    Tablero(float tamCasilla = 1.0f, float ox = 0.0f, float oy = 0.0f);
    ~Tablero();

    // Inicializacion
    void inicializarCasillas();

    // Dibujo - implementacion en Tablero.cpp
    void dibujar(Bando turno);
    void dibujarMarco(Bando turno);
    void dibujarCasillas();
    void dibujarSeleccion();
    void dibujarPuntosDePoder();
    void cambiarColorOscilantes();

    // Gestion de piezas
    void colocarPieza(Pieza* pieza, int fila, int col);
    bool moverPieza(int filaOrigen, int colOrigen, int filaDest, int colDest);
    bool hayEnemigo(int fila, int col, Bando bandoActual);
    void eliminarPieza(int fila, int col);

    // Seleccion con raton
    void seleccionarPieza(int fila, int col, Bando turno);
    void deseleccionar();
    bool destinoEsValido(int fila, int col);
    bool moverPiezaSeleccionada(int filaDest, int colDest);
    bool tieneSeleccion() const;
    int getFilaSeleccionada() const;
    int getColSeleccionada() const;

    // Condiciones de victoria
    bool controlaPuntosDePoder(Bando bando);
    int contarPiezas(Bando bando);

    // Actualizacion cada frame
    void actualizar(float dt);

    // 
    Pieza* getPieza(int fila, int col);
    Casilla& getCasilla(int fila, int col);
    float getTamCasilla() const;
    float getOffsetX() const;
    float getOffsetY() const;

    // Convierte coordenadas de pantalla a fila/columna (para el raton)
    bool pantallaATablero(float px, float py, int& filaOut, int& colOut);
};