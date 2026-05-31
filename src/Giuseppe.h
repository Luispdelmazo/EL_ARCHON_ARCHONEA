#pragma once
#include "Pieza.h"
#include "ETSIDI.h"
#include <GL/glut.h>
// Giuseppe - profe terrestre estricto del departamento
// Hereda de Pieza con : public Pieza - ES una Pieza 
// Habilidad: en sus combates no estan permitidas habilidades especiales
// Visual: cubo morado con borde negro - serio y estricto

class Giuseppe : public Pieza {
    bool escudoActivo;
public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/profesores/giuseppe_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/profesores/giuseppe_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/profesores/giuseppe_ataque.png", 5 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/profesores/giuseppe_especial.png", 2 };
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;
    Giuseppe(int fila, int col)
        : Pieza("Giuseppe", Bando::OSCURIDAD, TipoMovimiento::TERRESTRE,
                fila, col, 150, 30, 7, 3, 1)
    {
        escudoActivo = true;
    }

    void dibujar() const override {
        // calculamos la posición exacta en el plano del tablero (-4.5f a 4.5f)
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

    void habilidadEnBatalla() override {
        // Se implementa en recibirDano, no aquí
    }
    void habilidadPostBatalla() override {
        spriteActual = &spriteIdle;
        // No tiene habilidad post movimiento
    }
    void conjuros() override {
        // No tiene conjuros
    }

    void recibirDano(int dano) override {
        if (escudoActivo && vidaActual - dano <= 0) {
            vidaActual = 1;
            escudoActivo = false;
            spriteActual = &spriteEspecial;
        }
        else {
            vidaActual -= dano;
            if (vidaActual <= 0) {
                vidaActual = 0;
                estaViva = false;
            }
        }
    }

    // Batalla comprueba esto para saber si anular habilidades
    bool anulaHabilidades() const { return true; }
};
