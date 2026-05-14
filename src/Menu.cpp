#include "Menu.h"
Menu::Menu() {
    opcionSeleccionada = OpcionMenu::JUGAR;
    haSeleccionado = false;
}
void Menu::dibujarTexto(float x, float y, std::string texto) {
    glRasterPos2f(x, y);
    for (int i = 0; texto[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
    }
}
void Menu::dibujar() {
    if (viendoRanking) { dibujarRanking();return;}
    glColor3f(0.05f, 0.05f, 0.1f);//plantilla pang fondo oscuro
    glBegin(GL_QUADS);
    glVertex3f(-5.0f, -5.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, 0.0f);
    glVertex3f(5.0f, 5.0f, 0.0f);
    glVertex3f(-5.0f, 5.0f, 0.0f);
    glEnd();
    glColor3f(1.0f, 0.85f, 0.0f); 
    dibujarTexto(-1.5f, 3.0f, "PACHON");//titulo
    glColor3f(0.8f, 0.8f, 0.8f);
    dibujarTexto(-2.0f, 2.2f, "EE309 vs Automatica UPM");
    glColor3f(0.5f, 0.0f, 0.8f);
    glBegin(GL_LINES);
    glVertex3f(-3.0f, 1.8f, 0.0f);
    glVertex3f(3.0f, 1.8f, 0.0f);
    glEnd();
    if (opcionSeleccionada == OpcionMenu::JUGAR) {
        glColor3f(1.0f, 0.85f, 0.0f); 
    }else {
        glColor3f(1.0f, 1.0f, 1.0f);  
    }
    dibujarTexto(-0.5f, 1.0f, "JUGAR");

    if (opcionSeleccionada == OpcionMenu::RANKING) {
        glColor3f(1.0f, 0.85f, 0.0f);
    }else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    dibujarTexto(-0.7f, -0.5f, "RANKING");
    
    if (opcionSeleccionada == OpcionMenu::SALIR) {
        glColor3f(1.0f, 0.85f, 0.0f);
    }else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    dibujarTexto(-0.5f, -2.0f, "SALIR");
    glColor3f(0.5f, 0.5f, 0.5f);
    dibujarTexto(-3.5f, -4.0f, "Haz clic en una opcion o usa ENTER");//instrucciones
}
void Menu::dibujarRanking() {
    glColor3f(0.05f, 0.05f, 0.1f);//colores y codigo de las practicas de informatica
    glBegin(GL_QUADS);
    glVertex3f(-5.0f, -5.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, 0.0f);
    glVertex3f(5.0f, 5.0f, 0.0f);
    glVertex3f(-5.0f, 5.0f, 0.0f);
    glEnd();
    glColor3f(1.0f, 0.85f, 0.0f);
    dibujarTexto(-1.0f, 3.5f, "RANKING");
    glColor3f(0.5f, 0.0f, 0.8f);
    glBegin(GL_LINES);
    glVertex3f(-3.0f, 3.0f, 0.0f);
    glVertex3f(3.0f, 3.0f, 0.0f);
    glEnd();
    glColor3f(0.8f, 0.8f, 0.8f);
    dibujarTexto(-2.5f, 1.0f, "No hay partidas guardadas aun");// Mensaje provisional hasta implementar fichero
    glColor3f(0.5f, 0.5f, 0.5f);
    dibujarTexto(-2.0f, -3.5f, "Pulsa ESC para volver al menu");// Instruccion para volver
}
void Menu::gestionRaton(int boton, int estado, float glX, float glY) {
    if (boton != GLUT_LEFT_BUTTON || estado != GLUT_UP) return;
    if (glX > -2.0f && glX < 2.0f) {
        if (glY > 0.5f && glY < 1.5f) {        
            opcionSeleccionada = OpcionMenu::JUGAR;// Clic en JUGAR
            haSeleccionado = true;
        } else if (glY > -1.0f && glY < 0.0f) {
            opcionSeleccionada = OpcionMenu::RANKING;
            viendoRanking = true;
        } else if (glY > -2.5f && glY < -1.5f) { 
            opcionSeleccionada = OpcionMenu::SALIR;
            haSeleccionado = true;
        }
    }
}
void Menu::gestionTeclado(unsigned char tecla) {
    if (viendoRanking) {
        if (tecla == 27) { viendoRanking = false;} return;
    } else if (tecla == 13) { // ENTER confirma
        haSeleccionado = true;
    }
} 
OpcionMenu Menu::getOpcionSeleccionada() const {
    return opcionSeleccionada;
}