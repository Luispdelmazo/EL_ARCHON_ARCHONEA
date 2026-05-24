#pragma once
#include "Pieza.h"

// Dificultad de la IA - se elige en el menu antes de empezar
enum class DificultadIA {
    FACIL,   // La IA se mueve lento y ataca poco
    MEDIO,   // Comportamiento normal
    DIFICIL  // La IA es rapida y muy agresiva
};

// Estados posibles dentro de la batalla
// GANA_ATACANTE/DEFENSOR en vez de LUZ/OSCURIDAD porque el rol cambia
// segun quien invade la casilla de quien (propuesta de mi compañero)
enum class EstadoBatalla {
    EN_CURSO,
    GANA_ATACANTE,
    GANA_DEFENSOR
};

// CLASE: Batalla
// Cuando dos piezas coinciden en una casilla del tablero
// se abre esta arena de combate en tiempo real.
// El jugador controla su pieza con WASD y ataca con F.
// Gana quien reduzca la vida del rival a 0.
class Batalla {
private:
    // Las dos piezas que combaten
    // Son punteros a Pieza pero se comportan como lo que son (polimorfismo)
    Pieza* atacante;    // Pieza que se mueve a la casilla
    Pieza* defensor;    // Pieza que estaba en la casilla

    // Posiciones dentro de la arena
    float xAtacante, yAtacante;
    float xDefensor, yDefensor;

    // Velocidades de movimiento en la arena
    float vxAtacante, vyAtacante;
    float vxDefensor, vyDefensor;

    // Timers de recarga entre ataques
    float timerAtaqueAtacante;
    float timerAtaqueDefensor;

    // Indica si el jugador puede atacar ahora - se muestra con circulo verde
    bool puedeAtacarAtacante;

    // Estado actual de la batalla
    EstadoBatalla estado;

    // Dificultad de la IA - se pasa desde el menu
    DificultadIA dificultad;

    // Limites de la arena
    static const float ARENA_MIN;
    static const float ARENA_MAX;

    // Piedras en la arena - sirven de escudo igual que en el Archon original
    struct Piedra {
        float x, y;
    };
    static const int NUM_PIEDRAS = 6;
    Piedra piedras[NUM_PIEDRAS];

    // Metodos internos
    void dibujarArena();
    void dibujarBarrasDeVida();
    void dibujarPiezas();
    void dibujarPiedras();
    void comprobarAtaques(bool jugadorAtaca);
    void comprobarColisionesPiedras();
    void moverIA(float dt);
    void comprobarFinBatalla();

public:
    Batalla();

    // Inicia la batalla con las dos piezas que van a combatir
    void iniciar(Pieza* atac, Pieza* def);

    // Para pasar la dificultad elegida en el menu
    void setDificultad(DificultadIA d) { dificultad = d; }
    DificultadIA getDificultad() const { return dificultad; }

    // Dibujo y actualizacion - igual que en el Pang
    void dibujar();
    void actualizar(float dt);

    // Input del jugador
    void gestionTeclado(unsigned char tecla);
    void gestionTecladoSuelto(unsigned char tecla);

    EstadoBatalla getEstado()   const { return estado; }
    Pieza* getAtacante()        const { return atacante; }
    Pieza* getDefensor()        const { return defensor; }
};
