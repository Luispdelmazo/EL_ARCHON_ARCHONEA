#pragma once
#include "Tablero.h"
#include "Batalla.h"
#include "Menu.h"
#include "Ranking.h"

// Estados posibles del juego - maquina de estados igual que el Coordinador del Pang
enum class EstadoJuego {
    MENU,
    TABLERO,
    BATALLA,
    RANKING
};

class Juego {
private:
    Menu     menu;
    Tablero  tablero;
    Batalla  batalla;
    Ranking  ranking;

    EstadoJuego estadoActual;
    Bando       turnoActual;

    // Para saber donde fue el combate y actuar al terminar
    int filaDestinoBatalla;
    int colDestinoBatalla;

    // Para la pantalla de fin y el ranking
    bool  juegoTerminado;
    Bando ganador;
    int   turnosJugados;

    // Metodos privados
    void dibujarPantallaFin();
    void dibujarTexto(float x, float y, std::string texto);
    void comprobarVictoria();

public:
    Juego();

    void inicializar();
    void dibujar();
    void actualizar(float dt);
    void reshape(int w, int h);

    // Input
    void gestionRaton(int boton, int estado, int x, int y);
    void gestionTeclado(unsigned char tecla, int x, int y);
    void gestionTecladoSuelto(unsigned char tecla, int x, int y);

    // Cambio de estado
    void iniciarBatalla(Pieza* atacante, Pieza* defensor);
    void terminarBatalla();
    void cambiarTurno();

    void convertirCoordenadas(int pixelX, int pixelY, float& glX, float& glY);
};
