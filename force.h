#pragma once
#include<SFML\Graphics.hpp> 
#include <SFML\Audio.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include<vector>
#include<string>

using namespace sf;

class Force
{
private:
	Texture*my_texture;
	Sprite avatar;

	Vector2f max_velocity;

	RectangleShape hitbox;

public:
	Force(Texture*my_texture, Vector2f my_position, Vector2f max_velocity= Vector2f(15.f,0.f));
	virtual ~Force();

	//Accesors:
	inline const FloatRect& getGlobalBounds()const //we can do everything with its global bounds directly now 
	{
		return this->avatar.getGlobalBounds();
	}
	
	inline const Vector2f& getPossition()const
	{ 
		return this->avatar.getPosition();
	}

	//Methods:
	void movement();
	void update();
	void draw(RenderTarget &my_target);
	RectangleShape return_hitbox();

};