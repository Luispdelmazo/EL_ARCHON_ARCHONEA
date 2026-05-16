#include "Pieza.h"

std::vector<Coord> Pieza::getCasillasValidas(bool tablero[9][9]) {
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

void Pieza::recibirDano(int dano) {
    vidaActual -= dano;
    if (vidaActual <= 0) {
        vidaActual = 0;
        estaViva = false;
    }
}

void Pieza::curar(int cantidad) {
    vidaActual += cantidad;
    if (vidaActual > vidaMax) {
        vidaActual = vidaMax;
    }
}