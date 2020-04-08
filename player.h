#pragma once
#include"force.h"

class Player
{
private:
	Vector2f player_middle_position;// the coordinates of the center of the player,

	int shooter_timer;//plain shoot timer
	int shooter_timer_MAX;

	int damage_timer;//how long after particular damage the player can be hit again
	int damage_timer_max;

	Vector2u window_bounds;

	Texture *my_texture;
	Sprite avatar;

	RectangleShape hitbox;//the are where player" receive the move"

	Font my_font;
	Text score;

	std::vector<Force> bullets;//the weapon of the player

	Texture *my_force_tex;

	int control_the_player[5];//the array with all the controls

	int HealthP;
	int HP_max;
	int points;

public:
	//the values corresponding to the wanted push buttons on the keyboard:: 22=w, 18=s, 0=a, 3=d, 57=space
	Player(Texture* my_texture, Texture * my_force_tex, int go_up = 22, int go_down=18,int go_left=0, int go_right=3, int shooting=57);
	
	virtual ~Player();

	//Accesor:
	inline std::vector<Force>& getForce()
	{
		return this->bullets; 
	}

	//Methods that will be used:
	void movement();
	void draw(RenderTarget &my_target);
	void update(Vector2u windowBounds);
	void fight();
	void add_points(int enemy_level);
	void do_damage(int);

	RectangleShape return_hitbox();
	bool is_dead();
	int return_score();

};