#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include "SFML/Graphics.hpp"
#include <iostream>
#include <ctime>
#include <functional>


class Button
{
	public:
		sf::RectangleShape shape;
		sf::CircleShape C1, C2;
		sf::Vector2f inputBtnDmn;
		sf::Vector2f inputBtnPos;
		sf::Text text;
		sf::Font uiFont;
		std::string btnText;
		sf::FloatRect textBounds;
		sf::FloatRect shapeBounds;
		sf::Vector2i mousePos;
		sf::Vector2f mousePosView;
		sf::FloatRect wholeBtnRect;
		float fixFactor = 4.5f;
		float btnScale = 1.02f;
		bool mouseInside = false;
		bool mouseHeld = false;
		
		Button() {}

		Button(std::string BtnText, sf::Vector2f btnPos, sf::Font& font)
		{
			btnText = BtnText;
			inputBtnPos = btnPos;
			uiFont = font;
			LoadText();
			SetBtnShape();
			SetText();
			SetBtnRect();
		}

		void LoadText()
		{
			text.setFont(this->uiFont);
			text.setString(btnText);
			text.setCharacterSize(20);
		}

		void SetBtnShape()
		{
			textBounds = this->text.getGlobalBounds();
			shape.setSize({ textBounds.width+this->text.getCharacterSize(), textBounds.height+this->text.getCharacterSize() });
			shape.setOrigin({ shape.getSize().x / 2, shape.getSize().y / 2 });
			shape.setPosition(inputBtnPos);
			shapeBounds = this->shape.getGlobalBounds();

			C1.setRadius(shapeBounds.height / 2);
			C2.setRadius(shapeBounds.height / 2);
			C1.setOrigin({ C1.getRadius(), C1.getRadius() });
			C2.setOrigin({ C2.getRadius(), C2.getRadius() });
			C1.setPosition({shapeBounds.left, shapeBounds.top+shapeBounds.height/2});
			C2.setPosition({ shapeBounds.left + shapeBounds.width, shapeBounds.top + shapeBounds.height / 2 });
		}

		void SetText()
		{
			text.setOrigin({ textBounds.width / 2, textBounds.height / 2 });
			text.setPosition({shape.getPosition().x, shape.getPosition().y-text.getCharacterSize() / fixFactor });
			text.setFillColor(sf::Color::Black);
		}

		void SetBtnRect()
		{
			wholeBtnRect.width = C1.getRadius() * 2.f + shape.getSize().x;
			wholeBtnRect.left = C1.getGlobalBounds().left;
			wholeBtnRect.top = C1.getGlobalBounds().top;
			wholeBtnRect.height = C1.getRadius() * 2.f;
		} 

		void DrawTo(sf::RenderWindow &window)
		{
			
			window.draw(this->shape);
			window.draw(this->C1);
			window.draw(this->C2);
			//window.draw(this->text);
			
		}

		void BtnEvents(sf::RenderWindow& window, sf::Event &event, std::function<void()> func)
		{
			mousePos = sf::Mouse::getPosition(window);
			mousePosView = static_cast<sf::Vector2f>(mousePos);

			if (this->wholeBtnRect.contains(this->mousePosView))
			{
				if (!mouseInside)
				{
					this->btnScale = 1.02f;
					mouseInside = true;
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (!mouseHeld)
					{
						mouseHeld = true;
						func();
					}
					else if (mouseHeld)
					{
						this->btnScale = 0.99f;
					}
				}
				else
				{
					mouseHeld = false;
					this->btnScale = 1.02f;
				}
			}
			else
			{
				this->btnScale = 1.f;
				mouseInside = false;
			}
			
			//if (this->wholeBtnRect.contains(this->mousePosView))
			//{	
			//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			//	{
			//		if (!mouseHeld)
			//		{
			//			mouseHeld = true;
			//			func();
			//		}
			//		else if (mouseHeld)
			//		{
			//			this->btnScale = 0.95f;
			//			
			//		}
			//	}
			//	else
			//	{
			//		mouseHeld = false;
			//		this->btnScale = 1.05f;
			//	}
			//	/*this->shape.setScale(btnScale, btnScale);
			//	this->C1.setScale(btnScale, btnScale);
			//	this->C2.setScale(btnScale, btnScale);*/
			//}
			this->shape.setScale(btnScale, btnScale);
			this->C1.setScale(btnScale, btnScale);
			this->C2.setScale(btnScale, btnScale);
		}
};



#endif
