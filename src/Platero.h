#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
#include "ETSIDI.h"
// Platero - profe volador del departamento
// Hereda de Pieza con : public Pieza - ES una Pieza 
// Habilidad: su zona de dano crece en combate cuantos mas turnos pasan
// Visual: esfera morada con alas - volador del bando oscuridad

class Platero : public Pieza {
private:
    int turnosCombate; // Su alcance crece con los turnos

public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/profesores/platero_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/profesores/platero_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/profesores/platero_ataque.png", 5 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/profesores/platero_especial.png", 3 };
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;
    Platero(int fila, int col)
        : Pieza("Platero", Bando::OSCURIDAD, TipoMovimiento::VOLADOR,
                fila, col, 250, 30, 5, 4, 3)
    {
        turnosCombate = 0;
    }

  /*  void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.6f, 0.1f, 0.9f); // Morado claro
        }
        glutSolidSphere(0.3f, 20, 20);

        // Alas - marca que es volador
        glColor3f(0.4f, 0.0f, 0.6f);
        glBegin(GL_TRIANGLES);
        glVertex3f(-0.15f,  0.0f, 0.0f);
        glVertex3f(-0.45f,  0.2f, 0.0f);
        glVertex3f(-0.45f, -0.2f, 0.0f);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex3f( 0.15f,  0.0f, 0.0f);
        glVertex3f( 0.45f,  0.2f, 0.0f);
        glVertex3f( 0.45f, -0.2f, 0.0f);
        glEnd();

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

    }*/

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
        // La zona de dano crece con los turnos en combate
        spriteActual = &spriteEspecial;
        turnosCombate++;
        alcanceAtaque += 1;
    }

    int getTurnosCombate() const { return turnosCombate; }
};
