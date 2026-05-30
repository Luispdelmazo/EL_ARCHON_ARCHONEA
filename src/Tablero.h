#pragma once
#include "Pieza.h"
#include "Casilla.h"
#include "CasillaOscilante.h"
#include "PuntoDePoder.h"
#include <vector>

// CLASE: Tablero
// MH dijo: el tablero tiene DOS matrices:
//   1. Pieza* casillas[9][9]- donde esta cada pieza
//   2. Casilla* tablero[9][9] - que tipo es cada casilla (punteros para polimorfismo)
// nullptr en la primera matriz = casilla vacia
// Usamos punteros en la segunda para poder tener CasillaOscilante y PuntoDePoder igual que ListaEsferas usaba Esfera* para poder meter EsferaPulsante 

class Tablero {
private:
    Pieza*   piezas[9][9]; // punteros a piezas (nullptr = vacio)
    Casilla* casillas[9][9];  // punteros a casillas - polimorfismo como en el Pang

    // parametros graficos
    float tamCasilla;
    float offsetX;
    float offsetY;

    // posiciones de los 5 puntos de poder
    int puntosPoder[5][2];

    // para generar colores en cada turno
    float colorOscilanteR;
    float colorOscilanteG;
    float colorOscilanteB;

    // seleccion de piezas
    int filaSeleccionada;
    int colSeleccionada;
    bool haySeleccion;

    // casilla en la que el jugador está posicionado por teclado previo a seleccionarla
    int filaTeclado;
    int colTeclado;

    // casillas validas para moverse
    std::vector<Coord> casillasValidas;//nose como poneerlo si no

public:
    Tablero(float tamCasilla = 1.0f, float ox = 0.0f, float oy = 0.0f);
    ~Tablero();

    void inicializarCasillas();
    void dibujar(Bando turno);
    void dibujarMarco(Bando turno);
    void dibujarCasillas();
    void dibujarSeleccion();
    void dibujarPuntosDePoder();
    void cambiarColorOscilantes();

    // gestion de piezas
    void colocarPieza(Pieza* pieza, int fila, int col);
    bool moverPieza(int filaOrigen, int colOrigen, int filaDest, int colDest);
    bool hayEnemigo(int fila, int col, Bando bandoActual);
    void eliminarPieza(int fila, int col);

    // seleccion con raton
    void seleccionarPieza(int fila, int col, Bando turno);
    void deseleccionar();
    bool destinoEsValido(int fila, int col);
    bool moverPiezaSeleccionada(int filaDest, int colDest);
    bool tieneSeleccion() const;
    int  getFilaSeleccionada() const;
    int  getColSeleccionada()  const;
	int  getFilaTeclado() const { return filaTeclado; }
	int getColTeclado()  const { return colTeclado; }
	// gestion con teclado
	void gestionTeclado(unsigned char tecla, Bando turno);

	void setFilaTeclado(int fila) { filaTeclado = fila; }
	void setColTeclado(int col) { colTeclado = col; }

    // condiciones de victoria
    bool controlaPuntosDePoder(Bando bando);
    int  contarPiezas(Bando bando);

    // zctualizacion cada turno
    void actualizar(float dt);

    Pieza*   getPieza(int fila, int col);
    Casilla* getCasilla(int fila, int col);
    float    getTamCasilla() const;
    float    getOffsetX()    const;
    float    getOffsetY()    const;

    bool pantallaATablero(float px, float py, int& filaOut, int& colOut);

    void ActivarHabilidad(int fila, int col);
};
