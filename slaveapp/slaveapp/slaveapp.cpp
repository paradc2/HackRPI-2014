// slaveapp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>
#include <vector>

#define NUM_SPEAKERS 2

typedef double dist;
typedef double volume;

void getDist(dist &x, dist &y) {
	//Interpret KINECT data to update x and y position
}

void update(volume &L_0, dist &x, dist &y, const volume &L_c, const dist &x_0, const dist &y_0, const dist &x_c, const dist &y_c) {

	getDist(x, y);

	dist r_0 = sqrt(pow((x - x_0), 2) + pow((y - y_0), 2));
	dist r = sqrt(pow((x - x_c), 2) + pow((y - y_c), 2));

	L_0 = L_c + 20 * log(r_0 / r);
}

int _tmain(int argc, _TCHAR* argv[])
{

	// Variables that will be updated
	dist x, y;
	volume L = 60; // dB

	// Constants
	std::vector<Speaker> speakers(NUM_SPEAKERS);
	speakers[0] = Speaker(-100, 50);
	speakers[1] = Speaker(100, 50);

	/*for (unsigned int i=0; i<speakers.size(); ++i) {
		update(...);
	}
	*/

	//
	return 0;
}

// Class declaration...put somewhere else?

class Speaker {
public:
	Speaker(const dist x0, const dist y0);

	// ACCESSORS
	dist getX() const;
	dist getY() const;
	volume getL() const;

	// MODIFIERS
	void setX(const dist x0);
	void setY(const dist y0);
	void setL(const volume L0);

	// OTHER
private:
	dist x_0;
	dist y_0;
	volume L_0;

};

void getAverages(const Speaker &s1, const Speaker &s2, dist &x_c, dist &y_c);

// Class implementation...put somewhere else
Speaker::Speaker(const dist x0, const dist y0) {
	x_0 = x0;
	y_0 = y0;
}

dist Speaker::getX() const { return x_0; }
dist Speaker::getY() const { return y_0; }
volume Speaker::getL() const { return L_0; }

void Speaker::setX(const dist x0) { x_0 = x0; }
void Speaker::setY(const dist y0) { y_0 = y0; }
void Speaker::setL(const volume L0) { L_0 = L0; }
