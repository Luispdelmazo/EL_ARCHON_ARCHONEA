#include "Juego.h"
#include "Delegado.h"
#include "Veterano.h"
#include "Nocturno.h"
#include "Todo10.h"
#include "Mago.h"
#include "Ocupado.h"
#include "Ausente.h"
#include "Humilde.h"
#include "MiguelHernando.h"
#include "Platero.h"
#include "Basil.h"
#include "HectorMontes.h"
#include "OscarC.h"
#include "SanSegundo.h"
#include "Giuseppe.h"
#include "Imanol.h"
#include <GL/glut.h>

// CONSTRUCTOR
Juego::Juego() : tablero{ Tablero(1.0f, -4.5f, -4.5f) }
{
    estadoActual       = EstadoJuego::MENU;
    turnoActual        = Bando::LUZ;
    juegoTerminado     = false;
    ganador            = Bando::LUZ;
    filaDestinoBatalla = -1;
    colDestinoBatalla  = -1;
    turnosJugados      = 0;
}

// INICIALIZAR
// Colocamos las piezas en el tablero al empezar, igual que en el Pang se agregaban esferas con esferas.agregar(new Esfera(...)) en inicializa()
// LUZ en columna izquierda, OSCURIDAD en derecha
void Juego::inicializar() {
    turnosJugados = 0;
    juegoTerminado = false;

    // --- BANDO LUZ - columna izquierda (col 0) ---
    tablero.colocarPieza(new Delegado(4, 0), 4, 0); // Lider en el centro
    tablero.colocarPieza(new Todo10(0, 0), 0, 0); // Volador arriba
    tablero.colocarPieza(new Mago(1, 0), 1, 0); // Volador
    tablero.colocarPieza(new Ocupado(2, 0), 2, 0); // Volador
    tablero.colocarPieza(new Veterano(3, 0), 3, 0); // Terrestre
    tablero.colocarPieza(new Ausente(5, 0), 5, 0); // Terrestre
    tablero.colocarPieza(new Nocturno(6, 0), 6, 0); // Terrestre
    tablero.colocarPieza(new Humilde(7, 0), 7, 0); // Peon
    tablero.colocarPieza(new Humilde(8, 0), 8, 0); // Peon

    // --- BANDO OSCURIDAD - columna derecha (col 8) ---
    tablero.colocarPieza(new MiguelHernando(4, 8), 4, 8); // Lider en el centro
    tablero.colocarPieza(new Platero(0, 8), 0, 8); // Volador arriba
    tablero.colocarPieza(new Basil(1, 8), 1, 8); // Volador
    tablero.colocarPieza(new SanSegundo(2, 8), 2, 8); // Volador
    tablero.colocarPieza(new Giuseppe(3, 8), 3, 8); // Terrestre
    tablero.colocarPieza(new HectorMontes(5, 8), 5, 8); // Terrestre
    tablero.colocarPieza(new OscarC(6, 8), 6, 8); // Terrestre
    tablero.colocarPieza(new Imanol(7, 8), 7, 8); // Peon
    tablero.colocarPieza(new Imanol(8, 8), 8, 8); // Peon
}

// DIBUJAR - decide que pantalla mostrar segun el estado igual que el Coordinador del Pang gestionaba el dibujo
void Juego::dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (juegoTerminado) {
        dibujarPantallaFin();
    } else if (estadoActual == EstadoJuego::MENU) {
        menu.dibujar();
    } else if (estadoActual == EstadoJuego::TABLERO) {
        tablero.dibujar(turnoActual);
    } else if (estadoActual == EstadoJuego::BATALLA) {
        batalla.dibujar();
    } else if (estadoActual == EstadoJuego::RANKING) {
        ranking.dibujar();
    }

    glutSwapBuffers();
}

// CAMBIAR TURNO
void Juego::cambiarTurno() {
    if (turnoActual == Bando::LUZ) {
        turnoActual = Bando::OSCURIDAD;
    } else {
        turnoActual = Bando::LUZ;
    }
    tablero.cambiarColorOscilantes();
    turnosJugados++;
    comprobarVictoria();
}

// ACTUALIZAR - igual que Mundo::mueve en el Pang
void Juego::actualizar(float dt) {
    if (estadoActual == EstadoJuego::TABLERO) {
        tablero.actualizar(dt);
    } else if (estadoActual == EstadoJuego::BATALLA) {
        batalla.actualizar(dt);
        if (batalla.getEstado() != EstadoBatalla::EN_CURSO) {
            terminarBatalla();
        }
    }
}

void Juego::reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void Juego::convertirCoordenadas(int pixelX, int pixelY, float& glX, float& glY) {
    int ancho = glutGet(GLUT_WINDOW_WIDTH);
    int alto  = glutGet(GLUT_WINDOW_HEIGHT);
    glX =  ((float)pixelX / ancho) * 10.0f - 5.0f;
    glY = -((float)pixelY / alto)  * 10.0f + 5.0f;
}

// GESTION RATON
void Juego::gestionRaton(int boton, int estado, int x, int y) {
    if (juegoTerminado) return;

    float glX, glY;
    convertirCoordenadas(x, y, glX, glY);

    if (estadoActual == EstadoJuego::MENU) {
        menu.gestionRaton(boton, estado, glX, glY);
        if (menu.haSeleccionado) {
            if (menu.getOpcionSeleccionada() == OpcionMenu::JUGAR) {
                batalla.setDificultad(menu.getDificultad());
                estadoActual = EstadoJuego::TABLERO;
                inicializar();
            } else if (menu.getOpcionSeleccionada() == OpcionMenu::RANKING) {
                estadoActual = EstadoJuego::RANKING;
            } else if (menu.getOpcionSeleccionada() == OpcionMenu::SALIR) {
                exit(0);
            }
            menu.haSeleccionado = false;
        }
        return;
    }

    if (estadoActual == EstadoJuego::RANKING) return;

    if (boton != GLUT_LEFT_BUTTON || estado != GLUT_UP) return;
    if (estadoActual != EstadoJuego::TABLERO) return;

    int fila, col;
    if (!tablero.pantallaATablero(glX, glY, fila, col)) {
        tablero.deseleccionar();
        return;
    }

    if (!tablero.tieneSeleccion()) {
        tablero.seleccionarPieza(fila, col, turnoActual);
    } else {
        if (tablero.destinoEsValido(fila, col)) {
            if (tablero.hayEnemigo(fila, col, turnoActual)) {
                filaDestinoBatalla = fila;
                colDestinoBatalla  = col;
                Pieza* atacante = tablero.getPieza(tablero.getFilaSeleccionada(),
                                                   tablero.getColSeleccionada());
                Pieza* defensor = tablero.getPieza(fila, col);
                iniciarBatalla(atacante, defensor);
            } else {
                tablero.moverPiezaSeleccionada(fila, col);
                cambiarTurno();
            }
        }
        tablero.deseleccionar();
    }
    glutPostRedisplay();
}

// GESTION TECLADO
void Juego::gestionTeclado(unsigned char tecla, int x, int y) {
    if (juegoTerminado) {
        if (tecla == 13) {
            juegoTerminado = false;
            estadoActual   = EstadoJuego::MENU;
            glutPostRedisplay();
        }
        return;
    }

    if (tecla == 27) { // ESC
        if (estadoActual == EstadoJuego::TABLERO  ||
            estadoActual == EstadoJuego::BATALLA  ||
            estadoActual == EstadoJuego::RANKING) {
            estadoActual = EstadoJuego::MENU;
            menu.haSeleccionado = false;
            glutPostRedisplay();
            return;
        } else {
            menu.gestionTeclado(tecla); // Deja que el menu gestione el ESC
            glutPostRedisplay();
            return;
        }
    }

    if (estadoActual == EstadoJuego::MENU) {
        menu.gestionTeclado(tecla);
        if (menu.haSeleccionado) {
            if (menu.getOpcionSeleccionada() == OpcionMenu::JUGAR) {
                batalla.setDificultad(menu.getDificultad());
                estadoActual = EstadoJuego::TABLERO;
                inicializar();
            } else if (menu.getOpcionSeleccionada() == OpcionMenu::RANKING) {
                estadoActual = EstadoJuego::RANKING;
            } else if (menu.getOpcionSeleccionada() == OpcionMenu::SALIR) {
                exit(0);
            }
            menu.haSeleccionado = false;
        }
        return;
    }

    if (estadoActual == EstadoJuego::BATALLA) {
        batalla.gestionTeclado(tecla);
    }
}

void Juego::gestionTecladoSuelto(unsigned char tecla, int x, int y) {
    if (estadoActual == EstadoJuego::BATALLA) {
        batalla.gestionTecladoSuelto(tecla);
    }
}

// INICIAR BATALLA
void Juego::iniciarBatalla(Pieza* atacante, Pieza* defensor) {
    estadoActual = EstadoJuego::BATALLA;
    batalla.iniciar(atacante, defensor);
}

// TERMINAR BATALLA
// Segun quien gano, el tablero elimina al perdedor
// Igual que en el Pang el coordinador eliminaba la esfera cuando chocaba
void Juego::terminarBatalla() {
    estadoActual = EstadoJuego::TABLERO;

    int filaAtacante = tablero.getFilaSeleccionada();
    int colAtacante  = tablero.getColSeleccionada();

    if (batalla.getEstado() == EstadoBatalla::GANA_ATACANTE) {
        tablero.eliminarPieza(filaDestinoBatalla, colDestinoBatalla);
        tablero.moverPieza(filaAtacante, colAtacante, filaDestinoBatalla, colDestinoBatalla);
    } else if (batalla.getEstado() == EstadoBatalla::GANA_DEFENSOR) {
        tablero.eliminarPieza(filaAtacante, colAtacante);
    }

    tablero.deseleccionar();
    cambiarTurno();
}

// COMPROBAR VICTORIA - las dos condiciones del Archon original
void Juego::comprobarVictoria() {
    if (tablero.controlaPuntosDePoder(Bando::LUZ)) {
        juegoTerminado = true;
        ganador        = Bando::LUZ;
        ranking.guardarResultado("EE309", turnosJugados);
        return;
    }
    if (tablero.controlaPuntosDePoder(Bando::OSCURIDAD)) {
        juegoTerminado = true;
        ganador        = Bando::OSCURIDAD;
        ranking.guardarResultado("Automatica", turnosJugados);
        return;
    }
    if (tablero.contarPiezas(Bando::LUZ) == 0) {
        juegoTerminado = true;
        ganador        = Bando::OSCURIDAD;
        ranking.guardarResultado("Automatica", turnosJugados);
        return;
    }
    if (tablero.contarPiezas(Bando::OSCURIDAD) == 0) {
        juegoTerminado = true;
        ganador        = Bando::LUZ;
        ranking.guardarResultado("EE309", turnosJugados);
        return;
    }
}

// PANTALLA DE FIN
void Juego::dibujarPantallaFin() {
    glColor3f(0.05f, 0.05f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(-5.0f, -5.0f, 0.0f);
    glVertex3f( 5.0f, -5.0f, 0.0f);
    glVertex3f( 5.0f,  5.0f, 0.0f);
    glVertex3f(-5.0f,  5.0f, 0.0f);
    glEnd();

    if (ganador == Bando::LUZ) {
        glColor3f(1.0f, 0.85f, 0.0f);
        dibujarTexto(-2.5, 1.5f, "GANAN LOS ALUMNOS EE309!");
        dibujarTexto(-2.0, 0.5f, "Los profes suspenden en el tablero");
    } else {
        glColor3f(0.5f, 0.0f, 0.8f);
        dibujarTexto(-2.5, 1.5f, "GANA EL DEPARTAMENTO!");
        dibujarTexto(-2.0, 0.5f, "Te vas a julio amigo...");
    }

    glColor3f(0.7f, 0.7f, 0.7f);
    std::string textoTurnos = std::to_string(turnosJugados) + " turnos jugados";
    dibujarTexto(-1.5f, -0.5f, textoTurnos);

    glColor3f(0.5f, 0.5f, 0.5f);
    dibujarTexto(-2.5f, -2.0f, "Pulsa ENTER para volver al menu");
}

void Juego::dibujarTexto(float x, float y, std::string texto) {
    glRasterPos2f(x, y);
    for (int i = 0; i < (int)texto.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
    }
}
