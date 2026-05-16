#pragma once
#include "Pieza.h"
// TIPOS DE CASILLA
enum class TipoCasilla {
    NORMAL,         // Casilla estandar, sin efecto especial
    PUNTO_DE_PODER, // Los 5 puntos especiales del tablero 
    OSCILANTE       // Cambia entre claro y oscuro a lo largo del juego
};

// Estado de color actual de la casilla
enum class EstadoCasilla {
    CLARA,    // Ventaja para el bando LUZ
    OSCURA,   // Ventaja para el bando OSCURIDAD
    NEUTRA    // Sin ventaja para ninguno (casillas normales fijas)
};
// CLASE: Casilla
class Casilla {
private:
    TipoCasilla tipo;       // Que tipo de casilla es
    EstadoCasilla estado;   // Color actual
    bool ocupada;           // Si tiene una pieza encima
    float timerOscilacion;  // Tiempo acumulado para cambiar color
    float periodoOscilacion; // Cada cuanto cambia (en segundos)
public:
    // CONSTRUCTOR
    Casilla();

    // Constructor con parametros
    Casilla(TipoCasilla tipo, EstadoCasilla estadoInicial, float periodo = 5.0f);

    // Actualiza el color de las casillas oscilantes con el tiempo
    void actualizar(float dt);

    // Devuelve el bonus de curacion segun el bando que este en la casilla
    // Los puntos de poder curan mas rapido, y el color propio tambien ayuda
    float getBonusCuracion(Bando bandoPieza) const;

    TipoCasilla getTipo() const { return tipo; }
    EstadoCasilla getEstado() const { return estado; }
    bool getOcupada() const { return ocupada; }
    void setOcupada(bool ocu) { ocupada = ocu; }
    void setEstado(EstadoCasilla nuevoEstado) { estado = nuevoEstado; }
    void setTipo(TipoCasilla nuevoTipo) { tipo = nuevoTipo; }

    // Fuerza el cambio de estado (para el hechizo Shift Time del lider)
    void forzarCambioColor();

};