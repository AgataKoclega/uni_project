#include"player.h"
#include<string>

enum control_the_player { go_up = 0, go_down, go_right, go_left, shooting };

Player::Player(Texture* my_texture, Texture * my_force_tex, int go_up, int go_down, int go_left, int go_right, int shooting)
	:  HealthP(100), HP_max(100),  points(0)//initialization list
{
	std::cout << "Player\n";

	this->my_texture = my_texture;
	this->my_force_tex = my_force_tex;
	this->avatar.setTexture(*this->my_texture);
	this->avatar.setScale(0.09f, 0.09f);

	hitbox.setPosition(avatar.getPosition());//we put the hitbox the same place as the avatar
	hitbox.setSize(Vector2f(1,1));
	hitbox.setScale(avatar.getGlobalBounds().width, avatar.getGlobalBounds().height);

	this->shooter_timer_MAX = 25;
	this->shooter_timer = this->shooter_timer_MAX;

	this->damage_timer_max = 10;
	this->damage_timer = this->damage_timer_max;

	//control
	this->control_the_player[control_the_player::go_up] = go_up;
	this->control_the_player[control_the_player::go_down] = go_down ;
	this->control_the_player[control_the_player::go_right] = go_right;
	this->control_the_player[control_the_player::go_left] = go_left;
	this->control_the_player[control_the_player::shooting] = shooting;

	//The score of the game visible for the user
	this->my_font.loadFromFile("images/arial.ttf");

	score.setFont(my_font);
	score.setFillColor(Color::Red);
	score.setString("0");
	score.setCharacterSize(45);
    score.setStyle(Text::Bold);
	score.setPosition(650, 1);
}

Player::~Player()
{
	std::cout << " Player is destroyed" << std::endl;
}


//the movement method in this class is responsible for the movement of the player 
//with the use of the keyboard(by pushing its buttons:a,d,w,s)
//in this method we also ensure that our player is not out of the window bounds

void Player::movement()
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->control_the_player[control_the_player::go_up])) && avatar.getPosition().y>0)
		this->avatar.move(0.f, -10.f);
	if (Keyboard::isKeyPressed(Keyboard::Key(this->control_the_player[control_the_player::go_down] )) && avatar.getPosition().y < window_bounds.y- avatar.getGlobalBounds().height)
		this->avatar.move(0.f, 10.f);
	if (Keyboard::isKeyPressed(Keyboard::Key(this->control_the_player[control_the_player::go_left] )) && avatar.getPosition().x > 0)
		this->avatar.move(-10.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::Key(this->control_the_player[control_the_player::go_right])) && avatar.getPosition().x < window_bounds.x - avatar.getGlobalBounds().width)
		this->avatar.move(10.f, 0.f);
}

void Player::fight()
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->control_the_player[shooting])) &&this->shooter_timer >= shooter_timer_MAX)
	{
		this->bullets.push_back( Force(my_force_tex, this->player_middle_position) );//creates bullets
		//thanks to player_middle_position, the bullets come just from the center of the player

		this->shooter_timer = 0;//reset timer
	}
}

void Player::update(Vector2u windowBounds)
{
	window_bounds = windowBounds;

	//update timers
	if (this->shooter_timer < this->shooter_timer_MAX)
		this->shooter_timer++;

	if (this->damage_timer < this->damage_timer_max)
		this->damage_timer++;

	//update position of the bullet from the player
	//as we want the bullet to have its orgigin from the center of our player
	this->player_middle_position.x = this->avatar.getPosition().x + this->avatar.getGlobalBounds().width / 2; 
	this->player_middle_position.y= this->avatar.getPosition().y + this->avatar.getGlobalBounds().height / 2;

	this->movement();
	this->fight();

	hitbox.setPosition(avatar.getPosition());

	//the added points are changed into the "string score" thanks to the use of to_string 
	score.setString(std::to_string(points));
}

void Player::draw(RenderTarget &my_target)//RenderTarget is the class in SFML derived from RenderWindow
                                          //it is pretty much the same as RenderWindow, with the exception,
                                          //that we want the bullets from force to be drawn in the player's window(game)
	                                      //as well as the score visible for the player in the games's window
                                          //and this class allows us to do it that way
{
	my_target.draw(this->avatar);

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].draw(my_target);
	}

	my_target.draw(this->score);
}

void Player::add_points(int enemy_level)
{
	points += enemy_level * 100;
}

void Player::do_damage(int amount)
{
	HealthP -= amount;
}

bool Player::is_dead()
{
	return HealthP <= 0;
}

RectangleShape Player::return_hitbox()
{
	return hitbox;
}

int  Player::return_score()
{
	return points;
}
