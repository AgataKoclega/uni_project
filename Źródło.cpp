///_________________________________________________PROPER CODE_________________________________________________________________

#include "main_game.h"
#include <iostream>
#include"menu.h"

int main()
{
	srand(time(NULL));//source reset
	int choice = 0;//variable which helps with switching the windows

	//creating my window-Menu

	RenderWindow my_window_menu(VideoMode(1080, 608), "MENU", Style::Default);
	Menu my_menu(&my_window_menu);

	//main game loop
	while (my_window_menu.isOpen())
	{
		Event my_event_menu;
		while (my_window_menu.pollEvent(my_event_menu))
		{
			switch (my_event_menu.type)
			{
			case Event::Closed:  
			{
				my_window_menu.close();
				return 0;								
				break;
			}
			case Event::KeyPressed:
				switch (my_event_menu.key.code)
				{
				case Keyboard::Escape:
					my_window_menu.close();
					return 0;
					break;
				}
		
			case Event::MouseButtonPressed:
			{
				switch (my_menu.my_converter()) 
				{
				case 0: 
				{
					std::cout << "Start" << std::endl;

					choice = 1;
					break;
				}
				case 1: 
				{
					my_window_menu.close();
					return 0;
					break;
				}
				case 2: 
				{
					std::cout << "Score" << std::endl;
					choice = 2;
					break;
				}
				default:
				{
					break;
				}

				}
				break;
			}
			}
		}
			my_menu.draw_menu();

			switch (choice)
			{

			case 1:
			{
			RenderWindow my_window(VideoMode(1080, 608), "THE GALAXY, far far away...", Style::Default);
			Main_game my_game(&my_window);
				
				while (my_window.isOpen()&&my_game.game_over())
				{
					Event my_event_game;

					while (my_window.pollEvent(my_event_game))
					{
						switch (my_event_game.type)
						{
						case Event::Closed:
						{
							my_window.close();
							return 0;									
							break;
						}
						case Event::KeyPressed:
							switch (my_event_game.key.code)
							{
							case Keyboard::Escape:
								choice = 0;
								my_window.close();
								break;
							}

						}
						
					}
					my_game.update();
	                my_game.draw();

				}
				my_game.save_score();
			
				my_window.close();// closing the menu and returning to the menu loop
				choice = 0;
				break;
			}

			case 2:
			{
				RenderWindow my_window(VideoMode(1080, 608), "Score", Style::Default);
				Main_game my_game(&my_window);

				while (my_window.isOpen())
				{
					Event my_event_game;

					while (my_window.pollEvent(my_event_game))
					{
						switch (my_event_game.type)
						{
						case Event::Closed:
						{
							my_window.close();
							return 0;
							break;
						}
						case Event::KeyPressed:
							switch (my_event_game.key.code)
							{
							case Keyboard::Escape:
								choice = 0;
								my_window.close();
								break;
							}
						}
					}
                   my_game.draw_score();
				}
				break;
			}
			default: 
			{
				break;
			}
			}
	}

	system("PAUSE");
	return 0;
}


