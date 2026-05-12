#pragma once
#include "Tablero.h"
#include "Batalla.h"

// Estados posibles del juego
enum class EstadoJuego {
    TABLERO,   // Vista del tablero estrategico
    BATALLA    // Arena de combate entre dos piezas
};

class Juego {
private:
    Tablero tablero;
    Batalla batalla;
    EstadoJuego estadoActual;
    Bando turnoActual;  // A quien le toca mover

public:
    Juego();

    void inicializar();
    void dibujar();
    void actualizar(float dt);
    void reshape(int w, int h);

    // Input
    void gestionRaton(int boton, int estado, int x, int y);
    void gestionTeclado(unsigned char tecla, int x, int y);

    // Cambio de estado
    void iniciarBatalla(Pieza* atacante, Pieza* defensor);
    void terminarBatalla();
    void cambiarTurno();
};