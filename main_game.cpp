#include"main_game.h"
#include<fstream>
#include <sstream>

Main_game::Main_game(RenderWindow*window)
{
	std::cout << "Game\n";

	this->my_window = window;
	this->my_window->setFramerateLimit(60);// we use the pointer to have set frame here rather than in the int main()

	//initializing font
	this->my_font.loadFromFile("images/arial.ttf");

	// initializing textures
    this->my_player_tex.loadFromFile("images/brit1.png"); 
	this->my_force_tex.loadFromFile("images/star.png");
	this->my_ship_tex.loadFromFile("images/bebe.png");//enemy

	this->my_ship_destroyed.loadFromFile("images/expo.png");
	this->my_bonus_destroyed.loadFromFile("images/gift.png");


	this->my_backg.loadFromFile("images/dark.png");
	this->score_bg.loadFromFile("images/dede1.png");

	// initializing the player
	my_player = new Player(&this->my_player_tex,&this->my_force_tex);

	difficulty = 1;

	New_level.setFont(my_font);
	New_level.setString("Difficulty increased !!!");
	New_level.setPosition(334,200);
	New_level.setCharacterSize(70);
	New_level.setStyle(Text::Bold);
	New_level.setFillColor(Color::Red);

	info_timer = 30;
}

Main_game::~Main_game()
{
	delete my_player;//we created new Player, so to avoid memory leak we have to delete it in the destuctor
	std::cout << "Main_game is destroyed" << std::endl;
}


int Main_game::check_collision()//we are checking the collision of player with the enemy and then with the frenemy
{
	for (size_t k = 0; k < this->my_player->getForce().size(); k++)
	{
		for (size_t l = 0; l < this->getEnemy().size(); l++)
		{
			if (!getEnemy()[l].return_killed() && getEnemy()[l].check_if_hit(my_player->getForce()[k].return_hitbox()))//returns the "the level" of enemy- if the player was killed
			{
				this->my_player->getForce().erase(this->my_player->getForce().begin() + k);
				my_player->add_points(getEnemy()[l].level());
				return 1;
			}
		}
		
		for (size_t l = 0; l < this->getFrenemy().size(); l++)
		{
			if (!getFrenemy()[l].return_killed() && getFrenemy()[l].check_if_hit(my_player->getForce()[k].return_hitbox()))
			{
				this->my_player->getForce().erase(this->my_player->getForce().begin() + k);
				return 1;
			}
		}

	}
	return 0;
}

void Main_game::update()
{
    //player update
	my_player->update(this->my_window->getSize());//it will update it to the movement stuff

	//bullets update
	for (size_t k = 0; k < this->my_player->getForce().size(); k++)
	{ 
		this->my_player->getForce()[k].update();

		//window bounds checking
           if (this->my_player->getForce()[k].getPossition().x > this->my_window->getSize().x)
	          {
		           this->my_player->getForce().erase(this->my_player->getForce().begin() + k);
		           break;
	          }
	}

	//enemy update
	for (size_t k = 0; k < this->getEnemy().size(); k++)
	{
		this->getEnemy()[k].update();

		if (this->getEnemy()[k].getPossition().x < 0 || this->getEnemy()[k].dead())	//this one is destroying the enemy
		{
			//std::cout << "dead";
			this->getEnemy().erase(this->getEnemy().begin() + k);
			break;
		}
	}

	//frenemy update
	for (size_t l = 0; l < this->getFrenemy().size(); l++)
	{
		this->getFrenemy()[l].update();

		if (this->getFrenemy()[l].getPossition().x < 0)
		{
			this->getFrenemy().erase(this->getFrenemy().begin() + l);
			break;
		}
	}

	if (rand() % 30 / difficulty == 1)
		spawn_enemy();

	if (my_player->return_score() > 5000 && info_timer == 30)//when the diffiluty would increased, the speed of the game(enemies)
	{                                                        //increases as well
		difficulty = 2;
		info_timer--;
	}

	check_collision();
	check_collision_dead();
}

void Main_game::draw()
{
	this->my_window->clear();

	//setting the background of the main game
	Sprite s_backg;
	s_backg.setTexture(my_backg);
	s_backg.setPosition(0, 0);
	my_window->draw(s_backg);
	
	my_player->draw(*my_window);

	//drawing enemies
	for (size_t i = 0; i < this->ships.size(); i++)
	{
		this->ships[i].draw(*my_window);
	}

	for (size_t i = 0; i < this->bonuses.size(); i++)
	{
		this->bonuses[i].draw(*my_window);
	}
	if (info_timer < 30 && info_timer>0)
	{
		my_window->draw(New_level);
		info_timer--;
	}
	
	this->my_window->display();
}

void Main_game::spawn_enemy()
{
	int position_height = rand() % (my_window->getSize().y + 100) - 20;

	bool special_ship = (rand() % 5 == 1); //// 1 out of 5 ships(frenemy) is a bonus one

	if (special_ship)
		this->bonuses.push_back(Frenemy(&my_ship_tex, &my_bonus_destroyed, Vector2f(my_window->getSize().x, position_height), difficulty, Vector2f(-2.f, 0)));
	else
		this->ships.push_back(Enemy(&my_ship_tex, &my_ship_destroyed, Vector2f(my_window->getSize().x, position_height), difficulty, Vector2f(-2.f, 0)));
}

void Main_game::draw_score()
{
	this->my_window->clear();

	//setting the background of the score
	Sprite score_backg;
	score_backg.setTexture(score_bg);
	score_backg.setPosition(0, 0);
	my_window->draw(score_backg);

	best_score.setFont(my_font);
	best_score.setFillColor(Color::Blue);
	best_score.setString("BEST ONES");
	best_score.setCharacterSize(58);
    best_score.setStyle(Text::Bold);
	best_score.setPosition(334, 1);
	my_window->draw(best_score);

	load_game();

	this->my_window->display();
}

bool Main_game::game_over()
{
	return !my_player->is_dead();
}

bool Main_game::check_collision_dead()//collision of the player with the enemy/frenemy
{

	for (size_t l = 0; l < this->getEnemy().size(); l++)
	{
		if (getEnemy()[l].check_if_hit(my_player->return_hitbox()))
		{
			my_player->do_damage(10 * getEnemy()[l].level());

			this->getEnemy().erase(this->getEnemy().begin() + l);
			return 1;
		}
	}


	for (size_t l = 0; l < this->getFrenemy().size(); l++)
	{
		if (this->getFrenemy()[l].check_if_hit(my_player->return_hitbox()))
		{
			if (getFrenemy()[l].return_killed())
				my_player->add_points(10);
			else
				my_player->do_damage(10);
			this->getFrenemy().erase(this->getFrenemy().begin() + l);
			break;

		}
	}
	return 0;
}

// I/O streams
void Main_game::load_game()
{
	std::fstream myfile;
	myfile.open("save.txt");
	if (!myfile.is_open())
	{
		std::cout << "no scores\n";//First we have to check if the file(we want to keep the scores) is open
	}
	else
	{
		std::string line;
		int max = 10;
		std::getline(myfile, line);//Get line from stream into string

		std::stringstream degree(line);//A stringstream function is to associate a string object with a stream  
		                               //allowing us to read from the string as if it were a stream(just like from cin)
		degree >> Leaderboard;

		// "just" Leaderboard
		while (max > 0) //The score would be read until everything is read
		{
			if (10 - max == Leaderboard)// The current score would be in the red color
				best_score.setFillColor(Color::Red);
			else
				best_score.setFillColor(Color::White);// rest would be white

			std::getline(myfile, line);

			best_score.setString(line);
			best_score.setPosition(425, 70 + (10 - max) * 51);
			my_window->draw(best_score);
			max--;
		}
		myfile.close();
	}
}

void Main_game::save_score()
{
	std::fstream myfile;
	myfile.open("save.txt");

	if (!myfile.is_open())
	{
		std::ofstream tempfile;     // Now we are checking if the file is able to open and 
		tempfile.open("save.txt");	//if not then the new one is going to be created							
		tempfile.close();
		myfile.open("save.txt");
	}

	std::string line;
	int player_score = my_player->return_score();   //Score and line

	int score_table[10] = { 0,0,0,0,0,0,0,0,0,0 }; //in the best scores window, 10 scores would be shown
	std::getline(myfile, line);

	for (int i = 0; i < 10; i++)
	{
		std::getline(myfile, line);          //Now the score is got from the file, convertd from string to int
		std::stringstream degree(line);      //and saved into the table
		degree >> score_table[i];                        
		std::cout << score_table[i] << "\n";
	}

	myfile.close();//We have to close the file and in the next line we open it again to delete what is inside in there
	myfile.open("save.txt", std::ios::out | std::ios::in | std::ios::trunc);   

	int x = 0;
	int temp_score_table[10];

	while (true)
	{	//The new leaderborad table is created with regard to player's score			 

		if (player_score > score_table[x])
		{
			Leaderboard = x;
			for (int i = 0; i < x; i++)
				temp_score_table[i] = score_table[i];
			temp_score_table[x] = player_score;
			for (int i = x + 1; i < 10; i++)
				temp_score_table[i] = score_table[i - 1];
			break;
		}
		x++;
	}

	myfile << Leaderboard;
	myfile << "\n";

	for (int i = 0; i < 10; i++)
	{
		myfile << temp_score_table[i];
		std::cout << temp_score_table[i] << "\n";
		myfile << "\n";
	}

	myfile.close();
}

