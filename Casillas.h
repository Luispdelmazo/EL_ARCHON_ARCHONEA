#pragma once
#include "Pieza.h"
// TIPOS DE CASILLA

// Que tipo de casilla es segun el tablero original del Archon
enum class TipoCasilla {
    NORMAL,         // Casilla estandar, sin efecto especial
    PUNTO_DE_PODER, // Los 5 puntos especiales del tablero (centro y bordes)
    OSCILANTE       // Cambia entre claro y oscuro a lo largo del juego
};

// Estado de color actual de la casilla
// (afecta a las ventajas de combate de cada bando)
enum class EstadoCasilla {
    CLARA,    // Ventaja para el bando LUZ
    OSCURA,   // Ventaja para el bando OSCURIDAD
    NEUTRA    // Sin ventaja para ninguno (casillas normales fijas)
};

// CLASE: Casilla

// Representa una casilla del tablero 9x9.
// El Tablero tiene una matriz de estas.


class Casilla {
private:
    TipoCasilla tipo;       // Que tipo de casilla es
    EstadoCasilla estado;   // Color actual
    bool ocupada;           // Si tiene una pieza encima

    // Para las casillas oscilantes: temporizador del ciclo
    float timerOscilacion;  // Tiempo acumulado para cambiar color
    float periodoOscilacion; // Cada cuanto cambia (en segundos)

public:
    // CONSTRUCTOR
    Casilla()
        : tipo(TipoCasilla::NORMAL),
        estado(EstadoCasilla::NEUTRA),
        ocupada(false),
        timerOscilacion(0.0f),
        periodoOscilacion(5.0f) // Cambia cada 5 segundos por defecto
    {
    }

    // Constructor con parametros
    Casilla(TipoCasilla tipo, EstadoCasilla estadoInicial, float periodo = 5.0f)
        : tipo(tipo),
        estado(estadoInicial),
        ocupada(false),
        timerOscilacion(0.0f),
        periodoOscilacion(periodo)
    {
    }

    // Actualiza el color de las casillas oscilantes con el tiempo
    void actualizar(float dt) {
        if (tipo == TipoCasilla::OSCILANTE) {
            timerOscilacion += dt;
            if (timerOscilacion >= periodoOscilacion) {
                timerOscilacion = 0.0f;
                // Alterna entre clara y oscura
                if (estado == EstadoCasilla::CLARA) {
                    estado = EstadoCasilla::OSCURA;
                }
                else {
                    estado = EstadoCasilla::CLARA;
                }
            }
        }
    }

    // Devuelve el bonus de curacion segun el bando que este en la casilla
    // Los puntos de poder curan mas rapido, y el color propio tambien ayuda
    float getBonusCuracion(Bando bandoPieza) const {
        float bonus = 0.0f;

        if (tipo == TipoCasilla::PUNTO_DE_PODER) {
            bonus += 2.0f; // Curacion doble en puntos de poder
        }

        // Casilla del color propio da ventaja adicional
        if (bandoPieza == Bando::LUZ && estado == EstadoCasilla::CLARA) {
            bonus += 1.0f;
        }
        else if (bandoPieza == Bando::OSCURIDAD && estado == EstadoCasilla::OSCURA) {
            bonus += 1.0f;
        }

        return bonus;
    }

    TipoCasilla getTipo() const { return tipo; }
    EstadoCasilla getEstado() const { return estado; }
    bool getOcupada() const { return ocupada; }
    void setOcupada(bool ocu) { ocupada = ocu; }
    void setEstado(EstadoCasilla nuevoEstado) { estado = nuevoEstado; }
    void setTipo(TipoCasilla nuevoTipo) { tipo = nuevoTipo; }

    // Fuerza el cambio de estado (para el hechizo Shift Time del lider)
    void forzarCambioColor() {
        if (tipo == TipoCasilla::OSCILANTE) {
            if (estado == EstadoCasilla::CLARA) {
                estado = EstadoCasilla::OSCURA;
            }
            else {
                estado = EstadoCasilla::CLARA;
            }
            timerOscilacion = 0.0f; // Reinicia el timer
        }
    }
};
