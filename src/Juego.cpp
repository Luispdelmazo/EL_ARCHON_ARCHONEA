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
    modoJuego          = ModoJuego::JvsIA;
    ganador            = Bando::LUZ;
    filaDestinoBatalla = -1;
    colDestinoBatalla  = -1;
    turnosJugados      = 0;
    filaAtacanteBatalla = -1;
    colAtacanteBatalla = -1;
    turnoIA = false;
    timerIA = 1.5f;
    //IA
    faseIA = 0;
    filaOrigenIA = -1;
    colOrigenIA = -1;
    filaDestIA = -1;
    colDestIA = -1;
}

// INICIALIZAR
// Colocamos las piezas en el tablero al empezar, igual que en el Pang se agregaban esferas con esferas.agregar(new Esfera(...)) en inicializa() LUZ en columna izquierda, OSCURIDAD en derecha
void Juego::inicializar() {
    turnosJugados = 0;
    //  BANDO LUZ - columna izquierda (col 0) + peones en col 1 
    tablero.colocarPieza(new Ocupado(0, 0), 0, 0);
    tablero.colocarPieza(new Veterano(1, 0), 1, 0);
    tablero.colocarPieza(new Nocturno(2, 0), 2, 0);
    tablero.colocarPieza(new Mago(3, 0), 3, 0);
    tablero.colocarPieza(new Delegado(4, 0), 4, 0); // Lider en el centro
    tablero.colocarPieza(new Todo10(5, 0), 5, 0);
    tablero.colocarPieza(new Nocturno(6, 0), 6, 0);
    tablero.colocarPieza(new Veterano(7, 0), 7, 0);
    tablero.colocarPieza(new Ocupado(8, 0), 8, 0);
    // Fila de peones LUZ - columna 1
    tablero.colocarPieza(new Ausente(0, 1), 0, 1);
    tablero.colocarPieza(new Humilde(1, 1), 1, 1);
    tablero.colocarPieza(new Humilde(2, 1), 2, 1);
    tablero.colocarPieza(new Humilde(3, 1), 3, 1);
    tablero.colocarPieza(new Humilde(4, 1), 4, 1);
    tablero.colocarPieza(new Humilde(5, 1), 5, 1);
    tablero.colocarPieza(new Humilde(6, 1), 6, 1);
    tablero.colocarPieza(new Humilde(7, 1), 7, 1);
    tablero.colocarPieza(new Ausente(8, 1), 8, 1);
    // BANDO OSCURIDAD - columna derecha (col 8) + peones en col 7 
    tablero.colocarPieza(new SanSegundo(0, 8), 0, 8);
    tablero.colocarPieza(new HectorMontes(1, 8), 1, 8);
    tablero.colocarPieza(new OscarC(2, 8), 2, 8);
    tablero.colocarPieza(new Basil(3, 8), 3, 8);
    tablero.colocarPieza(new MiguelHernando(4, 8), 4, 8); // lider
    tablero.colocarPieza(new Platero(5, 8), 5, 8);
    tablero.colocarPieza(new OscarC(6, 8), 6, 8);
    tablero.colocarPieza(new HectorMontes(7, 8), 7, 8);
    tablero.colocarPieza(new SanSegundo(8, 8), 8, 8);
    // fila de peones OSCURIDAD - columna 7
    tablero.colocarPieza(new Giuseppe(0, 7), 0, 7);
    tablero.colocarPieza(new Imanol(1, 7), 1, 7);
    tablero.colocarPieza(new Imanol(2, 7), 2, 7);
    tablero.colocarPieza(new Imanol(3, 7), 3, 7);
    tablero.colocarPieza(new Imanol(4, 7), 4, 7);
    tablero.colocarPieza(new Imanol(5, 7), 5, 7);
    tablero.colocarPieza(new Imanol(6, 7), 6, 7);
    tablero.colocarPieza(new Imanol(7, 7), 7, 7);
    tablero.colocarPieza(new Giuseppe(8, 7), 8, 7);
}
// DIBUJAR - decide que pantalla mostrar segun el estado igual que el Coordinador del Pang gestionaba el dibujo

void Juego::dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    switch (estadoActual) {
    case EstadoJuego::MENU:
        menu.dibujar();
        break;
    case EstadoJuego::TABLERO:
        tablero.dibujar(turnoActual);
        break;
    case EstadoJuego::BATALLA:
        batalla.dibujar(); 
        break;
    case EstadoJuego::RANKING:
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-5.0, 5.0, -5.0, 5.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        ranking.dibujar();
        glEnable(GL_DEPTH_TEST);
        break;
    case EstadoJuego::FIN_PARTIDA:
		dibujarPantallaFin();
		break;
	case EstadoJuego::PAUSA_TABLERO:
		tablero.dibujar(turnoActual);
        glColor3f(1.0f, 0.0f, 0.0f);
        dibujarTexto(-1.5, 0.25f, 0.11f, "Partida en pausa");
        dibujarTexto(-1.5, -0.25f, 0.11f, "Pulsa -C- para continuar");
		break;
	case EstadoJuego::PAUSA_BATALLA:
		batalla.dibujar();
        glColor3f(1.0f, 0.0f, 0.0f);
        dibujarTexto(-1.5, 0.25f, 0.11f, "Batalla en pausa");
        dibujarTexto(-1.5, -0.25f, 0.11f, "Pulsa -C- para continuar");
		break;
    }
    glutSwapBuffers();
}

// CAMBIAR TURNO
void Juego::cambiarTurno() {
    if (turnoActual == Bando::LUZ) {
        turnoActual = Bando::OSCURIDAD;
        tablero.setFilaTeclado(4);
		tablero.setColTeclado(8);
    } else {
        turnoActual = Bando::LUZ;
        tablero.setFilaTeclado(4);
        tablero.setColTeclado(0);
    }
    tablero.cambiarColorOscilantes();
    turnosJugados++;
    comprobarVictoria();
    // Si ahora toca OSCURIDAD, activar la IA
    if (turnoActual == Bando::OSCURIDAD && modoJuego == ModoJuego::JvsIA) {
        turnoIA = true;
        timerIA = 1.2f;
        faseIA = 0;
    }
}

// ACTUALIZAR - igual que Mundo::mueve en el Pang
void Juego::actualizar(float dt) {
    if (estadoActual == EstadoJuego::TABLERO) {
        tablero.actualizar(dt);

        if (turnoIA) {
            timerIA -= dt;

            if (faseIA == 0 && timerIA <= 0.0f) {
                if (tablero.calcularMovimientoIA(filaOrigenIA, colOrigenIA, filaDestIA, colDestIA)) {
                    // Naranja en origen, morado en destino
                    tablero.setFilaTeclado(filaOrigenIA);
                    tablero.setColTeclado(colOrigenIA);
                    tablero.setDestinoIA(filaDestIA, colDestIA);
                    faseIA = 1;
                    timerIA = 1.5f;
                }
                else {
                    turnoIA = false;
                    faseIA = 0;
                    cambiarTurno();
                }
                glutPostRedisplay();
            }
            else if (faseIA == 1 && timerIA <= 0.0f) {
                // Ejecutar - quitar morado y mover
                turnoIA = false;
                faseIA = 0;
                tablero.ocultarDestinoIA();

                if (tablero.hayEnemigo(filaDestIA, colDestIA, Bando::OSCURIDAD)) {
                    filaAtacanteBatalla = filaOrigenIA;
                    colAtacanteBatalla = colOrigenIA;
                    filaDestinoBatalla = filaDestIA;
                    colDestinoBatalla = colDestIA;
                    Pieza* profesor = tablero.getPieza(filaOrigenIA, colOrigenIA);
                    Pieza* alumno = tablero.getPieza(filaDestIA, colDestIA);
                    estadoActual = EstadoJuego::BATALLA;
                    batalla.iniciar(alumno, profesor);
                }
                else {
                    tablero.moverPieza(filaOrigenIA, colOrigenIA, filaDestIA, colDestIA);
                    cambiarTurno();
                }
                glutPostRedisplay();
            }
        }

    }
    else if (estadoActual == EstadoJuego::BATALLA) {
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
    if (estadoActual == EstadoJuego::FIN_PARTIDA) return;
    float glX, glY;
    convertirCoordenadas(x, y, glX, glY);
    if (estadoActual == EstadoJuego::MENU) {
        menu.gestionRaton(boton, estado, glX, glY);
        if (menu.haSeleccionado) {
            if (menu.getOpcionSeleccionada() == OpcionMenu::JUGAR) {
                modoJuego = menu.getModo();
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
                if (turnoActual == Bando::LUZ) {
                    Pieza* alumno = tablero.getPieza(tablero.getFilaSeleccionada(),
                                                     tablero.getColSeleccionada());
                    Pieza* profesor = tablero.getPieza(fila, col);
                    iniciarBatalla(alumno, profesor);
                } else {
                    Pieza* profesor = tablero.getPieza(tablero.getFilaSeleccionada(),
                        tablero.getColSeleccionada());
                    Pieza* alumno = tablero.getPieza(fila, col);
                    iniciarBatalla(alumno, profesor);
                }
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
    if (estadoActual == EstadoJuego::FIN_PARTIDA) {
        if (tecla == 13) {
            //juegoTerminado = false;
            ETSIDI::play("sonidos/menu.wav");
            estadoActual   = EstadoJuego::MENU;
            glutPostRedisplay();
        }
        return;
    }

    if (tecla == 27) { // ESC
        if (estadoActual == EstadoJuego::BATALLA  ||
            estadoActual == EstadoJuego::RANKING) {
            estadoActual = EstadoJuego::MENU;
            menu.haSeleccionado = false;
            glutPostRedisplay();
            return;
        }
        else if(estadoActual == EstadoJuego::TABLERO) {
            if (tablero.tieneSeleccion()) {
				tablero.deseleccionar();
            }
            else {
                estadoActual = EstadoJuego::MENU;
                menu.haSeleccionado = false;
                glutPostRedisplay();
                return;  
            }
        }
        else {
            menu.gestionTeclado(tecla); // deja que el menu gestione el ESC
            glutPostRedisplay();
            return;
        }
    }

	if (estadoActual == EstadoJuego::TABLERO && tecla == 'p') {
		estadoActual = EstadoJuego::PAUSA_TABLERO;
		glutPostRedisplay();
		return;
	} 

    if (estadoActual == EstadoJuego::BATALLA && tecla == 'p') {
        estadoActual = EstadoJuego::PAUSA_BATALLA;
        glutPostRedisplay();
        return;
    }

    if (estadoActual == EstadoJuego::PAUSA_TABLERO && tecla == 'c') {
        estadoActual = EstadoJuego::TABLERO;
        glutPostRedisplay();
        return;
    }

    if(estadoActual == EstadoJuego::PAUSA_BATALLA && tecla == 'c') {
        estadoActual = EstadoJuego::BATALLA;
        glutPostRedisplay();
        return;
    }

    if (estadoActual == EstadoJuego::MENU) {
        menu.gestionTeclado(tecla);
        if (menu.haSeleccionado) {
            if (menu.getOpcionSeleccionada() == OpcionMenu::JUGAR) {
                modoJuego = menu.getModo();
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

    if (estadoActual == EstadoJuego::TABLERO) {
		tablero.gestionTeclado(tecla, turnoActual);
        if (tecla == 13) { // Enter
            if (!tablero.tieneSeleccion()) {
                tablero.seleccionarPieza(tablero.getFilaTeclado(), tablero.getColTeclado(), turnoActual);
            }
            else {
                if (tablero.destinoEsValido(tablero.getFilaTeclado(), tablero.getColTeclado())) {
                    if (tablero.hayEnemigo(tablero.getFilaTeclado(), tablero.getColTeclado(), turnoActual)) {
                        if (turnoActual == Bando::LUZ) {
                            Pieza* alumno = tablero.getPieza(tablero.getFilaSeleccionada(),
                                                             tablero.getColSeleccionada());
                            Pieza* profesor = tablero.getPieza(tablero.getFilaTeclado(), tablero.getColTeclado());
                            iniciarBatalla(alumno, profesor);
                        }
                        else {
                            Pieza* profesor = tablero.getPieza(tablero.getFilaSeleccionada(),
                                                               tablero.getColSeleccionada());
                            Pieza* alumno = tablero.getPieza(tablero.getFilaTeclado(), tablero.getColTeclado());
                            iniciarBatalla(alumno, profesor);
                        }   
                    }
                    else {
                        tablero.moverPiezaSeleccionada(tablero.getFilaTeclado(), tablero.getColTeclado());
                        cambiarTurno();
                    }
                }
                tablero.deseleccionar();
            }
            glutPostRedisplay();
        }

    }
}

void Juego::gestionTecladoSuelto(unsigned char tecla, int x, int y) {
    if (estadoActual == EstadoJuego::BATALLA) {
        //batalla.gestionTecladoSuelto(tecla);
    }
}

// INICIAR BATALLA
void Juego::iniciarBatalla(Pieza* alumno, Pieza* profesor) {
    // guardar posicion del atacante aqui - despues getFilaSeleccionada() vale -1
    filaAtacanteBatalla = tablero.getFilaSeleccionada();
    colAtacanteBatalla = tablero.getColSeleccionada();
    estadoActual = EstadoJuego::BATALLA;
    batalla.iniciar(alumno, profesor);
    batalla.setJvsJ(modoJuego == ModoJuego::JvsJ);
}

// TERMINAR BATALLA
// Segun quien gano, el tablero elimina al perdedor(igual que en el Pang el coordinador eliminaba la esfera cuando chocaba)
void Juego::terminarBatalla() {
    estadoActual = EstadoJuego::TABLERO;

    // usamos las coordenadas guardadas en iniciarBatalla, NO getFilaSeleccionada()
    int filaAtacante = filaAtacanteBatalla;
    int colAtacante = colAtacanteBatalla;

    if (batalla.getEstado() == EstadoBatalla::GANA_ALUMNO) {
        // el profesor muere, el alumno se queda en la casilla disputada
        if (turnoActual == Bando::LUZ) {
            tablero.eliminarPieza(filaDestinoBatalla, colDestinoBatalla);
            tablero.moverPieza(filaAtacante, colAtacante,
                  filaDestinoBatalla, colDestinoBatalla);
        }
        else {
            tablero.eliminarPieza(filaAtacante, colAtacante);
        }
        
    }
    else if (batalla.getEstado() == EstadoBatalla::GANA_PROFESOR) {
        if (turnoActual == Bando::OSCURIDAD) {
            tablero.eliminarPieza(filaDestinoBatalla, colDestinoBatalla);
            tablero.moverPieza(filaAtacante, colAtacante,
                  filaDestinoBatalla, colDestinoBatalla);
        }
        else {
            tablero.eliminarPieza(filaAtacante, colAtacante);
        }
    }
    else if (batalla.getEstado() == EstadoBatalla::EMPATE) {
        tablero.eliminarPieza(filaDestinoBatalla, colDestinoBatalla);
        tablero.eliminarPieza(filaAtacante, colAtacante);
    }
    tablero.deseleccionar();
    cambiarTurno();
}
// COMPROBAR VICTORIA - las dos condiciones del ARCHON 
void Juego::comprobarVictoria() {
    if (tablero.controlaPuntosDePoder(Bando::LUZ)) {
        estadoActual = EstadoJuego::FIN_PARTIDA;
        ganador        = Bando::LUZ;
        ETSIDI::play("sonidos/victoria.wav");
        ranking.guardarResultado("EE309", turnosJugados);
        return;
    }
    if (tablero.controlaPuntosDePoder(Bando::OSCURIDAD)) {
        estadoActual = EstadoJuego::FIN_PARTIDA;
        ganador        = Bando::OSCURIDAD;
        ETSIDI::play("sonidos/derrota.wav");
        ranking.guardarResultado("Automatica", turnosJugados);
        return;
    }
    if (tablero.contarPiezas(Bando::LUZ) == 0) {
        estadoActual = EstadoJuego::FIN_PARTIDA;
        ganador        = Bando::OSCURIDAD;
        ETSIDI::play("sonidos/derrota.wav");
        ranking.guardarResultado("Automatica", turnosJugados);
        return;
    }
    if (tablero.contarPiezas(Bando::OSCURIDAD) == 0) {
        estadoActual = EstadoJuego::FIN_PARTIDA;
        ganador        = Bando::LUZ;
        ETSIDI::play("sonidos/victoria.wav");
        ranking.guardarResultado("EE309", turnosJugados);
        return;
    }
}

// PANTALLA DE FIN
void Juego::dibujarPantallaFin() {
    glColor3f(0.05f, 0.05f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(-5.0f, -5.0f, 0.1f);
    glVertex3f( 5.0f, -5.0f, 0.1f);
    glVertex3f( 5.0f,  5.0f, 0.1f);
    glVertex3f(-5.0f,  5.0f, 0.1f);
    glEnd();

    if (ganador == Bando::LUZ) {
        glColor3f(1.0f, 0.85f, 0.0f);
        dibujarTexto(-2.5, 1.5f,0.11f, "GANAN LOS ALUMNOS EE309!");
        dibujarTexto(-2.0, 0.5f,0.11f, "Los profes suspenden en el tablero");
    } else {
        glColor3f(0.5f, 0.0f, 0.8f);
        dibujarTexto(-2.5, 1.5f,0.11f, "GANA EL DEPARTAMENTO!");
        dibujarTexto(-2.0, 0.5f,0.11f, "Te vas a julio amigo...");
    }

    glColor3f(0.7f, 0.7f, 0.7f);
    std::string textoTurnos = std::to_string(turnosJugados) + " turnos jugados";
    dibujarTexto(-1.5f, -0.5f,0.11f, textoTurnos);

    glColor3f(0.5f, 0.5f, 0.5f);
    dibujarTexto(-2.5f, -2.0f,0.11f, "Pulsa ENTER para volver al menu");
}

void Juego::dibujarTexto(float x, float y, float z, std::string texto) {
    glRasterPos3f(x, y, z);
    for (int i = 0; i < (int)texto.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
    }
}
