#pragma once
class arch {
public:
	arch(int, int);
	void setInitial_x(int);
	void setInitial_y(int);
	int getInitial_x();
	int getInitial_y();
	void setPosition_x(int);
	void setPosition_y(int);
	int getPosition_x();
	int getPosition_y();
	void setPixelPosition_x(int);
	void setPixelPosition_y(int);
	int getPixelPosition_x();
	int getPixelPosition_y();
	void setLife(bool);
	bool getLife();


private:
	int initial_x;
	int initial_y;
	int position_x;
	int position_y;
	int Pixel_x;
	int Pixel_y;
	bool life;
};