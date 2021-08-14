#include "Icon.h"
extern int viewPos;

/// <summary>
/// Default Constructor
/// </summary>
Icon::Icon()
{
}

/// <summary>
/// Parameterized Constructor
/// </summary>
/// <param name="btn_texture">Texture of the icon</param>
/// <param name="pos">Position of the icon</param>
Icon::Icon(sf::Texture& btn_texture, sf::Vector2f pos)
{
	this->icon_texture = btn_texture;
	this->icon_pos = pos;
	this->rect_pos = { pos.x + 4.f, pos.y + 4.f };
	this->Set_Dimensions();
	this->Set_Icon_Sprite();
	this->show_shadow = true; 
	this->mouse_held = false;
	this->Set_Icon_Shadow_Dimension();
}

/// <summary>
/// Setter for icon texture
/// </summary>
/// <param name="btn_texture"></param>
Icon::Icon(sf::Texture& btn_texture)
{
	this->icon_texture = btn_texture;
	this->mouse_held = false;
	this->show_shadow = false;
}

/// <summary>
/// Setter for the position of icon
/// </summary>
/// <param name="pos"></param>
void Icon::Set_Icon_Pos(sf::Vector2f pos)
{
	this->icon_pos = pos;
	this->Set_Icon_Sprite();
}

/// <summary>
/// Setting the dimension and components of the icon
/// </summary>
void Icon::Set_Dimensions()
{
	this->circle_radius = 13.f;
	this->rect_w = this->rect_h = 74.f;
	this->rect_size = { this->rect_w, this->rect_h };
	this->background_color = sf::Color(SHADOW_C);
}

/// <summary>
/// Shadow of the icon
/// </summary>
void Icon::Set_Icon_Shadow_Dimension()
{
	main_rect.setSize(rect_size);
	up_rect.setSize({ rect_size.x, circle_radius });
	left_rect.setSize({ circle_radius, rect_size.y });
	right_rect.setSize({ circle_radius, rect_size.y });
	bottom_rect.setSize({ rect_size.x, circle_radius });

	main_rect.setOrigin({ main_rect.getSize().x / 2, main_rect.getSize().y / 2 });
	main_rect.setPosition(rect_pos);

	main_rect_pos = main_rect.getPosition();
	main_rect_size = main_rect.getSize();
	circle_origin = { circle_radius, circle_radius };

	c_top_left.setRadius(circle_radius);
	c_top_right.setRadius(circle_radius);
	c_bottom_left.setRadius(circle_radius);
	c_bottom_right.setRadius(circle_radius);

	c_top_left.setOrigin(circle_origin);
	c_top_right.setOrigin(circle_origin);
	c_bottom_left.setOrigin(circle_origin);
	c_bottom_right.setOrigin(circle_origin);

	c_top_left.setPosition({ main_rect_pos.x - main_rect_size.x / 2, main_rect_pos.y - main_rect_size.y / 2 });
	c_top_right.setPosition({ main_rect_pos.x + main_rect_size.x / 2, main_rect_pos.y - main_rect_size.y / 2 });
	c_bottom_left.setPosition({ main_rect_pos.x - main_rect_size.x / 2, main_rect_pos.y + main_rect_size.y / 2 });
	c_bottom_right.setPosition({ main_rect_pos.x + main_rect_size.x / 2, main_rect_pos.y + main_rect_size.y / 2 });

	up_rect.setOrigin({ up_rect.getSize().x / 2, up_rect.getSize().y / 2 });
	left_rect.setOrigin({ left_rect.getSize().x / 2, left_rect.getSize().y / 2 });
	right_rect.setOrigin({ right_rect.getSize().x / 2, right_rect.getSize().y / 2 });
	bottom_rect.setOrigin({ bottom_rect.getSize().x / 2, bottom_rect.getSize().y / 2 });

	up_rect.setPosition({ main_rect_pos.x, main_rect_pos.y - main_rect_size.y / 2 - up_rect.getSize().y / 2 });
	bottom_rect.setPosition({ main_rect_pos.x, main_rect_pos.y + main_rect_size.y / 2 + up_rect.getSize().y / 2 });
	left_rect.setPosition({ main_rect_pos.x - main_rect_size.x / 2 - left_rect.getSize().x / 2, main_rect_pos.y });
	right_rect.setPosition({ main_rect_pos.x + main_rect_size.x / 2 + left_rect.getSize().x / 2, main_rect_pos.y });

	this->Set_Shadow_Color();
}

/// <summary>
/// Setter for the icon sprite from texture
/// </summary>
void Icon::Set_Icon_Sprite()
{
	this->icon_background.setTexture(this->icon_texture);
	this->icon_background.setOrigin({ this->icon_background.getGlobalBounds().width / 2, this->icon_background.getGlobalBounds().height / 2 });
	this->icon_background.setPosition(this->icon_pos);
}

/// <summary>
/// Setting the color of the shadow
/// </summary>
void Icon::Set_Shadow_Color()
{
	c_top_left.setFillColor(background_color);
	c_top_right.setFillColor(background_color);
	c_bottom_left.setFillColor(background_color);
	c_bottom_right.setFillColor(background_color);

	up_rect.setFillColor(background_color);
	left_rect.setFillColor(background_color);
	right_rect.setFillColor(background_color);
	bottom_rect.setFillColor(background_color);
	main_rect.setFillColor(background_color);
}

/// <summary>
/// Rendering every components of the icon to the Main Window
/// </summary>
/// <param name="window">Main Window referenced</param>
void Icon::Draw_To(sf::RenderWindow& window)
{
	if (show_shadow)
	{
		window.draw(main_rect);
		window.draw(c_top_left);
		window.draw(c_top_right);
		window.draw(c_bottom_left);
		window.draw(c_bottom_right);
		window.draw(up_rect);
		window.draw(left_rect);
		window.draw(right_rect);
		window.draw(bottom_rect);
	}
	window.draw(icon_background);
}

/// <summary>
/// Event handler for the icon
/// </summary>
/// <param name="window">Main Window referenced</param>
/// <param name="event">Events related to the main window</param>
/// <param name="func">Lambda expressions</param>
void Icon::Run_Outside_Event(sf::RenderWindow& window, sf::Event& event, std::function<void()>func)
{
	mouse_pos = sf::Mouse::getPosition(window);
	mouse_pos_view = static_cast<sf::Vector2f>(mouse_pos);

	if (event.type == sf::Event::MouseButtonPressed) 
	{
		if (event.key.code == sf::Mouse::Left) 
		{
			if (icon_background.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) 
			{
				this->iconClickedStatus = 1;
			}
		}
	}
	if (event.type == sf::Event::MouseButtonReleased) 
	{
		if (event.key.code == sf::Mouse::Left) 
		{
			if (this->iconClickedStatus && icon_background.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) 
			{
				this->iconClickedStatus = 2;
			}
			else
			{
				this->iconClickedStatus = 0;
			}
		}
	}
	if (iconClickedStatus == 2) 
	{
		func();
		this->iconClickedStatus = 0;
	}

	if (icon_background.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
	{
		this->background_color = sf::Color(0,0,0);
	}
	else
	{
		this->background_color = sf::Color(SHADOW_C);
	}
	this->Set_Shadow_Color();
}

/// <summary>
/// Updaters / Modifiers 
/// </summary>
/// <param name="window">Main Window referenced</param>
/// <param name="event">Events related to the main window</param>
/// <returns>Button pressed boolean</returns>
bool Icon::Run_Outside_Event(sf::RenderWindow& window, sf::Event& event)
{
	mouse_pos = sf::Mouse::getPosition(window);
	mouse_pos.y = mouse_pos.y - 220 + viewPos;
	mouse_pos_view = static_cast<sf::Vector2f>(mouse_pos);

	if (icon_background.getGlobalBounds().contains(mouse_pos_view))
	{
		this->background_color = sf::Color(0, 0, 0);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!mouse_held)
			{
				mouse_held = true;
			}
		}
		else
		{
			mouse_held = false;
		}
	}
	else
	{
		this->background_color = sf::Color(SHADOW_C);
	}
	this->Set_Shadow_Color();
	return mouse_held;
}

/// <summary>
/// Un hold the mouse left key
/// </summary>
void Icon::Set_Unheld()
{
	this->mouse_held = false;
}