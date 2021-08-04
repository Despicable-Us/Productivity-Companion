#pragma once
#ifndef TIMESETTER
#define TIMESETTER

#include <SFML\Graphics.hpp>
#include <SFML\audio.hpp>
#include <iostream>
#include <math.h>
#include <string.h>
#include <fstream>
#include <Windows.h>
#include "Btn.h"

#define BACKGROUND_COLOR 35,40,52
#define MAIN_CIRCLE_COLOR 220,220,170
#define PLAY_AND_PAUSE_COLOR 75,79,88
#define KNOB_COLOR 121,131,140
#define FILLER_COLOR 75,79,88
#define TIMER_TEXT_COLOR 251,208,60

#include "Points.h"
#include "toggleMusic.h"
namespace dial {
	class timeSetter : private Points,public TOGGLE::ToggleMusic
	{
	private:	
		sf::CircleShape mainCircle;		
		sf::CircleShape knobCircle;
		sf::CircleShape fillers;	
		sf::CircleShape playButton;
		sf::RectangleShape stopButton;

		sf::Vector2f cursorCurrentPos;
		size_t cursor_size;

		std::vector <sf::Vector2f> all_pos;
		std::vector <sf::Vector3f> fiveMult_pos1;
		std::vector <sf::Vector3f> eachMinPos;

		sf::Vector2f stop_pos;
		float stopTime;

		sf::Text timeText;
		sf::Clock clk;
		sf::Font timeFont;

		sf::Music timeUpSound;			//sounds
		sf::Music pauseSound;

		int stopSignDisp;		//for functions that run on main
		int tickingFlag;	
		int knobPressing;
		int stopPressed;

	public:
		//constructor (intializes timeFont and calls initialSetup
		timeSetter(sf::RenderWindow&);

		//initializes all the visual components 
		void initialSetup(sf::RenderWindow& window,int);// 0(first run) 1(timeUP) 2(stop pressed)

		//returns all points on outline of mainCircle
		std::vector<sf::Vector2f> findAllPos();

		//returns all point on outline where time is 0,5,10,15,20....120 mins
		std::vector<sf::Vector3f> find5MultPos();

		//returns all the points where time is 1,2,3,4,5....120 min
		std::vector<sf::Vector3f> findEachMinpos();

		//returns time as a function of angle 360 deg = 120 mins
		float timeInMinutes(sf::Vector2f pos);

		//returns position for time(divisible by 5) form fiveMult_pos1
		//used for setting stop_pos
		sf::Vector2f posForTime(float);

		//returns time in the format "MM::SS" to display
		sf::String timeOutString(float);

		//restarts clk
		void restartClock();

		//updates the timeText according to elapsed time. updates timeText using timeOUtString
		void updateTimeText();

		//(while dragging) it updates cursorCurrentPos,then points the knob and sets cursor_size to print
		void updateFillers(sf::Vector2f);

		//point the Knob circle according the cursorCurrentPos
		void pointKnob();

		//Sets the value of cursor_size and is used for printing fillers 
		void getCursorSize(); 

		//Check if the bounds of cursorCurrentPos is within the knoBCircle.
		//Used to apply dragging fucntionality
		int checkInKnob(sf::Vector2f);

		/*for hover effect*/
		int checkInPlay(sf::Vector2f);
		int checkInStop(sf::Vector2f);
		void increseScale(int);
		void resetScale();

		//Displays the dial when user drags the knob
		void printPressing(sf::RenderWindow& window);

		//Displays the dial when user releases the knob
		void printReleased(sf::RenderWindow& window);

		//Displays the dial when countdown is going on.
		//Calls initialSetup (1) is timer complete
		//Calls initalSteop (2) if timer stopped
		void printTicking(sf::RenderWindow& window, int&, int&);

		void dialPollEvents(sf::RenderWindow&,sf::Event&);
		void dialUpdateFromEvents(sf::RenderWindow&, sf::Event&, bool&, bool&);
		void dialDrawComponents(sf::RenderWindow&);

		//HOME BUTTON
		Btn* home_back_btn;
		bool home_back_btn_clicked;
		std::function<void()> home_back_btn_func;
		sf::Font roboto_font;

		void loadFontBtn();

	};

}

#endif