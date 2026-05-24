#pragma once
#include <GL/glut.h>
#include <string>
#include "Batalla.h"

enum class OpcionMenu {
    JUGAR,
    RANKING,
    INSTRUCCIONES,
    SALIR
};

// Estados internos del menu - maquina de estados pequena igual que Juego tiene EstadoJuego, Menu tiene EstadoMenu
enum class EstadoMenu {
    PRINCIPAL,      // Menu principal con opciones
    NIVEL,          // Submenu de seleccion de nivel de dificultad
    INSTRUCCIONES   // Pantalla de instrucciones
};

class Menu {
private:
    OpcionMenu     opcionSeleccionada;
    DificultadIA   dificultadSeleccionada;
    EstadoMenu     estadoMenu;

    void dibujarTexto(float x, float y, std::string texto);
    void dibujarMenuPrincipal();
    void dibujarSeleccionNivel();
    void dibujarInstrucciones();

public:
    Menu();

    void dibujar();
    void gestionRaton(int boton, int estado, float glX, float glY);
    void gestionTeclado(unsigned char tecla);

    OpcionMenu   getOpcionSeleccionada() const;
    DificultadIA getDificultad()         const { return dificultadSeleccionada; }

    bool haSeleccionado;
};
