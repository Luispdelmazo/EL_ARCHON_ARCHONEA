#pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
#include "ETSIDI.h"
// Ausente - alumno que nunca va a clase, movimiento terrestre
// Hereda de Pieza con : public Pieza - ES una Pieza (Miguel)
// Habilidad: ataque se duplica cuando vida baja del 50%
// Sobreescribimos recibirDano igual que Mago - patron del Pang

class Ausente : public Pieza {
private:
    bool habilidadActivada; // Solo se activa una vez

public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/alumnos/ausente_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/alumnos/ausente_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/alumnos/ausente_ataque.png", 4 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/alumnos/ausente_idle1.png",  1 }; // mismo idle
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;
    bool ataqueDoble = false;
    Ausente(int fila, int col)
        : Pieza("Ausente", Bando::LUZ, TipoMovimiento::TERRESTRE,
            fila, col, 150, 30, 3, 3, 1)
    {
        habilidadActivada = false;
    }

    /*void dibujar() override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            // Cambia a rojo cuando activa la habilidad
            if (habilidadActivada) {
                glColor3f(1.0f, 0.3f, 0.3f);
            } else {
                glColor3f(0.4f, 0.6f, 0.9f);
            }
        }
        glutSolidSphere(0.32f, 20, 20);

        glPopMatrix();
    } */
 /*   void dibujar() const override {
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

    // Sobreescribimos recibirDano - mismo patron que Mago con su escudo
    void recibirDano(int dano) override {
        Pieza::recibirDano(dano);
        vidaActual -= dano;
        if (vidaActual <= 0) {
            vidaActual = 0;
            estaViva   = false;
            return;
        }
        // Si baja del 50% duplica el ataque una sola vez
        if (!ataqueDoble && vidaActual < vidaMax / 2) {
            ataque *= 2;
            ataqueDoble = true;
            spriteActual = &spriteAtaque;
        }
    }

    void habilidadPostBatalla() override {
        spriteActual = &spriteEspecial;
        // Se activa automaticamente en recibirDano
    }
	void habilidadEnBatalla() override {
		// No tiene habilidad post movimiento
	}
	void conjuros() override {
		// No tiene conjuros
	}

    bool getHabilidadActivada() const { return habilidadActivada; }
};
