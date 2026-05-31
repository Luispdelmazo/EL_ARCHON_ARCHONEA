#pragma once
#include "Pieza.h"
#include <GL/glut.h>
#include "ETSIDI.h"
// HectorMontes - profe terrestre, el mas resistente del departamento
// Hereda de Pieza con : public Pieza - ES una Pieza (Miguel)
// Habilidad: recupera 1 punto de vida por segundo en batalla
// Visual: cubo morado con cruz verde - simbolo de curacion

class HectorMontes : public Pieza {
private:
    int controlAtaques; //guarda los ataques hasta este momento, para aumentar la vida cada vez que ataque
public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/profesores/hmontes_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/profesores/hmontes_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/profesores/hmontes_ataque.png", 5 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/profesores/hmontes_especial.png", 1 };
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;
    HectorMontes(int fila, int col)
        : Pieza("HectorMontes", Bando::OSCURIDAD, TipoMovimiento::TERRESTRE,
                fila, col, 300, 30, 3, 3, 1)
    {
        controlAtaques = 0;
    }

    void dibujar() const override {
        // calculamos la posición exacta en el plano del tablero (-4.5f a 4.5f)
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        // usamos el empuje de matriz clásico para movernos a la casilla
        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        // aplicamos el color de selección si el usuario la pincha
        if (estaSeleccionada) glColor3f(1.0f, 1.0f, 0.0f);
        else                  glColor3f(1.0f, 1.0f, 1.0f);

        // CONFIGURACIÓN DEL SPRITE: Volvemos a los valores métricos
        spriteActual->setCenter(0.5f, 0.5f); // Centrado absoluto en el origen de la traslación
        spriteActual->setSize(0.9f, 0.9f);   // Tamaño relativo a 1 casilla de ancho

        // dibujamos el gráfico
        spriteActual->draw();
        spriteActual->loop();

        // liberamos la matriz para la siguiente casilla
        glPopMatrix();
    }

    void habilidadEnBatalla() override { // recupera 1 punto de vida por segundo - se llama desde Batalla
        if(contadorAtaques-controlAtaques==1)
        curar(5);
        spriteActual = &spriteEspecial;
		controlAtaques = contadorAtaques;
    }
    void habilidadPostBatalla() override {
		spriteActual = &spriteIdle;
        // No tiene habilidad post movimiento
    }
    void conjuros() override {
        // No tiene conjuros
    }

};
