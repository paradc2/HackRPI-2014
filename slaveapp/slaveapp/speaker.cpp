
#include "stdafx.h"
#include "speaker.h"

#include <vector>

typedef double dist;
typedef double volume;

Speaker::Speaker() {
	x_0 = 0;
	y_0 = 0;
	z_0 = 0;
	L_0 = 0;
}

Speaker::Speaker(const dist x0, const dist y0, const dist z0) {
	x_0 = x0;
	y_0 = y0;
	z_0 = z0;
	L_0 = 0;
}

dist Speaker::getX() const { return x_0; }
dist Speaker::getY() const { return y_0; }
dist Speaker::getZ() const { return z_0; }
volume Speaker::getL() const { return L_0; }

void Speaker::setX(const dist x0) { x_0 = x0; }
void Speaker::setY(const dist y0) { y_0 = y0; }
void Speaker::setZ(const dist z0) { y_0 = z0; }
void Speaker::setL(const volume L0) { L_0 = L0; }

void getAverages(const std::vector<Speaker> &speakers, dist &x_c, dist &y_c, dist &z_c) {
	dist x_c_ = 0;
	dist y_c_ = 0;
	dist z_c_ = 0;

	for (unsigned int i = 0; i < speakers.size(); ++i) {
		x_c_ += speakers[i].getX();
		y_c_ += speakers[i].getY();
		z_c_ += speakers[i].getZ();
	}

	x_c = x_c_ / speakers.size();
	y_c = y_c_ / speakers.size();
	z_c = z_c_ / speakers.size();
}