#pragma once
#include <vector>
#include <string>


// TIPOS ENUMERADOS
// Bando al que pertenece la pieza
enum class Bando {
    LUZ,        // Alumnos EE309
    OSCURIDAD   // Profes Automatica
};

// Tipo de movimiento de la pieza
enum class TipoMovimiento {
    TERRESTRE,      // Solo horizontal/vertical, no diagonal
    VOLADOR,        // Libre, puede ir en diagonal
    TELETRANSPORTE  // A cualquier casilla valida del tablero
};

// Coordenada en el tablero (fila, columna)
struct Coord {
    int fila;
    int col;

    Coord(int f = 0, int c = 0) : fila(f), col(c) {}

    // Para comparar coordenadas facilmente
    bool operator==(const Coord& otra) const {
        return fila == otra.fila && col == otra.col;
    }
};

// =============================================
// CLASE BASE: Pieza
// =============================================
// Todos los personajes del juego heredan de esta clase.
// Miguel dijo: los personajes SON una Pieza (herencia),
// no CONTIENEN una Pieza (atributo).
// =============================================

class Pieza {
protected:
    // --- Posicion en el tablero ---
    int fila;       // Fila actual (0-8)
    int col;        // Columna actual (0-8)

    // --- Identidad ---
    std::string nombre;     // Nombre del personaje
    Bando bando;            // LUZ u OSCURIDAD
    TipoMovimiento tipoMov; // Como se mueve

    // --- Estadisticas de combate ---
    int vidaMax;        // Vida maxima
    int vidaActual;     // Vida actual
    int ataque;         // Dano que hace
    int velocidad;      // Velocidad de movimiento en arena
    int rango;          // Casillas que puede moverse en el tablero
    int alcanceAtaque;  // Distancia de ataque en arena

    // --- Estado ---
    bool estaViva;      // Si ha sido eliminada
    bool estaSeleccionada; // Si el jugador la ha seleccionado

public:
    // =============================================
    // CONSTRUCTOR
    // =============================================
    Pieza(std::string nombre, Bando bando, TipoMovimiento tipoMov,
          int fila, int col,
          int vidaMax, int ataque, int velocidad, int rango, int alcanceAtaque)
        : nombre(nombre), bando(bando), tipoMov(tipoMov),
          fila(fila), col(col),
          vidaMax(vidaMax), vidaActual(vidaMax),
          ataque(ataque), velocidad(velocidad),
          rango(rango), alcanceAtaque(alcanceAtaque),
          estaViva(true), estaSeleccionada(false)
    {}

    // Destructor virtual (imprescindible cuando hay herencia)
    virtual ~Pieza() {}

    // =============================================
    // METODOS VIRTUALES PUROS
    // (cada personaje los implementa a su manera)
    // =============================================

    // Dibuja la pieza en pantalla con OpenGL
    virtual void dibujar() = 0;

    // Ejecuta la habilidad especial del personaje
    virtual void habilidadEspecial() = 0;

    // =============================================
    // METODOS VIRTUALES (con implementacion base)
    // =============================================

    // Calcula las casillas validas a las que puede moverse
    // Devuelve un vector de coordenadas validas
    virtual std::vector<Coord> getCasillasValidas(bool tablero[9][9]) {
        std::vector<Coord> validas;

        if (tipoMov == TipoMovimiento::TELETRANSPORTE) {
            // Puede ir a cualquier casilla libre del tablero
            for (int f = 0; f < 9; f++) {
                for (int c = 0; c < 9; c++) {
                    if (!tablero[f][c]) { // Si esta libre
                        validas.push_back(Coord(f, c));
                    }
                }
            }
        }
        else if (tipoMov == TipoMovimiento::VOLADOR) {
            // Puede moverse en cualquier direccion dentro del rango
            for (int f = fila - rango; f <= fila + rango; f++) {
                for (int c = col - rango; c <= col + rango; c++) {
                    // Que este dentro del tablero y no sea su propia casilla
                    if (f >= 0 && f < 9 && c >= 0 && c < 9 && !(f == fila && c == col)) {
                        if (!tablero[f][c]) { // Si esta libre
                            validas.push_back(Coord(f, c));
                        }
                    }
                }
            }
        }
        else { // TERRESTRE: solo horizontal y vertical
            // Direcciones: arriba, abajo, izquierda, derecha
            int df[] = { -1, 1, 0, 0 };
            int dc[] = { 0, 0, -1, 1 };

            for (int dir = 0; dir < 4; dir++) {
                for (int paso = 1; paso <= rango; paso++) {
                    int nuevaFila = fila + df[dir] * paso;
                    int nuevaCol = col + dc[dir] * paso;

                    if (nuevaFila < 0 || nuevaFila >= 9 || nuevaCol < 0 || nuevaCol >= 9)
                        break; // Fuera del tablero, paramos

                    if (tablero[nuevaFila][nuevaCol])
                        break; // Casilla ocupada, no puede pasar

                    validas.push_back(Coord(nuevaFila, nuevaCol));
                }
            }
        }

        return validas;
    }

    // Recibe dano en combate
    virtual void recibirDano(int dano) {
        vidaActual -= dano;
        if (vidaActual <= 0) {
            vidaActual = 0;
            estaViva = false;
        }
    }

    // Cura a la pieza (para casillas especiales y hechizos)
    virtual void curar(int cantidad) {
        vidaActual += cantidad;
        if (vidaActual > vidaMax) {
            vidaActual = vidaMax;
        }
    }

    // =============================================
    // GETTERS
    // =============================================
    int getFila() const { return fila; }
    int getCol() const { return col; }
    std::string getNombre() const { return nombre; }
    Bando getBando() const { return bando; }
    TipoMovimiento getTipoMovimiento() const { return tipoMov; }
    int getVidaActual() const { return vidaActual; }
    int getVidaMax() const { return vidaMax; }
    int getAtaque() const { return ataque; }
    int getVelocidad() const { return velocidad; }
    int getRango() const { return rango; }
    int getAlcanceAtaque() const { return alcanceAtaque; }
    bool getEstaViva() const { return estaViva; }
    bool getEstaSeleccionada() const { return estaSeleccionada; }

    // =============================================
    // SETTERS
    // =============================================
    void setPosicion(int nuevaFila, int nuevaCol) {
        fila = nuevaFila;
        col = nuevaCol;
    }

    void setSeleccionada(bool sel) {
        estaSeleccionada = sel;
    }

    void setViva(bool viva) {
        estaViva = viva;
    }
};
