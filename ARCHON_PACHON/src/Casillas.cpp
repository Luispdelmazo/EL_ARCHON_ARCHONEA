#include "Casillas.h"

Casilla::Casilla(): tipo(TipoCasilla::NORMAL),
estado(EstadoCasilla::NEUTRA),
ocupada(false),
timerOscilacion(0.0f),
periodoOscilacion(5.0f) // Cambia cada 5 segundos por defecto
{
}

Casilla::Casilla(TipoCasilla tipo, EstadoCasilla estadoInicial, float periodo) : tipo(tipo),
estado(estadoInicial),
ocupada(false),
timerOscilacion(0.0f),
periodoOscilacion(periodo)
{
}

void Casilla::actualizar(float dt) {
    if (tipo == TipoCasilla::OSCILANTE) {
        timerOscilacion += dt;
        if (timerOscilacion >= periodoOscilacion) {
            timerOscilacion = 0.0f;
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
float Casilla::getBonusCuracion(Bando bandoPieza) const {
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

void Casilla::forzarCambioColor() {
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