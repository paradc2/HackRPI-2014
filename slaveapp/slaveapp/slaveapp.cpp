// slaveapp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>
#include <vector>

#include "speaker.h"
#define NUM_SPEAKERS 2

typedef double dist;
typedef double volume;

void getDist(dist &x, dist &y, dist &z) {
	x = -50;
	y = 50;
	z = 0;
	//Interpret KINECT data to update x, y, and z position
}

void update(Speaker &s, dist &x, dist &y, dist &z, const volume &L_c, const dist &x_c, const dist &y_c const dist &z_c) {

	getDist(x, y, z);

	dist r_0 = sqrt(pow((x - x_0), 2) + pow((y - y_0), 2) + pow((z - z_0), 2));
	dist r = sqrt(pow((x - x_c), 2) + pow((y - y_c), 2) + pow((z - z_c), 2));

	volume L_0 = L_c + 20 * log(r_0 / r);

	s.setL(L_0);
}

int _tmain(int argc, _TCHAR* argv[])
{

	// Variables that will be updated
	dist x, y, z;
	dist x_c = 0;
	dist y_c = 0;
	dist z_c = 0;
	volume L_c = 60; // dB

	// Constants
	std::vector<Speaker> speakers(NUM_SPEAKERS);
	speakers[0] = Speaker(-100, 50, 0);
	speakers[1] = Speaker(100, 50, 0);

	getAverages(speakers, x_c, y_c, z_c);

	for (unsigned int i=0; i<speakers.size(); ++i) {
		update(speakers[i], x, y, z, L_c, x_c, y_c, z_c);
	}

	return 0;
}