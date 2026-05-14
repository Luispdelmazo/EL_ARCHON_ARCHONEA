#pragma once
// esqueleto
#include "Pieza.h"

/*CLASE: Batalla
Cuando dos piezas coinciden en una casilla del tablero
se abre esta arena de combate en tiempo real.
El jugador controla su pieza con el teclado y dispara.
Gana quien reduzca la vida del rival a 0.*/

// Estados posibles dentro de la batalla
enum class EstadoBatalla {
    EN_CURSO,   // Las dos piezas siguen vivas
    GANA_LUZ,   // Gano la pieza del bando luz
    GANA_OSCURIDAD // Gano la pieza del bando oscuridad
};

class Batalla {
private:
    // Las dos piezas que combaten
    // Son punteros a Pieza pero se comportan como lo que son (polimorfismo)
    Pieza* atacante;    // Pieza que se mueve a la casilla
    Pieza* defensor;    // Pieza que estaba en la casilla

    // Posiciones dentro de la arena (coordenadas de pantalla, no del tablero)
    float xAtacante, yAtacante;
    float xDefensor, yDefensor;

    // Velocidades de movimiento en la arena
    float vxAtacante, vyAtacante;
    float vxDefensor, vyDefensor;

    // Temporizador para el intervalo entre ataques (recarga)
    float timerAtaqueAtacante;
    float timerAtaqueDefensor;

    // Estado actual de la batalla
    EstadoBatalla estado;

    // Limites de la arena
    static const float ARENA_MIN;
    static const float ARENA_MAX;

public:
    Batalla();

    // Inicia la batalla con las dos piezas que van a combatir
    void iniciar(Pieza* atac, Pieza* def);

    // Dibujo de la arena completa
    void dibujar();
    void dibujar(Bando turno);
    // Actualizacion cada frame (movimiento, colisiones, ataques de la IA)
    void actualizar(float dt);

    // Input del jugador (teclado)
    void gestionTeclado(unsigned char tecla);

    EstadoBatalla getEstado() const { return estado; }
    Pieza* getAtacante() const { return atacante; }
    Pieza* getDefensor() const { return defensor; }

private:
    // Metodos internos
    void dibujarArena();
    void dibujarBarrasDeVida();
    void dibujarPiezas();
    void comprobarAtaques();
    void moverIA(float dt);         // La IA mueve al defensor automaticamente
    void comprobarFinBatalla();
};