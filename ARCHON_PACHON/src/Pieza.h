#pragma once
//version prueba daniella para que fufe 
#include <vector>
#include <string>

enum class Bando {
    LUZ,        // Alumnos
    OSCURIDAD   // Profesors Automatica
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

    virtual std::vector<Coord> getCasillasValidas(bool tablero[9][9]);

    virtual void recibirDano(int dano);

    virtual void curar(int cantidad);


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
