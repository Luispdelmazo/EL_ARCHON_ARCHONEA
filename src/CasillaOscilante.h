#pragma once
#include "Casillas.h"

// CasillaOscilante - hereda de Casilla
// Igual que EsferaPulsante heredaba de Esfera en el Pang 
// Especializa el comportamiento - cambia de color sola con el tiempo
// Idea de mi compañero: las oscilantes son como las pulsantes del Pang

class CasillaOscilante : public Casilla {
public:
    CasillaOscilante(EstadoCasilla estadoInicial, float periodo = 5.0f)
        : Casilla(TipoCasilla::OSCILANTE, estadoInicial, periodo)
    {}

	
};
