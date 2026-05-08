# EL ARCHON ARCHONEA 🎮
### Trabajo de Informática Industrial - Curso 2025/2026
### EE309 - Departamento de Automática, UPM

---

## 🎯 Descripción del juego

Variación del juego clásico ARCHON (1983) con temática universitaria.
Enfrentamiento entre los alumnos de la clase EE309 contra los profesores 
del Departamento de Automática de la UPM.

El juego combina estrategia por turnos en un tablero 9x9 con combates 
en tiempo real cuando dos piezas se encuentran en la misma casilla.

---

## ⚔️ Bandos

### 🟡 Bando EE309 - ALUMNOS (Luz)

| Pieza | Movimiento | Habilidad especial | Ataque | Vida | Velocidad | Cantidad |
|-------|-----------|-------------------|--------|------|-----------|---------|
| Delegado | Teletransporte | Lanza conjuros | Largo alcance - 50 | 250 | Lento | 1 |
| Todo10 | Volador | Copia las habilidades del profe en combate | En zona - 30/s | 250 | Medio | 1 |
| Mago | Volador | Sobrevive el primer golpe mortal, hace milagros | Largo alcance - 30 | 200 | Rápido | 1 |
| Veterano | Terrestre | Lo que no le mata le hace más fuerte, su ataque sube al ganar batallas | Cuerpo a cuerpo - 30 | 300 | Lento | 2 |
| Nocturno | Terrestre | Pico de adrenalina: puede duplicar su velocidad una vez por batalla | Media distancia - 20 | 250 | Medio | 2 |
| Ocupado | Volador | Uno de cada 5 ataques es más fuerte, sorprende con conocimiento del exterior | Media distancia - 30 | 200 | Medio | 2 |
| Ausente | Terrestre | Cuando su vida baja del 50% su ataque se duplica | Cuerpo a cuerpo - 30 | 150 | Rápido | 2 |
| Humilde | Terrestre | Al ganar una batalla puede transformarse en uno de sus compañeros | Cuerpo a cuerpo - 20 | 100 | Medio | 7 |

### 🔴 Bando AUTOMÁTICA - PROFESORES (Oscuridad)

| Pieza | Movimiento | Habilidad especial | Ataque | Vida | Velocidad | Cantidad |
|-------|-----------|-------------------|--------|------|-----------|---------|
| Miguel Hernando | Teletransporte | Lanza conjuros | Largo alcance - 50 | 250 | Lento | 1 |
| Platero | Volador | Su zona de daño crece poco a poco sin detenerse | En zona - 30/s | 250 | Medio | 1 |
| Basil | Volador | Carga ataques muy potentes pero si falla se hace daño a sí mismo | Largo alcance - 30 | 200 | Rápido | 1 |
| Héctor Montes | Terrestre | Recupera 1 punto de vida por segundo en batalla | Cuerpo a cuerpo - 30 | 300 | Lento | 2 |
| Óscar C | Terrestre | Su ataque, vida y velocidad aumentan con cada batalla ganada | Medio alcance - 20 | 250 | Medio | 2 |
| San Segundo | Volador | Puede dividirse en 2 una vez por partida | Media distancia - 30 | 200 | Medio | 2 |
| Giuseppe | Terrestre | En sus combates no están permitidas las habilidades especiales | Cuerpo a cuerpo - 30 | 150 | Rápido | 2 |
| Imanol | Terrestre | Alguno de sus ataques puede paralizar al rival unos segundos | Cuerpo a cuerpo - 20 | 100 | Medio | 7 |
---

## 🏆 Condiciones de victoria

- Controlar los 5 puntos de poder del tablero
- Eliminar todas las piezas del rival
- Dejar al rival con solo una pieza encarcelada

---

## 🛠️ Tecnologías utilizadas

- C++ con Visual Studio 2026
- Librería ETSIDI (UPM)
- OpenGL / freeglut

---


## 📅 Estado del desarrollo

- [x] Proyecto creado en Visual Studio
- [x] Librería ETSIDI configurada
- [x] Tablero 9x9 dibujado en pantalla
- [x] Clases base Pieza y Tablero creadas
- [ ] Piezas de cada bando implementadas
- [ ] Movimiento en el tablero
- [ ] Arena de combate
- [ ] Conjuros del líder
