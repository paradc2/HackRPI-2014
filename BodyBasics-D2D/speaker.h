
#ifndef SPEAKER_H
#define SPEAKER_H

#include <vector>

typedef double volume;

class Speaker {
public:
	Speaker();
	Speaker(const int ID_, const float x0, const float y0, const float z0);

	// ACCESSORS
	float getX() const;
	float getY() const;
	float getZ() const;
	volume getL() const;
	int getID() const;

	// MODIFIERS
	void setX(const float x0);
	void setY(const float y0);
	void setZ(const float z0);
	void setL(const volume L0);

	// OTHER
private:
	float x_0;
	float y_0;
	float z_0;
	volume L_0;
	int ID;

};

void getAverages(const std::vector<Speaker> &speakers, float &x_c, float &y_c, float &z_c);

#endif
