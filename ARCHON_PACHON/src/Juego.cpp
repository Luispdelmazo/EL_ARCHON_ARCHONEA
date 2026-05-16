#include "Juego.h"
#include <GL/glut.h>

// CONSTRUCTOR
Juego::Juego() {
    tablero = Tablero(1.0f, -4.5f, -4.5f);
    /*estadoActual = EstadoJuego::TABLERO;*/
    estadoActual = EstadoJuego::MENU; // Arranca en el menu
    turnoActual = Bando::LUZ;
}

// INICIALIZAR: Aqui se colocaran las piezas cuando esten hechas
// tablero.colocarPieza(new Delegado(...), fila, col);
void Juego::inicializar() {

}
void Juego::dibujar() {// que pantalla mostrar segun el estado
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if (estadoActual == EstadoJuego::TABLERO) {
        tablero.dibujar(turnoActual);
    }
    else if (estadoActual == EstadoJuego::BATALLA) {
        batalla.dibujar();
    }
    else if (estadoActual == EstadoJuego::MENU) {
        menu.dibujar();
    }
    glutSwapBuffers();
}

// CAMBIAR TURNO: Alterna entre LUZ y OSCURIDAD y cambia el color de las oscilantes
void Juego::cambiarTurno() {
    if (turnoActual == Bando::LUZ) {
        turnoActual = Bando::OSCURIDAD;
    }
    else {
        turnoActual = Bando::LUZ;
    }
    tablero.cambiarColorOscilantes();
}

void Juego::actualizar(float dt) {//actualizar
    if (estadoActual == EstadoJuego::TABLERO) {
        tablero.actualizar(dt);
    }
    else if (estadoActual == EstadoJuego::BATALLA) {
        batalla.actualizar(dt);
        if (batalla.getEstado() != EstadoBatalla::EN_CURSO) {// Comprobar si termino la batalla
            terminarBatalla();
        }
    }
}
void Juego::reshape(int w, int h) {//pang 
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

// CONVERTIR COORDENADAS: Convierte coordenadas de pixel a coordenadas OpenGL para el raton
void Juego::convertirCoordenadas(int pixelX, int pixelY, float& glX, float& glY) {
    int ancho = glutGet(GLUT_WINDOW_WIDTH);
    int alto = glutGet(GLUT_WINDOW_HEIGHT);
    // De pixeles a coordenadas OpenGL (-5 a 5)
    glX = ((float)pixelX / ancho) * 10.0f - 5.0f;
    glY = -((float)pixelY / alto) * 10.0f + 5.0f; // Invertir Y
}

// GESTION RATON: Selecciona piezas y gestiona movimientos
void Juego::gestionRaton(int boton, int estado, int x, int y) {
    if (estadoActual == EstadoJuego::MENU) {
        float glX, glY;
        convertirCoordenadas(x, y, glX, glY);
        menu.gestionRaton(boton, estado, glX, glY);
        // Comprobar si eligio algo
        if (menu.haSeleccionado) {
            if (menu.getOpcionSeleccionada() == OpcionMenu::JUGAR) {
                estadoActual = EstadoJuego::TABLERO;
                inicializar();
            }
            else if (menu.getOpcionSeleccionada() == OpcionMenu::SALIR) {
                exit(0);
            }
            menu.haSeleccionado = false;
        }
        return;
    }
    // Solo boton izquierdo al soltar y solo en el tablero
    if (boton != GLUT_LEFT_BUTTON || estado != GLUT_UP) return;
    if (estadoActual != EstadoJuego::TABLERO) return;
    // Convertir coordenadas de pixel a OpenGL
    float glX, glY;
    convertirCoordenadas(x, y, glX, glY); // Convertir a fila/columna del tablero
    int fila, col;
    if (!tablero.pantallaATablero(glX, glY, fila, col)) { // Clic fuera del tablero, deseleccionar
        tablero.deseleccionar();
        return;
    }
    if (!tablero.tieneSeleccion()) { // No hay pieza seleccionada, intentar seleccionar
        tablero.seleccionarPieza(fila, col, turnoActual);
    }
    else {
        if (tablero.destinoEsValido(fila, col)) {// Ya hay pieza seleccionada, ver a donde se mueve
            if (tablero.hayEnemigo(fila, col, turnoActual)) { // hay enemigo iniciar batlla
                Pieza* atacante = tablero.getPieza(tablero.getFilaSeleccionada(),
                    tablero.getColSeleccionada());
                Pieza* defensor = tablero.getPieza(fila, col);
                iniciarBatalla(atacante, defensor);
            }
            else {
                tablero.moverPiezaSeleccionada(fila, col);
                cambiarTurno();
            }
        }
        tablero.deseleccionar();// Deseleccionar siempre despues de intentar mover
    }
    glutPostRedisplay();
}

// GESTION TECLADO
void Juego::gestionTeclado(unsigned char tecla, int x, int y) {
    if (tecla == 27) { // ESC
        if (estadoActual == EstadoJuego::TABLERO || estadoActual == EstadoJuego::BATALLA) { // Volver al menu en vez de cerrar
            estadoActual = EstadoJuego::MENU;
            menu.haSeleccionado = false;
            glutPostRedisplay();
            return;
        }
        else {
            exit(0); // Si ya estas en el menu, ESC cierra
        }
    }
    else if (estadoActual == EstadoJuego::MENU) {
        menu.gestionTeclado(tecla);
        if (menu.haSeleccionado) {
            if (menu.getOpcionSeleccionada() == OpcionMenu::JUGAR) {
                estadoActual = EstadoJuego::TABLERO;
                inicializar();
            }
            else if (menu.getOpcionSeleccionada() == OpcionMenu::SALIR) {
                exit(0);
            }
            menu.haSeleccionado = false;
        }
        return;
    }
    else if (tecla == 27) { // ESC
        exit(0);
    }
    else if (estadoActual == EstadoJuego::BATALLA) {
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
