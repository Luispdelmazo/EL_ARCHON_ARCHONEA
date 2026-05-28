#pragma once
#include "Pieza.h"

// TIPOS DE CASILLA IDEA DEL CABEZON
// que tipo de casilla es segun el tablero original del Archon
enum class TipoCasilla {
    NORMAL,         // casilla estandar (ajedrez)
    PUNTO_DE_PODER, // los 5 puntos especiales del tablero (centro y bordes)
    OSCILANTE       // cambia  a lo largo del juego
};

// estado de color actual de la casilla (afecta a las ventajas de combate de cada bando)
enum class EstadoCasilla {
    CLARA,    // ventaja para el bando LUZ
    OSCURA,   // ventaja para el bando OSCURIDAD
    NEUTRA    // Ssn ventaja para ninguno (casillas normales fijas)
};


// CLASE: Casilla representa una casilla del tablero 9x9.
// el Tablero tiene una matriz de estas.

class Casilla {
private:
    TipoCasilla tipo;       
    EstadoCasilla estado;   // color actual
    bool ocupada;           // si tiene una pieza encima

    // para las casillas oscilantes: temporizador del ciclo
    float timerOscilacion;  
    float periodoOscilacion; 
public:
  //constructor
    Casilla()
        : tipo(TipoCasilla::NORMAL),
          estado(EstadoCasilla::NEUTRA),
          ocupada(false),
          timerOscilacion(0.0f),
          periodoOscilacion(5.0f) // cambia cada 5 segundos por defecto
    {}

    // constructor con parametros
    Casilla(TipoCasilla tipo, EstadoCasilla estadoInicial, float periodo = 5.0f)
        : tipo(tipo),
          estado(estadoInicial),
          ocupada(false),
          timerOscilacion(0.0f),
          periodoOscilacion(periodo)
    {}

   
    // METODOS
    // actualiza el color de las casillas oscilantes con el tiempo
    //IMP: SIN VIRTUAL EN LA CLASE BASE EL OVERRRIDE EN PUNTODEPODER NO FUNCIONA  — exactamente igual que en el Pang donde mueve() tenía que ser virtual en objetomovil para que esferapulsante pudiera sobreescribirlo.
    virtual void actualizar(float dt) {
        if (tipo == TipoCasilla::OSCILANTE) {
            timerOscilacion += dt;
            if (timerOscilacion >= periodoOscilacion) {
                timerOscilacion = 0.0f;
                // alterna entre clara y oscura
                if (estado == EstadoCasilla::CLARA) {
                    estado = EstadoCasilla::OSCURA;
                } else {
                    estado = EstadoCasilla::CLARA;
                }
            }
        }
    }

    // devuelve el bonus de curacion segun el bando que este en la casilla
    // los puntos de poder curan mas rapido, y el color propio tambien ayuda
    virtual float getBonusCuracion(Bando bandoPieza) const {
        float bonus = 0.0f;

        if (tipo == TipoCasilla::PUNTO_DE_PODER) {
            bonus += 2.0f; // Curacion doble en puntos de poder
        }

        // casilla del color propio da ventaja adicional
        if (bandoPieza == Bando::LUZ && estado == EstadoCasilla::CLARA) {
            bonus += 1.0f;
        } else if (bandoPieza == Bando::OSCURIDAD && estado == EstadoCasilla::OSCURA) {
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

    // fuerza el cambio de estado (para el hechizo Shift Time del lider)
    void forzarCambioColor() {
        if (tipo == TipoCasilla::OSCILANTE) {
            if (estado == EstadoCasilla::CLARA) {
                estado = EstadoCasilla::OSCURA;
            } else {
                estado = EstadoCasilla::CLARA;
            }
            timerOscilacion = 0.0f; // Reinicia el timer
        }
    }

    virtual ~Casilla() {} //destructor, virtual para evitar problemas con el polimorfismo
};

// Necesitamos incluir Bando aqui porque Casilla lo usa
// (getBonusCuracion recibe un Bando)

