#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
#include "ETSIDI.h"
// Ocupado - alumno siempre liado, movimiento volador
// Hereda de Pieza con : public Pieza - ES una Pieza (Miguel)
// Habilidad: cada 5 ataques hace dano doble
// Visual: esfera azul con puntos alrededor - siempre ocupado con mil cosas

class Ocupado : public Pieza {
private:

public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/alumnos/ocupado_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/alumnos/ocupado_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/alumnos/ocupado_ataque.png", 5 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/alumnos/ocupado_especial.png", 3 };
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;
    Ocupado(int fila, int col)
        : Pieza("Ocupado", Bando::LUZ, TipoMovimiento::VOLADOR,
            fila, col, 200, 30, 2, 3, 2)
    {
        contadorAtaques = 0;
    }

    /*void dibujar() override {
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

        // Puntos alrededor - simboliza que esta ocupado con mil cosas
        glColor3f(0.6f, 0.8f, 1.0f);
        float angulos[] = { 0.0f, 60.0f, 120.0f, 180.0f, 240.0f, 300.0f };
        for (int i = 0; i < 6; i++) {
            float rad = angulos[i] * 3.14159f / 180.0f;
            glPushMatrix();
            glTranslatef(0.38f * cosf(rad), 0.38f * sinf(rad), 0.0f);
            glutSolidSphere(0.06f, 8, 8);
            glPopMatrix();
        }

        glPopMatrix();
    }*/
    
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

    void habilidadEnBatalla() override {
        // cada 5 ataques el siguiente es mas fuerte
        if (contadorAtaques == 0) ataque = 30;
        if ((contadorAtaques+1)% 5 == 0 && contadorAtaques > 0) {
            spriteActual = &spriteEspecial;
        }
        else if (contadorAtaques % 5 == 0 && contadorAtaques > 0) {
            ataque = 60;
            spriteActual = &spriteIdle;
        } else if((contadorAtaques-1) % 5 == 0 && contadorAtaques > 5) {
            ataque = 30;
        }
    }
    void habilidadPostBatalla() override {
        // No tiene habilidad post movimiento
        spriteActual = &spriteIdle;
    }
    void conjuros() override {
        // No tiene conjuros
    }

    // Para que Batalla compruebe si toca dano doble
    bool deberiaDanoDoble() {
        return (contadorAtaques > 0 && contadorAtaques % 5 == 0);
    }

    int getContadorAtaques() const { return contadorAtaques; }
};
