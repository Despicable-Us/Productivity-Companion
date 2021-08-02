#pragma once
#ifndef MUSIC_OPTIONS
#define MUSIC_OPTIONS
#include <SFML/Audio.hpp>
#include "Btn.h"

#define INITIAL_COLOR 121,131,140
#define HOVER_COLOR
#define ACTIVE_COLOR

class musicOptions
{
	Btn* btn1;
	Btn* btn2;
	Btn* btn3;
	Btn* btn4;
	sf::Music music;
	int activeTrack;
	int prevActiveTrack;
	
public:
	int nowPlaying;
	int isPlaying;
	void musicOptInitialSetup();
	void loadActiveMusic();
	void playActiveMusic();
	void pauseActiveMusic();
	void musicOptPollEvents(sf::RenderWindow& , sf::Event& );
	void musicOptUpdateFromEvents();
	void musicOptDrawComponents(sf::RenderWindow & window);
};

#endif


