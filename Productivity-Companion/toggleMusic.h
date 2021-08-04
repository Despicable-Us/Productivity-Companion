#pragma once
#ifndef LOFIIMUSIC
#define LOFIIMUSIC
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "musicOptions.h"


//while inheriting this class 
// 1. inherit publicly
// 2. run the default constructor with the constructor of derived class
// 3. run togglePollEvent inside polling loop
// 4. run updateFromEvent outside polling loop
// 5. run drawbutton 

namespace TOGGLE {
	class ToggleMusic:public musicOptions
	{
	protected:
		sf::RectangleShape btnRect;
		sf::CircleShape btnCirc1;
		sf::CircleShape btnCirc2;
		sf::CircleShape slideCirc;
		sf::Music lofiMusic;
		sf::RectangleShape squiggle;
		sf::Texture squiggle_texture;
		int btnClickedStatus; //for functions running on main
		int interruptedOnce;
		int toggleInterrupt;
		int timerTicking;
		int toggleStatus; 

	public:
		ToggleMusic(sf::RenderWindow&);

		//for click detection
		int checkInBtn(sf::Vector2f);

		//if clicked it changes status (from off to on and vice-versa)
		//also calls another function to run if it is on (for now plays music)
		void changeToggleStatus();

		//functions that run on main
		void toggledrawComponents(sf::RenderWindow &); // updates toggle button according to toggleStatus and draws them
		void togglePollEvent(sf::RenderWindow&,sf::Event&);
		void toggleUpadteFromEvent();

	};
}
#endif