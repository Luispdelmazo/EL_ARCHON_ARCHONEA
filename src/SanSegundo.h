#pragma once
#include "Pieza.h"
#include "ETSIDI.h"
#include <GL/glut.h>
// SanSegundo - profe volador misterioso del departamento
// Hereda de Pieza con : public Pieza - ES una Pieza 
// Habilidad: puede dividirse en 2 una vez por partida subiendo sus stats
// Visual: dos esferas pequenas moradas juntas - representa la division

class SanSegundo : public Pieza {
private:
    bool divisionUsada; // Solo puede dividirse una vez

public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/profesores/sansegundo_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/profesores/sansegundo_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/profesores/sansegundo_ataque.png", 4 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/profesores/sansegundo_especial.png", 2 };
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;
    SanSegundo(int fila, int col)
        : Pieza("SanSegundo", Bando::OSCURIDAD, TipoMovimiento::VOLADOR,
                fila, col, 200, 30, 2, 3, 2)
    {
        divisionUsada = false;
    }

  /*  void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
            glutSolidSphere(0.35f, 20, 20);
        } else {
            // Dos esferas juntas - representa que puede dividirse
            glColor3f(0.6f, 0.0f, 0.8f);
            glPushMatrix();
            glTranslatef(-0.15f, 0.0f, 0.0f);
            glutSolidSphere(0.22f, 15, 15);
            glPopMatrix();

            glPushMatrix();
            glTranslatef( 0.15f, 0.0f, 0.0f);
            glutSolidSphere(0.22f, 15, 15);
            glPopMatrix();
        }

        glPopMatrix();
    } */
   
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

    } */

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
        // Division - sube sus stats al usarla
        if (!divisionUsada && ((float)vidaActual/ (float)vidaMax) < 0.5f){
            spriteActual = &spriteEspecial;
            vidaMax       += 20;
            vidaActual    += 20;
            ataque        += 5;
            divisionUsada  = true;
        }
    }
    void habilidadPostBatalla() override {
        // No tiene habilidad post movimiento
    }
    void conjuros() override {
        // No tiene conjuros
    }

    bool getDivisionUsada() const { return divisionUsada; }
};
