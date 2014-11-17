// slaveapp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>
#include <vector>
#include <Windows.h>
#include <MMsystem.h>
#include <iostream>

#include "speaker.h"
#define NUM_SPEAKERS 2

typedef double dist;
typedef double volume;

// This is the function that needs to pull data from KINECT position sensors
void getDist(dist &x, dist &y, dist &z) {
	//std::cin >> x >> y >> z;
	// Interpret KINECT data to update x, y, and z position
	// Don't return, just change, since they are passed in by reference
}

// This function updates that member variable representing the volume for a certain speaker
// based on the readings of position
void update(Speaker &s, dist &x, dist &y, dist &z, const volume &L_c, const dist &x_c, const dist &y_c, const dist &z_c) {

	//std::cout << "Speaker " << s.getID() << ":\nx: " << s.getX() << ", y: " << s.getY() << ", z: " << s.getZ() << "\n";
	getDist(x, y, z);

	dist r_0 = sqrt(pow((x - s.getX()), 2) + pow((y - s.getY()), 2) + pow((z - s.getZ()), 2));
	dist r = sqrt(pow((s.getX() - x_c), 2) + pow((s.getY() - y_c), 2) + pow((s.getZ() - z_c), 2));
	//std::cout << "r_0: " << r_0 << "\nr: " << r << "\n";

	volume L_0 = L_c + 20 * log(r_0 / r);
	//std::cout << "L_c: " << L_c << "\n20*log(r0/r)" << 20 * log(r_0 / r) << "\n";

	if (L_0 > 78) { L_0 = 78; }
	if (L_0 < 0) { L_0 = 0; }

	s.setL(L_0);

	volume send_val = (pow(10, (L_0 / 20)) - 1) / 8000;
	//send value L_0 to database, 
	//std::cout << L_0 << "\n";
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
	speakers[0] = Speaker(1, -100, 50, 0);
	speakers[1] = Speaker(2, 100, 50, 0);

	getAverages(speakers, x_c, y_c, z_c);

	// Loop forever, update each speaker every time
	while (1) {
		for (unsigned int i = 0; i < speakers.size(); ++i) {
			update(speakers[i], x, y, z, L_c, x_c, y_c, z_c);
		}
	}
	return 0;
}