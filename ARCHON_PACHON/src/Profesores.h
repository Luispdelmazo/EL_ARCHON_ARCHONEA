#pragma once
#include <vector>
#include "Imanol.h"
#include "Giuseppe.h"
#include "SanSegundo.h"
#include "Oscar.h"
#include "HectorM.h"
#include "Basil.h"
#include "Platero.h"
#include "MiguelH.h"

using std::vector;

class Profesores
{
	vector<Imanol> imanol;
	vector<Giuseppe> giuseppe;
	vector<SanSegundo> sansegundo;
	vector<Oscar> oscar;
	vector<HectorM> hectorm;
	vector<Platero> platero;
	vector<Basil> basil;
	vector<MiguelH> miguelh;

public:
	Profesores();

	void dibuja();
};

