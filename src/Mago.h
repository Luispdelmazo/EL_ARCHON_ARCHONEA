#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
#include "ETSIDI.h"
// Mago - alumno con poderes, movimiento volador
// Hereda de Pieza con : public Pieza - ES una Pieza (Miguel)
// Habilidad: sobrevive el primer golpe mortal con 1 de vida
// Sobreescribimos recibirDano igual que EsferaPulsante sobreescribia mueve en el Pang

class Mago : public Pieza {
private:
    bool escudoActivo; // El escudo que le salva de morir una vez

public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/alumnos/mago_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/alumnos/mago_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/alumnos/mago_ataque.png", 4 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/alumnos/mago_especial.png", 1 };
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;
    Mago(int fila, int col)
        : Pieza("Mago", Bando::LUZ, TipoMovimiento::VOLADOR,
            fila, col, 200, 30, 3, 5, 4)
    {
        escudoActivo = true;
    }
    
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

    void habilidadPostBatalla() override { spriteActual = &spriteIdle; }
    void habilidadEnBatalla() override {
		// Se implementa en recibirDano, no aquí
    }
    void conjuros() override {
        // No tiene conjuros
    }

   /* void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.3f, 0.5f, 0.9f);
        }
        glutSolidSphere(0.3f, 20, 20);

        // Octaedro encima - simbolo de magia
        if (escudoActivo) {
            glColor3f(0.8f, 0.8f, 1.0f); // Brillante cuando el escudo esta activo
        } else {
            glColor3f(0.3f, 0.3f, 0.5f); // Apagado cuando ya lo uso
        }
        glPushMatrix();
        glTranslatef(0.0f, 0.38f, 0.0f);
        glScalef(0.4f, 0.4f, 0.4f);
        glutSolidOctahedron();
        glPopMatrix();

        glPopMatrix();
    }*/

    // Sobreescribimos recibirDano para implementar el escudo
    // Igual que en el Pang EsferaPulsante sobreescribia mueve()
    void recibirDano(int dano) override {
        if (escudoActivo && vidaActual - dano <= 0) {
            vidaActual   = 1;
            escudoActivo = false;
            spriteActual = &spriteEspecial;
        } else {
            vidaActual -= dano;
            if (vidaActual <= 0) {
                vidaActual = 0;
                estaViva   = false;
            }
        }
    }

 

    bool getEscudoActivo() const { return escudoActivo; }
};
