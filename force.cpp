#include "force.h"

Force::Force(Texture*my_texture, Vector2f my_position, Vector2f max_velocity )
{
	this->my_texture = my_texture;
	this->avatar.setTexture(*this->my_texture);
	this->max_velocity = max_velocity;

	this->avatar.setScale(0.1f,0.1f);
	this->avatar.setPosition(my_position);// the ammunition would be assigned to the avatar

	hitbox.setPosition(avatar.getPosition());//hitbox assigned to the position of the avatar
	hitbox.setSize(Vector2f(1, 1));
	hitbox.setScale(avatar.getGlobalBounds().width, avatar.getGlobalBounds().height);

}

Force::~Force()
{
	std::cout << "Force is destroyed" << std::endl;
}

void Force::movement()
{
	this->avatar.move(this->max_velocity.x, this->max_velocity.y);
}

void Force::update()
{
	this->movement();

	hitbox.setPosition(avatar.getPosition());
}

void Force::draw(RenderTarget &my_target)
{
	my_target.draw(this->avatar);
}

RectangleShape Force::return_hitbox()
{
	return hitbox;
}