#pragma once

struct position {
	//int identity;
	int x;
	int y;
};

class Role
{
public:

	int R_run;
	int L_run;
	int R_jump;
	int L_jump;
	bool acting;


	Role(int x, int y);

	void setLife(bool);
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

	position getPosition();
	position getPixelPosition();

	//set  speed
	void setSpeed_x(int);
	void setSpeed_y(int);
	int getSpeed_x();
	int getSpeed_y();
	void setFriction(int);
	int getFriction();
	void setJumped(int); //jump only on ground
	int getJumped();

	//set direction
	void setDirection(int);
	int getDirection();



	//identify
	void setIdentify(int);
	int getIdentify();


private:
	bool life;
	int speed;
	int direction;// right -> 1 left -> 2
	int speed_y;
	int speed_x;
	int friction;
	int jumped;
	int identify;
	position role_position;
	position role_pixel_position;
};
