#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
#include "ETSIDI.h"
// Veterano - alumno con experiencia, movimiento terrestre
// Hereda de Pieza con : public Pieza - ES una Pieza 
// Habilidad: su ataque sube cada vez que gana una batalla
// Visual: cubo solido azul oscuro - robusto y resistente

class Veterano : public Pieza {
private:
    int batallasGanadas; // Cada victoria le hace mas fuerte

public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/alumnos/veterano_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/alumnos/veterano_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/alumnos/veterano_ataque.png", 5 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/alumnos/veterano_especial.png", 4 };
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;
    Veterano(int fila, int col)
        : Pieza("Veterano", Bando::LUZ, TipoMovimiento::TERRESTRE,
            fila, col, 300, 30, 3, 3, 1)
    {
        batallasGanadas = 0;
    }

    /* void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.1f, 0.2f, 0.7f); // Azul oscuro
        }
        glutSolidCube(0.6f);

        glPopMatrix();
    }*/
    
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
        // Su ataque sube al ganar batallas
        batallasGanadas++;
        ataque += 5;// lo que no le mata le hace mas fuerte
        spriteActual = &spriteEspecial;
    }

    int getBatallasGanadas() const { return batallasGanadas; }
};
