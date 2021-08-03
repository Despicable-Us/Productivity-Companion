#include "Icon.h"

Icon::Icon()
{
}

Icon::Icon(sf::Texture& btn_texture, sf::Vector2f pos, bool shadow)
{
	this->icon_texture = btn_texture;
	this->icon_pos = pos;
	this->rect_pos = { pos.x + 4.f, pos.y + 4.f };
	this->Set_Dimensions();
	this->Set_Icon_Sprite();
	if (!shadow)
	{
		this->show_shadow = false;
	}
	else
	{
		this->show_shadow = true; 
		this->Set_Icon_Shadow_Dimension();
	}
}

void Icon::Set_Dimensions()
{
	this->mouse_held = false;
	this->circle_radius = 13.f;
	this->rect_w = this->rect_h = 74.f;
	this->rect_size = { this->rect_w, this->rect_h };
	this->background_color = sf::Color(SHADOW_C);
}

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

void Icon::Set_Icon_Sprite()
{
	this->icon_background.setTexture(this->icon_texture);
	this->icon_background.setOrigin({ this->icon_background.getGlobalBounds().width / 2, this->icon_background.getGlobalBounds().height / 2 });
	this->icon_background.setPosition(this->icon_pos);
}

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

void Icon::Run_Outside_Event(sf::RenderWindow& window, sf::Event& event, std::function<void()>func)
{
	mouse_pos = sf::Mouse::getPosition(window);
	mouse_pos_view = static_cast<sf::Vector2f>(mouse_pos);

	if (icon_background.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
	{
		this->background_color = sf::Color(0,0,0);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!mouse_held)
			{
				mouse_held = true;
				func();
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
}