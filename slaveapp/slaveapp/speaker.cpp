
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
