#include "Menu.h"

Menu::Menu() {
    opcionSeleccionada     = OpcionMenu::JUGAR;
    dificultadSeleccionada = DificultadIA::MEDIO;
    estadoMenu             = EstadoMenu::PRINCIPAL;
    haSeleccionado         = false;
}
/*
void Menu::dibujarTexto(float x, float y, std::string texto) {
    glRasterPos2f(x, y);
    for (int i = 0; i < (int)texto.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
    }
}*/
void Menu::dibujarTexto(float x, float y, float z, std::string texto) {
    glRasterPos3f(x, y, z);
    for (int i = 0; i < (int)texto.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
    }
}

void Menu::dibujar() {
    if (estadoMenu == EstadoMenu::PRINCIPAL) {
        dibujarMenuPrincipal();
    } else if (estadoMenu == EstadoMenu::NIVEL) {
        dibujarSeleccionNivel();
    }
    else if (estadoMenu == EstadoMenu::INSTRUCCIONES) {
        dibujarInstrucciones();
    }
}

void Menu::dibujarMenuPrincipal() {
    // Fondo oscuro - plantilla pang
    glColor3f(0.05f, 0.05f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(-5.0f, -5.0f, -0.1f);
    glVertex3f( 5.0f, -5.0f, -0.1f);
    glVertex3f( 5.0f,  5.0f, -0.1f);
    glVertex3f(-5.0f,  5.0f, -0.1f);
    glEnd();

    // Titulo
    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-1.5f, 3.0f, 0.1f,"PACHON");

    glColor3f(0.8f, 0.8f, 0.8f);
    dibujarTexto(-2.0f, 2.2f, 0.1f, "EE309 vs Automatica UPM");

    // Linea separadora
    glColor3f(0.5f, 0.0f, 0.8f);
    glBegin(GL_LINES);
    glVertex3f(-3.0f, 1.8f, 0.0f);
    glVertex3f( 3.0f, 1.8f, 0.0f);
    glEnd();

    // JUGAR
    if (opcionSeleccionada == OpcionMenu::JUGAR) {
        glColor3f(1.0f, 0.85f, 0.0f);
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    dibujarTexto(-0.5f, 1.0f, 0.1f, "JUGAR");

    // RANKING
    if (opcionSeleccionada == OpcionMenu::RANKING) {
        glColor3f(1.0f, 0.85f, 0.0f);
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    dibujarTexto(-0.7f, 0.0f, 0.1f, "RANKING");

    // INSTRUCCIONES
    if (opcionSeleccionada == OpcionMenu::INSTRUCCIONES) {
        glColor3f(1.0f, 0.85f, 0.0f);
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    dibujarTexto(-1.2f, -1.0f, 0.1f ,"INSTRUCCIONES");

    // SALIR
    if (opcionSeleccionada == OpcionMenu::SALIR) {
        glColor3f(1.0f, 0.85f, 0.0f);
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    dibujarTexto(-0.5f, -2.0f, 0.1f, "SALIR");

    glColor3f(0.5f, 0.5f, 0.5f);
    dibujarTexto(-3.5f, -4.5f, 0.1f, "Haz clic en una opcion o usa ENTER");
}

/* d Menu::dibujarSeleccionNivel() {
    glColor3f(0.05f, 0.05f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(-5.0f, -5.0f, 0.0f);
    glVertex3f( 5.0f, -5.0f, 0.0f);
    glVertex3f( 5.0f,  5.0f, 0.0f);
    glVertex3f(-5.0f,  5.0f, 0.0f);
    //glEnd();

    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-2.0f, 3.0f, "SELECCIONA NIVEL");

    glColor3f(0.5f, 0.0f, 0.8f);
    glBegin(GL_LINES);
    glVertex3f(-3.0f, 2.5f, 0.0f);
    glVertex3f( 3.0f, 2.5f, 0.0f);
    glEnd();

    // FACIL
    if (dificultadSeleccionada == DificultadIA::FACIL) {
        glColor3f(0.0f, 1.0f, 0.0f);
    } else {
        glColor3f(0.6f, 0.6f, 0.6f);
    }
    dibujarTexto(-0.5f, 1.2f, "FACIL");
    glColor3f(0.4f, 0.4f, 0.4f);
    dibujarTexto(-2.5f, 0.6f, "La IA se mueve lento y ataca poco");

    // MEDIO
    if (dificultadSeleccionada == DificultadIA::MEDIO) {
        glColor3f(1.0f, 0.85f, 0.0f);
    } else {
        glColor3f(0.6f, 0.6f, 0.6f);
    }
    dibujarTexto(-0.5f, -0.2f, "MEDIO");
    glColor3f(0.4f, 0.4f, 0.4f);
    dibujarTexto(-2.5f, -0.8f, "Comportamiento equilibrado");

    // DIFICIL
    if (dificultadSeleccionada == DificultadIA::DIFICIL) {
        glColor3f(1.0f, 0.2f, 0.2f);
    } else {
        glColor3f(0.6f, 0.6f, 0.6f);
    }
    dibujarTexto(-0.7f, -1.6f, "DIFICIL");
    glColor3f(0.4f, 0.4f, 0.4f);
    dibujarTexto(-2.5f, -2.2f, "La IA es rapida y muy agresiva");

    glColor3f(0.5f, 0.5f, 0.5f);
    dibujarTexto(-3.5f, -3.5f, "Haz clic o usa 1 2 3 para elegir");
    dibujarTexto(-3.5f, -4.2f, "ENTER para confirmar - ESC para volver");
    glEnd();
}*/
void Menu::dibujarSeleccionNivel() {
    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.05f, 0.1f);
    glVertex3f(-5.0f, -5.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, 0.0f);
    glVertex3f(5.0f, 5.0f, 0.0f);
    glVertex3f(-5.0f, 5.0f, 0.0f);
    glEnd();

    dibujarTexto(-2.0f, 3.0f, 0.1f, "SELECCIONA NIVEL");

    glColor3f(0.0f, 1.0f, 0.0f);
    dibujarTexto(-0.7f, 1.2f, 0.1f, "1 - FACIL");
    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-0.7f, 0.0f, 0.1f, "2 - MEDIO");
    glColor3f(1.0f, 0.2f, 0.2f);
    dibujarTexto(-0.7f, -1.2f, 0.1f, "3 - DIFICIL");
    glColor3f(0.5f, 0.5f, 0.5f);
    dibujarTexto(-3.5f, -4.2f, 0.1f, "ENTER confirma - ESC vuelve");
}

void Menu::dibujarInstrucciones() {
    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.05f, 0.1f);
    glVertex3f(-5.0f, -5.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, 0.0f);
    glVertex3f(5.0f, 5.0f, 0.0f);
    glVertex3f(-5.0f, 5.0f, 0.0f);
    glEnd();

    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-1.5f, 4.0f, 0.1f, "INSTRUCCIONES");
    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-4.0f, 2.8f, 0.1f, "TABLERO:");
    glColor3f(0.8f, 0.8f, 0.8f);
    dibujarTexto(-4.0f, 2.2f, 0.1f, "Click izquierdo - seleccionar pieza");
    dibujarTexto(-4.0f, 1.6f, 0.1f, "Click en circulo verde - mover pieza");
    dibujarTexto(-4.0f, 1.0f, 0.1f, "ESC - volver al menu");
    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-4.0f, 0.2f, 0.1f, "BATALLA:");
    glColor3f(0.8f, 0.8f, 0.8f);
    dibujarTexto(-4.0f, -0.4f, 0.1f, "WASD - mover tu pieza");
    dibujarTexto(-4.0f, -1.0f, 0.1f, "F - atacar cuando el circulo este verde");
    dibujarTexto(-4.0f, -1.6f, 0.1f, "ESC - volver al menu");
    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-4.0f, -2.4f, 0.1f, "OBJETIVO:");
    glColor3f(0.8f, 0.8f, 0.8f);
    dibujarTexto(-4.0f, -3.0f, 0.1f, "Controla los 5 puntos de poder");
    dibujarTexto(-4.0f, -3.6f, 0.1f, "o elimina todas las piezas rivales");
    glColor3f(0.5f, 0.5f, 0.5f);
    dibujarTexto(-2.0f, -4.5f, 0.1f, "ESC para volver al menu");
}

/*                                      
    glColor3f(0.05f, 0.05f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(-5.0f, -5.0f, 0.0f);
    glVertex3f( 5.0f, -5.0f, 0.0f);
    glVertex3f( 5.0f,  5.0f, 0.0f);
    glVertex3f(-5.0f,  5.0f, 0.0f);
    //glEnd();

    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-1.5f, 4.0f, "INSTRUCCIONES");

    glColor3f(0.5f, 0.0f, 0.8f);
    glBegin(GL_LINES);
    glVertex3f(-4.0f, 3.5f, 0.0f);
    glVertex3f( 4.0f, 3.5f, 0.0f);
    glEnd();

    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-4.0f, 2.8f, "TABLERO:");
    glColor3f(0.8f, 0.8f, 0.8f);
    dibujarTexto(-4.0f, 2.2f, "Click izquierdo - seleccionar pieza");
    dibujarTexto(-4.0f, 1.6f, "Click en circulo verde - mover pieza");
    dibujarTexto(-4.0f, 1.0f, "ESC - volver al menu");

    glColor3f(0.5f, 0.0f, 0.8f);
    glBegin(GL_LINES);
    glVertex3f(-4.0f, 0.6f, 0.0f);
    glVertex3f( 4.0f, 0.6f, 0.0f);
    glEnd();

    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-4.0f, 0.0f, "BATALLA:");
    glColor3f(0.8f, 0.8f, 0.8f);
    dibujarTexto(-4.0f, -0.6f, "WASD - mover tu pieza");
    dibujarTexto(-4.0f, -1.2f, "F - atacar cuando el circulo este verde");
    dibujarTexto(-4.0f, -1.8f, "ESC - volver al menu");

    glColor3f(0.5f, 0.0f, 0.8f);
    glBegin(GL_LINES);
    glVertex3f(-4.0f, -2.3f, 0.0f);
    glVertex3f( 4.0f, -2.3f, 0.0f);
    glEnd();

    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-4.0f, -2.9f, "OBJETIVO:");
    glColor3f(0.8f, 0.8f, 0.8f);
    dibujarTexto(-4.0f, -3.5f, "Controla los 5 puntos de poder");
    dibujarTexto(-4.0f, -4.1f, "o elimina todas las piezas rivales");

    glColor3f(0.5f, 0.5f, 0.5f);
    dibujarTexto(-2.0f, -4.7f, "ESC para volver al menu");
    glEnd();
} 
void Menu::dibujarInstrucciones() {
    // Fondo oscuro
    glColor3f(0.05f, 0.05f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(-5.0f, -5.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, 0.0f);
    glVertex3f(5.0f, 5.0f, 0.0f);
    glVertex3f(-5.0f, 5.0f, 0.0f);
    glEnd(); // <- aqui va el glEnd del fondo

    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-1.5f, 4.0f, "INSTRUCCIONES");

    glColor3f(0.5f, 0.0f, 0.8f);
    glBegin(GL_LINES);
    glVertex3f(-4.0f, 3.5f, 0.0f);
    glVertex3f(4.0f, 3.5f, 0.0f);
    glEnd();

    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-4.0f, 2.8f, "TABLERO:");
    glColor3f(0.8f, 0.8f, 0.8f);
    dibujarTexto(-4.0f, 2.2f, "Click izquierdo - seleccionar pieza");
    dibujarTexto(-4.0f, 1.6f, "Click en circulo verde - mover pieza");
    dibujarTexto(-4.0f, 1.0f, "ESC - volver al menu");

    glColor3f(0.5f, 0.0f, 0.8f);
    glBegin(GL_LINES);
    glVertex3f(-4.0f, 0.6f, 0.0f);
    glVertex3f(4.0f, 0.6f, 0.0f);
    glEnd();

    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-4.0f, 0.0f, "BATALLA:");
    glColor3f(0.8f, 0.8f, 0.8f);
    dibujarTexto(-4.0f, -0.6f, "WASD - mover tu pieza");
    dibujarTexto(-4.0f, -1.2f, "F - atacar cuando el circulo este verde");
    dibujarTexto(-4.0f, -1.8f, "ESC - volver al menu");

    glColor3f(0.5f, 0.0f, 0.8f);
    glBegin(GL_LINES);
    glVertex3f(-4.0f, -2.3f, 0.0f);
    glVertex3f(4.0f, -2.3f, 0.0f);
    glEnd();

    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-4.0f, -2.9f, "OBJETIVO:");
    glColor3f(0.8f, 0.8f, 0.8f);
    dibujarTexto(-4.0f, -3.5f, "Controla los 5 puntos de poder");
    dibujarTexto(-4.0f, -4.1f, "o elimina todas las piezas rivales");

    glColor3f(0.5f, 0.5f, 0.5f);
    dibujarTexto(-2.0f, -4.7f, "ESC para volver al menu");
    // sin glEnd() aqui - no hay ningún glBegin abierto
} */

void Menu::gestionRaton(int boton, int estado, float glX, float glY) {
    if (boton != GLUT_LEFT_BUTTON || estado != GLUT_UP) return;

    if (estadoMenu == EstadoMenu::PRINCIPAL) {
        if (glX > -2.0f && glX < 2.0f) {
            if (glY > 0.5f && glY < 1.5f) {
                opcionSeleccionada = OpcionMenu::JUGAR;
                estadoMenu         = EstadoMenu::NIVEL;
            } else if (glY > -0.5f && glY < 0.5f) {
                opcionSeleccionada = OpcionMenu::RANKING;
                haSeleccionado     = true;
            } else if (glY > -1.5f && glY < -0.5f) {
                opcionSeleccionada = OpcionMenu::INSTRUCCIONES;
                estadoMenu         = EstadoMenu::INSTRUCCIONES;
            } else if (glY > -2.5f && glY < -1.5f) {
                opcionSeleccionada = OpcionMenu::SALIR;
                haSeleccionado     = true;
            }
        }
    } else if (estadoMenu == EstadoMenu::NIVEL) {
        if (glY > 0.8f && glY < 1.6f) {
            dificultadSeleccionada = DificultadIA::FACIL;
        } else if (glY > -0.6f && glY < 0.2f) {
            dificultadSeleccionada = DificultadIA::MEDIO;
        } else if (glY > -2.0f && glY < -1.2f) {
            dificultadSeleccionada = DificultadIA::DIFICIL;
        }
    }
}

void Menu::gestionTeclado(unsigned char tecla) {
    if (estadoMenu == EstadoMenu::INSTRUCCIONES) {
        if (tecla == 27) {
            estadoMenu = EstadoMenu::PRINCIPAL;
        }
        return;
    }

    if (estadoMenu == EstadoMenu::NIVEL) {
        if (tecla == '1') dificultadSeleccionada = DificultadIA::FACIL;
        if (tecla == '2') dificultadSeleccionada = DificultadIA::MEDIO;
        if (tecla == '3') dificultadSeleccionada = DificultadIA::DIFICIL;
        if (tecla == 13)  haSeleccionado = true;
        if (tecla == 27)  estadoMenu = EstadoMenu::PRINCIPAL;
        return;
    }

    // Menu principal
    if (tecla == 13) {
        if (opcionSeleccionada == OpcionMenu::JUGAR) {
            estadoMenu = EstadoMenu::NIVEL;
        } else if (opcionSeleccionada == OpcionMenu::INSTRUCCIONES) {
            estadoMenu = EstadoMenu::INSTRUCCIONES;
        } else {
            haSeleccionado = true;
        }
    }
    if (tecla == 27) {
        exit(0);
    }

    if (estadoMenu == EstadoMenu::PRINCIPAL) {
        if (tecla == 'w') {
			if (opcionSeleccionada == OpcionMenu::JUGAR) {
				opcionSeleccionada = OpcionMenu::SALIR;
			}
			else if (opcionSeleccionada == OpcionMenu::RANKING) {
				opcionSeleccionada = OpcionMenu::JUGAR;
			}
			else if (opcionSeleccionada == OpcionMenu::INSTRUCCIONES) {
				opcionSeleccionada = OpcionMenu::RANKING;
			}
			else if (opcionSeleccionada == OpcionMenu::SALIR) {
				opcionSeleccionada = OpcionMenu::INSTRUCCIONES;
			}
        }
		if (tecla == 's') {
			if (opcionSeleccionada == OpcionMenu::JUGAR) {
				opcionSeleccionada = OpcionMenu::RANKING;
			}
			else if (opcionSeleccionada == OpcionMenu::RANKING) {
				opcionSeleccionada = OpcionMenu::INSTRUCCIONES;
			}
			else if (opcionSeleccionada == OpcionMenu::INSTRUCCIONES) {
				opcionSeleccionada = OpcionMenu::SALIR;
			}
			else if (opcionSeleccionada == OpcionMenu::SALIR) {
				opcionSeleccionada = OpcionMenu::JUGAR;
			}
		}
    }
}

OpcionMenu Menu::getOpcionSeleccionada() const {
    return opcionSeleccionada;
}
