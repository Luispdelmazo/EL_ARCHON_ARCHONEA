#define USE_ETSIDI
#include "lib/ETSIDI.h"
#include "lib/GL/glut.h"
#include "Pieza.h"
using namespace ETSIDI;

//Pieza pieza({ 4,0 }, Equipo::Alumnos, Movimiento::volador, 3, 100);



void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(320, 320, 800,    // posición de la cámara
        320, 320, 0,      // punto al que mira (centro del tablero)
        0, 1, 0);         // vector "arriba"
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