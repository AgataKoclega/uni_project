#include"menu.h"
#include<math.h>

using namespace sf;

Menu::Menu(RenderWindow* window)
{
	std::cout << "Menu\n";

	this->my_window_menu =window;
	this->my_window_menu->setFramerateLimit(60);//limit to 60 frames per second,
	                                            //we won't be able to display more frames than the monitor can 

	//initializing font 
	this->my_font.loadFromFile("images/arial.ttf");

	// initializing textures 
	this->my_backg.loadFromFile("images/backg11.png");
	this->my_start.loadFromFile("images/1o.png");
	this->my_exit.loadFromFile("images/2o.png");
	this->my_score.loadFromFile("images/3o.png");

	                                      //setting the text in the menu//
	//start(text) 
	t_start.setFont(my_font);
	t_start.setFillColor(Color::Magenta);
	t_start.setString("START");
	t_start.setCharacterSize(45);
	t_start.setStyle(Text::Bold );
	t_start.setPosition(180, 150);

	//exit(text)
	t_exit.setFont(my_font);
	t_exit.setFillColor(Color::Yellow);
	t_exit.setString("EXIT");
	t_exit.setCharacterSize(45);
	t_exit.setStyle(Text::Bold);
	t_exit.setPosition(460, 50);

	//score(text)
	t_score.setFont(my_font);
	t_score.setFillColor(Color::Cyan);
	t_score.setString("BEST SCORE");
	t_score.setCharacterSize(45);
	t_score.setStyle(Text::Bold);
	t_score.setPosition(650, 150);

}

//RTTI
// we need to convert values from float to int
// (in a compile time cast)

int Menu::my_converter()
{
	enum t_names { start, exit, score, nothing };

	if (t_start.getGlobalBounds().contains(static_cast<Vector2f>(sf::Mouse::getPosition(*my_window_menu))))
		return start;//0
	else if (t_exit.getGlobalBounds().contains(static_cast<Vector2f>(sf::Mouse::getPosition(*my_window_menu))))
		return exit;//1
	else if (t_score.getGlobalBounds().contains(static_cast<Vector2f>(sf::Mouse::getPosition(*my_window_menu))))
		return score;//2
	else return nothing;

}

void Menu::draw_menu()
{
	this->my_window_menu->clear();

	//setting the background of the menu
	Sprite s_backg;
	s_backg.setTexture(my_backg);
	s_backg.setScale(0.7f, 0.60f);
	s_backg.setPosition(0,0);
	my_window_menu->draw(s_backg);
	
	//setting the options-images, as all option "has" its own planet
	Sprite s_start;
	s_start.setTexture(my_start);
	s_start.setScale(0.5f,0.5f);
	s_start.setPosition(200,200);

	my_window_menu->draw(s_start);
	my_window_menu->draw(t_start);

	Sprite s_exit;
	s_exit.setTexture(my_exit);
	s_exit.setScale(0.5f, 0.5f);
	s_exit.setPosition(460, 100);

	my_window_menu->draw(s_exit);
	my_window_menu->draw(t_exit);

	Sprite s_score;
	s_score.setTexture(my_score);
	s_score.setScale(0.5f, 0.5f);
	s_score.setPosition(720, 200);

	my_window_menu->draw(s_score);
	my_window_menu->draw(t_score);

	this->my_window_menu->display();
}

Menu::~Menu()
{
	std::cout << "Menu is destroyed"<<std::endl;
}
