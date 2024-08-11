#include"arch.h"

arch::arch(int x, int y) {
	setLife(true);
	setInitial_x(x);
	setInitial_y(y);
	setPixelPosition_x(getInitial_y() * 100);
	setPixelPosition_y(getInitial_x() * 100 + 1);
}

void arch::setLife(bool l) {
	life = l;
}
bool arch::getLife() {
	return life;
}
void arch::setInitial_x(int x) {
	initial_x = x;
}
void arch::setInitial_y(int y) {
	initial_y = y;
}
int arch::getInitial_x() {
	return initial_x;
}
int arch::getInitial_y() {
	return initial_y;
}
void arch::setPosition_x(int x) {
	position_x = x;
}
void arch::setPosition_y(int y) {
	position_y = y;
}
int arch::getPosition_x() {
	return position_x;
}
int arch::getPosition_y() {
	return position_y;
}
void arch::setPixelPosition_x(int x) {
	Pixel_x = x;
}
void arch::setPixelPosition_y(int y) {
	Pixel_y = y;
}
int arch::getPixelPosition_x() {
	return Pixel_x;
}
int arch::getPixelPosition_y() {
	return Pixel_y;
}