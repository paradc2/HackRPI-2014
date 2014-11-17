
#ifndef SPEAKER_H
#define SPEAKER_H

#include <vector>

typedef double dist;
typedef double volume;

class Speaker {
public:
	Speaker();
	Speaker(const int ID_, const dist x0, const dist y0, const dist z0);

	// ACCESSORS
	dist getX() const;
	dist getY() const;
	dist getZ() const;
	volume getL() const;
	int getID() const;

	// MODIFIERS
	void setX(const dist x0);
	void setY(const dist y0);
	void setZ(const dist z0);
	void setL(const volume L0);

	// OTHER
private:
	dist x_0;
	dist y_0;
	dist z_0;
	volume L_0;
	int ID;

};

void getAverages(const std::vector<Speaker> &speakers, dist &x_c, dist &y_c, dist &z_c);

#endif
