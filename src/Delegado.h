#pragma once
#include "Pieza.h"
#include <GL/glut.h> 
#include "ETSIDI.h"

class Delegado : public Pieza {
private:
    int conjurosRestantes;
    bool conjuroUsado[7];

public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/alumnos/delegado_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/alumnos/delegado_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/alumnos/delegado_ataque.png", 5 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/alumnos/delegado_especial.png", 5 };
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;

    Delegado(int fila, int col)
        : Pieza("Delegado", Bando::LUZ, TipoMovimiento::TELETRANSPORTE,
            fila, col, 250, 50, 3, 3, 4)
    {
        conjurosRestantes = 7;
        for (int i = 0; i < 7; i++) conjuroUsado[i] = false;
    }

    void dibujar() const override {
        //calculamos la posición exacta en el plano del tablero (-4.5f a 4.5f)
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        //usamos el empuje de matriz clásico para movernos a la casilla
        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        //aplicamos el color de selección si el usuario la pincha
        if (estaSeleccionada) glColor3f(1.0f, 1.0f, 0.0f);
        else                  glColor3f(1.0f, 1.0f, 1.0f);

        //CONFIGURACIÓN DEL SPRITE: Volvemos a los valores métricos
        spriteActual->setCenter(0.5f, 0.5f); // Centrado absoluto en el origen de la traslación
        spriteActual->setSize(0.9f, 0.9f);   // Tamaño relativo a 1 casilla de ancho

        //dibujamos el gráfico
        spriteActual->draw();
        spriteActual->loop();

        // liberamos la matriz para la siguiente casilla
        glPopMatrix();
    }
    void habilidadPostBatalla() override { spriteActual = &spriteEspecial; }
    void habilidadEnBatalla() override {
        // No tiene habilidad post movimiento
    }
    void conjuros() override {
    }

    // estos metodos estaban fuera de la clase por error - ahora dentro
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