  #pragma once
#include "Pieza.h"
//#include "glut.h"
#include <GL/glut.h>
#include "ETSIDI.h"
// Humilde - el alumno mas modesto, movimiento terrestre
// Hereda de Pieza con : public Pieza - ES una Pieza (Miguel)
// Habilidad: sube sus stats al ganar una batalla
// Visual: esfera azul muy pequena - el peon del bando luz, hay varios

class Humilde : public Pieza {
public:
    mutable ETSIDI::SpriteSequence spriteIdle{ "imagenes/alumnos/humilde_idle1.png",  1 };
    mutable ETSIDI::SpriteSequence spriteWalk{ "imagenes/alumnos/humilde_walk.png",   1 };
    mutable ETSIDI::SpriteSequence spriteAtaque{ "imagenes/alumnos/humilde_ataque.png", 5 };
    mutable ETSIDI::SpriteSequence spriteEspecial{ "imagenes/alumnos/humilde_especial.png", 3 };
    mutable ETSIDI::SpriteSequence* spriteActual = &spriteIdle;
    Humilde(int fila, int col)
        : Pieza("Humilde", Bando::LUZ, TipoMovimiento::TERRESTRE,
            fila, col, 100, 20, 5, 3, 1)
    {}

    /*void dibujar() const override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;

        glPushMatrix();
        glTranslatef(x, y, 0.2f);

        if (estaSeleccionada) {
            glColor3f(1.0f, 1.0f, 0.0f);
        } else {
            glColor3f(0.5f, 0.7f, 1.0f); // Azul muy claro - modesto
        }
        // Mas pequeno que el resto - es el peon del bando luz
        glutSolidSphere(0.22f, 15, 15);

        glPopMatrix();
    }*/
    /*void dibujar() const override {
        float x = -4.5f + col * 1.0f + 0.5f;
        float y = -4.5f + fila * 1.0f + 0.5f;
        glPushMatrix();
        glTranslatef(x, y, 0.2f);
        if (estaSeleccionada) glColor3f(1.0f, 1.0f, 0.0f);
        else glColor3f(1.0f, 1.0f, 1.0f);
        spriteActual->setCenter(1, 0);
        spriteActual->setSize(0.9f, 0.9f);
        spriteActual->draw();
        spriteActual->loop();
        glPopMatrix();
        
    }*/
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

    void habilidadEspecial() override {
        // Al ganar sube sus stats - se vuelve mas fuerte con la experiencia
        ataque    += 5;
        vidaMax   += 10;
        velocidad += 1;
        spriteActual = &spriteEspecial;
    }
    void loop() const override {
        spriteActual->loop();
    }
} ;