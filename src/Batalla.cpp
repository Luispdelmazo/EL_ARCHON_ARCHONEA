#include "Batalla.h"
#include <GL/glut.h>

// Limites de la arena de combate
const float Batalla::ARENA_MIN = -4.5f;
const float Batalla::ARENA_MAX =  4.5f;

// CONSTRUCTOR
Batalla::Batalla()
    : atacante(nullptr), defensor(nullptr),
    xAtacante(-3.0f), yAtacante(0.0f),
    xDefensor( 3.0f), yDefensor(0.0f),
    vxAtacante(0.0f), vyAtacante(0.0f),
    vxDefensor(0.0f), vyDefensor(0.0f),
    timerAtaqueAtacante(0.0f),
    timerAtaqueDefensor(0.0f),
    puedeAtacarAtacante(false),
    estado(EstadoBatalla::EN_CURSO),
    dificultad(DificultadIA::MEDIO)
{}

// INICIAR
void Batalla::iniciar(Pieza* atac, Pieza* def) {
    atacante = atac;
    defensor = def;
    estado   = EstadoBatalla::EN_CURSO;

    // Colocar las piezas en lados opuestos de la arena
    xAtacante = ARENA_MIN + 1.0f;
    yAtacante = 0.0f;
    xDefensor = ARENA_MAX - 1.0f;
    yDefensor = 0.0f;

    // Velocidades a 0 al empezar
    vxAtacante = vyAtacante = 0.0f;
    vxDefensor = vyDefensor = 0.0f;

    // Reiniciar timers y estado de ataque
    timerAtaqueAtacante = 0.0f;
    timerAtaqueDefensor = 0.0f;
    puedeAtacarAtacante = false;

    // Colocar piedras en posiciones fijas - igual que en el Archon original
    // Dos columnas de tres piedras a cada lado del centro
    piedras[0] = { -2.0f,  1.5f };
    piedras[1] = { -2.0f, -1.5f };
    piedras[2] = { -2.0f,  0.0f };
    piedras[3] = {  2.0f,  1.5f };
    piedras[4] = {  2.0f, -1.5f };
    piedras[5] = {  2.0f,  0.0f };
}

// DIBUJAR
// Miguel dijo: cada clase sabe dibujarse a si misma
void Batalla::dibujar() {
    dibujarArena();
    dibujarPiedras();      // Las piedras van encima del fondo
    dibujarBarrasDeVida();
    dibujarPiezas();       // Las piezas van encima de todo
}

void Batalla::dibujarArena() {
    // Fondo oscuro de la arena de combate
    glColor3f(0.05f, 0.05f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(ARENA_MIN, ARENA_MIN, 0.0f);
    glVertex3f(ARENA_MAX, ARENA_MIN, 0.0f);
    glVertex3f(ARENA_MAX, ARENA_MAX, 0.0f);
    glVertex3f(ARENA_MIN, ARENA_MAX, 0.0f);
    glEnd();

    // Borde de la arena
    glColor3f(0.8f, 0.8f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(ARENA_MIN, ARENA_MIN, 0.0f);
    glVertex3f(ARENA_MAX, ARENA_MIN, 0.0f);
    glVertex3f(ARENA_MAX, ARENA_MAX, 0.0f);
    glVertex3f(ARENA_MIN, ARENA_MAX, 0.0f);
    glEnd();
    glLineWidth(1.0f);

    // Mostrar dificultad en pantalla
    glColor3f(0.5f, 0.5f, 0.5f);
    glRasterPos2f(-4.3f, -4.0f);
    std::string textoNivel;
    if      (dificultad == DificultadIA::FACIL)  textoNivel = "Nivel: FACIL";
    else if (dificultad == DificultadIA::MEDIO)  textoNivel = "Nivel: MEDIO";
    else                                          textoNivel = "Nivel: DIFICIL";
    for (int i = 0; i < textoNivel.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, textoNivel[i]);
    }

    // Instrucciones de control
    glRasterPos2f(-1.0f, -4.0f);
    std::string textoControles = "WASD mover | F atacar";
    for (int i = 0; i < textoControles.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, textoControles[i]);
    }
}

void Batalla::dibujarPiedras() {
    for (int i = 0; i < NUM_PIEDRAS; i++) {
        glPushMatrix();
        glTranslatef(piedras[i].x, piedras[i].y, 0.0f);

        // Piedra gris oscura - cubo solido
        glColor3f(0.4f, 0.4f, 0.4f);
        glutSolidCube(0.5f);

        // Borde mas oscuro para que parezca piedra de verdad
        glColor3f(0.2f, 0.2f, 0.2f);
        glLineWidth(2.0f);
        glutWireCube(0.52f);
        glLineWidth(1.0f);

        glPopMatrix();
    }
}

void Batalla::dibujarBarrasDeVida() {
    if (atacante == nullptr || defensor == nullptr) return;

    // Barra de vida del atacante (izquierda)
    float porcAtacante = (float)atacante->getVidaActual() / (float)atacante->getVidaMax();

    // Fondo gris
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex3f(-4.5f, 3.8f, 0.0f);
    glVertex3f(-0.5f, 3.8f, 0.0f);
    glVertex3f(-0.5f, 4.2f, 0.0f);
    glVertex3f(-4.5f, 4.2f, 0.0f);
    glEnd();

    // Vida actual - azul para el atacante
    glColor3f(0.0f, 0.4f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-4.5f,                    3.8f, 0.0f);
    glVertex3f(-4.5f + 4.0f * porcAtacante, 3.8f, 0.0f);
    glVertex3f(-4.5f + 4.0f * porcAtacante, 4.2f, 0.0f);
    glVertex3f(-4.5f,                    4.2f, 0.0f);
    glEnd();

    // Nombre del atacante
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-4.3f, 4.3f);
    std::string nombreAtacante = atacante->getNombre();
    for (int i = 0; i < nombreAtacante.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, nombreAtacante[i]);
    }

    // Barra de vida del defensor (derecha)
    float porcDefensor = (float)defensor->getVidaActual() / (float)defensor->getVidaMax();

    // Fondo gris
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex3f(0.5f, 3.8f, 0.0f);
    glVertex3f(4.5f, 3.8f, 0.0f);
    glVertex3f(4.5f, 4.2f, 0.0f);
    glVertex3f(0.5f, 4.2f, 0.0f);
    glEnd();

    // Vida actual - rojo para el defensor
    glColor3f(1.0f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(4.5f,                     3.8f, 0.0f);
    glVertex3f(4.5f - 4.0f * porcDefensor, 3.8f, 0.0f);
    glVertex3f(4.5f - 4.0f * porcDefensor, 4.2f, 0.0f);
    glVertex3f(4.5f,                     4.2f, 0.0f);
    glEnd();

    // Nombre del defensor
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(2.0f, 4.3f);
    std::string nombreDefensor = defensor->getNombre();
    for (int i = 0; i < nombreDefensor.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, nombreDefensor[i]);
    }

    // Circulo verde cuando el jugador puede atacar con F
    if (puedeAtacarAtacante) {
        glColor3f(0.0f, 1.0f, 0.0f);
        glPushMatrix();
        glTranslatef(-4.3f, 3.5f, 0.1f);
        glutSolidSphere(0.1f, 10, 10);
        glPopMatrix();

        glColor3f(0.0f, 1.0f, 0.0f);
        glRasterPos2f(-4.1f, 3.45f);
        std::string textoF = "F";
        for (int i = 0; i < textoF.size(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, textoF[i]);
        }
    }
}

void Batalla::dibujarPiezas() {
    if (atacante == nullptr || defensor == nullptr) return;

    // Atacante - azul
    glPushMatrix();
    glTranslatef(xAtacante, yAtacante, 0.0f);
    glColor3f(0.2f, 0.4f, 1.0f);
    glutSolidSphere(0.4f, 20, 20);
    glPopMatrix();

    // Defensor - rojo
    glPushMatrix();
    glTranslatef(xDefensor, yDefensor, 0.0f);
    glColor3f(1.0f, 0.1f, 0.1f);
    glutSolidSphere(0.4f, 20, 20);
    glPopMatrix();
}

// ACTUALIZAR - igual que Mundo::mueve en el Pang
void Batalla::actualizar(float dt) {
    if (estado != EstadoBatalla::EN_CURSO) return;
    if (atacante == nullptr || defensor == nullptr) return;

    // Mover el atacante segun su velocidad
    xAtacante += vxAtacante * dt * atacante->getVelocidad();
    yAtacante += vyAtacante * dt * atacante->getVelocidad();

    // Limitar al atacante dentro de la arena
    if (xAtacante < ARENA_MIN + 0.4f) xAtacante = ARENA_MIN + 0.4f;
    if (xAtacante > ARENA_MAX - 0.4f) xAtacante = ARENA_MAX - 0.4f;
    if (yAtacante < ARENA_MIN + 0.4f) yAtacante = ARENA_MIN + 0.4f;
    if (yAtacante > ARENA_MAX - 0.4f) yAtacante = ARENA_MAX - 0.4f;

    // Actualizar timers
    timerAtaqueAtacante += dt;
    timerAtaqueDefensor += dt;

    // Cuando se carga el timer el jugador puede atacar con F
    float intervaloAtaque = 1.0f;
    if (timerAtaqueAtacante >= intervaloAtaque) {
        puedeAtacarAtacante = true;
    }

    // Comprobar colisiones con las piedras
    comprobarColisionesPiedras();

    // La IA mueve al defensor
    moverIA(dt);

    // La IA ataca automaticamente
    comprobarAtaques(false);

    comprobarFinBatalla();
}

// COLISIONES CON PIEDRAS
// Las piedras bloquean el movimiento - sirven de escudo
void Batalla::comprobarColisionesPiedras() {
    for (int i = 0; i < NUM_PIEDRAS; i++) {
        // Colision del atacante con la piedra
        float dxA = xAtacante - piedras[i].x;
        float dyA = yAtacante - piedras[i].y;
        float distA = sqrtf(dxA * dxA + dyA * dyA);
        if (distA < 0.5f && distA > 0.01f) {
            float nx = dxA / distA;
            float ny = dyA / distA;
            xAtacante = piedras[i].x + nx * 0.5f;
            yAtacante = piedras[i].y + ny * 0.5f;
        }

        // Colision del defensor con la piedra
        float dxD = xDefensor - piedras[i].x;
        float dyD = yDefensor - piedras[i].y;
        float distD = sqrtf(dxD * dxD + dyD * dyD);
        if (distD < 0.5f && distD > 0.01f) {
            float nx = dxD / distD;
            float ny = dyD / distD;
            xDefensor = piedras[i].x + nx * 0.5f;
            yDefensor = piedras[i].y + ny * 0.5f;
        }
    }
}

// IA DEL DEFENSOR
// Tres niveles de dificultad que cambian velocidad e intervalo de ataque
void Batalla::moverIA(float dt) {
    if (defensor == nullptr) return;

    // Parametros segun dificultad
    float multiplicadorVelocidad;
    float intervaloAtaqueIA;

    if (dificultad == DificultadIA::FACIL) {
        multiplicadorVelocidad = 0.2f; // Muy lenta
        intervaloAtaqueIA      = 2.0f; // Ataca cada 2 segundos
    }
    else if (dificultad == DificultadIA::MEDIO) {
        multiplicadorVelocidad = 0.5f; // Normal
        intervaloAtaqueIA      = 1.0f; // Ataca cada 1 segundo
    }
    else { // DIFICIL
        multiplicadorVelocidad = 0.9f; // Muy rapida
        intervaloAtaqueIA      = 0.5f; // Ataca cada medio segundo
    }

    float dx = xAtacante - xDefensor;
    float dy = yAtacante - yDefensor;
    float distancia = sqrtf(dx * dx + dy * dy);

    // En dificil mantiene distancia para atacar desde lejos
    float distanciaMinima = (dificultad == DificultadIA::DIFICIL) ? 1.5f : 0.5f;

    if (distancia > distanciaMinima) {
        dx /= distancia;
        dy /= distancia;
        xDefensor += dx * dt * defensor->getVelocidad() * multiplicadorVelocidad;
        yDefensor += dy * dt * defensor->getVelocidad() * multiplicadorVelocidad;
    }

    // Limitar al defensor dentro de la arena
    if (xDefensor < ARENA_MIN + 0.4f) xDefensor = ARENA_MIN + 0.4f;
    if (xDefensor > ARENA_MAX - 0.4f) xDefensor = ARENA_MAX - 0.4f;
    if (yDefensor < ARENA_MIN + 0.4f) yDefensor = ARENA_MIN + 0.4f;
    if (yDefensor > ARENA_MAX - 0.4f) yDefensor = ARENA_MAX - 0.4f;

    // La IA ataca automaticamente cuando puede
    if (timerAtaqueDefensor >= intervaloAtaqueIA) {
        float dx2 = xAtacante - xDefensor;
        float dy2 = yAtacante - yDefensor;
        float dist2 = sqrtf(dx2 * dx2 + dy2 * dy2);
        if (dist2 < (float)defensor->getAlcanceAtaque()) {
            atacante->recibirDano(defensor->getAtaque());
            timerAtaqueDefensor = 0.0f;
        }
    }
}

// COMPROBAR ATAQUES
// jugadorAtaca = true cuando el jugador pulsa F
// jugadorAtaca = false cuando lo llama la IA
void Batalla::comprobarAtaques(bool jugadorAtaca) {
    float dx = xAtacante - xDefensor;
    float dy = yAtacante - yDefensor;
    float distancia = sqrtf(dx * dx + dy * dy);

    // Ataque del jugador - solo si pulso F y esta cargado y cerca
    if (jugadorAtaca && puedeAtacarAtacante) {
        if (distancia < (float)atacante->getAlcanceAtaque()) {
            defensor->recibirDano(atacante->getAtaque());
            timerAtaqueAtacante = 0.0f;
            puedeAtacarAtacante = false; // Resetear hasta que se cargue
        }
    }
}

// COMPROBAR FIN DE BATALLA
void Batalla::comprobarFinBatalla() {
    if (atacante == nullptr || defensor == nullptr) return;

    if (!atacante->getEstaViva() && !defensor->getEstaViva()) {
        estado = EstadoBatalla::GANA_DEFENSOR; // Empate: gana el defensor
    }
    else if (!atacante->getEstaViva()) {
        estado = EstadoBatalla::GANA_DEFENSOR;
    }
    else if (!defensor->getEstaViva()) {
        estado = EstadoBatalla::GANA_ATACANTE;
    }
}

// GESTION TECLADO
// WASD para mover, F para atacar cuando este cargado
void Batalla::gestionTeclado(unsigned char tecla) {
    if (estado != EstadoBatalla::EN_CURSO) return;

    switch (tecla) {
    case 'w': vyAtacante =  1.0f; break;
    case 's': vyAtacante = -1.0f; break;
    case 'a': vxAtacante = -1.0f; break;
    case 'd': vxAtacante =  1.0f; break;
    case 'f': // F para atacar cuando el circulo este verde
        comprobarAtaques(true);
        break;
    }
}

// Para parar la pieza cuando se suelta la tecla
void Batalla::gestionTecladoSuelto(unsigned char tecla) {
    switch (tecla) {
    case 'w': case 's': vyAtacante = 0.0f; break;
    case 'a': case 'd': vxAtacante = 0.0f; break;
    }
}
