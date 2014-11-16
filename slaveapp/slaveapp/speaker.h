
typedef double dist;
typedef double volume;

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
