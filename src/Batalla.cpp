#include "Batalla.h"
#include <GL/glut.h>

// Limites de la arena de combate
const float Batalla::ARENA_MIN = -4.5f;
const float Batalla::ARENA_MAX =  4.5f;

// CONSTRUCTOR
Batalla::Batalla()
    : alumno(nullptr), profesor(nullptr),
    xAlumno(-3.0f), yAlumno(0.0f),
    xProfesor( 3.0f), yProfesor(0.0f),
    vxAlumno(0.0f), vyAlumno(0.0f),
    vxProfesor(0.0f), vyProfesor(0.0f),
    timerAtaqueAlumno(0.0f),
    timerAtaqueProfesor(0.0f),
    puedeAtacarAlumno(false),
    estado(EstadoBatalla::EN_CURSO),
    dificultad(DificultadIA::MEDIO)
{}

// INICIAR
void Batalla::iniciar(Pieza* alum, Pieza* prof) {
    alumno = alum;
    profesor = prof;
    estado = EstadoBatalla::EN_CURSO;

    xAlumno = ARENA_MIN + 1.0f;   // -3.5
    yAlumno = 0.0f;
    xProfesor = ARENA_MAX - 1.0f;   //  3.5
    yProfesor = 0.0f;

    // velocidades a 0 para que el atacante no se mueva solo
    vxAlumno = 0.0f;
    vyAlumno = 0.0f;
    vxProfesor = 0.0f;
    vyProfesor = 0.0f;

    // Timer ya cargado para que F funcione desde el primer momento
    timerAtaqueAlumno = 1.0f;
    timerAtaqueProfesor = 1.0f;
    puedeAtacarAlumno = true;
	alumno->resetAtaques();
	profesor->resetAtaques();
    alumno->resetFallos();
    profesor->resetAtaques();

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

    proyectilAlumno.dibujar();
    proyectilProfesor.dibujar();

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
    if (alumno == nullptr || profesor == nullptr) return;

    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity(); // Nos aseguramos de estar en el origen del plano 2D

    float porcAlumno, porcProfesor;
	std::string nAlumno, nProfesor;

    
    porcAlumno = (float)alumno->getVidaActual() / (float)alumno->getVidaMax();
    nAlumno = alumno->getNombre();
    porcProfesor = (float)profesor->getVidaActual() / (float)profesor->getVidaMax();
    nProfesor = profesor->getNombre();
	

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
    glVertex3f(-4.8f + 4.6f * porcAlumno, 4.7f, 0.0f);
    glVertex3f(-4.8f + 4.6f * porcAlumno, 5.1f, 0.0f);
    glVertex3f(-4.8f, 5.1f, 0.0f);
    glEnd();
    // nombre
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-4.8f, 5.2f);
    for (int i = 0; i < (int)nAlumno.size(); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, nAlumno[i]);

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
    glVertex3f(4.8f - 4.6f * porcProfesor, 4.7f, 0.0f);
    glVertex3f(4.8f - 4.6f * porcProfesor, 5.1f, 0.0f);
    glVertex3f(4.8f, 5.1f, 0.0f);
    glEnd();
    // nombre
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(0.3f, 5.2f);
    for (int i = 0; i < (int)nProfesor.size(); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, nProfesor[i]);

    // indicador F verde cuando puede atacar
    if (puedeAtacarAlumno) {
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
    if (alumno == nullptr || profesor == nullptr) return;

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
    glTranslatef(xAlumno, yAlumno, 0.1f);

    // 2. Truco fundamental: Como el .dibujar() de tu personaje calcula 
    // automáticamente la posición basada en col y fila del tablero principal,
    // vamos a contrarrestar esa traslación para que dibuje en el origen local (0,0).
    glPushMatrix();
    float tableroX_luz = -4.5f + alumno->getCol() * 1.0f + 0.5f;
    float tableroY_luz = -4.5f + alumno->getFila() * 1.0f + 0.5f;
    glTranslatef(-tableroX_luz, -tableroY_luz, 0.0f);

    glEnable(GL_TEXTURE_2D); // ETSIDI necesita las texturas activas
    alumno->dibujar();     // Llama al draw() del SpriteSequence
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
    glTranslatef(xProfesor, yProfesor, 0.1f);

    // 2. Contrarrestamos la posición fija de su fila/columna del tablero
    glPushMatrix();
    float tableroX_osc = -4.5f + profesor->getCol() * 1.0f + 0.5f;
    float tableroY_osc = -4.5f + profesor->getFila() * 1.0f + 0.5f;
    glTranslatef(-tableroX_osc, -tableroY_osc, 0.0f);

    glEnable(GL_TEXTURE_2D);
    profesor->dibujar();
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
    if (alumno == nullptr || profesor == nullptr) return;

    xAlumno += vxAlumno * dt;
    yAlumno += vyAlumno * dt;

    if (xAlumno < ARENA_MIN + 0.4f) xAlumno = ARENA_MIN + 0.4f;
    if (xAlumno > ARENA_MAX - 0.4f) xAlumno = ARENA_MAX - 0.4f;
    if (yAlumno < ARENA_MIN + 0.4f) yAlumno = ARENA_MIN + 0.4f;
    if (yAlumno > ARENA_MAX - 0.4f) yAlumno = ARENA_MAX - 0.4f;

    timerAtaqueAlumno += dt;
    timerAtaqueProfesor += dt;
    if (timerAtaqueAlumno >= 1.0f) {
        puedeAtacarAlumno = true;
        timerAtaqueAlumno = 0.0f;
    }

    alumno->habilidadEnBatalla();
    profesor->habilidadEnBatalla();
    

    comprobarColisionesPiedras();

    proyectilAlumno.mover(dt);
    proyectilProfesor.mover(dt);

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
        float dxA = xAlumno - piedras[i].x;
        float dyA = yAlumno - piedras[i].y;
        float distA = sqrtf(dxA * dxA + dyA * dyA);
        if (distA < 0.5f && distA > 0.01f) {
            float nx = dxA / distA;
            float ny = dyA / distA;
            xAlumno = piedras[i].x + nx * 0.5f;
            yAlumno = piedras[i].y + ny * 0.5f;
        }

        // colision del defensor con la piedra
        float dxD = xProfesor - piedras[i].x;
        float dyD = yProfesor - piedras[i].y;
        float distD = sqrtf(dxD * dxD + dyD * dyD);
        if (distD < 0.5f && distD > 0.01f) {
            float nx = dxD / distD;
            float ny = dyD / distD;
            xProfesor = piedras[i].x + nx * 0.5f;
            yProfesor = piedras[i].y + ny * 0.5f;
        }
    }
}

// IA DE la oscuridad
// tres niveles de dificultad que cambian velocidad e intervalo de ataque
void Batalla::moverIA(float dt) {
    if (profesor == nullptr) return;

    float velIA;
    float intervaloAtaqueIA;

    if (dificultad == DificultadIA::FACIL) {
        velIA = (float)profesor->getVelocidad()*0.7f;
        intervaloAtaqueIA = 2.5f;
    }
    else if (dificultad == DificultadIA::MEDIO) {
        velIA = (float)profesor->getVelocidad();
        intervaloAtaqueIA = 1.5f;
    }
    else {
		velIA = (float)profesor->getVelocidad() * 1.5f;
        intervaloAtaqueIA = 0.8f;
    }

    float dx = xAlumno - xProfesor;
    float dy = yAlumno - yProfesor;
    float distancia = sqrtf(dx * dx + dy * dy);

    float distMin = (dificultad == DificultadIA::DIFICIL) ? 2.0f : 1.5f;


    if (distancia > distMin && distancia > 0.01f) {
        dx /= distancia;
        dy /= distancia;
        xProfesor += dx * dt * velIA;
        yProfesor += dy * dt * velIA;
    }

    if (xProfesor < ARENA_MIN + 0.4f) xProfesor = ARENA_MIN + 0.4f;
    if (xProfesor > ARENA_MAX - 0.4f) xProfesor = ARENA_MAX - 0.4f;
    if (yProfesor < ARENA_MIN + 0.4f) yProfesor = ARENA_MIN + 0.4f;
    if (yProfesor > ARENA_MAX - 0.4f) yProfesor = ARENA_MAX - 0.4f;

        // la IA dispara cuando el timer esta listo
    if (timerAtaqueProfesor >= intervaloAtaqueIA) {
        if (!proyectilProfesor.getActivo()) {
            // apunta hacia el atacante con algo de imprecision en FACIL
            float ddx = xAlumno - xProfesor;
            float ddy = yAlumno - yProfesor;
            float ddist = sqrtf(ddx * ddx + ddy * ddy);
            if (ddist > 0.01f) {
                ddx /= ddist;
                ddy /= ddist;
            }

            // en FACIL la IA apunta un poco mal a proposito
            /*if (dificultad == DificultadIA::FACIL) {
                ddx += ((rand() % 100) - 50) / 200.0f;
                ddy += ((rand() % 100) - 50) / 200.0f;
                float norm = sqrtf(ddx * ddx + ddy * ddy);
                if (norm > 0.01f) { ddx /= norm; ddy /= norm; }
            }*/

            const float VEL_PROYECTIL = 5.0f;
            proyectilProfesor.disparar(
            xProfesor, yProfesor,
            ddx * VEL_PROYECTIL,
            ddy * VEL_PROYECTIL
            );
            timerAtaqueProfesor = 0.0f;
            profesor->nuevoAtaque();
        }
    }
}
// COMPROBAR ATAQUES
void Batalla::comprobarAtaques(bool jugadorAtaca) {
    if (jugadorAtaca && puedeAtacarAlumno) {
        // solo disparar si no hay ya un proyectil en vuelo
        if (!proyectilAlumno.getActivo()) {
            // direccion hacia el defensor
            float dx = xProfesor - xAlumno;
            float dy = yProfesor - yAlumno;
            float dist = sqrtf(dx * dx + dy * dy);
            if (dist > 0.01f) {
                dx /= dist;
                dy /= dist;
            }
            // Velocidad del proyectil: 6 unidades/seg
            const float VEL_PROYECTIL = 5.0f;
            proyectilAlumno.disparar(
                xAlumno, yAlumno,
                dx * VEL_PROYECTIL,
                dy * VEL_PROYECTIL);
            puedeAtacarAlumno = false;
            timerAtaqueAlumno = 0.0f;
            alumno->nuevoAtaque();
        }
    }
}
void Batalla::comprobarColisionesProyectiles() {
    // proyectil atacante golpea defensor
    if (proyectilAlumno.getActivo()) {
        float dx = proyectilAlumno.getX() - xProfesor;
        float dy = proyectilAlumno.getY() - yProfesor;
        float dist = sqrtf(dx * dx + dy * dy);
        if (dist < 0.3f) {
            profesor->recibirDano(alumno->getAtaque());
            proyectilAlumno.setActivo(false);
        }
    }

    // proyectil defensor golpea atacante
    if (proyectilProfesor.getActivo()) {
        float dx = proyectilProfesor.getX() - xAlumno;
        float dy = proyectilProfesor.getY() - yAlumno;
        float dist = sqrtf(dx * dx + dy * dy);
        if (dist < 0.3f) {
            alumno->recibirDano(profesor->getAtaque());
            proyectilProfesor.setActivo(false);
            //printf("Proyectil ataca atacante - vida restante: %d/%d\n",
            //alumno->getVidaActual(), alumno->getVidaMax());
        }
    }

    // proyectiles bloqueados por piedras
    for (int i = 0; i < NUM_PIEDRAS; i++) {
        if (proyectilAlumno.getActivo()) {
            float dx = proyectilAlumno.getX() - piedras[i].x;
            float dy = proyectilAlumno.getY() - piedras[i].y;
            if (sqrtf(dx * dx + dy * dy) < 0.35f) {
                proyectilAlumno.setActivo(false);
                alumno->nuevoFallo();
            }
        }
        if (proyectilProfesor.getActivo()) {
            float dx = proyectilProfesor.getX() - piedras[i].x;
            float dy = proyectilProfesor.getY() - piedras[i].y;
            if (sqrtf(dx * dx + dy * dy) < 0.35f) {
                proyectilProfesor.setActivo(false);
                profesor->nuevoFallo();
            }
        }
    }
}
// COMPROBAR FIN DE BATALLA
void Batalla::comprobarFinBatalla() {
    if (alumno == nullptr || profesor == nullptr) return;

    if (!alumno->getEstaViva() && !profesor->getEstaViva()) {
        estado = EstadoBatalla::EMPATE; // empate: se eliminaran las 2 piezas
    }
    else if (!alumno->getEstaViva()) {
        estado = EstadoBatalla::GANA_PROFESOR;
    }
    else if (!profesor->getEstaViva()) {
        estado = EstadoBatalla::GANA_ALUMNO;
    }
}

// GESTION TECLADO
// WASD para mover, F para atacar cuando este cargado circulo verde
void Batalla::gestionTeclado(unsigned char tecla) {
    if (estado != EstadoBatalla::EN_CURSO) return;

    switch (tecla) {
    case 'w': case 'W': vyAlumno = (float)alumno->getVelocidad(); break;
        case 's': case 'S': vyAlumno = -(float)alumno->getVelocidad(); break;
        case 'a': case 'A': vxAlumno = -(float)alumno->getVelocidad(); break;
        case 'd': case 'D': vxAlumno = (float)alumno->getVelocidad(); break;
        case 'f': case 'F':
        comprobarAtaques(true);
        break;
    }
    
}

/*void Batalla::gestionTecladoSuelto(unsigned char tecla) {
    switch (tecla) {
    case 'w': case 'W': case 's': case 'S': vyAtacante = 0.0f; break;
    case 'a': case 'A': case 'd': case 'D': vxAtacante = 0.0f; break;
    }
}*/

