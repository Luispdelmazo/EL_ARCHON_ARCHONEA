#include "Ranking.h"
#include <GL/glut.h>

Ranking::Ranking() {
    nombreFichero = "ranking.txt";
    cargarResultados();
}

// Guarda un resultado al final de cada partida
void Ranking::guardarResultado(std::string ganador, int turnosJugados) {
    Resultado r;
    r.ganador = ganador;
    r.turnosJugados = turnosJugados;
    resultados.push_back(r);

    std::ofstream fichero(nombreFichero, std::ios::app);
    if (fichero.is_open()) {
        fichero << ganador << " " << turnosJugados << "\n";
        fichero.close();
    }
}

// Carga los resultados del fichero al arrancar
void Ranking::cargarResultados() {
    resultados.clear();

    std::ifstream fichero(nombreFichero);
    if (fichero.is_open()) {
        std::string ganador;
        int turnos;
        while (fichero >> ganador >> turnos) {
            Resultado r;
            r.ganador = ganador;
            r.turnosJugados = turnos;
            resultados.push_back(r);
        }
        fichero.close();
    }
}

// Convierte coordenadas de mundo (-5 a 5) a pixels de ventana
void Ranking::dibujarTexto(float x, float y, std::string texto, void* fuente) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glRasterPos2f(x, y);
    for (int i = 0; i < (int)texto.size(); i++) {
        glutBitmapCharacter(fuente, texto[i]);
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

// Dibuja el ranking en pantalla
void Ranking::dibujar() {
    // Fondo oscuro
    glColor3f(0.05f, 0.05f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(-5.0f, -5.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, 0.0f);
    glVertex3f(5.0f, 5.0f, 0.0f);
    glVertex3f(-5.0f, 5.0f, 0.0f);
    glEnd();

    // Linea separadora
    glColor3f(0.5f, 0.0f, 0.8f);
    glBegin(GL_LINES);
    glVertex3f(-3.0f, 3.5f, 0.0f);
    glVertex3f(3.0f, 3.5f, 0.0f);
    glEnd();

    // Titulo
    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-1.0f, 4.0f, "RANKING", GLUT_BITMAP_HELVETICA_18);

    // Si no hay resultados mostrar mensaje
    if (resultados.empty()) {
        glColor3f(0.8f, 0.8f, 0.8f);
        dibujarTexto(-2.5f, 0.0f, "No hay partidas guardadas aun",
            GLUT_BITMAP_HELVETICA_18);
    }
    else {
        // Mostrar los ultimos 8 resultados
        int inicio = 0;
        if ((int)resultados.size() > 8) {
            inicio = (int)resultados.size() - 8;
        }

        for (int i = inicio; i < (int)resultados.size(); i++) {
            float y = 3.0f - (i - inicio) * 0.7f;

            if (resultados[i].ganador == "EE309") {
                glColor3f(1.0f, 0.85f, 0.0f); // Amarillo
            }
            else {
                glColor3f(0.5f, 0.0f, 0.8f);  // Morado
            }

            std::string linea = resultados[i].ganador + " - " +
                std::to_string(resultados[i].turnosJugados) +
                " turnos";
            dibujarTexto(-2.0f, y, linea, GLUT_BITMAP_HELVETICA_12);
        }
    }

    // Instruccion salir
    glColor3f(0.5f, 0.5f, 0.5f);
    dibujarTexto(-2.5f, -4.5f, "Pulsa ESC para volver al menu",
        GLUT_BITMAP_HELVETICA_12);
}