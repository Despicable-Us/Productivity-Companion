#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <functional>

#define SHADOW_C 170, 170, 170

class Icon
{
	public:
		// UI PROPERTIES
		sf::Texture icon_texture;
		float rect_w, rect_h;
		float circle_radius;
		sf::Vector2f rect_pos;
		sf::Vector2f rect_size;
		sf::Vector2f circle_origin;
		sf::Vector2f main_rect_pos;
		sf::Vector2f main_rect_size;
		sf::Vector2f icon_pos;
		sf::Vector2i mouse_pos;
		sf::Vector2f mouse_pos_view;

		// UI DESIGN COMPONENTS
		sf::Color background_color;
		sf::RectangleShape main_rect;
		sf::RectangleShape up_rect;
		sf::RectangleShape left_rect;
		sf::RectangleShape right_rect;
		sf::RectangleShape bottom_rect;
		sf::CircleShape c_top_left;
		sf::CircleShape c_top_right;
		sf::CircleShape c_bottom_left;
		sf::CircleShape c_bottom_right;
		sf::Sprite icon_background;

		// BOOLEAN
		bool show_shadow;
		bool mouse_held;
		int iconClickedStatus;
		
		// CONSTRUCTORS AND DESTRUCTOR
		Icon();
		Icon(sf::Texture& btn_texture, sf::Vector2f pos);
		Icon(sf::Texture& btn_texture);
		
		// SETTER
		void Set_Icon_Pos(sf::Vector2f pos);
		void Set_Dimensions();
		void Set_Icon_Shadow_Dimension();
		void Set_Icon_Sprite();
		void Set_Shadow_Color();
		void Set_Unheld();

		// RENDERER
		void Draw_To(sf::RenderWindow& window);

		// ALL EVENTS AND BOOLEAN
		void Run_Outside_Event(sf::RenderWindow& window, sf::Event& event, std::function<void()> func);
		bool Run_Outside_Event(sf::RenderWindow& window, sf::Event& event);
};