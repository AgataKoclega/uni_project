#pragma once
#include "player.h"
#include"frenemy.h"

class Main_game
{
	private:
		RenderWindow*my_window;
		
		Font my_font;
		
		Player *my_player;

		Texture my_player_tex;
		Texture my_force_tex;
		Texture my_backg;
		Texture score_bg;

		Text best_score;

		std::vector<Enemy> ships;
		Texture my_ship_tex;
		
		std::vector<Frenemy> bonuses;
		Texture my_ship_destroyed;
		Texture my_bonus_destroyed;

		Text New_level;

		int difficulty;
		int Leaderboard;
		int info_timer;

	public:
		Main_game(RenderWindow*my_window);
		virtual ~Main_game();

		//Accesors we need:
		inline RenderWindow& getWindow()
		{
			return *this->my_window;
		}

		inline std::vector<Enemy>& getEnemy() 
		{ 
			return this->ships;
		}

		inline std::vector<Frenemy>& getFrenemy()
		{
			return this->bonuses;
		}

		//Methods that will be used:
		void update();
		void draw();
		void spawn_enemy();
	    int check_collision();
		void draw_score();

		bool game_over();
		bool check_collision_dead();

		void save_score();
		void load_game();	
};


