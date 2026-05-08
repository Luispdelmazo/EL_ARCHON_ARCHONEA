#pragma once
#include <windows.h>
#include <GL/gl.h>
#include "GL/glut.h"

// tipos de casilla que puede haber en el tablero
// cada tipo se comporta y se pinta de forma diferente
enum class TipoCasilla {
    normal,       // casilla fija blanca o negra
    oscilante,    // cambia de color cada cierto tiempo
    puntoPoder    // punto de poder, da ventajas a quien la ocupa
};

// estado de las casillas oscilantes
// indica si ahora mismo favorecen a la luz o a la oscuridad
enum class EstadoCasilla {
    clara,   // favorece a los alumnos EE309
    oscura   // favorece a los profes de Automatica
};

class Casilla {
private:
    TipoCasilla tipo;
    EstadoCasilla estado;
    bool esClara;  // si es clara u oscura en el patron de ajedrez base

public:
    // constructor: le decimos que tipo es y si es clara u oscura
    Casilla(TipoCasilla tipo, bool esClara) {
        this->tipo = tipo;
        this->esClara = esClara;
        this->estado = EstadoCasilla::clara;  // empieza en fase clara
    }

    // constructor por defecto
    Casilla() {
        tipo = TipoCasilla::normal;
        esClara = true;
        estado = EstadoCasilla::clara;
    }

    // cambia el estado de las casillas oscilantes
    void cambiarEstado() {
        if (tipo == TipoCasilla::oscilante) {
            if (estado == EstadoCasilla::clara)
                estado = EstadoCasilla::oscura;
            else
                estado = EstadoCasilla::clara;
        }
    }

    // dibuja la casilla segun su tipo y estado actual
    void dibujar(float x, float y, float tam) {
        if (tipo == TipoCasilla::oscilante) {
            // las casillas oscilantes cambian entre azul claro y azul oscuro
            if (estado == EstadoCasilla::clara) {
                if (esClara)
                    glColor3f(0.5f, 0.5f, 1.0f);   // azul claro
                else
                    glColor3f(0.3f, 0.3f, 0.8f);   // azul medio
            }
            else {
                if (esClara)
                    glColor3f(0.2f, 0.2f, 0.7f);   // azul oscuro
                else
                    glColor3f(0.1f, 0.1f, 0.5f);   // azul muy oscuro
            }
        }
        else {
            // casillas normales y puntos de poder son blancas o negras
            if (esClara)
                glColor3f(1.0f, 1.0f, 1.0f);  // blanco
            else
                glColor3f(0.0f, 0.0f, 0.0f);  // negro
        }

        // dibujamos el cuadrado de la casilla
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + tam, y);
        glVertex2f(x + tam, y + tam);
        glVertex2f(x, y + tam);
        glEnd();

        // si es punto de poder dibujamos una cruz dorada encima
        if (tipo == TipoCasilla::puntoPoder)
            dibujarCruz(x, y, tam);
    }

    TipoCasilla getTipo() { return tipo; }
    EstadoCasilla getEstado() { return estado; }

private:
    // dibuja la cruz dorada de los puntos de poder
    void dibujarCruz(float x, float y, float tam) {
        glColor3f(1.0f, 0.8f, 0.0f);  // amarillo dorado
        float cx = x + tam / 2;
        float cy = y + tam / 2;
        float t = tam * 0.25f;

        glBegin(GL_QUADS);
        glVertex2f(cx - t, cy - 4);
        glVertex2f(cx + t, cy - 4);
        glVertex2f(cx + t, cy + 4);
        glVertex2f(cx - t, cy + 4);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2f(cx - 4, cy - t);
        glVertex2f(cx + 4, cy - t);
        glVertex2f(cx + 4, cy + t);
        glVertex2f(cx - 4, cy + t);
        glEnd();
    }
};