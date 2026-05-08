#define USE_ETSIDI
#include "lib/ETSIDI.h"
#include "lib/GL/glut.h"
#include "src/Alumnos.h"
#include "src/Profesores.h"

using namespace ETSIDI;

const int TAM_CASILLA = 60;
const int FILAS = 9;
const int COLS = 9;
const int MARGEN = 50;

Alumnos alumnos;
Profesores profesores;

int tiempoOscilacion = 0;
bool faseClaraOscura = true;

bool casillaOscila[FILAS][COLS] = {
    {0,0,0,1,1,1,0,0,0},
    {0,0,1,0,1,0,1,0,0},
    {0,1,0,0,1,0,0,1,0},
    {1,0,0,0,1,0,0,0,1},
    {0,1,1,1,1,1,1,1,0},
    {1,0,0,0,1,0,0,0,1},
    {0,1,0,0,1,0,0,1,0},
    {0,0,1,0,1,0,1,0,0},
    {0,0,0,1,1,1,0,0,0}
};

bool esPuntoPoder(int fila, int col) {
    if (fila == 4 && col == 4) return true;
    if (fila == 0 && col == 4) return true;
    if (fila == 8 && col == 4) return true;
    if (fila == 4 && col == 0) return true;
    if (fila == 4 && col == 8) return true;
    return false;
}

void dibujarCruz(float x, float y, float z) {
    glColor3f(1.0f, 0.8f, 0.0f);
    float cx = x + TAM_CASILLA / 2;
    float cy = y + TAM_CASILLA / 2;
    float tam = 15.0f;
    float grosor = 4.0f;

    // Barra horizontal
    glBegin(GL_QUADS);
    glVertex3f(cx - tam, cy - grosor, z);
    glVertex3f(cx + tam, cy - grosor, z);
    glVertex3f(cx + tam, cy + grosor, z);
    glVertex3f(cx - tam, cy + grosor, z);
    glEnd();

    // Barra vertical
    glBegin(GL_QUADS);
    glVertex3f(cx - grosor, cy - tam, z);
    glVertex3f(cx + grosor, cy - tam, z);
    glVertex3f(cx + grosor, cy + tam, z);
    glVertex3f(cx - grosor, cy + tam, z);
    glEnd();
}

void dibujarTablero() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLS; j++) {
            float x = MARGEN + j * TAM_CASILLA;
            float y = MARGEN + i * TAM_CASILLA;
            float z = 0.0f;

            bool esCasillaClara = (i + j) % 2 == 0;
            if (j > 4) esCasillaClara = !esCasillaClara;

            if (casillaOscila[i][j]) {
                if (faseClaraOscura) {
                    glColor3f(0.5f, 0.5f, 1.0f);
                }
                else {
                    glColor3f(0.1f, 0.1f, 0.5f);
                }
            }
            else {
                if (esCasillaClara)
                    glColor3f(1.0f, 1.0f, 1.0f);
                else
                    glColor3f(0.0f, 0.0f, 0.0f);
            }

            glBegin(GL_QUADS);
            glVertex3f(x, y, z);
            glVertex3f(x + TAM_CASILLA, y, z);
            glVertex3f(x + TAM_CASILLA, y + TAM_CASILLA, z);
            glVertex3f(x, y + TAM_CASILLA, z);
            glEnd();

            if (esPuntoPoder(i, j))
                dibujarCruz(x, y, z);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity();

    gluLookAt(320, 320, 800,    // posición de la cámara
        320, 320, 0,      // punto al que mira (centro del tablero)
        0, 1, 0);         // vector "arriba"

    dibujarTablero();
    alumnos.dibuja();
    profesores.dibuja();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Cambiar a proyección perspectiva (3D)
    gluPerspective(45.0, (double)w / (double)h, 1.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
    tiempoOscilacion++;
    if (tiempoOscilacion >= 50) {
        tiempoOscilacion = 0;
        faseClaraOscura = !faseClaraOscura;
    }
    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(650, 650);
    glutCreateWindow("ARCHONEA - EE309 vs Automatica");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(100, timer, 0);
    glutMainLoop();
    return 0;
}