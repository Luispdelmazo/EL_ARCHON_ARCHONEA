#include "Batalla.h"
#include <GL/glut.h>

// Limites de la arena de combate
const float Batalla::ARENA_MIN = -4.5f;
const float Batalla::ARENA_MAX = 4.5f;

// CONSTRUCTOR
Batalla::Batalla()
    : atacante(nullptr), defensor(nullptr),
    xAtacante(-3.0f), yAtacante(0.0f),
    xDefensor(3.0f), yDefensor(0.0f),
    vxAtacante(0.0f), vyAtacante(0.0f),
    vxDefensor(0.0f), vyDefensor(0.0f),
    timerAtaqueAtacante(0.0f),
    timerAtaqueDefensor(0.0f),
    estado(EstadoBatalla::EN_CURSO)
{
}

// INICIAR
void Batalla::iniciar(Pieza* atac, Pieza* def) {
    atacante = atac;
    defensor = def;
    estado = EstadoBatalla::EN_CURSO;

    // Colocar las piezas en lados opuestos de la arena
    xAtacante = ARENA_MIN + 1.0f;
    yAtacante = 0.0f;
    xDefensor = ARENA_MAX - 1.0f;
    yDefensor = 0.0f;

    // Velocidades a 0 al empezar
    vxAtacante = vyAtacante = 0.0f;
    vxDefensor = vyDefensor = 0.0f;

    // Reiniciar timers de ataque
    timerAtaqueAtacante = 0.0f;
    timerAtaqueDefensor = 0.0f;
}

// DIBUJAR
// Miguel dijo: cada clase sabe dibujarse a si misma
// Batalla dibuja: fondo arena + barras de vida + piezas
void Batalla::dibujar() {
    dibujarArena();
    dibujarBarrasDeVida();
    dibujarPiezas();
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
    glBegin(GL_LINE_LOOP);
    glVertex3f(ARENA_MIN, ARENA_MIN, 0.0f);
    glVertex3f(ARENA_MAX, ARENA_MIN, 0.0f);
    glVertex3f(ARENA_MAX, ARENA_MAX, 0.0f);
    glVertex3f(ARENA_MIN, ARENA_MAX, 0.0f);
    glEnd();
}

void Batalla::dibujarBarrasDeVida() {
    if (atacante == nullptr || defensor == nullptr) return;

    // Barra de vida del atacante (bando LUZ, azul, izquierda)
    float porcentajeAtacante = (float)atacante->getVidaActual() / (float)atacante->getVidaMax();
    // Fondo de la barra (gris)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex3f(-4.5f, 3.8f, 0.0f);
    glVertex3f(-0.5f, 3.8f, 0.0f);
    glVertex3f(-0.5f, 4.2f, 0.0f);
    glVertex3f(-4.5f, 4.2f, 0.0f);
    glEnd();
    // Vida actual (azul para luz)
    glColor3f(0.0f, 0.4f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-4.5f, 3.8f, 0.0f);
    glVertex3f(-4.5f + 4.0f * porcentajeAtacante, 3.8f, 0.0f);
    glVertex3f(-4.5f + 4.0f * porcentajeAtacante, 4.2f, 0.0f);
    glVertex3f(-4.5f, 4.2f, 0.0f);
    glEnd();
    //Barra de vida del defensor (bando OSCURIDAD, rojo, derecha) 
    float porcentajeDefensor = (float)defensor->getVidaActual() / (float)defensor->getVidaMax();
    // Fondo de la barra (gris)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex3f(0.5f, 3.8f, 0.0f);
    glVertex3f(4.5f, 3.8f, 0.0f);
    glVertex3f(4.5f, 4.2f, 0.0f);
    glVertex3f(0.5f, 4.2f, 0.0f);
    glEnd();

    // Vida actual (rojo para oscuridad)
    glColor3f(1.0f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(4.5f, 3.8f, 0.0f);
    glVertex3f(4.5f - 4.0f * porcentajeDefensor, 3.8f, 0.0f);
    glVertex3f(4.5f - 4.0f * porcentajeDefensor, 4.2f, 0.0f);
    glVertex3f(4.5f, 4.2f, 0.0f);
    glEnd();
}

void Batalla::dibujarPiezas() {
    if (atacante == nullptr || defensor == nullptr) return;

    // Dibujar atacante (bando LUZ, azul)
    glPushMatrix();
    glTranslatef(xAtacante, yAtacante, 0.0f);
    glColor3f(0.2f, 0.4f, 1.0f);
    glutSolidSphere(0.4f, 20, 20);
    glPopMatrix();

    // Dibujar defensor (bando OSCURIDAD, rojo)
    glPushMatrix();
    glTranslatef(xDefensor, yDefensor, 0.0f);
    glColor3f(1.0f, 0.1f, 0.1f);
    glutSolidSphere(0.4f, 20, 20);
    glPopMatrix();
}

// ACTUALIZAR
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

    // Actualizar timers de ataque
    timerAtaqueAtacante += dt;
    timerAtaqueDefensor += dt;

    // La IA mueve al defensor
    moverIA(dt);

    // Comprobar si hay ataques
    comprobarAtaques();

    // Comprobar si ha terminado la batalla
    comprobarFinBatalla();
}

// IA DEL DEFENSOR
// El defensor se mueve hacia el atacante automaticamente
void Batalla::moverIA(float dt) {
    if (defensor == nullptr) return;
    // Calcular direccion hacia el atacante
    float dx = xAtacante - xDefensor;
    float dy = yAtacante - yDefensor;
    // Normalizar la direccion
    float distancia = sqrtf(dx * dx + dy * dy);
    if (distancia > 0.5f) { // Solo se mueve si no esta demasiado cerca
        dx /= distancia;
        dy /= distancia;
        xDefensor += dx * dt * defensor->getVelocidad() * 0.5f;
        yDefensor += dy * dt * defensor->getVelocidad() * 0.5f;
    }
    // Limitar al defensor dentro de la arena
    if (xDefensor < ARENA_MIN + 0.4f) xDefensor = ARENA_MIN + 0.4f;
    if (xDefensor > ARENA_MAX - 0.4f) xDefensor = ARENA_MAX - 0.4f;
    if (yDefensor < ARENA_MIN + 0.4f) yDefensor = ARENA_MIN + 0.4f;
    if (yDefensor > ARENA_MAX - 0.4f) yDefensor = ARENA_MAX - 0.4f;
}


// COMPROBAR ATAQUES
// Si las dos piezas estan cerca, se hacen daño
// El intervalo entre ataques depende de la velocidad de ataque de cada pieza
void Batalla::comprobarAtaques() {
    float dx = xAtacante - xDefensor;
    float dy = yAtacante - yDefensor;
    float distancia = sqrtf(dx * dx + dy * dy);
    // Intervalo entre ataques (cuanto menor sea la velocidad, mas tarda)
    float intervaloAtaque = 1.0f; // 1 segundo entre ataques por defecto
    // Si estan suficientemente cerca, pueden atacarse
    if (distancia < (float)atacante->getAlcanceAtaque()) {
        if (timerAtaqueAtacante >= intervaloAtaque) {
            // El atacante golpea al defensor
            defensor->recibirDano(atacante->getAtaque());
            timerAtaqueAtacante = 0.0f;
        }
    }

    if (distancia < (float)defensor->getAlcanceAtaque()) {
        if (timerAtaqueDefensor >= intervaloAtaque) {
            // El defensor golpea al atacante
            atacante->recibirDano(defensor->getAtaque());
            timerAtaqueDefensor = 0.0f;
        }
    }
}

// COMPROBAR FIN DE BATALLA
void Batalla::comprobarFinBatalla() {
    if (atacante == nullptr || defensor == nullptr) return;

    if (!atacante->getEstaViva() && !defensor->getEstaViva()) {
        // Empate: gana el defensor (el que estaba en la casilla)
        estado = EstadoBatalla::GANA_OSCURIDAD;
    }
    else if (!atacante->getEstaViva()) {
        estado = EstadoBatalla::GANA_OSCURIDAD;
    }
    else if (!defensor->getEstaViva()) {
        estado = EstadoBatalla::GANA_LUZ;
    }
}

// GESTION TECLADO
// WASD para mover al atacante (bando LUZ)
void Batalla::gestionTeclado(unsigned char tecla) {
    if (estado != EstadoBatalla::EN_CURSO) return;

    // Velocidad de movimiento normalizada (el getVelocidad() ya lo escala en actualizar)
    switch (tecla) {
    case 'w': vyAtacante = 1.0f; break; // Arriba
    case 's': vyAtacante = -1.0f; break; // Abajo
    case 'a': vxAtacante = -1.0f; break; // Izquierda
    case 'd': vxAtacante = 1.0f; break; // Derecha

        // Al soltar (velocidad a 0) - se haria con glutKeyboardUpFunc
        // Por ahora paramos al llegar a los limites
    }
}