#include "Button.h"
extern int viewPos;

udh::Button::Button()
{
	this->shape.setFillColor(sf::Color(235, 235, 235));
	this->btnRect={ 0.f,0.f,10.f,5.f };
}
udh::Button::Button(sf::Font& font)
{
	this->setBtnTextFont(font);
	this->shape.setFillColor(sf::Color(235, 235, 235));
}

udh::Button::Button(std::string btnText, sf::Vector2f btnDmn, sf::Vector2f btnPos, sf::Font& font)
{
	this->btnText=btnText;
	this->setBtnSize(btnDmn);
	this->setBtnPosition(btnPos);
	this->setBtnTextFont(font);
	this->text.setString(this->btnText);
	this->setTextSize(16);
	this->setTextPos();
	this->shape.setFillColor(sf::Color(235,235,235));
	this->text.setFillColor(sf::Color(100,100,100));
	btnRect = sf::FloatRect(btnPos.x, btnPos.y, btnDmn.x, btnDmn.y);
}

void udh::Button::setbtnRect(sf::FloatRect rec)
{
	this->btnRect = rec;
}

void udh::Button::setBtnSize(sf::Vector2f sizeF)
{
	this->shape.setSize(sizeF);
}

void udh::Button::setBtnPosition(sf::Vector2f pos)
{
	this->shape.setPosition(pos);
}

void udh::Button::setTextSize(uint8_t size)
{
	this->text.setCharacterSize(size);
}

void udh::Button::setTextColor(sf::Color color)
{
	this->text.setFillColor(color);
}

void udh::Button::setBtnTextFont(sf::Font& font)
{
	this->text.setFont(font);
}

void udh::Button::setTextPos()
{
	sf::FloatRect tB = this->text.getGlobalBounds();
	sf::FloatRect sB = this->shape.getGlobalBounds();
	sf::Vector2f textPos;
	textPos = sf::Vector2f(sB.left+(sB.width / 2 - tB.width / 2) - 20.f, sB.top+(sB.height - tB.height)/5);
	this->text.setPosition(textPos);

}

sf::FloatRect  udh::Button::getbounds()
{
	return this->shape.getGlobalBounds();
}

void udh::Button::setbtntext(const char* a)
{
	this->text.setString(a);
}

sf::Vector2f udh::Button::getPosition()
{
	return this->shape.getPosition();
}

void udh::Button::setEditing()
{
	this->editing = true;
}

void udh::Button::unsetEditing()
{
	this->editing = false;
}

void udh::Button::drawTo(sf::RenderWindow& window)
{
	window.draw(this->shape);
	window.draw(this->text);
}

void udh::Button::setbtncolor(sf::Color color)
{
	this->shape.setFillColor(color);
}

void udh::Button::setoutline(sf::Color color, int width)
{
	this->shape.setOutlineColor(color);
	this->shape.setOutlineThickness(float(width));
}

bool udh::Button::getAdding()
{
	return this->adding;
}

void udh::Button::setAddding()
{
	this->adding = true;
}

void udh::Button::unSetAdding()
{
	this->adding = false;
}

bool udh::Button::getstate()
{
	return state;
}

bool udh::Button::IsEditing()
{
	return this->editing;
}

bool udh::Button::isclicked(sf::Event event, sf::RenderWindow& window)
{
	sf::Vector2i mouseCursorPos = sf::Mouse::getPosition(window);
	if (this->btnRect.contains((sf::Vector2f)mouseCursorPos))
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			std::cout << "clicked:";
			this->state = true;
			this->setbtntext("");
		}
	}
	else if (!this->btnRect.contains((sf::Vector2f)mouseCursorPos) && event.mouseButton.button == sf::Mouse::Left)
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			if (!this->IsEditing())
			{
				this->setbtntext("Add Task");
				this->state = false;
			}
		}
	}
	return this->state;
}

bool udh::Button::ispressed(sf::Event event, sf::RenderWindow& window)
{
	sf::Vector2i mouseCursorPos = { sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y-220+viewPos};
	if (this->btnRect.contains((sf::Vector2f)mouseCursorPos))
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			this->state = true;
			this->setbtntext("");
		}
	}
	else
		state = false;
	return state;
}

void udh::Button::setpressed()
{
	this->state = true;
}

void udh::Button::releasePressed()
{
	this->state = false;
	this->setbtntext("Add Task");
}