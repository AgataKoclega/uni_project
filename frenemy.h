#pragma once
#include "enemy.h"

//The main difference between the Enemy and Frenemy is the moment of being hit 
class Frenemy : public Enemy
{
private:
public:
	Frenemy(Texture*my_texture, Texture*bonus, Vector2f my_position, int difficulty, Vector2f max_velocity = Vector2f(15.f, 0.f));
	~Frenemy();

	bool check_if_hit(RectangleShape);
};
