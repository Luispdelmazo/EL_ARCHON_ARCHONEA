#pragma once
#include "Casillas.h"

// PuntoDePoder - hereda de Casilla
// Igual que EsferaPulsante heredaba de Esfera en el Pang 
// Los 5 puntos especiales del tablero - dan bonus de curacion doble
// Idea de mi compañero: subclase para diferenciar mejor los tipos

class PuntoDePoder : public Casilla {
public:
    PuntoDePoder(EstadoCasilla estadoInicial)
        : Casilla(TipoCasilla::PUNTO_DE_PODER, estadoInicial)
    {}

    // Sobreescribimos getBonusCuracion para dar mas bonus en puntos de poder
    // igual que EsferaPulsante sobreescribia mueve() en el Pang
    float getBonusCuracion(Bando bandoPieza) const override {
        float bonus = 2.0f; // Siempre curacion doble en puntos de poder

        // Ademas el color propio da ventaja adicional
        if (bandoPieza == Bando::LUZ && getEstado() == EstadoCasilla::CLARA) {
            bonus += 1.0f;
        } else if (bandoPieza == Bando::OSCURIDAD && getEstado() == EstadoCasilla::OSCURA) {
            bonus += 1.0f;
        }

        return bonus;
    }
};
