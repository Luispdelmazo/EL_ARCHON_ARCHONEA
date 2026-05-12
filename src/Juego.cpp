#include "Juego.h"
#include <GL/glut.h>
// CONSTRUCTOR
Juego::Juego() {
    tablero = Tablero(1.0f, -4.5f, -4.5f);
    estadoActual = EstadoJuego::TABLERO;
    turnoActual = Bando::LUZ;
}

// INICIALIZAR: Aqui se colocaran las piezas cuando esten hechas
// tablero.colocarPieza(new Delegado(...), fila, col);

void Juego::inicializar() {

}

// DIBUJAR: Decide que pantalla mostrar segun el estado
void Juego::dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (estadoActual == EstadoJuego::TABLERO) {
        tablero.dibujar(turnoActual);
    }
    else if (estadoActual == EstadoJuego::BATALLA) {
        batalla.dibujar();
    }

    glutSwapBuffers();
}
void Juego::cambiarTurno() {
    if (turnoActual == Bando::LUZ) {
        turnoActual = Bando::OSCURIDAD;
    }
    else {
        turnoActual = Bando::LUZ;
    }
    tablero.cambiarColorOscilantes();
}

// ACTUALIZAR
void Juego::actualizar(float dt) {
    if (estadoActual == EstadoJuego::TABLERO) {
        tablero.actualizar(dt);
    }
    else if (estadoActual == EstadoJuego::BATALLA) {
        batalla.actualizar(dt);

        // Comprobar si termino la batalla
        if (batalla.getEstado() != EstadoBatalla::EN_CURSO) {
            terminarBatalla();
        }
    }
}

//COMO EN EL PANG
void Juego::reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

// GESTION RATON
void Juego::gestionRaton(int boton, int estado, int x, int y) {
    if (estadoActual == EstadoJuego::TABLERO) {
        // Se completara cuando hagamos la seleccion de piezas
    }
}

// GESTION TECLADO
/*void Juego::gestionTeclado(unsigned char tecla, int x, int y) {
    if (tecla == 27) { // ESC
        exit(0);
    }

    if (estadoActual == EstadoJuego::BATALLA) {
        batalla.gestionTeclado(tecla);
    }
} */
//prueba 1 
void Juego::gestionTeclado(unsigned char tecla, int x, int y) {
    if (tecla == 27) { // ESC
        exit(0);
    }
    if (tecla == ' ') { // Espacio para probar el cambio de turno
        cambiarTurno();
    }
    if (estadoActual == EstadoJuego::BATALLA) {
        batalla.gestionTeclado(tecla);
    }
}

// INICIAR Y TERMINAR BATALLA
void Juego::iniciarBatalla(Pieza* atacante, Pieza* defensor) {
    estadoActual = EstadoJuego::BATALLA;
    batalla.iniciar(atacante, defensor);
}

void Juego::terminarBatalla() {
    estadoActual = EstadoJuego::TABLERO;
}