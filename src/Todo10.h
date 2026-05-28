#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
#include "ETSIDI.h"
// Todo10 - el alumno que siempre saca 10, movimiento volador
// Hereda de Pieza con : public Pieza - ES una Pieza 
// Habilidad: copia las estadisticas del rival en combate
// Visual: esfera azul clara con alas trianguladas a los lados

class Todo10 : public Pieza {
private:
    bool habilidadUsada; // Solo copia una vez por batalla

public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/alumnos/todo10_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/alumnos/todo10_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/alumnos/todo10_ataque.png", 4 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/alumnos/todo10_especial.png", 3 };
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;

    Todo10(int fila, int col)
        : Pieza("Todo10", Bando::LUZ, TipoMovimiento::VOLADOR,
            fila, col, 250, 30, 5, 4, 3) {
        habilidadUsada = false;
    }

    /*void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.4f, 0.6f, 1.0f); // Azul claro - volador
        }
        glutSolidSphere(0.3f, 20, 20);

        // Alas - marca que es volador
        glColor3f(0.6f, 0.8f, 1.0f);
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
    }

    void habilidadEspecial() override {
        // Copia stats del rival - se gestiona en Batalla
        habilidadUsada = true;
    }*/
    
/*    void dibujar() const override {
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

    void habilidadEspecial() override { spriteActual = &spriteEspecial; }
    // Para que Batalla pueda copiar las stats del rival
    void copiarStats(Pieza* rival) {
        if (!habilidadUsada && rival != nullptr) {
            ataque = rival->getAtaque();
            velocidad = rival->getVelocidad();
            setAlcanceAtaque(rival->getAlcanceAtaque());
            habilidadUsada = true;
        }
    }

    bool getHabilidadUsada() const { return habilidadUsada; }

};
