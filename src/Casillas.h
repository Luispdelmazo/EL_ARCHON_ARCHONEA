//ANTIGUO 
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
    CLARA,  // Ventaja para el bando LUZ
    OSCURA, // Ventaja para el bando OSCURIDAD
    NEUTRA  // Sin ventaja para ninguno
};

// CLASE BASE: Casilla
// Igual que Pieza es la base de los personajes,
// Casilla es la base de los tipos de casilla (Miguel)
class Casilla {
private:
    TipoCasilla tipo;
    EstadoCasilla estado;
    bool ocupada;
    float timerOscilacion;
    float periodoOscilacion;

public:
    Casilla();
    Casilla(TipoCasilla tipo, EstadoCasilla estadoInicial, float periodo = 5.0f);

    // Destructor virtual - Miguel lo pide siempre en clases base
    virtual ~Casilla() {}

    // Actualiza el color de las casillas oscilantes con el tiempo
    virtual void actualizar(float dt);

    // Devuelve el bonus de curacion segun el bando que este en la casilla
    virtual float getBonusCuracion(Bando bandoPieza) const;

    TipoCasilla   getTipo()    const { return tipo; }
    EstadoCasilla getEstado()  const { return estado; }
    bool          getOcupada() const { return ocupada; }

    void setOcupada(bool ocu)              { ocupada = ocu; }
    void setEstado(EstadoCasilla nuevoEstado) { estado = nuevoEstado; }
    void setTipo(TipoCasilla nuevoTipo)    { tipo = nuevoTipo; }

    // Fuerza el cambio de estado - para el conjuro Shift Time del lider
    void forzarCambioColor();
};
