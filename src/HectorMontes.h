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
    float timerCuracion; // Timer para curar cada segundo

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
        timerCuracion = 0.0f;
    }

 /*   void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.4f, 0.0f, 0.6f); // Morado oscuro
        }
        glutSolidCube(0.6f);

        // Cruz verde encima - simbolo de curacion
        glColor3f(0.0f, 0.8f, 0.0f);
        glBegin(GL_QUADS);
        glVertex3f(-0.25f,  0.05f, 0.35f);
        glVertex3f( 0.25f,  0.05f, 0.35f);
        glVertex3f( 0.25f, -0.05f, 0.35f);
        glVertex3f(-0.25f, -0.05f, 0.35f);
        glVertex3f(-0.05f,  0.25f, 0.35f);
        glVertex3f( 0.05f,  0.25f, 0.35f);
        glVertex3f( 0.05f, -0.25f, 0.35f);
        glVertex3f(-0.05f, -0.25f, 0.35f);
        glEnd();

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
        // 1. Calculamos la posición exacta en el plano del tablero (-4.5f a 4.5f)
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        // 2. Usamos el empuje de matriz clásico para movernos a la casilla
        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        // 3. Aplicamos el color de selección si el usuario la pincha
        if (estaSeleccionada) glColor3f(1.0f, 1.0f, 0.0f);
        else                  glColor3f(1.0f, 1.0f, 1.0f);

        // 4. CONFIGURACIÓN DEL SPRITE: Volvemos a los valores métricos
        spriteActual->setCenter(0.5f, 0.5f); // Centrado absoluto en el origen de la traslación
        spriteActual->setSize(0.9f, 0.9f);   // Tamaño relativo a 1 casilla de ancho

        // 5. Dibujamos el gráfico
        spriteActual->draw();
        spriteActual->loop();

        // 6. Liberamos la matriz para la siguiente casilla
        glPopMatrix();
    }

    void habilidadEspecial() override { // recupera 1 punto de vida por segundo - se llama desde Batalla
        curar(1);
        spriteActual = &spriteEspecial;
    }

    // Batalla llama a esto con dt para curar cada segundo
    void actualizarCuracion(float dt) {
        timerCuracion += dt;
        if (timerCuracion >= 1.0f) {
            curar(1);
            timerCuracion = 0.0f;
        }
    }
};
