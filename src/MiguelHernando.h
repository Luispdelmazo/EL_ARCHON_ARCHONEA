#pragma once
#include "Pieza.h"
#include <GL/glut.h>
#include "ETSIDI.h"
// MiguelHernando - Lider del Departamento de Automatica
// Hereda de Pieza con : public Pieza - ES una Pieza, no TIENE una Pieza 
// Teletransporte: puede ir a cualquier casilla del tablero
// Los conjuros son atributos suyos - no hace falta una clase aparte 

class MiguelHernando : public Pieza {
private:
    int conjurosRestantes;
    bool conjuroUsado[7]; // Cada conjuro solo se puede usar una vez por partida

public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/profesores/mhernando_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/profesores/mhernando_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/profesores/mhernando_ataque.png", 5 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/profesores/mhernando_especial.png", 5 };
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;
    MiguelHernando(int fila, int col)
        : Pieza("MHernando", Bando::OSCURIDAD, TipoMovimiento::TELETRANSPORTE,
            fila, col, 250, 50, 3, 3, 4)
    {
        conjurosRestantes = 7;
        for (int i = 0; i < 7; i++) {
            conjuroUsado[i] = false;
        }
    }

    void dibujar() const override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
        }
        else {
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        }
        //CONFIGURACIÓN DEL SPRITE: Volvemos a los valores métricos
        spriteActual->setCenter(0.5f, 0.5f); // Centrado absoluto en el origen de la traslación
        spriteActual->setSize(1, 1);   // Tamaño relativo a 1 casilla de ancho
        //Dibujamos el gráfico
        spriteActual->draw();
        spriteActual->loop();

        glPopMatrix();
    }

    void habilidadPostBatalla() override {
        spriteActual = &spriteEspecial;
        // Los conjuros se lanzan desde Juego con usarConjuro()
    }
    void habilidadEnBatalla() override {
        // No tiene habilidad post movimiento
    }
    void conjuros() override {
    }

    bool puedeUsarConjuro(int indice) {
        if (indice < 0 || indice >= 7) return false;
        return !conjuroUsado[indice];
    }

    void usarConjuro(int indice) {
        if (puedeUsarConjuro(indice)) {
            conjuroUsado[indice] = true;
            conjurosRestantes--;
        }
    }

    int getConjurosRestantes() const { return conjurosRestantes; }
};
