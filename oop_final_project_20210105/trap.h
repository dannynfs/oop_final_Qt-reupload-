#pragma once

struct position_t {
	int x;
	int y;
};

class trap
{
public:


	trap(int x, int y);

	void setLife();
	bool getLife();

	//set array position
	void setPosition_x(int);
	void setPosition_y(int);
	int getPosition_x();
	int getPosition_y();

	//set pixel position
	void setPixelPosition_x(int);
	void setPixelPosition_y(int);
	int getPixelPosition_x();
	int getPixelPosition_y();

	position_t getPosition();
	position_t getPixelPosition();



private:
	bool life;
	position_t role_position;
	position_t role_pixel_position;
};
#pragma once

