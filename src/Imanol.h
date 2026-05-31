#pragma once
#include "Pieza.h"
#include "ETSIDI.h"
#include <GL/glut.h>
// Imanol - peon del departamento, hay varios en el tablero
// Hereda de Pieza con : public Pieza - ES una Pieza (Miguel)
// Habilidad: sus ataques pueden paralizar al rival un turno
// Visual: esfera pequena morada oscura - son muchos pero debiles

class Imanol : public Pieza {
private:
    bool puedeParalizar; // puede paralizar una vez por batalla

public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/profesores/imanol_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/profesores/imanol_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/profesores/imanol_ataque.png", 5 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/profesores/imanol_especial.png", 2 };
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;
    Imanol(int fila, int col)
        : Pieza("Imanol", Bando::OSCURIDAD, TipoMovimiento::TERRESTRE,
                fila, col, 100, 20, 2, 3, 1)
    {
        puedeParalizar = true;
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
    }
    void habilidadPostBatalla() override {
        ataque += 5;
        vidaMax += 10;
        velocidad += 1;
        spriteActual = &spriteEspecial;
    }
    void conjuros() override {
        // No tiene conjuros
    }

    bool getPuedeParalizar() const { return puedeParalizar; }
    void usarParalisis()           { puedeParalizar = false; }
};
