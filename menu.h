#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace sf;

class Menu
{
private:
	RenderWindow*my_window_menu;

	Font my_font;

    Texture my_backg;
	Texture my_start;
	Texture my_exit;
	Texture my_score;

	Text t_start;
	Text t_exit;
	Text t_score;
	
public:
	Menu(RenderWindow*my_window_menu);
	~Menu();

	//Accesor:
	inline RenderWindow& getWindow()
	{
		return *this->my_window_menu; // we need to get the window out of the private part of the class
	}

	//Methods:
	int my_converter();//the method that is responsible for converting the Vector 2f to 2i
	                   //as we need int values to use MouseButtonPress then, but to use getPosition
	                   // there must be used Vector2f with "floats"
	void draw_menu();//the method that is responsible for drawing the menu

};
