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
    estado = EstadoBatalla::EN_CURSO;

    xAtacante = ARENA_MIN + 1.0f;   // -3.5
    yAtacante = 0.0f;
    xDefensor = ARENA_MAX - 1.0f;   //  3.5
    yDefensor = 0.0f;

    // velocidades a 0 para que el atacante no se mueva solo
    vxAtacante = 0.0f;
    vyAtacante = 0.0f;
    vxDefensor = 0.0f;
    vyDefensor = 0.0f;

    // Timer ya cargado para que F funcione desde el primer momento
    timerAtaqueAtacante = 1.0f;
    timerAtaqueDefensor = 1.0f;
    puedeAtacarAtacante = true;

    // Piedras en posiciones fijas
    piedras[0] = { -2.0f,  1.5f };
    piedras[1] = { -2.0f, -1.5f };
    piedras[2] = { -2.0f,  0.0f };
    piedras[3] = { 2.0f,  1.5f };
    piedras[4] = { 2.0f, -1.5f };
    piedras[5] = { 2.0f,  0.0f };
}
// DIBUJAR
// Miguel dijo: cada clase sabe dibujarse a si misma
void Batalla::dibujar() {
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    glOrtho(-5.0, 5.0, -5.0, 6.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

    
    dibujarArena();

    dibujarPiedras();

    proyectilAtacante.dibujar();
    proyectilDefensor.dibujar();

    dibujarBarrasDeVida();
   
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    dibujarPiezas(); 

    glDisable(GL_BLEND);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void Batalla::dibujarArena() {
    //fondooscuro de la arena de combate
    glColor3f(0.05f, 0.05f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(ARENA_MIN, ARENA_MIN, 0.0f);
    glVertex3f(ARENA_MAX, ARENA_MIN, 0.0f);
    glVertex3f(ARENA_MAX, ARENA_MAX, 0.0f);
    glVertex3f(ARENA_MIN, ARENA_MAX, 0.0f);
    glEnd();

    // borde de la arena
    glColor3f(0.8f, 0.8f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(ARENA_MIN, ARENA_MIN, 0.0f);
    glVertex3f(ARENA_MAX, ARENA_MIN, 0.0f);
    glVertex3f(ARENA_MAX, ARENA_MAX, 0.0f);
    glVertex3f(ARENA_MIN, ARENA_MAX, 0.0f);
    glEnd();
    glLineWidth(1.0f);

    // mostrar dificultad en pantalla
    glColor3f(0.5f, 0.5f, 0.5f);
    glRasterPos2f(-4.3f, -4.0f);
    std::string textoNivel;
    if      (dificultad == DificultadIA::FACIL)  textoNivel = "Nivel: FACIL";
    else if (dificultad == DificultadIA::MEDIO)  textoNivel = "Nivel: MEDIO";
    else                                          textoNivel = "Nivel: DIFICIL";
    for (int i = 0; i < textoNivel.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, textoNivel[i]);
    }

    // instrucciones de control
    glRasterPos2f(-1.0f, -4.0f);
    std::string textoControles = "WASD mover | F atacar";
    for (int i = 0; i < textoControles.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, textoControles[i]);
    }
}

void Batalla::dibujarPiedras() {
    glDisable(GL_TEXTURE_2D);
    for (int i = 0; i < NUM_PIEDRAS; i++) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity(); // <--- Clave para que no se acumulen escalas
        glTranslatef(piedras[i].x, piedras[i].y, 0.0f);

        // Piedra gris
        glColor3f(0.4f, 0.4f, 0.4f);
        glutSolidCube(0.4f); // Un pelín más pequeña para que cuadre con la colisión

        // Borde oscuro
        glColor3f(0.1f, 0.1f, 0.1f);
        glLineWidth(2.0f);
        glutWireCube(0.42f);
        glLineWidth(1.0f);

        glPopMatrix();
    }
}

void Batalla::dibujarBarrasDeVida() {
    if (atacante == nullptr || defensor == nullptr) return;

    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity(); // Nos aseguramos de estar en el origen del plano 2D

    float porcAtacante = (float)atacante->getVidaActual() / (float)atacante->getVidaMax();
    float porcDefensor = (float)defensor->getVidaActual() / (float)defensor->getVidaMax();

    // fondo gris
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex3f(-4.8f, 4.7f, 0.0f);
    glVertex3f(-0.2f, 4.7f, 0.0f);
    glVertex3f(-0.2f, 5.1f, 0.0f);
    glVertex3f(-4.8f, 5.1f, 0.0f);
    glEnd();
    // vida azul
    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-4.8f, 4.7f, 0.0f);
    glVertex3f(-4.8f + 4.6f * porcAtacante, 4.7f, 0.0f);
    glVertex3f(-4.8f + 4.6f * porcAtacante, 5.1f, 0.0f);
    glVertex3f(-4.8f, 5.1f, 0.0f);
    glEnd();
    // nombre
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-4.8f, 5.2f);
    std::string nA = atacante->getNombre();
    for (int i = 0; i < (int)nA.size(); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, nA[i]);

    // BARRA DEFENSOR 
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex3f(0.2f, 4.7f, 0.0f);
    glVertex3f(4.8f, 4.7f, 0.0f);
    glVertex3f(4.8f, 5.1f, 0.0f);
    glVertex3f(0.2f, 5.1f, 0.0f);
    glEnd();
    // vidaroja (se vacía de derecha a izquierda como en el Archon)
    glColor3f(1.0f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(4.8f, 4.7f, 0.0f);
    glVertex3f(4.8f - 4.6f * porcDefensor, 4.7f, 0.0f);
    glVertex3f(4.8f - 4.6f * porcDefensor, 5.1f, 0.0f);
    glVertex3f(4.8f, 5.1f, 0.0f);
    glEnd();
    // nombre
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(0.3f, 5.2f);
    std::string nD = defensor->getNombre();
    for (int i = 0; i < (int)nD.size(); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, nD[i]);

    // indicador F verde cuando puede atacar
    if (puedeAtacarAtacante) {
        glColor3f(0.0f, 1.0f, 0.0f);
        glPushMatrix();
        glTranslatef(-4.6f, 4.4f, 0.1f);
        glutSolidSphere(0.15f, 10, 10);
        glPopMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);
        glRasterPos2f(-4.3f, 4.35f);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'F');
    }
    glPopMatrix();
}

/*void Batalla::dibujarPiezas() {
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
} */

void Batalla::dibujarPiezas() {
    if (atacante == nullptr || defensor == nullptr) return;

    // ==========================================
    // RENDERIZADO DEL ATACANTE (Luz / Alumnos)
    // ==========================================
    glPushAttrib(GL_ALL_ATTRIB_BITS); // Guardamos TODO el estado de texturas/luces/mezclas
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // 1. Lo movemos a la posición real de la arena de combate en Z = 0.1
    glTranslatef(xAtacante, yAtacante, 0.1f);

    // 2. Truco fundamental: Como el .dibujar() de tu personaje calcula 
    // automáticamente la posición basada en col y fila del tablero principal,
    // vamos a contrarrestar esa traslación para que dibuje en el origen local (0,0).
    glPushMatrix();
    float tableroX_at = -4.5f + atacante->getCol() * 1.0f + 0.5f;
    float tableroY_at = -4.5f + atacante->getFila() * 1.0f + 0.5f;
    glTranslatef(-tableroX_at, -tableroY_at, 0.0f);

    glEnable(GL_TEXTURE_2D); // ETSIDI necesita las texturas activas
    atacante->dibujar();     // Llama al draw() del SpriteSequence
    glPopMatrix();

    // Restauramos las matrices para este elemento
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib(); // El estado de OpenGL vuelve a estar limpio


    // ==========================================
    // RENDERIZADO DEL DEFENSOR (Oscuridad / Profes)
    // ==========================================
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // 1. Lo movemos a la posición de la arena
    glTranslatef(xDefensor, yDefensor, 0.1f);

    // 2. Contrarrestamos la posición fija de su fila/columna del tablero
    glPushMatrix();
    float tableroX_def = -4.5f + defensor->getCol() * 1.0f + 0.5f;
    float tableroY_def = -4.5f + defensor->getFila() * 1.0f + 0.5f;
    glTranslatef(-tableroX_def, -tableroY_def, 0.0f);

    glEnable(GL_TEXTURE_2D);
    defensor->dibujar();
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();

    // Apagamos las texturas por seguridad para los siguientes ciclos de dibujado
    glDisable(GL_TEXTURE_2D);
}

/*void Batalla::dibujarPiezas() {
    if (atacante == nullptr || defensor == nullptr) return;

    // ATACANTE
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    // Lo movemos directamente a su posición de la arena en tiempo real
    glTranslatef(xAtacante, yAtacante, 0.0f);
    atacante->dibujar();
    glPopMatrix();

    // DEFENSOR
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(xDefensor, yDefensor, 0.0f);
    defensor->dibujar();
    glPopMatrix();

    // Apagamos texturas por si ETSIDI las dejó encendidas
    glDisable(GL_TEXTURE_2D);
}*/
// ACTUALIZAR - igual que Mundo::mueve en el Pang
void Batalla::actualizar(float dt) {
    if (estado != EstadoBatalla::EN_CURSO) return;
    if (atacante == nullptr || defensor == nullptr) return;

    xAtacante += vxAtacante * dt * 3.0f;
    yAtacante += vyAtacante * dt * 3.0f;

    if (xAtacante < ARENA_MIN + 0.4f) xAtacante = ARENA_MIN + 0.4f;
    if (xAtacante > ARENA_MAX - 0.4f) xAtacante = ARENA_MAX - 0.4f;
    if (yAtacante < ARENA_MIN + 0.4f) yAtacante = ARENA_MIN + 0.4f;
    if (yAtacante > ARENA_MAX - 0.4f) yAtacante = ARENA_MAX - 0.4f;

    timerAtaqueAtacante += dt;
    timerAtaqueDefensor += dt;

    if (timerAtaqueAtacante >= 1.0f) {
        puedeAtacarAtacante = true;
        timerAtaqueAtacante = 0.0f;
    }

    comprobarColisionesPiedras();

    proyectilAtacante.mover(dt);
    proyectilDefensor.mover(dt);

    comprobarColisionesProyectiles();

    moverIA(dt);
    comprobarFinBatalla();
    glutPostRedisplay();
}

// COLISIONES CON PIEDRAS
// las piedras bloquean el movimiento - sirven de escudo
void Batalla::comprobarColisionesPiedras() {
    for (int i = 0; i < NUM_PIEDRAS; i++) {
        // colision del atacante con la piedra
        float dxA = xAtacante - piedras[i].x;
        float dyA = yAtacante - piedras[i].y;
        float distA = sqrtf(dxA * dxA + dyA * dyA);
        if (distA < 0.5f && distA > 0.01f) {
            float nx = dxA / distA;
            float ny = dyA / distA;
            xAtacante = piedras[i].x + nx * 0.5f;
            yAtacante = piedras[i].y + ny * 0.5f;
        }

        // colision del defensor con la piedra
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
// tres niveles de dificultad que cambian velocidad e intervalo de ataque
void Batalla::moverIA(float dt) {
    if (defensor == nullptr) return;

    float velIA;
    float intervaloAtaqueIA;

    if (dificultad == DificultadIA::FACIL) {
        velIA = 1.0f;
        intervaloAtaqueIA = 2.5f;
    }
    else if (dificultad == DificultadIA::MEDIO) {
        velIA = 2.0f;
        intervaloAtaqueIA = 1.5f;
    }
    else {
        velIA = 3.0f;
        intervaloAtaqueIA = 0.8f;
    }

    float dx = xAtacante - xDefensor;
    float dy = yAtacante - yDefensor;
    float distancia = sqrtf(dx * dx + dy * dy);

    float distMin = (dificultad == DificultadIA::DIFICIL) ? 2.0f : 1.5f;

    if (distancia > distMin && distancia > 0.01f) {
        dx /= distancia;
        dy /= distancia;
        xDefensor += dx * dt * velIA;
        yDefensor += dy * dt * velIA;
    }

    if (xDefensor < ARENA_MIN + 0.4f) xDefensor = ARENA_MIN + 0.4f;
    if (xDefensor > ARENA_MAX - 0.4f) xDefensor = ARENA_MAX - 0.4f;
    if (yDefensor < ARENA_MIN + 0.4f) yDefensor = ARENA_MIN + 0.4f;
    if (yDefensor > ARENA_MAX - 0.4f) yDefensor = ARENA_MAX - 0.4f;

    // la IA dispara cuando el timer esta listo
    if (timerAtaqueDefensor >= intervaloAtaqueIA) {
        if (!proyectilDefensor.getActivo()) {
            // apunta hacia el atacante con algo de imprecision en FACIL
            float ddx = xAtacante - xDefensor;
            float ddy = yAtacante - yDefensor;
            float ddist = sqrtf(ddx * ddx + ddy * ddy);
            if (ddist > 0.01f) {
                ddx /= ddist;
                ddy /= ddist;
            }

            // en FACIL la IA apunta un poco mal a proposito
            if (dificultad == DificultadIA::FACIL) {
                ddx += ((rand() % 100) - 50) / 200.0f;
                ddy += ((rand() % 100) - 50) / 200.0f;
                float norm = sqrtf(ddx * ddx + ddy * ddy);
                if (norm > 0.01f) { ddx /= norm; ddy /= norm; }
            }

            const float VEL_PROYECTIL = 5.0f;
            proyectilDefensor.disparar(
                xDefensor, yDefensor,
                ddx * VEL_PROYECTIL,
                ddy * VEL_PROYECTIL
            );
            timerAtaqueDefensor = 0.0f;
        }
    }
}
// COMPROBAR ATAQUES
void Batalla::comprobarAtaques(bool jugadorAtaca) {
    if (jugadorAtaca && puedeAtacarAtacante) {
        // solo disparar si no hay ya un proyectil en vuelo
        if (!proyectilAtacante.getActivo()) {
            // direccion hacia el defensor
            float dx = xDefensor - xAtacante;
            float dy = yDefensor - yAtacante;
            float dist = sqrtf(dx * dx + dy * dy);
            if (dist > 0.01f) {
                dx /= dist;
                dy /= dist;
            }
            // Velocidad del proyectil: 6 unidades/seg
            const float VEL_PROYECTIL = 6.0f;
            proyectilAtacante.disparar(
                xAtacante, yAtacante,
                dx * VEL_PROYECTIL,
                dy * VEL_PROYECTIL
            );
            puedeAtacarAtacante = false;
            timerAtaqueAtacante = 0.0f;
        }
    }
}
void Batalla::comprobarColisionesProyectiles() {
    // proyectil atacante golpea defensor
    if (proyectilAtacante.getActivo()) {
        float dx = proyectilAtacante.getX() - xDefensor;
        float dy = proyectilAtacante.getY() - yDefensor;
        float dist = sqrtf(dx * dx + dy * dy);
        if (dist < 0.3f) {
            defensor->recibirDano(atacante->getAtaque());
            proyectilAtacante.setActivo(false);
        }
    }

    // proyectil defensor golpea atacante
    if (proyectilDefensor.getActivo()) {
        float dx = proyectilDefensor.getX() - xAtacante;
        float dy = proyectilDefensor.getY() - yAtacante;
        float dist = sqrtf(dx * dx + dy * dy);
        if (dist < 0.3f) {
            atacante->recibirDano(defensor->getAtaque());
            proyectilDefensor.setActivo(false);
            printf("Proyectil ataca atacante - vida restante: %d/%d\n",
                atacante->getVidaActual(), atacante->getVidaMax());
        }
    }

    // proyectiles bloqueados por piedras
    for (int i = 0; i < NUM_PIEDRAS; i++) {
        if (proyectilAtacante.getActivo()) {
            float dx = proyectilAtacante.getX() - piedras[i].x;
            float dy = proyectilAtacante.getY() - piedras[i].y;
            if (sqrtf(dx * dx + dy * dy) < 0.35f)
                proyectilAtacante.setActivo(false);
        }
        if (proyectilDefensor.getActivo()) {
            float dx = proyectilDefensor.getX() - piedras[i].x;
            float dy = proyectilDefensor.getY() - piedras[i].y;
            if (sqrtf(dx * dx + dy * dy) < 0.35f)
                proyectilDefensor.setActivo(false);
        }
    }
}
// COMPROBAR FIN DE BATALLA
void Batalla::comprobarFinBatalla() {
    if (atacante == nullptr || defensor == nullptr) return;

    if (!atacante->getEstaViva() && !defensor->getEstaViva()) {
        estado = EstadoBatalla::GANA_DEFENSOR; // empate: gana el defensor
    }
    else if (!atacante->getEstaViva()) {
        estado = EstadoBatalla::GANA_DEFENSOR;
    }
    else if (!defensor->getEstaViva()) {
        estado = EstadoBatalla::GANA_ATACANTE;
    }
}

// GESTION TECLADO
// WASD para mover, F para atacar cuando este cargado circulo verde
void Batalla::gestionTeclado(unsigned char tecla) {
    if (estado != EstadoBatalla::EN_CURSO) return;

    switch (tecla) {
    case 'w': case 'W': vyAtacante = 1.0f; break;
    case 's': case 'S': vyAtacante = -1.0f; break;
    case 'a': case 'A': vxAtacante = -1.0f; break;
    case 'd': case 'D': vxAtacante = 1.0f; break;
    case 'f': case 'F':
        comprobarAtaques(true);
        break;
    }
}

void Batalla::gestionTecladoSuelto(unsigned char tecla) {
    switch (tecla) {
    case 'w': case 'W': case 's': case 'S': vyAtacante = 0.0f; break;
    case 'a': case 'A': case 'd': case 'D': vxAtacante = 0.0f; break;
    }
}

