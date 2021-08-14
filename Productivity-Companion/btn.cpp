#include "Btn.h"

/// <summary>
/// Parameterized Contructor
/// </summary>
/// <param name="BtnText">Button Name</param>
/// <param name="btnPos">Position of the button (horizontally and vertically centered)</param>
/// <param name="charSize">Size of the character of the text within the button</param>
/// <param name="font">Font of the text within the button</param>
/// <param name="id">Default parameter for id</param>
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

/// <summary>
/// Loading the text within the button
/// </summary>
void Btn::LoadText()
{
	text.setFont(this->uiFont);
	text.setString(this->btnText);
	text.setCharacterSize(charSize);
	text.setFillColor(sf::Color::Black);
}

/// <summary>
/// Setting the shape of the button 
/// </summary>
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

/// <summary>
/// Setting the position of the button
/// </summary>
/// <param name="pos">2D Vector2f position</param>
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

/// <summary>
/// Setting the text within the button shape
/// </summary>
void Btn::SetText()
{
	text.setOrigin({ textBounds.width / 2, textBounds.height / 2 });
	text.setPosition({ shape.getPosition().x, shape.getPosition().y - text.getCharacterSize() / fixFactor });
}

/// <summary>
/// Setting all the components of the button as a Whole rect
/// </summary>
void Btn::SetBtnRect()
{
	wholeBtnRect.width = C1.getRadius() * 2.f + shape.getSize().x;
	wholeBtnRect.left = C1.getGlobalBounds().left;
	wholeBtnRect.top = C1.getGlobalBounds().top;
	wholeBtnRect.height = C1.getRadius() * 2.f;
}

/// <summary>
/// Setter for the color of the button
/// </summary>
/// <param name="color">Color of button</param>
void Btn::SetFillColor(sf::Color color)
{
	this->shape.setFillColor(color);
	this->C1.setFillColor(color);
	this->C2.setFillColor(color);
}

/// <summary>
/// Setter for the text within the button
/// </summary>
/// <param name="color">Color of text</param>
void Btn::SetTextColor(sf::Color color)
{
	text.setFillColor(color);
}

/// <summary>
/// Hovering effect for the button
/// </summary>
/// <param name="uFlag">uflag is true when yellow hover effect is needed(in pomodoro timer music options)</param>
void Btn::hoverEffect(bool uFlag) //
{
	if (this->wholeBtnRect.contains(this->mousePosView))
	{
		if (uFlag) {
			this->SetFillColor(sf::Color(252, 218, 97));
			text.setFillColor(sf::Color::Black);
		}
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
		if (uFlag) {
			text.setFillColor(sf::Color::White);
			this->SetFillColor(sf::Color(121, 131, 140));
		}
		this->btnScale = 1.f;
		mouseInside = false;
	}

	this->shape.setScale(btnScale, btnScale);
	this->C1.setScale(btnScale, btnScale);
	this->C2.setScale(btnScale, btnScale);
}

/// <summary>
/// Event handler for clicking of the button
/// </summary>
/// <param name="window">Main window referenced</param>
/// <param name="event">Events related to the main window</param>
void Btn::checkClicked(sf::RenderWindow& window, sf::Event& event)
{
	mousePos = sf::Mouse::getPosition(window);
	mousePosView = static_cast<sf::Vector2f>(mousePos);

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.key.code == sf::Mouse::Left) 
		{
			if (this->wholeBtnRect.contains(this->mousePosView)) 
			{
				this->btnClickedStatus = 1;
			}
		}
	}

	if (event.type == sf::Event::MouseButtonReleased) 
	{
		if (event.key.code == sf::Mouse::Left) 
		{
			if (this->btnClickedStatus && this->wholeBtnRect.contains(this->mousePosView)) {
				this->btnClickedStatus = 2;
			}
			else 
			{
				this->btnClickedStatus = 0;
			}
		}
	}
}

/// <summary>
/// Button events for Study Planner
/// </summary>
/// <param name="window">Main Window referenced</param>
/// <param name="event">Events related to the main window</param>
/// <param name="func">Anonymous function bind to the button</param>
/// <param name="btnHide">Referenced boolean</param>
void Btn::BtnEvents(sf::RenderWindow& window, sf::Event& event, std::function<void()> func, bool &btnHide)
{
	if (!btnHide)
	{
		this->checkClicked(window, event);
		this->hoverEffect(false);

		if (this->btnClickedStatus == 2) 
		{
			func();
			this->btnClickedStatus = 0;
		}
	}
}

/// <summary>
/// Overloaded funtion for the event handler
/// </summary>
/// <param name="window">Main Window referenced</param>
/// <param name="event">Events related to the main window</param>
/// <param name="func">Anonymous function bind to the button</param>
void Btn::BtnEvents(sf::RenderWindow& window, sf::Event& event, std::function<void()> func)
{
	this->checkClicked(window, event);
	this->hoverEffect(false);

	if (this->btnClickedStatus == 2) 
	{
		func();
		this->btnClickedStatus = 0;
	}
}

/// <summary>
/// Overloaded function for the event handler
/// </summary>
/// <param name="window">Main Window referenced</param>
/// <param name="event">Events related to the main window</param>
/// <param name="func">Anonymous function bind to the button</param>
/// <param name="name">Selected name</param>
/// <param name="selected_session_name">Referenced selecte name data</param>
void Btn::BtnEvents(sf::RenderWindow& window, sf::Event& event, std::function<void()> func, std::string name, std::string& selected_session_name)
{
	this->checkClicked(window, event);
	this->hoverEffect(false);

	if (this->btnClickedStatus == 2) 
	{
		selected_session_name = name;
		func();
		this->btnClickedStatus = 0;
	}
}

/// <summary>
/// Overloaded function for the button event handler
/// </summary>
/// <param name="window">Main Window referenced</param>
/// <param name="event">Events related to the main window</param>
/// <param name="btn_show">Referenced boolean</param>
void Btn::BtnEvents(sf::RenderWindow& window, sf::Event& event, bool& btn_show)
{
	this->checkClicked(window, event);
	this->hoverEffect(false);

	if (this->btnClickedStatus == 2) 
	{
		btn_show = true;
		this->btnClickedStatus = 0;
	}
}

/// <summary>
/// Overloaded funtion for the button event handler
/// </summary>
/// <param name="window">Main Window referenced</param>
/// <param name="event">Events related to the main window</param>
/// <param name="func">Anonymous function bind to the button</param>
/// <param name="first">First referenced boolean</param>
/// <param name="second">Second referenced boolean</param>
void Btn::BtnEvents(sf::RenderWindow& window, sf::Event& event, std::function<void()> func, bool& first, bool& second)
{
	this->checkClicked(window, event);
	this->hoverEffect(false);

	if (this->btnClickedStatus == 2) 
	{
		func();
		first = false;
		second = false;
		this->btnClickedStatus = 0;
	}
}

/// <summary>
/// Overloaded function for the button event handler
/// </summary>
/// <param name="window">Main Window referenced</param>
/// <param name="event">Events related to the main window</param>
/// <returns>Return the button ID clicked</returns>
std::string Btn::BtnEvents(sf::RenderWindow& window, sf::Event& event)
{
	text.setFillColor(sf::Color::White);
	this->checkClicked(window, event);
	this->hoverEffect(true);

	if (this->btnClickedStatus == 2) 
	{
		return this->btnId;
		this->btnClickedStatus = 0;
	}
	return "";
}

/// <summary>
/// Render all the components of the button to the window referenced
/// </summary>
/// <param name="window">Main window referenced</param>
void Btn::DrawTo(sf::RenderWindow& window)
{
	window.draw(this->shape);
	window.draw(this->C1);
	window.draw(this->C2);
	window.draw(this->text);
}