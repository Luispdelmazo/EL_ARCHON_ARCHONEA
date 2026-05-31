#pragma once
#include "Pieza.h"


// CLASE: Conjuros
// Gestiona los 7 conjuros del lider de cada bando igual que en el Archon original - cada conjuro solo se puede usar una vez por partida


enum class TipoConjuro {
    CURAR,          // Cura completamente una pieza aliada
    TELETRANSPORTE, // Mueve una pieza aliada a otra casilla
    SHIFT_TIME,     // Cambia el color de las casillas oscilantes
    INTERCAMBIAR,   // Intercambia dos piezas aliadas de posicion
    REVIVIR,        // Resucita una pieza aliada eliminada
    ENCARCELAR,     // Encierra una pieza enemiga en su casilla
    INVOCAR         // Invoca un aliado temporal para combatir
};

class Conjuros {
private:
    bool usados[7]; // Si cada conjuro ya fue usado
    int conjurosRestantes;

public:
    Conjuros() {
        conjurosRestantes = 7;
        for (int i = 0; i < 7; i++) {
            usados[i] = false;
        }
    }

    // Comprueba si un conjuro esta disponible
    bool estaDisponible(TipoConjuro tipo) const {
        int idx = (int)tipo;
        return !usados[idx];
    }

    // Marca el conjuro como usado
    void marcarUsado(TipoConjuro tipo) {
        int idx = (int)tipo;
        if (!usados[idx]) {
            usados[idx] = false;
            conjurosRestantes--;
        }
    }

    int getConjurosRestantes() const { return conjurosRestantes; }
};
