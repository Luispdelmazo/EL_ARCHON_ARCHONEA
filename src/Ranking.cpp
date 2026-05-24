#include "Ranking.h"
#include <GL/glut.h>

Ranking::Ranking() {
    nombreFichero = "ranking.txt";
    cargarResultados();
}

// Guarda un resultado al final de cada partida
void Ranking::guardarResultado(std::string ganador, int turnosJugados) {
    // Añadir al vector
    Resultado r;
    r.ganador = ganador;
    r.turnosJugados = turnosJugados;
    resultados.push_back(r);

    // Guardar en fichero - app añade al final sin borrar lo anterior
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

    // Titulo
    glColor3f(1.0f, 0.85f, 0.0f);
    glRasterPos2f(-1.0f, 4.0f);
    std::string titulo = "RANKING";
    for (int i = 0; i < titulo.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, titulo[i]);
    }

    // Mostrar los ultimos 8 resultados
    int inicio = 0;
    if (resultados.size() > 8) {
        inicio = resultados.size() - 8;
    }

    for (int i = inicio; i < (int)resultados.size(); i++) {
        float y = 3.0f - (i - inicio) * 0.7f;

        // Color segun quien gano
        if (resultados[i].ganador == "LUZ") {
            glColor3f(1.0f, 0.85f, 0.0f); // Amarillo
        }
        else {
            glColor3f(0.5f, 0.0f, 0.8f);  // Morado
        }

        // Dibujar linea del resultado
        std::string linea = resultados[i].ganador + " - " +
            std::to_string(resultados[i].turnosJugados) + " turnos";
        glRasterPos2f(-2.0f, y);
        for (int j = 0; j < linea.size(); j++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, linea[j]);
        }
    }

    // Instruccion salir
    glColor3f(0.5f, 0.5f, 0.5f);
    glRasterPos2f(-2.0f, -4.0f);
    std::string msg = "Pulsa ESC para volver al menu";
    for (int i = 0; i < msg.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, msg[i]);
    }
}