#pragma once
#include "Pieza.h"
#include <GL/glut.h>
#include "ETSIDI.h"
// OscarC - profe terrestre que se hace mas fuerte con victorias
// Hereda de Pieza con : public Pieza - ES una Pieza 
// Habilidad: ataque vida y velocidad aumentan con cada batalla ganada
// Visual: esfera morada que crece y cambia de color con las victorias

class OscarC : public Pieza {
private:
    int batallasGanadas;
    float tamano; // Crece visualmente con cada victoria

public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/profesores/oscarc_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/profesores/oscarc_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/profesores/oscarc_ataque.png", 5 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/profesores/oscarc_especial.png", 1 };
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;
    OscarC(int fila, int col)
        : Pieza("OscarC", Bando::OSCURIDAD, TipoMovimiento::TERRESTRE,
                fila, col, 250, 20, 5, 4, 2)
    {
        batallasGanadas = 0;
        tamano          = 0.32f;
    }

 /*   void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            // Cambia de color segun las batallas ganadas
            if (batallasGanadas == 0) {
                glColor3f(0.5f, 0.0f, 0.5f);
            } else if (batallasGanadas == 1) {
                glColor3f(0.7f, 0.0f, 0.3f);
            } else {
                glColor3f(0.9f, 0.0f, 0.1f); // Casi rojo con muchas victorias
            }
        }
        glutSolidSphere(tamano, 20, 20);

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
        // Sube stats al ganar una batalla
        batallasGanadas++;
        ataque    += 3;
        vidaMax   += 5;
        vidaActual = vidaMax;
        velocidad += 1;
        tamano    += 0.04f; // Crece visualmente
        spriteActual = &spriteEspecial;
    }

    int getBatallasGanadas() const { return batallasGanadas; }
};
