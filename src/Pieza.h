#pragma once
#include <vector>
#include <string>


// TIPOS ENUMERADOS
// bando al que pertenece la pieza
enum class Bando {
    LUZ,        // alumnos EE309
    OSCURIDAD   // profes automatica
};

// tipo de movimiento de la pieza
enum class TipoMovimiento {
    TERRESTRE,      // solo horizontal/vertical, no diagonal
    VOLADOR,        // libre, puede ir en diagonal
    TELETRANSPORTE  // a cualquier casilla valida del tablero
};

// coordenada en el tablero (fila, columna)
struct Coord {
    int fila;
    int col;

    Coord(int f = 0, int c = 0) : fila(f), col(c) {}

    // para comparar coordenadas facilmente
    bool operator==(const Coord& otra) const {
        return fila == otra.fila && col == otra.col;
    }
};


// CLASE BASE: Pieza
// Todos los personajes del juego heredan de esta clase.
// Mhdijo: los personajes SON una Pieza (herencia), no CONTIENEN una Pieza (atributo).

class Pieza {
protected:
    //posicion en el tablero
    int fila;       // fila actual (0-8)
    int col;        // columna actual (0-8)
    std::string nombre;     // nombre del personaje
    Bando bando;            // LUZ u OSCURIDAD
    TipoMovimiento tipoMov; // como se mueve

    int vidaMax;
    int vidaActual;
    int ataque;         // Daño que hace
    int velocidad;
    int rango;          // casillas que puede moverse en el tablero
    int alcanceAtaque;  // distancia de ataque en arena

    bool estaViva;      // si ha sido eliminada
    bool estaSeleccionada; // si el jugador la ha seleccionado

    int contadorAtaques; // para habilidades que dependen de turnos
    int contadorFallos;   // para habilidades que dependen de fallos

public:
    // CONSTRUCTOR
    Pieza(std::string nombre, Bando bando, TipoMovimiento tipoMov,
        int fila, int col,
        int vidaMax, int ataque, int velocidad, int rango, int alcanceAtaque)
        : nombre(nombre), bando(bando), tipoMov(tipoMov),
        fila(fila), col(col),
        vidaMax(vidaMax), vidaActual(vidaMax),
        ataque(ataque), velocidad(velocidad),
        rango(rango), alcanceAtaque(alcanceAtaque),
        estaViva(true), estaSeleccionada(false)
    {
    }

    // destructor virtual (imprescindible cuando hay herencia)
    virtual ~Pieza() {}

    // METODOS VIRTUALES PUROS (cada personaje los implementa a su manera) 
    virtual void dibujar() const = 0;
    // ejecuta la habilidad especial del personaje
    virtual void habilidadPostBatalla() = 0;
    virtual void habilidadEnBatalla() = 0;
    virtual void conjuros() = 0;


    // METODOS VIRTUALES (con implementacion base)

    // calcula las casillas validas a las que puede moverse
    // devuelve un vector de coordenadas validas
    virtual std::vector<Coord> getCasillasValidas(bool tablero[9][9], bool enemigas[9][9]) {
        std::vector<Coord> validas;

        if (tipoMov == TipoMovimiento::TELETRANSPORTE) {
            // puede ir a cualquier casilla libre del tablero
            for (int f = fila - rango; f <= fila + rango; f++) {
                for (int c = col - rango; c <= col + rango; c++) {
                    // que este dentro del tablero y no sea su propia casilla
                    if (f >= 0 && f < 9 && c >= 0 && c < 9 && !(f == fila && c == col)) {
                        if (!tablero[f][c] || enemigas[f][c]) { // si esta libre u ocupada por enemigo, puede ir
                            validas.push_back(Coord(f, c));
                        }
                    }
                }
            }
        }
        else if (tipoMov == TipoMovimiento::VOLADOR) {
            // puede moverse en cualquier direccion dentro del rango
            for (int f = fila - rango; f <= fila + rango; f++) {
                for (int c = col - rango; c <= col + rango; c++) {
                    // que este dentro del tablero y no sea su propia casilla
                    if (f >= 0 && f < 9 && c >= 0 && c < 9 && !(f == fila && c == col)) {
                        if (!tablero[f][c] || enemigas[f][c]) { // si esta libre u ocupada por enemigo, puede ir
                            validas.push_back(Coord(f, c));
                        }
                    }
                }
            }
        }
        else { // TERRESTRE: solo horizontal y vertical
            // desde la posición actual, nos desplazamos dentro de las casillas en el rango rodeadas por 8 casillas aún pertenecientes al rango
            // es decir todas aquellas que no están en el "borde" del rango
            // comprobamos desde cada una de ellas a cuantas de las 8 contigas podemos ir
            // la matriz revisadas evita que se guarden casillas repetidas, evitando que el vector de validas crezca innecesariamente
            bool revisadas[9][9] = {}; // para no revisar casillas mas de una vez
            int df[] = { -1, 1, 0, 0 };
            int dc[] = { 0, 0, -1, 1 };


            validas.push_back(Coord(fila, col));
            for (size_t i = 0; i < validas.size(); i++) {
                Coord c = validas[i];
                if (tablero[c.fila][c.col] && i > 0) continue; // si la casilla esta ocupada por otra pieza, no se puede pasar
                for (int dir = 0; dir < 4; dir++) {

                    int nuevaFila = c.fila + df[dir];
                    int nuevaCol = c.col + dc[dir];

                    if (nuevaFila < 0 || nuevaFila >= 9 || nuevaCol < 0 || nuevaCol >= 9)
                        continue; // fuera del tablero, paramos

                    if (tablero[nuevaFila][nuevaCol] && !enemigas[nuevaFila][nuevaCol])
                        continue; // casilla ocupada por aliado, no puede pasar
                    if (nuevaFila > fila + rango || nuevaFila < fila - rango || nuevaCol > col + rango || nuevaCol < col - rango)
                        continue; // fuera del rango, paramos

                    if (revisadas[nuevaFila][nuevaCol])
                        continue; // ya revisamos esta casilla, no la revisamos de nuevo])

                    validas.push_back(Coord(nuevaFila, nuevaCol));
                    revisadas[nuevaFila][nuevaCol] = true; // marcamos como revisada
                }
            }
            validas.erase(validas.begin()); // eliminamos la casilla original, que no es valida para moverse]

        }

        return validas;
    }

    // recibe daño en combate
    virtual void recibirDano(int dano) {
        vidaActual -= dano;
        if (vidaActual <= 0) {
            vidaActual = 0;
            estaViva = false;
        }
    }

    // cura a la pieza (para casillas especiales y hechizos)
    virtual void curar(int cantidad) {
        vidaActual += cantidad;
        if (vidaActual > vidaMax) {
            vidaActual = vidaMax;
        }
    }

    void setAlcanceAtaque(int a) { alcanceAtaque = a; }

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
    void nuevoAtaque() { contadorAtaques++; }
    void resetAtaques() { contadorAtaques = 0; }
    void nuevoFallo() { contadorFallos++; }
    void resetFallos() { contadorFallos = 0; }


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
    virtual void loop() const {}
};
