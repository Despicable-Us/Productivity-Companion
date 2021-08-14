#include "Pop_Up_Message.h"

/// <summary>
/// Default Constructor
/// </summary>
Pop_Up_Message::Pop_Up_Message()
{
}

/// <summary>
/// Parameterized Constructor 
/// </summary>
/// <param name="name">Tab Name</param>
/// <param name="font">Font for the text</param>
Pop_Up_Message::Pop_Up_Message(std::string name, sf::Font& font)
{
	this->session_name = name;
	this->rect_size = { 380.f, 150.f };
	this->rect_pos = { 380.f, 300.5f };
	this->Load_Font();
	this->Set_Components();
	this->Set_Dimension();
	this->Set_Text_Font();
	this->Set_Button_And_InputField();
	this->session_name = "Prajesh";
}

/// <summary>
/// Default Destructor
/// </summary>
Pop_Up_Message::~Pop_Up_Message()
{
}

/// <summary>
/// Loading required fonts for the pop up message bar
/// </summary>
void Pop_Up_Message::Load_Font()
{
	if (!roboto_font.loadFromFile("Fonts/Roboto-Medium.ttf"))
		throw "Error in loading the font 'Roboto-Medium.ttf'";
}

/// <summary>
/// Set all the UI and required components for the pop-up bar
/// </summary>
void Pop_Up_Message::Set_Components()
{
	circle_radius = 8.f;
	background_color = sf::Color::White;

	this->input_func = [&]()
	{
		confirm_func();
	};

	this->confirm_func = [&]()
	{
		if (this->session_name == this->input_field_string)
		{
			*overlay = false;
			*popup = false;
			*run_delete = true;
			field->bufferString = "";
			field->SetText("");
			field->inputText = "";
		}
	};

	this->cancel_func = [&]()
	{
		field->bufferString = "";
		field->SetText("");
		field->inputText = "";
	};
}

/// <summary>
/// Set the required dimension of all the shape
/// For rounded corner effect
/// </summary>
void Pop_Up_Message::Set_Dimension()
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
/// Set and initialize the text
/// </summary>
void Pop_Up_Message::Set_Text_Font()
{
	sure_text.setFont(roboto_font);
	sure_text.setString("Are you absolutely sure?");
	sure_text.setCharacterSize(16);
	sure_text.setOrigin({ sure_text.getGlobalBounds().width / 2, sure_text.getGlobalBounds().height / 2 });
	sure_text.setPosition({ main_rect_pos.x, main_rect_pos.y - 65.f });
	sure_text.setFillColor(sf::Color::Black);

	confirm_text.setFont(roboto_font);
	std::string confirm_string = "Please type '" + session_name + "' to confirm.";
	confirm_text.setString(confirm_string);
	confirm_text.setCharacterSize(16);
	confirm_text.setOrigin({ confirm_text.getGlobalBounds().width / 2, confirm_text.getGlobalBounds().height / 2 });
	confirm_text.setPosition({ main_rect_pos.x, main_rect_pos.y - 40.f });
	confirm_text.setFillColor(sf::Color(247, 12, 55));
}

/// <summary>
/// Set the button and inputfields
/// </summary>
void Pop_Up_Message::Set_Button_And_InputField()
{
	confirm_btn = new Btn("Confirm", { main_rect_pos.x - 75.f, main_rect_pos.y + 50.f }, 14, roboto_font);
	confirm_btn->SetFillColor(sf::Color(23,137,252));
	confirm_btn->text.setFillColor(sf::Color::White);
	cancel_btn = new Btn("Cancel", { main_rect_pos.x + 75.f, main_rect_pos.y + 50.f }, 14, roboto_font);
	cancel_btn->SetFillColor(sf::Color(150, 150, 150));
	cancel_btn->text.setFillColor(sf::Color(20,20,20));
	field = new InputField({ main_rect_pos.x, main_rect_pos.y }, roboto_font);
}

/// <summary>
/// Renders all the required UI components to the UI
/// </summary>
/// <param name="window"></param>
void Pop_Up_Message::Draw_To(sf::RenderWindow& window)
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
	window.draw(sure_text);
	window.draw(confirm_text);
	confirm_btn->DrawTo(window);
	cancel_btn->DrawTo(window);
	field->DrawTo(window);
}

/// <summary>
/// Events handled within the main event loop
/// </summary>
/// <param name="window">Main Window referenced</param>
/// <param name="event">Events related to the main window</param>
void Pop_Up_Message::Run_Inside_Event(sf::RenderWindow& window, sf::Event& event)
{
	field->InputEvent(window, event, input_func, input_field_string);
}

/// <summary>
/// Updater / Modifiers event handler
/// </summary>
/// <param name="window">Main Window referenced</param>
/// <param name="event">Events related to the main window</param>
/// <param name="show_overlay">Overlay referenced boolean</param>
/// <param name="show_pop_up">Pop up referenced boolean</param>
/// <param name="delete_data_db">Signal for deletion of specific tab data</param>
void Pop_Up_Message::Run_Outside_Event(sf::RenderWindow& window, sf::Event& event, bool& show_overlay, bool& show_pop_up, bool& delete_data_db)
{
	overlay = &show_overlay;
	popup = &show_pop_up;
	run_delete = &delete_data_db;
	confirm_btn->BtnEvents(window, event, confirm_func);
	cancel_btn->BtnEvents(window, event, cancel_func, show_overlay, show_pop_up);
}

/// <summary>
/// Setter for the pop-up title name
/// </summary>
/// <param name="name"></param>
void Pop_Up_Message::Set_Session_Name(std::string name)
{
	this->session_name = name;
}