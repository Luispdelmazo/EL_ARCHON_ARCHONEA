// ARCHON_2026_G5.cpp : Este archivo contiene la función "main". 
#include <GL/glut.h>
#include "Juego.h"

Juego juego;

void display() {
    juego.dibujar();
}

void reshape(int w, int h) {
    juego.reshape(w, h);
}

void raton(int boton, int estado, int x, int y) {
    juego.gestionRaton(boton, estado, x, y);
}

void teclado(unsigned char tecla, int x, int y) {
    juego.gestionTeclado(tecla, x, y);
}

void timer(int valor) {
    juego.actualizar(0.016f); // ~60fps
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutCreateWindow("ARCHONEA - EE309 vs Automatica");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(raton);
    glutKeyboardFunc(teclado);

    juego.inicializar();
    glutTimerFunc(16, timer, 0);
    glutMainLoop();
    return 0;
}