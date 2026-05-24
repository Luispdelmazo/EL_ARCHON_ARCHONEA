// ARCHON_2026_G5.cpp : Este archivo contiene la función "main". 
#include <GL/glut.h>
#include "Juego.h"
// Objeto global del juego - igual que en el Pang
Juego juego;

void display() {
    juego.dibujar();
}

void reshape(int w, int h) {
    juego.reshape(w, h);
}

void teclado(unsigned char tecla, int x, int y) {
    juego.gestionTeclado(tecla, x, y);
    glutPostRedisplay();
}

void tecladoSuelto(unsigned char tecla, int x, int y) {
    juego.gestionTecladoSuelto(tecla, x, y);
}

void raton(int boton, int estado, int x, int y) {
    juego.gestionRaton(boton, estado, x, y);
    glutPostRedisplay();
}

void timer(int valor) {
    static int tiempoAnterior = 0;
    int tiempoActual = glutGet(GLUT_ELAPSED_TIME);
    float dt = (tiempoActual - tiempoAnterior) / 1000.0f;
    tiempoAnterior = tiempoActual;

    // Limitar dt para evitar saltos grandes si la ventana se mueve
    if (dt > 0.05f) dt = 0.05f;

    juego.actualizar(dt);
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); 
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("ARCHONEA - EE309 vs Automatica UPM");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutKeyboardUpFunc(tecladoSuelto);
    glutMouseFunc(raton);
    glutTimerFunc(16, timer, 0);

    glutMainLoop();
    return 0;
}