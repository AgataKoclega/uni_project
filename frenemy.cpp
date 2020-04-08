#include"frenemy.h"

Frenemy::Frenemy(Texture*my_texture, Texture*bonus, Vector2f my_position, int difficulty, Vector2f max_velocity)
	:Enemy(my_texture, bonus, my_position, difficulty, max_velocity)
{
	std::cout << "\nFrenemy constructed" << std::endl;
	//As Frenemy took after the Enemy class and we need only the Enemy part, 
	//the change in the constructor is not necessary
}

Frenemy::~Frenemy()
{
	std::cout << "frenemy destructed\n";
}

//When frenemy is hit,in the same moment it changes to the gift's texture and slows down
//After collecting such a gift, the player is granted with 1000 points
//Rest of functions are derived from Enemy
bool Frenemy::check_if_hit(RectangleShape bullet)
{
	bool is_hit = getHitbox().getGlobalBounds().intersects(bullet.getGlobalBounds());
	if (is_hit)
	{
		setVelocity(Vector2f(-1.f, 0));
		setAvatarTexture(IntRect(0, 0, 250, 239), Vector2f(0.1, 0.1));
		Kill();
	}
	return is_hit;
}
