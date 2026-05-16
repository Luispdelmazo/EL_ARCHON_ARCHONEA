#include "Tablero.h"
#include "ETSIDI.h"
#include <cstdlib> // para rand()

void Tablero::cambiarColorOscilantes() {
    colorOscilanteR = (float)(rand() % 100) / 100.0f;
    colorOscilanteG = (float)(rand() % 100) / 100.0f;
    colorOscilanteB = (float)(rand() % 100) / 100.0f;
}

// CONSTRUCTOR
Tablero::Tablero(float tamCasilla, float ox, float oy)
    : tamCasilla(tamCasilla), offsetX(ox), offsetY(oy)
{
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            casillas[f][c] = nullptr;
        }
    }

    puntosPoder[0][0] = 4; puntosPoder[0][1] = 4; // Centro
    puntosPoder[1][0] = 0; puntosPoder[1][1] = 4; // Borde superior
    puntosPoder[2][0] = 8; puntosPoder[2][1] = 4; // Borde inferior
    puntosPoder[3][0] = 4; puntosPoder[3][1] = 0; // Borde izquierdo
    puntosPoder[4][0] = 4; puntosPoder[4][1] = 8; // Borde derecho

    // Color inicial aleatorio para las oscilantes
    colorOscilanteR = (float)(rand() % 100) / 100.0f;
    colorOscilanteG = (float)(rand() % 100) / 100.0f;
    colorOscilanteB = (float)(rand() % 100) / 100.0f;

    // Inicializar seleccion como vacia
    filaSeleccionada = -1;
    colSeleccionada = -1;
    haySeleccion = false;

    inicializarCasillas();
}

//DESTRUCTOR
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

// INICIALIZAR CASILLAS
void Tablero::inicializarCasillas() {
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

    /* for (int i = 0; i < 5; i++) {
        int f = puntosPoder[i][0];
        int c = puntosPoder[i][1];
        // El estado sigue el patron ajedrez normal
        EstadoCasilla estadoInicial;
        if ((f + c) % 2 == 0) {
            estadoInicial = EstadoCasilla::CLARA;
        }
        else {
            estadoInicial = EstadoCasilla::OSCURA;
        }
        tablero[f][c] = Casilla(TipoCasilla::PUNTO_DE_PODER, estadoInicial);
    }*/

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

//DIBUJAR
// Recibe el turno actual para colorear el marco
void Tablero::dibujar(Bando turno) {
    // Primero el marco (cambia segun el turno)
    dibujarMarco(turno);

    // Luego las casillas
    dibujarCasillas();

    // Luego las cruces de los puntos de poder (encima de las casillas)
    dibujarPuntosDePoder();

    // Las casillas validas y la pieza seleccionada (encima de todo menos piezas)
    dibujarSeleccion();

    // Por ultimo las piezas
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            if (casillas[f][c] != nullptr && casillas[f][c]->getEstaViva()) {
                casillas[f][c]->dibujar();
            }
        }
    }
}

void Tablero::dibujarSeleccion() {
    if (!haySeleccion) return;

    // Dibujar la pieza seleccionada con un borde brillante
    float x = offsetX + colSeleccionada * tamCasilla;
    float y = offsetY + filaSeleccionada * tamCasilla;

    glColor3f(1.0f, 1.0f, 0.0f); // Amarillo brillante
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x, y, 0.1f);
    glVertex3f(x + tamCasilla, y, 0.1f);
    glVertex3f(x + tamCasilla, y + tamCasilla, 0.1f);
    glVertex3f(x, y + tamCasilla, 0.1f);
    glEnd();
    glLineWidth(1.0f);

    // Dibujar las casillas validas en verde semitransparente
    for (int i = 0; i < casillasValidas.size(); i++) {
        float xv = offsetX + casillasValidas[i].col * tamCasilla;
        float yv = offsetY + casillasValidas[i].fila * tamCasilla;

        glColor3f(0.0f, 0.8f, 0.0f); // Verde
        glBegin(GL_QUADS);
        glVertex3f(xv + 0.05f, yv + 0.05f, 0.1f);
        glVertex3f(xv + tamCasilla - 0.05f, yv + 0.05f, 0.1f);
        glVertex3f(xv + tamCasilla - 0.05f, yv + tamCasilla - 0.05f, 0.1f);
        glVertex3f(xv + 0.05f, yv + tamCasilla - 0.05f, 0.1f);
        glEnd();
    }
}

// DIBUJAR MARCO
// Amarillo si es turno de LUZ, morado si es de OSCURIDAD
void Tablero::dibujarMarco(Bando turno) {
    if (turno == Bando::LUZ) {
        glColor3f(1.0f, 0.85f, 0.0f); // Amarillo
    }
    else {
        glColor3f(0.5f, 0.0f, 0.8f);  // Morado
    }

    float margen = 0.3f;
    float x0 = offsetX - margen;
    float y0 = offsetY - margen;
    float x1 = offsetX + 9.0f * tamCasilla + margen;
    float y1 = offsetY + 9.0f * tamCasilla + margen;

    glBegin(GL_QUADS);
    glVertex3f(x0, y0, 0.0f);
    glVertex3f(x1, y0, 0.0f);
    glVertex3f(x1, y1, 0.0f);
    glVertex3f(x0, y1, 0.0f);
    glEnd();
}

// DIBUJAR CASILLAS
void Tablero::dibujarCasillas() {
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            float x = offsetX + c * tamCasilla;
            float y = offsetY + f * tamCasilla;

            if (tablero[f][c].getTipo() == TipoCasilla::OSCILANTE) {
                // Color aleatorio que cambia cada turno
                glColor3f(colorOscilanteR, colorOscilanteG, colorOscilanteB);
            }
            else {
                // Normales: blanco y negro
                if (tablero[f][c].getEstado() == EstadoCasilla::CLARA) {
                    glColor3f(0.95f, 0.95f, 0.95f);
                }
                else {
                    glColor3f(0.08f, 0.08f, 0.08f);
                }
            }

            glBegin(GL_QUADS);
            glVertex3f(x, y, 0.0f);
            glVertex3f(x + tamCasilla, y, 0.0f);
            glVertex3f(x + tamCasilla, y + tamCasilla, 0.0f);
            glVertex3f(x, y + tamCasilla, 0.0f);
            glEnd();

            //Linea negra fina
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

// DIBUJAR PUNTOS DE PODER
// Se dibuja una cruz encima de la casilla
void Tablero::dibujarPuntosDePoder() {
    glColor3f(0.0f, 0.8f, 0.0f); // Verde para la cruz como positivos

    for (int i = 0; i < 5; i++) {
        int f = puntosPoder[i][0];
        int c = puntosPoder[i][1];

        float x = offsetX + c * tamCasilla;
        float y = offsetY + f * tamCasilla;
        float cx = x + tamCasilla * 0.5f; // Centro de la casilla
        float cy = y + tamCasilla * 0.5f;
        float grosor = tamCasilla * 0.15f; // Grosor del brazo de la cruz
        float largo = tamCasilla * 0.4f;   // Largo del brazo de la cruz

        // Brazo horizontal
        glBegin(GL_QUADS);
        glVertex3f(cx - largo, cy - grosor, 0.01f);
        glVertex3f(cx + largo, cy - grosor, 0.01f);
        glVertex3f(cx + largo, cy + grosor, 0.01f);
        glVertex3f(cx - largo, cy + grosor, 0.01f);
        glEnd();

        // Brazo vertical
        glBegin(GL_QUADS);
        glVertex3f(cx - grosor, cy - largo, 0.01f);
        glVertex3f(cx + grosor, cy - largo, 0.01f);
        glVertex3f(cx + grosor, cy + largo, 0.01f);
        glVertex3f(cx - grosor, cy + largo, 0.01f);
        glEnd();
    }
}

// GESTION DE PIEZAS
void Tablero::colocarPieza(Pieza* pieza, int fila, int col) {
    if (fila < 0 || fila >= 9 || col < 0 || col >= 9) return;
    if (casillas[fila][col] != nullptr) return;

    casillas[fila][col] = pieza;
    pieza->setPosicion(fila, col);
    tablero[fila][col].setOcupada(true);
}

bool Tablero::moverPieza(int filaOrigen, int colOrigen, int filaDest, int colDest) {
    if (filaOrigen < 0 || filaOrigen >= 9 || colOrigen < 0 || colOrigen >= 9) return false;
    if (filaDest < 0 || filaDest >= 9 || colDest < 0 || colDest >= 9) return false;

    Pieza* pieza = casillas[filaOrigen][colOrigen];
    if (pieza == nullptr) return false;

    Pieza* piezaDestino = casillas[filaDest][colDest];
    if (piezaDestino != nullptr && piezaDestino->getBando() == pieza->getBando()) {
        return false;
    }

    casillas[filaOrigen][colOrigen] = nullptr;
    tablero[filaOrigen][colOrigen].setOcupada(false);

    casillas[filaDest][colDest] = pieza;
    pieza->setPosicion(filaDest, colDest);
    tablero[filaDest][colDest].setOcupada(true);

    return true;
}

bool Tablero::hayEnemigo(int fila, int col, Bando bandoActual) {
    if (casillas[fila][col] == nullptr) return false;
    return casillas[fila][col]->getBando() != bandoActual;
}

void Tablero::eliminarPieza(int fila, int col) {
    if (casillas[fila][col] != nullptr) {
        delete casillas[fila][col];
        casillas[fila][col] = nullptr;
        tablero[fila][col].setOcupada(false);
    }
}

// CONDICIONES DE VICTORIA
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

// ACTUALIZACION
void Tablero::actualizar(float dt) {
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            tablero[f][c].actualizar(dt);
        }
    }

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

bool Tablero::pantallaATablero(float px, float py, int& filaOut, int& colOut) {
    colOut = (int)((px - offsetX) / tamCasilla);
    filaOut = (int)((py - offsetY) / tamCasilla);

    if (filaOut < 0 || filaOut >= 9 || colOut < 0 || colOut >= 9) {
        return false;
    }
    return true;
}

// SELECCION DE PIEZAS
// Selecciona una pieza si pertenece al bando que tiene el turno
void Tablero::seleccionarPieza(int fila, int col, Bando turno) {
    Pieza* pieza = casillas[fila][col];

    if (pieza == nullptr || pieza->getBando() != turno) return;

    filaSeleccionada = fila;
    colSeleccionada = col;
    haySeleccion = true;

    // Calcular casillas validas para esta pieza
    bool ocupadas[9][9];
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            ocupadas[f][c] = (casillas[f][c] != nullptr);
        }
    }
    casillasValidas = pieza->getCasillasValidas(ocupadas);
}

// Deselecciona la pieza actual
void Tablero::deseleccionar() {
    haySeleccion = false;
    filaSeleccionada = -1;
    colSeleccionada = -1;
    casillasValidas.clear();
}

// Comprueba si una casilla esta entre las validas para moverse
bool Tablero::destinoEsValido(int fila, int col) {
    for (int i = 0; i < casillasValidas.size(); i++) {
        if (casillasValidas[i].fila == fila && casillasValidas[i].col == col) {
            return true;
        }
    }
    return false;
}

// Mueve la pieza seleccionada al destino indicado
bool Tablero::moverPiezaSeleccionada(int filaDest, int colDest) {
    return moverPieza(filaSeleccionada, colSeleccionada, filaDest, colDest);
}

// Devuelve si hay alguna pieza seleccionada
bool Tablero::tieneSeleccion() const {
    return haySeleccion;
}

int Tablero::getFilaSeleccionada() const { return filaSeleccionada; }
int Tablero::getColSeleccionada() const { return colSeleccionada; }
