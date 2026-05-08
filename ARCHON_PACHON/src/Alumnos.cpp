#include "Alumnos.h"

Alumnos::Alumnos() {
	for (int i = 0; i < 7; i++) {
		double x = 140;
		double y = 140 + 60 * i;
		humilde.push_back(Humilde(x, y));
	}

	for (int i = 0; i < 2; i++) {
		double x = 140;
		double y = 80 + 480 * i;
		ausente.push_back(Ausente(x, y));
	}

	for (int i = 0; i < 2; i++) {
		double x = 80;
		double y = 80 + 480 * i;
		ocupado.push_back(Ocupado(x, y));
	}

	for (int i = 0; i < 2; i++) {
		double x = 80;
		double y = 140 + 360 * i;
		nocturno.push_back(Nocturno(x, y));
	}

	for (int i = 0; i < 2; i++) {
		double x = 80;
		double y = 200 + 240 * i;
		veterano.push_back(Veterano(x, y));
	}

	mago.push_back(Mago(80, 260));
	todo10.push_back(Todo10(80, 380));
	delegado.push_back(Delegado(80, 320));

}

void Alumnos::dibuja() {
	for (auto a : humilde) a.dibuja();
	for (auto a : ausente) a.dibuja();
	for (auto a : ocupado) a.dibuja();
	for (auto a : nocturno) a.dibuja();
	for (auto a : veterano) a.dibuja();
	for (auto a : mago) a.dibuja();
	for (auto a : todo10) a.dibuja();
	for (auto a : delegado) a.dibuja();
}