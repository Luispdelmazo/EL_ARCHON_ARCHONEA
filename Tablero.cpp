#include "Tablero.h"
#include "ETSIDI.h"

// CONSTRUCTOR
Tablero::Tablero(float tamCasilla, float ox, float oy)
    : tamCasilla(tamCasilla), offsetX(ox), offsetY(oy)
{
    // Inicializar todas las casillas como vacias
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            casillas[f][c] = nullptr;
        }
    }

    // Definir los 5 puntos de poder: centro y bordes
    puntosPoder[0][0] = 4; puntosPoder[0][1] = 4; // Centro
    puntosPoder[1][0] = 0; puntosPoder[1][1] = 4; // Borde superior
    puntosPoder[2][0] = 8; puntosPoder[2][1] = 4; // Borde inferior
    puntosPoder[3][0] = 4; puntosPoder[3][1] = 0; // Borde izquierdo
    puntosPoder[4][0] = 4; puntosPoder[4][1] = 8; // Borde derecho

    inicializarCasillas();
}

// DESTRUCTOR
Tablero::~Tablero() {
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            if (casillas[f][c] != nullptr) {
                delete casillas[f][c];
                casillas[f][c] = nullptr;
            }
        }
    }
}

// INICIALIZACION DE CASILLAS
void Tablero::inicializarCasillas() {
    // Primero todas normales con patron ajedrez claro/oscuro
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            EstadoCasilla estadoInicial;
            if ((f + c) % 2 == 0) {
                estadoInicial = EstadoCasilla::CLARA;
            }
            else {
                estadoInicial = EstadoCasilla::OSCURA;
            }
            tablero[f][c] = Casilla(TipoCasilla::NORMAL, estadoInicial);
        }
    }

    // Marcar los 5 puntos de poder
    for (int i = 0; i < 5; i++) {
        int f = puntosPoder[i][0];
        int c = puntosPoder[i][1];
        tablero[f][c] = Casilla(TipoCasilla::PUNTO_DE_PODER, EstadoCasilla::NEUTRA);
    }

    // Marcar casillas oscilantes distribuidas por el tablero
    // Correccion despues de la reunion con Miguel
    bool esOscilante[9][9] = {
        {false,false,false,true ,true ,true ,false,false,false},
        {false,false,true ,false,true ,false,true ,false,false},
        {false,true ,false,false,true ,false,false,true ,false},
        {true ,false,false,false,true ,false,false,false,true },
        {false,true ,true ,true ,true ,true ,true ,true ,false},
        {true ,false,false,false,true ,false,false,false,true },
        {false,true ,false,false,true ,false,false,true ,false},
        {false,false,true ,false,true ,false,true ,false,false},
        {false,false,false,true ,true ,true ,false,false,false}
    };

    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            // No sobreescribir los puntos de poder
            if (esOscilante[f][c] && tablero[f][c].getTipo() != TipoCasilla::PUNTO_DE_PODER) {
                EstadoCasilla estadoInicial;
                if ((f + c) % 2 == 0) {
                    estadoInicial = EstadoCasilla::CLARA;
                }
                else {
                    estadoInicial = EstadoCasilla::OSCURA;
                }
                tablero[f][c] = Casilla(TipoCasilla::OSCILANTE, estadoInicial, 5.0f);
            }
        }
    }
}

// DIBUJO
// Miguel dijo: primero las casillas, luego las piezas
void Tablero::dibujar() {
    // dibujar todas las casillas
    dibujarCasillas();
    // recorrer la matriz y dibujar cada pieza en su posicion
    // Como dibujar() es virtual, cada personaje se dibuja a su manera
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            if (casillas[f][c] != nullptr && casillas[f][c]->getEstaViva()) {
                casillas[f][c]->dibujar();
            }
        }
    }
}

void Tablero::dibujarCasillas() {
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            // Calcular posicion en pantalla de esta casilla
            float x = offsetX + c * tamCasilla;
            float y = offsetY + f * tamCasilla;

            // Elegir color segun tipo y estado de la casilla
            if (tablero[f][c].getTipo() == TipoCasilla::PUNTO_DE_PODER) {
                glColor3f(1.0f, 0.85f, 0.0f); // Dorado
            }
            else if (tablero[f][c].getTipo() == TipoCasilla::OSCILANTE) {
                if (tablero[f][c].getEstado() == EstadoCasilla::CLARA) {
                    glColor3f(0.6f, 0.4f, 0.8f); // Morado claro
                }
                else {
                    glColor3f(0.3f, 0.1f, 0.5f); // Morado oscuro
                }
            }
            else { // NORMAL
                if (tablero[f][c].getEstado() == EstadoCasilla::CLARA) {
                    glColor3f(0.9f, 0.9f, 0.85f); // Beige claro (bando luz)
                }
                else {
                    glColor3f(0.15f, 0.15f, 0.2f); // Gris oscuro (bando oscuridad)
                }
            }

            // Dibujar el cuadrado de la casilla
            glBegin(GL_QUADS);
            glVertex3f(x, y, 0.0f);
            glVertex3f(x + tamCasilla, y, 0.0f);
            glVertex3f(x + tamCasilla, y + tamCasilla, 0.0f);
            glVertex3f(x, y + tamCasilla, 0.0f);
            glEnd();

            // Borde negro fino
            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_LINE_LOOP);
            glVertex3f(x, y, 0.0f);
            glVertex3f(x + tamCasilla, y, 0.0f);
            glVertex3f(x + tamCasilla, y + tamCasilla, 0.0f);
            glVertex3f(x, y + tamCasilla, 0.0f);
            glEnd();
        }
    }
}

// GESTION DE PIEZAS
// Coloca una pieza en el tablero al iniciar la partida
void Tablero::colocarPieza(Pieza* pieza, int fila, int col) {
    if (fila < 0 || fila >= 9 || col < 0 || col >= 9) return;
    if (casillas[fila][col] != nullptr) return;

    casillas[fila][col] = pieza;
    pieza->setPosicion(fila, col);
    tablero[fila][col].setOcupada(true);
}

// Mueve una pieza de una casilla a otra
// Devuelve true si el movimiento fue valido
bool Tablero::moverPieza(int filaOrigen, int colOrigen, int filaDest, int colDest) {
    if (filaOrigen < 0 || filaOrigen >= 9 || colOrigen < 0 || colOrigen >= 9) return false;
    if (filaDest < 0 || filaDest >= 9 || colDest < 0 || colDest >= 9) return false;

    Pieza* pieza = casillas[filaOrigen][colOrigen];
    if (pieza == nullptr) return false;

    // No puede moverse a casilla ocupada por un aliado
    Pieza* piezaDestino = casillas[filaDest][colDest];
    if (piezaDestino != nullptr && piezaDestino->getBando() == pieza->getBando()) {
        return false;
    }

    // Mover la pieza
    casillas[filaOrigen][colOrigen] = nullptr;
    tablero[filaOrigen][colOrigen].setOcupada(false);

    casillas[filaDest][colDest] = pieza;
    pieza->setPosicion(filaDest, colDest);
    tablero[filaDest][colDest].setOcupada(true);

    return true;
}

// Comprueba si hay un enemigo en una casilla
bool Tablero::hayEnemigo(int fila, int col, Bando bandoActual) {
    if (casillas[fila][col] == nullptr) return false;
    return casillas[fila][col]->getBando() != bandoActual;
}

// Elimina una pieza del tablero al perder un combate
void Tablero::eliminarPieza(int fila, int col) {
    if (casillas[fila][col] != nullptr) {
        delete casillas[fila][col];
        casillas[fila][col] = nullptr;
        tablero[fila][col].setOcupada(false);
    }
}

// CONDICIONES DE VICTORIA
// Comprueba si un bando controla los 5 puntos de poder
bool Tablero::controlaPuntosDePoder(Bando bando) {
    for (int i = 0; i < 5; i++) {
        int f = puntosPoder[i][0];
        int c = puntosPoder[i][1];
        Pieza* pieza = casillas[f][c];
        if (pieza == nullptr || pieza->getBando() != bando) {
            return false;
        }
    }
    return true;
}

// Cuenta las piezas vivas de un bando
int Tablero::contarPiezas(Bando bando) {
    int total = 0;
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            if (casillas[f][c] != nullptr && casillas[f][c]->getBando() == bando) {
                total++;
            }
        }
    }
    return total;
}

void Tablero::actualizar(float dt) {
    // Actualizar casillas oscilantes
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            tablero[f][c].actualizar(dt);
        }
    }

    // Curar piezas en casillas favorables
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            if (casillas[f][c] != nullptr) {
                float bonus = tablero[f][c].getBonusCuracion(casillas[f][c]->getBando());
                if (bonus > 0.0f) {
                    casillas[f][c]->curar((int)(bonus * dt));
                }
            }
        }
    }
}

Pieza* Tablero::getPieza(int fila, int col) {
    if (fila < 0 || fila >= 9 || col < 0 || col >= 9) return nullptr;
    return casillas[fila][col];
}

Casilla& Tablero::getCasilla(int fila, int col) {
    return tablero[fila][col];
}

float Tablero::getTamCasilla() const { return tamCasilla; }
float Tablero::getOffsetX() const { return offsetX; }
float Tablero::getOffsetY() const { return offsetY; }

// Convierte coordenadas de pantalla a fila/columna (para el raton)
bool Tablero::pantallaATablero(float px, float py, int& filaOut, int& colOut) {
    colOut = (int)((px - offsetX) / tamCasilla);
    filaOut = (int)((py - offsetY) / tamCasilla);

    if (filaOut < 0 || filaOut >= 9 || colOut < 0 || colOut >= 9) {
        return false;
    }
    return true;
}
