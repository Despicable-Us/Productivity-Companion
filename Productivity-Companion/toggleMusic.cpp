#include "toggleMusic.h"

TOGGLE::ToggleMusic::ToggleMusic(sf::RenderWindow& window)
{
	float length = 25.0f;
	float height = 35.0f;
	sf::Vector2f pos = sf::Vector2f(50.0f, window.getSize().y - 125.0f);
	this->btnRect.setPosition(pos);
	this->btnRect.setSize(sf::Vector2f(length, height));
	this->btnRect.setOrigin(sf::Vector2f(length/2 , height/2));
	this->btnRect.setFillColor(sf::Color(228, 228, 163));

	float circY = this->btnRect.getPosition().y;
	float circ1X = this->btnRect.getPosition().x - (this->btnRect.getSize().x /2);
	float circ2X = this->btnRect.getPosition().x + (this->btnRect.getSize().x / 2);

	this->btnCirc1.setRadius(height / 2);
	this->btnCirc1.setFillColor(sf::Color(228, 228, 163));
	this->btnCirc1.setOrigin(sf::Vector2f(this->btnCirc1.getRadius(), this->btnCirc1.getRadius()));
	this->btnCirc1.setPosition(sf::Vector2f(circ1X,circY));

	this->btnCirc2.setRadius(height / 2);
	this->btnCirc2.setFillColor(sf::Color(228, 228, 163));
	this->btnCirc2.setOrigin(sf::Vector2f(this->btnCirc2.getRadius(), this->btnCirc1.getRadius()));
	this->btnCirc2.setPosition(sf::Vector2f(circ2X, circY));

	this->slideCirc.setRadius(height / 2.7f);
	this->slideCirc.setFillColor(sf::Color::White);
	this->slideCirc.setOrigin(sf::Vector2f(this->slideCirc.getRadius(), this->slideCirc.getRadius()));

	if (!this->squiggle_texture.loadFromFile("Texture/squig3.png")) {
		std::cout << "could'nt load the squiggle texture" << std::endl;
	}
	this->squiggle.setPosition(sf::Vector2f(0, pos.y - 75.0f));
	this->squiggle.setTexture(&squiggle_texture);
	this->squiggle.setSize(sf::Vector2f(300.0f, 213.0f));
	
	if (!lofiMusic.openFromFile("Sounds/timeUP.ogg")) {
		std::cout << "Music file couldn't be loaded" << std::endl;
	}
	lofiMusic.setAttenuation(100);
	lofiMusic.setLoop(true);

	this->toggleStatus = 0;
	this->btnClickedStatus = 0;
	this->toggleInterrupt = 0;
	this->interruptedOnce = 0;
	this->timerTicking = 0;

	//added for musci options
	this->musicOptInitialSetup();
}

int TOGGLE::ToggleMusic::checkInBtn(sf::Vector2f pos)
{
	if (this->btnRect.getGlobalBounds().contains(pos)) return 1;
	if (this->btnCirc1.getGlobalBounds().contains(pos)) return 1;
	if (this->btnCirc2.getGlobalBounds().contains(pos)) return 1;
	return 0;
}

void TOGGLE::ToggleMusic::changeToggleStatus()
{
	this->toggleStatus = !this->toggleStatus;

}

//functions running on main

void TOGGLE::ToggleMusic::toggledrawComponents(sf::RenderWindow&window)
{
	if (! this->toggleStatus) {										//off
		this->btnRect.setFillColor(sf::Color(169,169,169));
		this->btnCirc1.setFillColor(sf::Color(169, 169, 169));
		this->btnCirc2.setFillColor(sf::Color(169, 169, 169));
		this->slideCirc.setPosition(this->btnCirc1.getPosition());
	}
	else {
		this->btnRect.setFillColor(sf::Color(251, 208, 60));			//on
		this->btnCirc1.setFillColor(sf::Color(251, 208, 60));
		this->btnCirc2.setFillColor(sf::Color(251, 208, 60));
		this->slideCirc.setPosition(this->btnCirc2.getPosition());
	}
	window.draw(this->squiggle);
	window.draw(this->btnRect);
	window.draw(this->btnCirc1);
	window.draw(this->btnCirc2);
	window.draw(this->slideCirc);

	//added for music Options
	if (this->toggleStatus) {
		this->musicOptDrawComponents(window);
	}

}

void TOGGLE::ToggleMusic::togglePollEvent(sf::RenderWindow & window,sf::Event& event)
{
	sf::Vector2f currentPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.key.code == sf::Mouse::Left) {
			if (this->checkInBtn(currentPos)) {
				this->btnClickedStatus = 1;
			}
		}
	}
	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.key.code == sf::Mouse::Left) {
			if (this->btnClickedStatus && this->checkInBtn(currentPos)) {
				this->btnClickedStatus = 2;
			}
			else {
				this->btnClickedStatus = 0;
			}
		}
	}
	//added for music options
	if (this->toggleStatus) {
		this->musicOptPollEvents(window, event);
	}
	//if(toggleStatus) then check for events in provided music options (Rishav ko portion)

}

void TOGGLE::ToggleMusic::toggleUpadteFromEvent()
{
	if (this->btnClickedStatus == 2) {
		this->changeToggleStatus();
		this->btnClickedStatus = 0;	
	}

	//addded for music options
	if (this->toggleStatus) {
		this->musicOptUpdateFromEvents();
		if (toggleInterrupt && timerTicking) {
			this->playActiveMusic();
			this->toggleInterrupt = 0;
		}
	}
	if ((!this->toggleStatus) && isPlaying) {
		this->pauseActiveMusic();
		this->toggleInterrupt = 1;
		this->interruptedOnce = 0;
	}
	
}
