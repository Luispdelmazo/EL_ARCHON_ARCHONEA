#pragma once
#include <GL/glut.h>
#include <string>
enum class OpcionMenu {// Opciones disponibles en el menu
    JUGAR,
    RANKING,
    SALIR
};
class Menu {
private:
    OpcionMenu opcionSeleccionada;
    bool viendoRanking;
    void dibujarTexto(float x, float y, std::string texto);
    void dibujarRanking();
public:
    Menu();
    void dibujar();
    void gestionRaton(int boton, int estado, float glX, float glY);
    void gestionTeclado(unsigned char tecla);
    OpcionMenu getOpcionSeleccionada() const;// Juego le pregunta que eligio el jugador
    bool haSeleccionado;
};
