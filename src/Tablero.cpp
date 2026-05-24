#include "Tablero.h"
#include "ETSIDI.h"
#include <cstdlib>

void Tablero::cambiarColorOscilantes() {
    colorOscilanteR = (float)(rand() % 100) / 100.0f;
    colorOscilanteG = (float)(rand() % 100) / 100.0f;
    colorOscilanteB = (float)(rand() % 100) / 100.0f;
}

// CONSTRUCTOR
Tablero::Tablero(float tamCasilla, float ox, float oy)
    : tamCasilla(tamCasilla), offsetX(ox), offsetY(oy)
{
    // Inicializar las dos matrices a nullptr
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            piezas[f][c] = nullptr;
            casillas[f][c]  = nullptr;
        }
    }

    // Posiciones de los 5 puntos de poder - igual que en el Archon original
    puntosPoder[0][0] = 4; puntosPoder[0][1] = 4; // Centro
    puntosPoder[1][0] = 0; puntosPoder[1][1] = 4; // Borde superior
    puntosPoder[2][0] = 8; puntosPoder[2][1] = 4; // Borde inferior
    puntosPoder[3][0] = 4; puntosPoder[3][1] = 0; // Borde izquierdo
    puntosPoder[4][0] = 4; puntosPoder[4][1] = 8; // Borde derecho

    // Color inicial aleatorio para las oscilantes
    colorOscilanteR = (float)(rand() % 100) / 100.0f;
    colorOscilanteG = (float)(rand() % 100) / 100.0f;
    colorOscilanteB = (float)(rand() % 100) / 100.0f;

    filaSeleccionada = -1;
    colSeleccionada  = -1;
    haySeleccion     = false;

    inicializarCasillas();
}

// DESTRUCTOR
// Libera la memoria de las dos matrices - como destruir_contenido en el Pang
Tablero::~Tablero() {
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            // Eliminar piezas
            if (piezas[f][c] != nullptr) {
                delete piezas[f][c];
                piezas[f][c] = nullptr;
            }
            // Eliminar casillas - ahora son punteros
            if (casillas[f][c] != nullptr) {
                delete casillas[f][c];
                casillas[f][c] = nullptr;
            }
        }
    }
}

// INICIALIZAR CASILLAS
// Ahora usamos new para crear cada tipo de casilla
// Igual que en el Pang se creaban esferas con new Esfera(...)
void Tablero::inicializarCasillas() {
    // Patron de casillas oscilantes - forma de cruz/X
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

    // Saber si es punto de poder
    bool esPuntoPoder[9][9] = {};
    for (int i = 0; i < 5; i++) {
        esPuntoPoder[puntosPoder[i][0]][puntosPoder[i][1]] = true;
    }

    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            EstadoCasilla estadoInicial;
            if ((f + c) % 2 == 0) {
				if (c < 4) {
					estadoInicial = EstadoCasilla::CLARA;
				}
				else {
					estadoInicial = EstadoCasilla::OSCURA;
				}
            }
            else {
                if (c < 4) {
                    estadoInicial = EstadoCasilla::OSCURA;
                }
                else {
                    estadoInicial = EstadoCasilla::CLARA;
                }
            }

            // Crear el tipo de casilla correcto con new
            // Polimorfismo igual que en el Pang con Esfera y EsferaPulsante
            if (esPuntoPoder[f][c]) {
                casillas[f][c] = new PuntoDePoder(estadoInicial);
            } else if (esOscilante[f][c]) {
                casillas[f][c] = new CasillaOscilante(estadoInicial, 5.0f);
            } else {
                casillas[f][c] = new Casilla(TipoCasilla::NORMAL, estadoInicial);
            }
        }
    }
}

// DIBUJAR
// Recibe el turno actual para colorear el marco
void Tablero::dibujar(Bando turno) {
    dibujarMarco(turno);
    dibujarCasillas();
    dibujarPuntosDePoder();
    dibujarSeleccion();

    // Dibujar las piezas por encima de todo
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            if (piezas[f][c] != nullptr && piezas[f][c]->getEstaViva()) {
                piezas[f][c]->dibujar();
            }
        }
    }
}

// DIBUJAR SELECCION
// Circulo verde donde puede ir, cruz roja donde no puede
void Tablero::dibujarSeleccion() {
    if (!haySeleccion) return;

    // Borde amarillo en la pieza seleccionada
    float x = offsetX + colSeleccionada * tamCasilla;
    float y = offsetY + filaSeleccionada * tamCasilla;

    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x,              y,              0.1f);
    glVertex3f(x + tamCasilla, y,              0.1f);
    glVertex3f(x + tamCasilla, y + tamCasilla, 0.1f);
    glVertex3f(x,              y + tamCasilla, 0.1f);
    glEnd();
    glLineWidth(1.0f);

    // Para cada casilla dibujamos circulo verde o cruz roja
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            if (f == filaSeleccionada && c == colSeleccionada) continue;

            // No marcamos casillas con aliados
            if (piezas[f][c] != nullptr && piezas[filaSeleccionada][colSeleccionada] != nullptr &&
                piezas[f][c]->getBando() == piezas[filaSeleccionada][colSeleccionada]->getBando()) continue;

            float cx = offsetX + c * tamCasilla + tamCasilla * 0.5f;
            float cy = offsetY + f * tamCasilla  + tamCasilla * 0.5f;

            if (destinoEsValido(f, c)) {
                // CIRCULO VERDE - puede moverse aqui
                glColor3f(0.0f, 0.9f, 0.0f);
                float radio = tamCasilla * 0.3f;
                glBegin(GL_POLYGON);
                for (int i = 0; i < 12; i++) {
                    float angulo = i * 2.0f * 3.14159f / 12.0f;
                    glVertex3f(cx + radio * cosf(angulo),
                               cy + radio * sinf(angulo),
                               0.1f);
                }
                glEnd();
            } else {
                // CRUZ ROJA - no puede moverse aqui
                float tam = tamCasilla * 0.25f;
                glColor3f(0.9f, 0.0f, 0.0f);
                glLineWidth(2.0f);
                glBegin(GL_LINES);
                glVertex3f(cx - tam, cy - tam, 0.1f);
                glVertex3f(cx + tam, cy + tam, 0.1f);
                glVertex3f(cx + tam, cy - tam, 0.1f);
                glVertex3f(cx - tam, cy + tam, 0.1f);
                glEnd();
                glLineWidth(1.0f);
            }
        }
    }
}

// DIBUJAR MARCO
// Amarillo si es turno de LUZ, morado si es de OSCURIDAD
void Tablero::dibujarMarco(Bando turno) {
    if (turno == Bando::LUZ) {
        glColor3f(1.0f, 0.85f, 0.0f);
    } else {
        glColor3f(0.5f, 0.0f, 0.8f);
    }

    float margen = 0.3f;
    float x0 = offsetX - margen;
    float y0 = offsetY - margen;
    float x1 = offsetX + 9.0f * tamCasilla + margen;
    float y1 = offsetY + 9.0f * tamCasilla + margen;

    glBegin(GL_QUADS);
    glVertex3f(x0, y0, -0.01f);
    glVertex3f(x1, y0, -0.01f);
    glVertex3f(x1, y1, -0.01f);
    glVertex3f(x0, y1, -0.01f);
    glEnd();
}

// DIBUJAR CASILLAS
// Usamos tablero[f][c]->getTipo() con puntero - polimorfismo
void Tablero::dibujarCasillas() {
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            if (casillas[f][c] == nullptr) continue;

            float x = offsetX + c * tamCasilla;
            float y = offsetY + f * tamCasilla;

            if (casillas[f][c]->getTipo() == TipoCasilla::OSCILANTE) {
                glColor3f(colorOscilanteR, colorOscilanteG, colorOscilanteB);
            } else {
                if (casillas[f][c]->getEstado() == EstadoCasilla::CLARA) {
                    glColor3f(0.95f, 0.95f, 0.95f);
                } else {
                    glColor3f(0.08f, 0.08f, 0.08f);
                }
            }

            glBegin(GL_QUADS);
            glVertex3f(x,              y,              0.0f);
            glVertex3f(x + tamCasilla, y,              0.0f);
            glVertex3f(x + tamCasilla, y + tamCasilla, 0.0f);
            glVertex3f(x,              y + tamCasilla, 0.0f);
            glEnd();

            // Linea negra fina de separacion
            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_LINE_LOOP);
            glVertex3f(x,              y,              0.01f);
            glVertex3f(x + tamCasilla, y,              0.01f);
            glVertex3f(x + tamCasilla, y + tamCasilla, 0.01f);
            glVertex3f(x,              y + tamCasilla, 0.01f);
            glEnd();
        }
    }
}

// DIBUJAR PUNTOS DE PODER
// Cruz verde encima de la casilla
void Tablero::dibujarPuntosDePoder() {
    glColor3f(0.0f, 0.8f, 0.0f);

    for (int i = 0; i < 5; i++) {
        int f = puntosPoder[i][0];
        int c = puntosPoder[i][1];

        float x  = offsetX + c * tamCasilla;
        float y  = offsetY + f * tamCasilla;
        float cx = x + tamCasilla * 0.5f;
        float cy = y + tamCasilla * 0.5f;
        float grosor = tamCasilla * 0.15f;
        float largo  = tamCasilla * 0.4f;

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
    if (piezas[fila][col] != nullptr) return;

    piezas[fila][col] = pieza;
    pieza->setPosicion(fila, col);
    casillas[fila][col]->setOcupada(true);
}

bool Tablero::moverPieza(int filaOrigen, int colOrigen, int filaDest, int colDest) {
    if (filaOrigen < 0 || filaOrigen >= 9 || colOrigen < 0 || colOrigen >= 9) return false;
    if (filaDest   < 0 || filaDest   >= 9 || colDest   < 0 || colDest   >= 9) return false;

    Pieza* pieza = piezas[filaOrigen][colOrigen];
    if (pieza == nullptr) return false;

    Pieza* piezaDestino = piezas[filaDest][colDest];
    if (piezaDestino != nullptr && piezaDestino->getBando() == pieza->getBando()) {
        return false;
    }

    casillas[filaOrigen][colOrigen] = nullptr;
    casillas[filaOrigen][colOrigen]->setOcupada(false);

    piezas[filaDest][colDest] = pieza;
    pieza->setPosicion(filaDest, colDest);
    casillas[filaDest][colDest]->setOcupada(true);

    return true;
}

bool Tablero::hayEnemigo(int fila, int col, Bando bandoActual) {
    if (piezas[fila][col] == nullptr) return false;
    return piezas[fila][col]->getBando() != bandoActual;
}

void Tablero::eliminarPieza(int fila, int col) {
    if (piezas[fila][col] != nullptr) {
        delete piezas[fila][col];
        piezas[fila][col] = nullptr;
    }
}

// CONDICIONES DE VICTORIA
bool Tablero::controlaPuntosDePoder(Bando bando) {
    for (int i = 0; i < 5; i++) {
        int f = puntosPoder[i][0];
        int c = puntosPoder[i][1];
        Pieza* pieza = piezas[f][c];
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
            if (piezas[f][c] != nullptr && piezas[f][c]->getBando() == bando) {
                total++;
            }
        }
    }
    return total;
}

// ACTUALIZACION
// Llamamos a actualizar() de cada casilla - polimorfismo en accion
// El tablero no sabe si es CasillaOscilante o PuntoDePoder, solo llama a actualizar()
void Tablero::actualizar(float dt) {
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            if (casillas[f][c] != nullptr) {
                casillas[f][c]->actualizar(dt);
            }
        }
    }

    // Bonus de curacion para las piezas segun la casilla en la que estan
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            if (casillas[f][c] != nullptr && piezas[f][c] != nullptr) {
                float bonus = casillas[f][c]->getBonusCuracion( piezas[f][c]->getBando());
                if (bonus > 0.0f) {
                    piezas[f][c]->curar((int)(bonus * dt));
                }
            }
        }
    }
}

// GETTERS
Pieza* Tablero::getPieza(int fila, int col) {
    if (fila < 0 || fila >= 9 || col < 0 || col >= 9) return nullptr;
    return piezas[fila][col];
}

Casilla* Tablero::getCasilla(int fila, int col) {
    if (fila < 0 || fila >= 9 || col < 0 || col >= 9) return nullptr;
    return casillas[fila][col];
}

float Tablero::getTamCasilla() const { return tamCasilla; }
float Tablero::getOffsetX()    const { return offsetX; }
float Tablero::getOffsetY()    const { return offsetY; }

bool Tablero::pantallaATablero(float px, float py, int& filaOut, int& colOut) {
    colOut  = (int)((px - offsetX) / tamCasilla);
    filaOut = (int)((py - offsetY) / tamCasilla);

    if (filaOut < 0 || filaOut >= 9 || colOut < 0 || colOut >= 9) {
        return false;
    }
    return true;
}

// SELECCION DE PIEZAS
void Tablero::seleccionarPieza(int fila, int col, Bando turno) {
    Pieza* pieza = piezas[fila][col];
    if (pieza == nullptr || pieza->getBando() != turno) return;

    filaSeleccionada = fila;
    colSeleccionada  = col;
    haySeleccion     = true;

    // Calcular casillas validas para esta pieza
    bool ocupadas[9][9];
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            ocupadas[f][c] = (casillas[f][c] != nullptr);
        }
    }
    casillasValidas = pieza->getCasillasValidas(ocupadas);
}

void Tablero::deseleccionar() {
    haySeleccion     = false;
    filaSeleccionada = -1;
    colSeleccionada  = -1;
    casillasValidas.clear();
}

bool Tablero::destinoEsValido(int fila, int col) {
    for (int i = 0; i < casillasValidas.size(); i++) {
        if (casillasValidas[i].fila == fila && casillasValidas[i].col == col) {
            return true;
        }
    }
    return false;
}

bool Tablero::moverPiezaSeleccionada(int filaDest, int colDest) {
    return moverPieza(filaSeleccionada, colSeleccionada, filaDest, colDest);
}

bool Tablero::tieneSeleccion() const { return haySeleccion; }
int  Tablero::getFilaSeleccionada() const { return filaSeleccionada; }
int  Tablero::getColSeleccionada()  const { return colSeleccionada; }
