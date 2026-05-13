#pragma once
//version prueba daniella para que fufe 
#include <vector>
#include <string>

enum class Bando {
    LUZ,        // Alumnos EE309
    OSCURIDAD   // Profes Automatica
};

enum class TipoMovimiento {
    TERRESTRE,
    VOLADOR,
    TELETRANSPORTE
};

struct Coord {
    int fila;
    int col;

    Coord(int f = 0, int c = 0) : fila(f), col(c) {}

    bool operator==(const Coord& otra) const {
        return fila == otra.fila && col == otra.col;
    }
};

// CLASE BASE: Pieza

class Pieza {
protected:
    int fila;
    int col;
    std::string nombre;
    Bando bando;
    TipoMovimiento tipoMov;
    int vidaMax;
    int vidaActual;
    int ataque;
    int velocidad;
    int rango;
    int alcanceAtaque;
    bool estaViva;
    bool estaSeleccionada;

public:
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

    virtual ~Pieza() {}
    //virtual es polimorfismo
    virtual void dibujar() = 0;
    virtual void habilidadEspecial() = 0;

    virtual std::vector<Coord> getCasillasValidas(bool tablero[9][9]) {
        std::vector<Coord> validas;

        if (tipoMov == TipoMovimiento::TELETRANSPORTE) {
            for (int f = 0; f < 9; f++) {
                for (int c = 0; c < 9; c++) {
                    if (!tablero[f][c]) {
                        validas.push_back(Coord(f, c));
                    }
                }
            }
        }
        else if (tipoMov == TipoMovimiento::VOLADOR) {
            for (int f = fila - rango; f <= fila + rango; f++) {
                for (int c = col - rango; c <= col + rango; c++) {
                    if (f >= 0 && f < 9 && c >= 0 && c < 9 && !(f == fila && c == col)) {
                        if (!tablero[f][c]) {
                            validas.push_back(Coord(f, c));
                        }
                    }
                }
            }
        }
        else { // TERRESTRE
            int df[] = { -1, 1, 0, 0 };
            int dc[] = { 0, 0, -1, 1 };

            for (int dir = 0; dir < 4; dir++) {
                for (int paso = 1; paso <= rango; paso++) {
                    int nuevaFila = fila + df[dir] * paso;
                    int nuevaCol = col + dc[dir] * paso;

                    if (nuevaFila < 0 || nuevaFila >= 9 || nuevaCol < 0 || nuevaCol >= 9)
                        break;
                    if (tablero[nuevaFila][nuevaCol])
                        break;

                    validas.push_back(Coord(nuevaFila, nuevaCol));
                }
            }
        }

        return validas;
    }

    virtual void recibirDano(int dano) {
        vidaActual -= dano;
        if (vidaActual <= 0) {
            vidaActual = 0;
            estaViva = false;
        }
    }

    virtual void curar(int cantidad) {
        vidaActual += cantidad;
        if (vidaActual > vidaMax) {
            vidaActual = vidaMax;
        }
    }

   
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

    void setPosicion(int nuevaFila, int nuevaCol) {
        fila = nuevaFila;
        col = nuevaCol;
    }
    void setSeleccionada(bool sel) { estaSeleccionada = sel; }
    void setViva(bool viva) { estaViva = viva; }
};