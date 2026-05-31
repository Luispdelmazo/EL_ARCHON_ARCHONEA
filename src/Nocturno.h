#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
#include "ETSIDI.h"
// Nocturno - alumno misterioso, movimiento terrestre
// Hereda de Pieza con : public Pieza - ES una Pieza 
// Habilidad: puede duplicar velocidad una vez por batalla
// Visual: esfera azul muy oscura con punto brillante interior

class Nocturno : public Pieza {
private:
    bool velocidadDuplicada; // Solo puede duplicar una vez por batalla

public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/alumnos/nocturno_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/alumnos/nocturno_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/alumnos/nocturno_ataque.png", 5 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/alumnos/nocturno_especial.png", 1 };
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;
    Nocturno(int fila, int col)
        : Pieza("Nocturno", Bando::LUZ, TipoMovimiento::TERRESTRE,
            fila, col, 250, 20, 2, 4, 2)
    {
        velocidadDuplicada = false;
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

    void habilidadEnBatalla() override {
        if (!velocidadDuplicada) {
            velocidad = 4;// pico de adrenalina
            spriteActual = &spriteEspecial;
		}
        else {
			velocidad = 2; // velocidad normal
        }
    }
    void habilidadPostBatalla() override {
        // No tiene habilidad post movimiento
        spriteActual = &spriteIdle;
        velocidadDuplicada = true;
    }
    void conjuros() override {
        // No tiene conjuros
    }

    bool getVelocidadDuplicada() const { return velocidadDuplicada; }
    void resetHabilidad()              { velocidadDuplicada = false; }
};
