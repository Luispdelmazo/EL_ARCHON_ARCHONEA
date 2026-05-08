#pragma once
#include <vector>
#include "Humilde.h"
#include "Ausente.h"
#include "Ocupado.h"
#include "Nocturno.h"
#include "Veterano.h"
#include "Mago.h"
#include "Todo10.h"
#include "Delegado.h"

using std::vector;

class Alumnos
{
	vector<Humilde> humilde;
	vector<Ausente> ausente;
	vector<Ocupado> ocupado;
	vector<Nocturno> nocturno;
	vector<Veterano> veterano;
	vector<Mago> mago;
	vector<Todo10> todo10;
	vector<Delegado> delegado;
	
public:
	Alumnos();

	void dibuja();

};

