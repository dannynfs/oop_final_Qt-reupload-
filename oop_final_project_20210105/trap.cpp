#include "trap.h"


trap::trap(int x, int y) {
	setLife();
	setPixelPosition_x(x);
	setPixelPosition_y(y);
	setPosition_x(x);
	setPosition_y(y);
}
void trap::setLife() {
	life = true;
}
bool trap::getLife() {
	return life;
}
void trap::setPosition_x(int x) {
	role_position.x = x;
}
void trap::setPosition_y(int y) {
	role_position.y = y;
}
int trap::getPosition_x() {
	return role_position.x;
}
int trap::getPosition_y() {
	return role_position.y;
}
void trap::setPixelPosition_x(int x) {
	role_pixel_position.x = x;
}
void trap::setPixelPosition_y(int y) {
	role_pixel_position.y = y;
}
int trap::getPixelPosition_x() {
	return role_pixel_position.x;
}
int trap::getPixelPosition_y() {
	return role_pixel_position.y;
}
position_t trap::getPosition() {
	return role_pixel_position;
}
position_t trap::getPixelPosition() {
	return role_pixel_position;
}
