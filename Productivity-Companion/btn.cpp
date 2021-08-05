#include "Btn.h"

Btn::Btn(std::string BtnText, sf::Vector2f btnPos, uint8_t charSize, sf::Font& font, const std::string& id) {
	this->btnText = BtnText;
	this->inputBtnPos = btnPos;
	this->uiFont = font;
	this->charSize = charSize;
	this->btnId = id;
	LoadText();
	SetBtnShape();
	SetText();
	SetBtnRect();
}

void Btn::LoadText()
{
	text.setFont(this->uiFont);
	text.setString(this->btnText);
	text.setCharacterSize(charSize);
	text.setFillColor(sf::Color::Black);
}

void Btn::SetBtnShape()
{
	textBounds = this->text.getGlobalBounds();
	shape.setSize({ textBounds.width + this->text.getCharacterSize(), textBounds.height + this->text.getCharacterSize() + this->charSize / 2 });
	shape.setOrigin({ shape.getSize().x / 2, shape.getSize().y / 2 });
	shape.setPosition(inputBtnPos);
	shapeBounds = this->shape.getGlobalBounds();

	C1.setRadius(shapeBounds.height / 2);
	C2.setRadius(shapeBounds.height / 2);
	C1.setOrigin({ C1.getRadius(), C1.getRadius() });
	C2.setOrigin({ C2.getRadius(), C2.getRadius() });
	C1.setPosition({ shapeBounds.left, shapeBounds.top + shapeBounds.height / 2 });
	C2.setPosition({ shapeBounds.left + shapeBounds.width, shapeBounds.top + shapeBounds.height / 2 });
}

void Btn::SetBtnPosition(sf::Vector2f pos)
{
	shape.setPosition(pos);
	shapeBounds = this->shape.getGlobalBounds();

	C1.setRadius(shapeBounds.height / 2);
	C2.setRadius(shapeBounds.height / 2);
	C1.setOrigin({ C1.getRadius(), C1.getRadius() });
	C2.setOrigin({ C2.getRadius(), C2.getRadius() });
	C1.setPosition({ shapeBounds.left, shapeBounds.top + shapeBounds.height / 2 });
	C2.setPosition({ shapeBounds.left + shapeBounds.width, shapeBounds.top + shapeBounds.height / 2 });
	SetText();
	SetBtnRect();
}

void Btn::SetText()
{
	text.setOrigin({ textBounds.width / 2, textBounds.height / 2 });
	text.setPosition({ shape.getPosition().x, shape.getPosition().y - text.getCharacterSize() / fixFactor });
}

void Btn::SetBtnRect()
{
	wholeBtnRect.width = C1.getRadius() * 2.f + shape.getSize().x;
	wholeBtnRect.left = C1.getGlobalBounds().left;
	wholeBtnRect.top = C1.getGlobalBounds().top;
	wholeBtnRect.height = C1.getRadius() * 2.f;
}

void Btn::SetFillColor(sf::Color color)
{
	this->shape.setFillColor(color);
	this->C1.setFillColor(color);
	this->C2.setFillColor(color);
}

void Btn::SetTextColor(sf::Color color)
{
	text.setFillColor(color);
}

void Btn::BtnEvents(sf::RenderWindow& window, sf::Event& event, std::function<void()> func, bool &btnHide)
{
	if (!btnHide)
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

		this->shape.setScale(btnScale, btnScale);
		this->C1.setScale(btnScale, btnScale);
		this->C2.setScale(btnScale, btnScale);
	}
}

void Btn::BtnEvents(sf::RenderWindow& window, sf::Event& event, std::function<void()> func)
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
	//	if (event.type == sf::Event::MouseButtonReleased)
	//	{
	//		if (event.key.code == sf::Mouse::Left)
	//		{
	//			func();
	//		}
	//	}
	//}



	this->shape.setScale(btnScale, btnScale);
	this->C1.setScale(btnScale, btnScale);
	this->C2.setScale(btnScale, btnScale);
	
}

void Btn::BtnEvents(sf::RenderWindow& window, sf::Event& event, std::function<void()> func, std::string name, std::string& selected_session_name)
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
				selected_session_name = name;
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

	this->shape.setScale(btnScale, btnScale);
	this->C1.setScale(btnScale, btnScale);
	this->C2.setScale(btnScale, btnScale);
}

void Btn::BtnEvents(sf::RenderWindow& window, sf::Event& event, bool& btn_show)
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
				btn_show = true;
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

	this->shape.setScale(btnScale, btnScale);
	this->C1.setScale(btnScale, btnScale);
	this->C2.setScale(btnScale, btnScale);
}

void Btn::BtnEvents(sf::RenderWindow& window, sf::Event& event, std::function<void()> func, bool& first, bool& second)
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
				first = false;
				second = false;
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

	this->shape.setScale(btnScale, btnScale);
	this->C1.setScale(btnScale, btnScale);
	this->C2.setScale(btnScale, btnScale);
}

std::string Btn::BtnEvents(sf::RenderWindow& window, sf::Event& event)
{
	text.setFillColor(sf::Color::White);
	mousePos = sf::Mouse::getPosition(window);
	mousePosView = static_cast<sf::Vector2f>(mousePos);

	if (this->wholeBtnRect.contains(this->mousePosView))
	{
		this->SetFillColor(sf::Color(252, 218, 97));
		text.setFillColor(sf::Color::Black);
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
				return btnId;
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
		text.setFillColor(sf::Color::White);
		this->SetFillColor(sf::Color(121, 131, 140));
		this->btnScale = 1.f;
		mouseInside = false;
	}

	this->shape.setScale(btnScale, btnScale);
	this->C1.setScale(btnScale, btnScale);
	this->C2.setScale(btnScale, btnScale);
	return "";
}



void Btn::DrawTo(sf::RenderWindow& window)
{
	window.draw(this->shape);
	window.draw(this->C1);
	window.draw(this->C2);
	window.draw(this->text);
}