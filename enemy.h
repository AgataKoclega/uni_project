#pragma once
#include"force.h"
#include<SFML\Graphics.hpp> 
#include <SFML\Audio.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include<vector>

using namespace sf;

class Enemy
{
private:
	Texture*my_texture;
	Texture*explosion;
	Sprite avatar;
	RectangleShape hitbox;

	Vector2f max_velocity;

	int lvl;
	int alive = 50;
	int killed = 0;

public:
	Enemy(Texture*my_texture, Texture*explosion, Vector2f my_position,int difficulty, Vector2f max_velocity = Vector2f(15.f, 0.f));
	virtual ~Enemy();

	//Accesors:
	inline const FloatRect& getGlobalBounds()const 
	{
		return this->avatar.getGlobalBounds();
	}
	
	inline const Vector2f& getPossition()const
	{
		return this->avatar.getPosition(); 
	}

	inline const RectangleShape getHitbox() const
	{
		return this->hitbox;
	}

	inline void setVelocity(Vector2f velocity) 
	{
		max_velocity = velocity;
	}

	inline void setAvatarTexture(IntRect texture_rect, Vector2f scale) 
	{
		avatar.setTextureRect(texture_rect); avatar.setTexture(*this->explosion); avatar.setScale(scale);
	}

	inline void Kill() 
	{
		killed = 1; 
	}

	//Methods:
	int level();
	void movement();
	void update();
	void draw(RenderTarget &my_target);

	virtual bool check_if_hit(RectangleShape);//polymorphizm
	bool return_killed();
	bool dead();

	

};
