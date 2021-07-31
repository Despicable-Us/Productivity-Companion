#pragma once
#ifndef SESSIONAPP_H
#define SESSIONAPP_H
#include "SFML/Graphics.hpp"
#include "Btn.h"
#include "InputField.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <functional>

// COLOR CONTAINER
#define BACKGROUNDC 255,255,255
#define WINWIDTH 740
#define WINHEIGHT 560
#define ANTIALIASING 8
#define FPS 60

class SessionApp
{
	private:
		// Main data components
		//sf::RenderWindow* window;
		//sf::VideoMode videoMode;
		//sf::ContextSettings settings;
		//sf::Event event;

		// UI Components
		sf::Texture texture;
		sf::Sprite background;
		sf::RectangleShape rect;
		sf::View sessionView;

		// Buttons and Inputfield;
		Btn *addSessionBtn;
		InputField* inputSession;

		// Components container
		std::vector<sf::RectangleShape> rects;
		std::vector<sf::Text> textVec;
		std::vector<std::string> inputTexts;

		// UI Typogrphy
		sf::Font fontKaushan;
		sf::Font fontRoboto;
		sf::Text uiText;
		sf::Text testText;
		std::vector<sf::Text> allUIText;

		// Data Accessors
		sf::Vector2u winSize;
		sf::Vector2f winSizeF;

		// Boolean data components and Methods
		std::function<void()> addRect;
		std::function<void()> addSessionTab;
		bool btnHide = false;
		bool inputHide = true;

		// Initializers
		void InitVariables();
		void InitWindow();
		void InitBackground();
		void InitUIFont();
		void InitUIComponents();

	public:
		// Constructors & Destructors
		SessionApp();
		~SessionApp();

		// Accessors
		//const bool isRunning() const;

		// Helper Functions
		void PollEvents();

		// UIText Updaters
		void LogoUITextUpdate();

		// Modifiers (UPDATE)
		void UITextUpdate();
		void ViewUpdate();

		// Window Update & Render
		void Update();
		void Render(sf::RenderWindow& window);
};

#endif