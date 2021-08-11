#include "musicOptions.h"


void musicOptions::musicOptInitialSetup()
{
	sf::Font font;
	if (!font.loadFromFile("Fonts/Roboto-Medium.ttf")) {
		throw "Font in musicOptions is not loading";
	}
	btn1 = new Btn("   Study   ", { 155.0f,610.0f }, 16,font,"1");
	btn2 = new Btn("    Rain   ", { 310.0f,610.0f }, 16, font,"2");
	btn3 = new Btn(" Chill-hop ", { 465.0f,610.0f }, 16, font,"3");
	btn4 = new Btn("   Beatz   ", { 620.0f,610.0f }, 16, font,"4");

	this->activeTrack= 1;						//track that is selected from options
	this->prevActiveTrack = 0;					//track that was selected previously

	btn1->SetFillColor(sf::Color(INITIAL_COLOR));
	btn2->SetFillColor(sf::Color(INITIAL_COLOR));
	btn3->SetFillColor(sf::Color(INITIAL_COLOR));
	btn4->SetFillColor(sf::Color(INITIAL_COLOR));
	btn1->SetTextColor(sf::Color::White);
	btn2->SetTextColor(sf::Color::White);
	btn3->SetTextColor(sf::Color::White);
	btn4->SetTextColor(sf::Color::White);
}


void musicOptions::loadActiveMusic()
{
	std::string filename = "Sounds/" + std::to_string(this->activeTrack) + ".ogg";
	std::cout << filename << std::endl;
	if (!music.openFromFile(filename)) {
		throw "Couldn't load the music file";
	}
	music.setLoop(true);
}

void musicOptions::playActiveMusic()
{
	music.play();
	this->isPlaying = 1;
}


void musicOptions::pauseActiveMusic()
{
	music.pause();
	this->isPlaying = 0;
}


void musicOptions::musicOptPollEvents(sf::RenderWindow& window,sf::Event& event)
{
	std::string temp;
	temp = btn1->BtnEvents(window, event);
	activeTrack = (!temp.length()) ? activeTrack : std::stoi(temp);
	temp = btn2->BtnEvents(window, event);
	activeTrack = (!temp.length()) ? activeTrack : std::stoi(temp);
	temp = btn3->BtnEvents(window, event);
	activeTrack = (!temp.length()) ? activeTrack : std::stoi(temp);
	temp = btn4->BtnEvents(window, event);
	activeTrack = (!temp.length()) ? activeTrack : std::stoi(temp);

}

void musicOptions::musicOptUpdateFromEvents()
{
	switch (this->activeTrack) {						//to make button for active track yellow (show if selected)
	case 1:
		btn1->SetFillColor(sf::Color(251, 208, 60));
		btn1->SetTextColor(sf::Color::Black);
		break;
	case 2:
		btn2->SetFillColor(sf::Color(251, 208, 60));
		btn2->SetTextColor(sf::Color::Black);
		break;
	case 3:
		btn3->SetFillColor(sf::Color(251, 208, 60));
		btn3->SetTextColor(sf::Color::Black);
		break;
	case 4:
		btn4->SetFillColor(sf::Color(251, 208, 60));
		btn4->SetTextColor(sf::Color::Black);
		break;
	}
	if (this->activeTrack != this->prevActiveTrack) {   //for not loading music again if the button which is active is pressed again
		if (this->isPlaying) {							//if music is playing and user opts to change first pause the music
			this->pauseActiveMusic();
			this->isPlaying = 1;						// For (94)..because pausing sets isPlaying to zero 
		}
		this->prevActiveTrack = this->activeTrack;
		this->loadActiveMusic();						
		if (this->isPlaying) {							// (94) if music was playing and user changes activeMusic then play music automatically
			this->playActiveMusic();
		}
	}
	
}

void musicOptions::musicOptDrawComponents(sf::RenderWindow& window)
{
	btn1->DrawTo(window);
	btn2->DrawTo(window);
	btn3->DrawTo(window);
	btn4->DrawTo(window);
}
