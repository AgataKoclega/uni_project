#include"enemy.h"

Enemy::Enemy(Texture*my_texture, Texture*explosion, Vector2f my_position, int difficulty, Vector2f max_velocity)
{
	lvl = rand() % 3 * difficulty + 1;//starter difficulty is 1, so we have the range form 1 to 3

	this->my_texture = my_texture;
	this->explosion = explosion;
	this->avatar.setTexture(*this->my_texture);
	this->max_velocity = Vector2f(max_velocity.x*lvl, max_velocity.y*lvl);

	this->avatar.setScale(0.22f, 0.22f);
	this->avatar.setPosition(my_position);

	hitbox.setPosition(avatar.getPosition());
	hitbox.setSize(Vector2f(1, 1));
	hitbox.setScale(avatar.getGlobalBounds().width, avatar.getGlobalBounds().height);
	
	std::cout << "enemy constructed\n" ;
}

Enemy::~Enemy()
{
	std::cout << "enemy destructed\n";
}

int Enemy::level()
{
	return lvl;
}

void Enemy::movement()
{
	this->avatar.move(this->max_velocity.x, this->max_velocity.y);
}

void Enemy::update()
{
	this->movement();

	hitbox.setPosition(avatar.getPosition());

}

void Enemy::draw(RenderTarget &my_target)
{
	my_target.draw(this->avatar);
}

//The enemies at first are shot- method Kill is set to 1, then for 10 loops, the enemy still alive
//goes down, while his velocity is (0,0) and texture changes to explosion. After this then loops 
//it is completely dead and it is erased
bool Enemy::check_if_hit(RectangleShape bullet)
{
	//is_hit checks if the force's hitbox lie in the enemy's hitbox, if so both are being erased
	bool is_hit = hitbox.getGlobalBounds().intersects(bullet.getGlobalBounds());
	 
	if (is_hit)
	{
		max_velocity = Vector2f(0, 0);
		avatar.setTextureRect(IntRect(0, 0, 175, 144)); //For correct graphics
		this->avatar.setTexture(*this->explosion);
		Kill();
	}
	return is_hit;
}

bool Enemy::return_killed()
{
	return killed;
}

bool Enemy::dead() 
{
	if (killed) //"slow killing"
		alive--;
	return alive <= 0;
}
