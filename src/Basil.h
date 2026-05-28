#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
#include "ETSIDI.h"
// Basil - profe volador agresivo del departamento
// Hereda de Pieza con : public Pieza - ES una Pieza (Miguel)
// Habilidad: ataque muy potente pero se daña a si mismo si falla
// Visual: esfera morada con puas - agresivo pero peligroso para el mismo

class Basil : public Pieza {
private:
    int autoDanoAlFallar; // Se daña a si mismo si el ataque no alcanza al rival

public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/profesores/basil_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/profesores/basil_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/profesores/basil_ataque.png", 4 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/profesores/basil_especial.png", 4 };
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;
    Basil(int fila, int col)
        : Pieza("Basil", Bando::OSCURIDAD, TipoMovimiento::VOLADOR,
                fila, col, 200, 30, 7, 5, 4)
    {
        autoDanoAlFallar = 5;
    }

 /*   void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.7f, 0.0f, 0.7f); // Morado brillante
        }
        glutSolidSphere(0.3f, 20, 20);

        // Puas - simboliza su caracter agresivo
        glColor3f(0.9f, 0.0f, 0.9f);
        float angulos[] = { 0.0f, 45.0f, 90.0f, 135.0f, 180.0f, 225.0f, 270.0f, 315.0f };
        for (int i = 0; i < 8; i++) {
            float rad = angulos[i] * 3.14159f / 180.0f;
            glBegin(GL_LINES);
            glVertex3f(0.3f * cosf(rad), 0.3f * sinf(rad), 0.0f);
            glVertex3f(0.5f * cosf(rad), 0.5f * sinf(rad), 0.0f);
            glEnd();
        }

        glPopMatrix();
    }  */
    /*void dibujar() const override {
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
        spriteActual->setSize(0.9f, 0.9f);   // Tamaño relativo a 1 casilla de ancho
        //Dibujamos el gráfico
        spriteActual->draw();
        spriteActual->loop();

        glPopMatrix();
    }
    void habilidadEspecial() override {
        // Ataque potente - si falla se daña a si mismo
        // Se gestiona en Batalla
        spriteActual = &spriteEspecial;
    }

    int getAutoDano() const { return autoDanoAlFallar; }
};
