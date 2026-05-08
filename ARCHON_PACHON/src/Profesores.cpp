#include "Profesores.h"

Profesores::Profesores() {
	for (int i = 0; i < 7; i++) {
		double x = 500;
		double y = 140 + 60 * i;
		imanol.push_back(Imanol(x, y));
	}

	for (int i = 0; i < 2; i++) {
		double x = 500;
		double y = 80 + 480 * i;
		giuseppe.push_back(Giuseppe(x, y));
	}

	for (int i = 0; i < 2; i++) {
		double x = 560;
		double y = 80 + 480 * i;
		sansegundo.push_back(SanSegundo(x, y));
	}

	for (int i = 0; i < 2; i++) {
		double x = 560;
		double y = 140 + 360 * i;
		oscar.push_back(Oscar(x, y));
	}

	for (int i = 0; i < 2; i++) {
		double x = 560;
		double y = 200 + 240 * i;
		hectorm.push_back(HectorM(x, y));
	}

	basil.push_back(Basil(560, 260));
	platero.push_back(Platero(560, 380));
	miguelh.push_back(MiguelH(560, 320));

}

void Profesores::dibuja() {
	for (auto a : imanol) a.dibuja();
	for (auto a : giuseppe) a.dibuja();
	for (auto a : sansegundo) a.dibuja();
	for (auto a : oscar) a.dibuja();
	for (auto a : hectorm) a.dibuja();
	for (auto a : basil) a.dibuja();
	for (auto a : platero) a.dibuja();
	for (auto a : miguelh) a.dibuja();
}