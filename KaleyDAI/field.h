#pragma once
#include <stdc++.h>
#include "SFML/Graphics.hpp"


class InputField
{
	public:
		sf::RectangleShape shape;
		sf::CircleShape Cleft, Cright;
		sf::Text text;
		std::string inputText;
		sf::Vector2f inputFieldPos;
		sf::Font inputFont;
		sf::Vector2f rectSize;
		sf::FloatRect rectBounds;
		size_t charSize = 16;
		sf::FloatRect wholeInputRect;
		sf::Vector2i mousePos;
		sf::Vector2f mousePosView;
		sf::FloatRect textBounds;
		bool mouseHeld = false;
		std::string bufferString;

		bool isFocused = false;

		InputField(sf::Vector2f fieldPos, sf::Font &font)
		{

			inputFont = font;
			inputFieldPos = fieldPos;
			LoadText();
			CreateInputShape();

		}
		void LoadText()
		{
			text.setFont(inputFont);
			text.setCharacterSize(charSize);
			text.setFillColor(sf::Color::Black);
		}

		void SetText(std::string inText)
		{
			text.setString(inText);
			text.setPosition({ wholeInputRect.left+14.f, wholeInputRect.top + 5.f});
		}

		void CreateInputShape()
		{
			shape.setSize({ 500.f, float(charSize + 14) });
			rectSize = shape.getSize();
			shape.setOrigin({rectSize.x/2, rectSize.y/2});
			shape.setPosition(inputFieldPos);
			rectBounds = shape.getGlobalBounds();

			Cleft.setRadius(rectSize.y / 2);
			Cright.setRadius(rectSize.y / 2);
			Cleft.setOrigin({Cleft.getRadius(), Cleft.getRadius()});
			Cright.setOrigin({ Cleft.getRadius(), Cleft.getRadius() });
			Cleft.setPosition({ rectBounds.left, rectBounds.top + rectBounds.height / 2 });
			Cright.setPosition({ rectBounds.left + rectBounds.width, rectBounds.top + rectBounds.height / 2 });

			SetWholeRect();
		}

		void SetWholeRect()
		{
			wholeInputRect.width = Cleft.getRadius() * 2.f + shape.getSize().x;
			wholeInputRect.left = Cleft.getGlobalBounds().left;
			wholeInputRect.top = Cleft.getGlobalBounds().top;
			wholeInputRect.height = Cleft.getRadius() * 2.f;
		}

		void InputEvent(sf::RenderWindow& window, sf::Event& event)
		{
			mousePos = sf::Mouse::getPosition(window);
			mousePosView = static_cast<sf::Vector2f>(mousePos);

			if (wholeInputRect.contains(mousePosView))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (!mouseHeld)
					{
						std::cout << "Inside" << std::endl;
						mouseHeld = true;
						isFocused = true; 
						shape.setFillColor(sf::Color(255, 255, 255, 255));
						Cleft.setFillColor(sf::Color(255, 255, 255, 255));
						Cright.setFillColor(sf::Color(255, 255, 255, 255));
					}
				}
				else
				{
					mouseHeld = false;
				}
			}
			else
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (!mouseHeld)
					{
						std::cout << "Ouside" << std::endl;
						mouseHeld = true;
						isFocused = false;
					}
				}
				else
				{
					mouseHeld = false;
				}
			}

			if (isFocused)
			{
				if (inputText.size() >= 1 && inputText[inputText.size() - 1] != '_')
				{
					inputText += '_';
					SetText(inputText);
				}
				// first time focussed
				if (inputText.size() == 0)
				{
					inputText += "_";
					SetText(inputText);
					std::cout << "Here" << std::endl;
				}
				else
				{
					if (event.type == sf::Event::TextEntered)
					{
						
						if (event.text.unicode < 128)
						{
							if (inputText.size() == 1)
							{
								inputText.clear();
							}

							if (event.text.unicode == 8 && bufferString.size() >= 1)
							{
								bufferString.pop_back();
							}

							else if(text.getGlobalBounds().width < shape.getGlobalBounds().width && event.text.unicode != 8)
							{
								bufferString.push_back(static_cast<char>(event.text.unicode));
							}
							inputText.clear();
							inputText += bufferString + "_";
							SetText(inputText);	
						}
					}
				}
			}
			else
			{
				shape.setFillColor(sf::Color(230, 230, 230));
				Cleft.setFillColor(sf::Color(230, 230, 230));
				Cright.setFillColor(sf::Color(230, 230, 230));
				if (inputText.size() >= 1 && inputText[inputText.size() - 1] == '_')
				{
					inputText.pop_back();
					SetText(inputText);
				}
			}

		}

		void DrawTo(sf::RenderWindow& window)
		{
			
			window.draw(Cleft);
			window.draw(Cright);
			window.draw(shape);
			window.draw(text);
		}
};
