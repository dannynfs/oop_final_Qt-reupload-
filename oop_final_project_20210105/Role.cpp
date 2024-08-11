#include "Role.h"



Role::Role(int x, int y) {
	setLife(true);
	setPosition_x(x);
	setPosition_y(y);
	setSpeed_y(0);
	setSpeed_x(0);
	setFriction(2);
	setJumped(0);
	setDirection(1);
}
void Role::setLife(bool l) {
	life = l;
}
bool Role::getLife() {
	return life;
}
void Role::setPosition_x(int x) {
	role_position.x = x;
}
void Role::setPosition_y(int y) {
	role_position.y = y;
}
int Role::getPosition_x() {
	return role_position.x;
}
int Role::getPosition_y() {
	return role_position.y;
}
void Role::setPixelPosition_x(int x) {
	role_pixel_position.x = x;
}
void Role::setPixelPosition_y(int y) {
	role_pixel_position.y = y;
}
int Role::getPixelPosition_x() {
	return role_pixel_position.x;
}
int Role::getPixelPosition_y() {
	return role_pixel_position.y;
}
position Role::getPosition() {
	return role_pixel_position;
}
position Role::getPixelPosition() {
	return role_pixel_position;
}
void Role::setSpeed_x(int Speed) {
	speed_x = Speed;
}
void Role::setSpeed_y(int Speed) {
	speed_y = Speed;
}
int Role::getSpeed_x() {
	return speed_x;
}
int Role::getSpeed_y() {
	return speed_y;
}
void Role::setFriction(int f) {
	friction = f;
}
int Role::getFriction() {
	return friction;
}
void Role::setJumped(int done) {
	jumped = done;
}
int Role::getJumped() {
	return jumped;
}
void Role::setDirection(int direction) {
	this->direction = direction;
}
int Role::getDirection() {
	return direction;
}
void Role::setIdentify(int i) {
	identify = i;
}
int Role::getIdentify() {
	return identify;
}