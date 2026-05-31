#pragma once
#include "Tablero.h"
#include "Batalla.h"
#include "Menu.h"
#include "Ranking.h"

// estados posibles del juego - maquina de estados igual que el Coordinador del Pang
enum class EstadoJuego {
    MENU,
    TABLERO,
    BATALLA,
    RANKING,
    FIN_PARTIDA,
    PAUSA_TABLERO,
	PAUSA_BATALLA
};

class Juego {
private:
    Menu     menu;
    Tablero  tablero;
    Batalla  batalla;
    Ranking  ranking;

    EstadoJuego estadoActual;
    Bando       turnoActual;
    ModoJuego   modoJuego;

    // para saber donde fue el combate y actuar al terminar
    int filaDestinoBatalla;
    int colDestinoBatalla;
    int filaAtacanteBatalla;  // donde estaba el atacante al iniciar la batalla
    int colAtacanteBatalla;

    // variables para la IA del tablero
    bool  turnoIA;        // true cuando toca mover a OSCURIDAD automaticamente
    float timerIA;        // cuenta atras antes de que la IA mueva
    int   faseIA;
    int   filaOrigenIA, colOrigenIA, filaDestIA, colDestIA;
  
    Bando ganador;
    int   turnosJugados;

    // metodos privados
    void dibujarPantallaFin();
    void dibujarTexto(float x, float y, float z, std::string texto);
    void comprobarVictoria();

public:
    Juego();

    void inicializar();
    void dibujar();
    void actualizar(float dt);
    void reshape(int w, int h);
    void gestionRaton(int boton, int estado, int x, int y);
    void gestionTeclado(unsigned char tecla, int x, int y);
    void gestionTecladoSuelto(unsigned char tecla, int x, int y);
    bool sonidoMenuReproducido;

    //cambio de estado
    void iniciarBatalla(Pieza* atacante, Pieza* defensor);
    void terminarBatalla();
    void cambiarTurno();
    void convertirCoordenadas(int pixelX, int pixelY, float& glX, float& glY);
};
