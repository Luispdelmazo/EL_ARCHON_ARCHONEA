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
                fila, col, 100, 20, 5, 3, 1)
    {
        puedeParalizar = true;
    }

  /*  void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.35f, 0.0f, 0.45f); // morado muy oscuro - peon
        }
        // mas pequeno que el resto - es el peon del bando oscuridad
        glutSolidSphere(0.25f, 15, 15);

        glPopMatrix();
    }  */
  /*  void dibujar() const override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMatrixMode(GL_PROJECTION); glPushMatrix();
        glMatrixMode(GL_MODELVIEW);  glPushMatrix();

        glTranslatef(x, y, 0.2f);
        if (estaSeleccionada) glColor3f(1.0f, 1.0f, 0.0f);
        else                  glColor3f(1.0f, 1.0f, 1.0f);

        spriteActual->setCenter(1, 0);
        spriteActual->setSize(0.9f, 0.9f);

        spriteActual->draw();
        spriteActual->loop();

        glMatrixMode(GL_MODELVIEW);  glPopMatrix();
        glMatrixMode(GL_PROJECTION); glPopMatrix();
        glPopAttrib();

        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

    }  */
    
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

    void habilidadEspecial() override {
        spriteActual = &spriteEspecial;
        // paraliza al rival - se gestiona desde Batalla
        puedeParalizar = true;
    }

    bool getPuedeParalizar() const { return puedeParalizar; }
    void usarParalisis()           { puedeParalizar = false; }
};
