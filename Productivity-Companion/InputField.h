#pragma once
#ifndef INPUT_FIELD
#define INPUT_FIELD

#include<iostream>
#include"SFML/Graphics.hpp"
#include<string.h>
#include"button.h"
namespace udh
{
	class inputField
	{
		std::string text;
		sf::Text textdata;
		sf::Font font;
	public:
		sf::RectangleShape crossline;
		bool completed = false;
		udh::Button done;
		udh::Button del;
		udh::Button edit;
		inputField();
		void setdata(std::string a);
		void drawtext(sf::RenderWindow* window);
		std::string getdata();
		sf::Text gettext();
		void setposition(sf::Vector2f position);
		sf::Font getfont();
		void changecolor(sf::RenderWindow* window);
		void setdone();
	};
	void drawlist(std::vector<udh::inputField>& textlist, sf::RenderWindow* window);
	void checkAction(sf::Event event, std::vector<udh::inputField>& textlist, sf::RenderWindow* window,
		std::vector<udh::inputField>::iterator& itredit, udh::inputField& sample, udh::Button& textarea);
	void editTask(udh::inputField& sampletext, std::string& a, sf::Event event, std::vector<udh::inputField>::iterator& edititr,
		udh::Button& textarea);
	void addTask(udh::inputField& sampletext, std::string& a, sf::Event event, std::vector<udh::inputField>& textlist, udh::Button textarea);
}
#endif // !INPUT_FIELD