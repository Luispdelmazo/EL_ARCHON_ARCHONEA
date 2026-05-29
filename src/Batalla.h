#pragma once
#include "Pieza.h"
#include "Proyectil.h"
// dificultad de la IA - se elige en el menu antes de empezar
enum class DificultadIA {
    FACIL,   // La IA se mueve lento y ataca poco
    MEDIO,   // Comportamiento normal
    DIFICIL  // La IA es rapida y muy agresiva
};

// estados posibles dentro de la batalla
// GANA_ATACANTE/DEFENSOR en vez de LUZ/OSCURIDAD porque el rol cambia
// segun quien invade la casilla de quien
enum class EstadoBatalla {
    EN_CURSO,
    GANA_ALUMNO,
    GANA_PROFESOR,
    EMPATE
};

// CLASE: Batalla
// cuando dos piezas coinciden en una casilla del tablero
// se abre esta arena de combate en tiempo real.
// el jugador controla su pieza con WASD y ataca con F.
// gana quien reduzca la vida del rival a 0.
class Batalla {
private:
    // Las dos piezas que combaten
    // Son punteros a Pieza pero se comportan como lo que son (polimorfismo)
    Pieza* alumno;    // Pieza que se mueve a la casilla
    Pieza* profesor;    // Pieza que estaba en la casilla

    // posiciones dentro de la arena
    float xAlumno, yAlumno;
    float xProfesor, yProfesor;

    // velocidades de movimiento en la arena
    float vxAlumno, vyAlumno;
    float vxProfesor, vyProfesor;

    float timerAtaqueAlumno;
    float timerAtaqueProfesor;

    // indica si el jugador puede atacar ahora - se muestra con circulo verde
    bool puedeAtacarAlumno;

    // estado actual de la batalla
    EstadoBatalla estado;

    // dificultad de la IA - se pasa desde el menu
    DificultadIA dificultad;

    // limites de la arena
    static const float ARENA_MIN;
    static const float ARENA_MAX;

    // piedras en la arena - sirven de escudo igual que en el ARCHON original
    struct Piedra {
        float x, y;
    };
    static const int NUM_PIEDRAS = 6;
    Piedra piedras[NUM_PIEDRAS];
    // uno por bando, igual que en el ARCHON origina solo puede haber un proyectil activo por pieza a la vez
    Proyectil proyectilAlumno;
    Proyectil proyectilProfesor;

    void dibujarArena();
    void dibujarBarrasDeVida();
    void dibujarPiezas();
    void dibujarPiedras();
    void comprobarAtaques(bool jugadorAtaca);
    void comprobarColisionesPiedras();
    void comprobarColisionesProyectiles(); 
    void moverIA(float dt);
    void comprobarFinBatalla();

public:
    Batalla();
    void iniciar(Pieza* alum, Pieza* prof);
    void setDificultad(DificultadIA d) { dificultad = d; }
    DificultadIA getDificultad() const { return dificultad; }
    void dibujar();
    void actualizar(float dt);
    void gestionTeclado(unsigned char tecla);
    void gestionTecladoSuelto(unsigned char tecla);
    EstadoBatalla getEstado()  const { return estado; }
    Pieza* getAlumno()       const { return alumno; }
    Pieza* getProfesor()       const { return profesor; }
};