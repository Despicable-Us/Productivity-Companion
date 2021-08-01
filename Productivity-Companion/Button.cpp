#include "Button.h"
extern int viewPos;
/*
			Empty BUTTON constructor
			\brief Constructor
		*/
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

/*
	Overloaded BUTTON constructor
	\brief Constructor
	\param btnText The string to be written in the button itself
	\param btnDmn The dimension / size of the button to be specified
	\param btnPos The sf::Vector2f position of the button in the rendered window
	\param font The font of the text within the button
*/
udh::Button::Button(std::string btnText, sf::Vector2f btnDmn, sf::Vector2f btnPos, sf::Font& font)
{
	this->btnText=btnText;
	this->setBtnSize(btnDmn);
	this->setBtnPosition(btnPos);
	this->setBtnTextFont(font);
	this->text.setString(this->btnText);
	this->setTextSize(20);
	this->setTextPos();
	this->shape.setFillColor(sf::Color(235,235,235));
	this->text.setFillColor(sf::Color::Black);
	btnRect = sf::FloatRect(btnPos.x, btnPos.y, btnDmn.x, btnDmn.y);
}

void udh::Button::setbtnRect(sf::FloatRect rec)
{
	this->btnRect = rec;
}
/*
	A setter for the dimension of the button.
	\brief Member function
	\param sizeF Vector2f as the Size of the Button
*/
void udh::Button::setBtnSize(sf::Vector2f sizeF)
{
	this->shape.setSize(sizeF);
}

/*
	A setter for the position of the button within the rendered window
	\brief Member function
	\param pos Vector2f as the position with respect to the rendered window
*/
void udh::Button::setBtnPosition(sf::Vector2f pos)
{
	this->shape.setPosition(pos);
}

/*
	A setter for the character size of the text in the button
	\brief Member function
	\param size Unsigned INT_8 bit value for the Char size
*/
void udh::Button::setTextSize(uint8_t size)
{
	this->text.setCharacterSize(size);
}

/*
	A setter for the color of the text in the button
	\brief Member function
	\param color sf::Color which takes RGA colorspace values
*/
void udh::Button::setTextColor(sf::Color color)
{
	this->text.setFillColor(color);
}

/*
	A setter for the font of the text in the button
	\brief Member funciton
	\param &font A reference to the sf::Font
*/
void udh::Button::setBtnTextFont(sf::Font& font)
{
	this->text.setFont(font);
}

/*
	Text Position setter with in the button
	\brief Member function
*/
void udh::Button::setTextPos()
{
	sf::FloatRect tB = this->text.getGlobalBounds();
	sf::FloatRect sB = this->shape.getGlobalBounds();
	sf::Vector2f textPos;
	textPos = sf::Vector2f(sB.left+(sB.width / 2 - tB.width / 2), sB.top+(sB.height - tB.height)/5);
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
/*
	Draws the button shape and the button text in the &rendereing window
	\brief Member function
*/
void udh::Button::drawTo(sf::RenderWindow& window)
{
	window.draw(this->shape);
	window.draw(this->text);
}
void udh::Button::setbtncolor(sf::Color color)
{
	this->shape.setFillColor(color);
}
/*
	Handles the events for the button such as the hovering effect,
	and the onClick replica which can be used for calling the function
	passed to this member function as the last parameter
	\brief Member function
	\param &event sf::Event, events polled from the window
	\param &window sf::RenderWindow, the rendering window
	\param func std::function<void()>, function passed as a lambda expression which calls the clicking action
*/
void udh::Button::btnEvents(sf::Event& event, sf::RenderWindow& window, std::function<void()> func)
{
	sf::Vector2i mouseCursorPos = sf::Mouse::getPosition(window);
	if (event.type == sf::Event::MouseMoved)
	{
		if (this->btnRect.contains((sf::Vector2f)mouseCursorPos))
		{
			this->shape.setFillColor(sf::Color(200, 200, 200));
		}
		else
		{
			this->shape.setFillColor(sf::Color::White);
		}
	}
	if (this->btnRect.contains((sf::Vector2f)mouseCursorPos))
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			func();
		}
	}
}

void udh::Button::setoutline(sf::Color color, int width)
{
	this->shape.setOutlineColor(color);
	this->shape.setOutlineThickness(width);
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
	//static bool state;
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
		if (!this->editing)
		{
			this->setbtntext("add task");
			this->state = false;
		}
	}
	return this->state;
}
bool udh::Button::ispressed(sf::Event event, sf::RenderWindow& window)
{
	//static bool state;
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
	this->setbtntext("add task");
}

