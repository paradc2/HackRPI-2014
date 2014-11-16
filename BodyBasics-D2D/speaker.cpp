
#include "stdafx.h"
#include "speaker.h"

#include <vector>

typedef double volume;

Speaker::Speaker() {
	x_0 = 0;
	y_0 = 0;
	z_0 = 0;
	L_0 = 0;
	ID = 0;
}

Speaker::Speaker(const int ID_, const float x0, const float y0, const float z0) {
	x_0 = x0;
	y_0 = y0;
	z_0 = z0;
	L_0 = 0;
	ID = ID_;
}

float Speaker::getX() const { return x_0; }
float Speaker::getY() const { return y_0; }
float Speaker::getZ() const { return z_0; }
volume Speaker::getL() const { return L_0; }
int Speaker::getID() const { return ID; }

void Speaker::setX(const float x0) { x_0 = x0; }
void Speaker::setY(const float y0) { y_0 = y0; }
void Speaker::setZ(const float z0) { y_0 = z0; }
void Speaker::setL(const volume L0) { L_0 = L0; }

void getAverages(const std::vector<Speaker> &speakers, float &x_c, float &y_c, float &z_c) {
	float x_c_ = 0;
	float y_c_ = 0;
	float z_c_ = 0;

	for (unsigned int i = 0; i < speakers.size(); ++i) {
		x_c_ += speakers[i].getX();
		y_c_ += speakers[i].getY();
		z_c_ += speakers[i].getZ();
	}

	x_c = x_c_ / speakers.size();
	y_c = y_c_ / speakers.size();
	z_c = z_c_ / speakers.size();
}