#include "InputField.h"

/// <summary>
/// Parameterized Constructors
/// </summary>
/// <param name="fieldPos">Position of the inputfield</param>
/// <param name="font">Font of the text within the field</param>
InputField::InputField(sf::Vector2f fieldPos, sf::Font& font)
{
	this->inputFont = font;
	this->inputFieldPos = fieldPos;
	this->LoadText();
	this->CreateInputShape();
}

/// <summary>
/// Loading and setting the text within the field
/// </summary>
void InputField::LoadText()
{
	text.setFont(inputFont);
	text.setCharacterSize(static_cast<unsigned>(charSize));
	text.setFillColor(sf::Color::Black);
}

/// <summary>
/// Setter for the text string
/// </summary>
/// <param name="inText">Text string data</param>
void InputField::SetText(std::string inText)
{
	text.setString(inText);
	text.setPosition({ wholeInputRect.left + padX, wholeInputRect.top + padY });
}

/// <summary>
/// Initialize the shape of the inputfield
/// </summary>
void InputField::CreateInputShape()
{
	shape.setSize({ this->fieldWidth, float(charSize) + this->padX });
	rectSize = shape.getSize();
	shape.setOrigin({ rectSize.x / 2, rectSize.y / 2 });
	shape.setPosition(inputFieldPos);
	rectBounds = shape.getGlobalBounds();

	Cleft.setRadius(rectSize.y / 2);
	Cright.setRadius(rectSize.y / 2);
	Cleft.setOrigin({ Cleft.getRadius(), Cleft.getRadius() });
	Cright.setOrigin({ Cleft.getRadius(), Cleft.getRadius() });
	Cleft.setPosition({ rectBounds.left, rectBounds.top + rectBounds.height / 2 });
	Cright.setPosition({ rectBounds.left + rectBounds.width, rectBounds.top + rectBounds.height / 2 });

	SetWholeRect();
}

/// <summary>
/// Set the dimension for the whole inputfield rect
/// </summary>
void InputField::SetWholeRect()
{
	wholeInputRect.width = Cleft.getRadius() * 2.f + shape.getSize().x;
	wholeInputRect.left = Cleft.getGlobalBounds().left;
	wholeInputRect.top = Cleft.getGlobalBounds().top;
	wholeInputRect.height = Cleft.getRadius() * 2.f;
}

/// <summary>
/// Event handler for inputfield
/// </summary>
/// <param name="window">Main Window referenced</param>
/// <param name="event">Events related to the main window</param>
/// <param name="inputHide">Referenced boolean</param>
/// <param name="btnHide">Boolean for hiding button</param>
/// <param name="inputTexts">Input text data in the field</param>
/// <param name="enter_pressed">Boolean for the enter key pressed</param>
void InputField::InputEvent(sf::RenderWindow& window, sf::Event& event, 
	bool &inputHide, bool &btnHide, std::vector<std::string> &inputTexts, 
	bool& enter_pressed)
{
		mousePos = sf::Mouse::getPosition(window);
		mousePosView = static_cast<sf::Vector2f>(mousePos);

		if (wholeInputRect.contains(mousePosView))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (!mouseHeld)
				{
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
					mouseHeld = true;
					isFocused = false;
				}
			}
			else
			{
				mouseHeld = false;
			}
		}
	if(!inputHide)
	{
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
						else if (text.getGlobalBounds().width < shape.getGlobalBounds().width && event.text.unicode != 8)
						{
							bufferString.push_back(static_cast<char>(event.text.unicode));
						}

						inputText.clear();
						inputText += bufferString + "_";
						SetText(inputText);
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !inputHide)
			{
				inputHide = true;
				btnHide = false;
				this->savedString = bufferString;
				inputTexts.push_back(this->savedString);
				this->bufferString = "";
				this->inputText = "";
				this->SetText("");
				enter_pressed = true;
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
}

/// <summary>
/// Overloaded function for input field event handler
/// </summary>
/// <param name="window">Main Window referenced</param>
/// <param name="event">Events related to the main window</param>
/// <param name="func">Lambda expressions</param>
void InputField::InputEvent(sf::RenderWindow& window, sf::Event& event,
	std::function<void()>func)
{
	mousePos = sf::Mouse::getPosition(window);
	mousePosView = static_cast<sf::Vector2f>(mousePos);

	if (wholeInputRect.contains(mousePosView))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!mouseHeld)
			{
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
		if (inputText.size() == 0)
		{
			inputText += "_";
			SetText(inputText);
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
					else if (text.getGlobalBounds().width < shape.getGlobalBounds().width && event.text.unicode != 8)
					{
						bufferString.push_back(static_cast<char>(event.text.unicode));
					}

					inputText.clear();
					inputText += bufferString + "_";
					SetText(inputText);
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			this->savedString = bufferString;
			this->bufferString = "";
			this->inputText = "";
			this->SetText("");
			func();
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

/// <summary>
/// Overloaded input field event handler
/// </summary>
/// <param name="window">Main Window referenced</param>
/// <param name="event">Events related to the main window</param>
/// <param name="func">Lambda expressions</param>
/// <param name="entered_field_string">String data</param>
void InputField::InputEvent(sf::RenderWindow& window, sf::Event& event, std::function<void()> func, std::string& entered_field_string)
{
	mousePos = sf::Mouse::getPosition(window);
	mousePosView = static_cast<sf::Vector2f>(mousePos);

	if (wholeInputRect.contains(mousePosView))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!mouseHeld)
			{
				mouseHeld = true;
				isFocused = true;
				shape.setFillColor(sf::Color(210, 210, 210 ));
				Cleft.setFillColor(sf::Color(210, 210, 210));
				Cright.setFillColor(sf::Color(210, 210, 210 ));
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
		if (inputText.size() == 0)
		{
			inputText += "_";
			SetText(inputText);
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
					else if (text.getGlobalBounds().width < shape.getGlobalBounds().width && event.text.unicode != 8)
					{
						bufferString.push_back(static_cast<char>(event.text.unicode));
					}

					inputText.clear();
					inputText += bufferString + "_";
					entered_field_string = bufferString;
					SetText(inputText);
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			entered_field_string = bufferString;
			func();
		}
	}
	else
	{
		shape.setFillColor(sf::Color(210, 210, 210));
		Cleft.setFillColor(sf::Color(210, 210, 210));
		Cright.setFillColor(sf::Color(210, 210, 210));
		if (inputText.size() >= 1 && inputText[inputText.size() - 1] == '_')
		{
			inputText.pop_back();
			SetText(inputText);
		}
	}
}

/// <summary>
/// Rendering components of the inpufield to the main window
/// </summary>
/// <param name="window">Main Window Referenced</param>
void InputField::DrawTo(sf::RenderWindow& window)
{
	window.draw(Cleft);
	window.draw(Cright);
	window.draw(shape);
	window.draw(text);
}