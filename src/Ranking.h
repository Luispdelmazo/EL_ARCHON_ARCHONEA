#pragma once
#include <string>
#include <vector>
#include <fstream> //para ficheros

// CLASE: Ranking
// Guarda y carga resultados en un fichero de texto
// Cada clase gestiona sus propios datos - como dijo MH

struct Resultado {
    std::string ganador;
    int turnosJugados;
};

class Ranking {
private:
    std::vector<Resultado> resultados;
    std::string nombreFichero;

public:
    Ranking();
    void guardarResultado(std::string ganador, int turnosJugados);
    void cargarResultados();
    void dibujar();
    std::vector<Resultado> getResultados() const { return resultados; }
};
