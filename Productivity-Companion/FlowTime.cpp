#include "FlowTime.h"

FlowTime::FlowTime()
{
}

FlowTime::FlowTime(sf::RenderWindow& window)
{
	this->win_size = window.getSize();
	this->win_sizeF = static_cast<sf::Vector2f>(win_size);

	this->Init_Variables();
	this->Init_Background();
	this->Init_UI_Components();
}

FlowTime::~FlowTime()
{
	delete this->add_flowtime_btn;
	delete this->input_flowtime_field;
}

void FlowTime::Init_Variables()
{
	this->rect.setPosition({ 0.f, 0.f });
	this->rect.setSize({ 740.f, 30.f });
	this->rect.setFillColor(sf::Color(240, 240, 240));
	this->btn_hide = false;
	this->input_hide = true;
	this->enter_pressed = false;
	//this->btn_event_func = [&]()
	//{
	//	this->show_session = true;
	//	this->show_session_tab = false;
	//	this->session->Run_Functions(selected_session_name);
	//};

	//this->delete_event_func = [&]()
	//{
	//	show_blur_overlay = true;
	//	show_pop_up = true;
	//	pop_up->Set_Session_Name(selected_session_name);
	//	pop_up->Set_Text_Font();
	//};

}

void FlowTime::Init_Background()
{
	if (!this->texture.loadFromFile("Texture/flowtime_background.png"))
		throw "Error in loading the 'flowtime_background.png'";
	this->background.setTexture(texture);
	this->background.setPosition({ 0.f, 0.f });
}

void FlowTime::Init_UI_Font()
{
	if (!kaushan_font.loadFromFile("Font/KaushanScript-Regular.ttf"))
		throw "Error in loading the 'KaushanScript-Regular.ttf'";
	if (!roboto_font.loadFromFile("Font/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium.ttf'";
}

void FlowTime::Init_UI_Components()
{
	Init_UI_Font();
	this->add_flowtime_btn = new Btn("+ Add new session", { win_sizeF.x / 2, 110.f }, static_cast<uint8_t>(16), roboto_font);
	this->add_flowtime_btn->SetFillColor(sf::Color(BLUE_THEMED_C));
	this->add_flowtime_btn->text.setFillColor(sf::Color::White);
	this->add_rect = [&]()
	{
		btn_hide = true;
		input_hide = false;
	};
	this->input_flowtime_field = new InputField({ win_sizeF.x / 2, 110.f }, roboto_font);

	//this->home_back_btn = new Btn("Home", { 55.f, 30.f }, 14, this->roboto_font);
	//this->home_back_btn->SetFillColor(sf::Color(23, 137, 252));
	//this->home_back_btn->text.setFillColor(sf::Color::White);
	//this->home_back_btn_clicked = false;
	//this->home_back_btn_func = [&]()
	//{
	//	this->home_back_btn_clicked = true;
	//};
}

void FlowTime::Run_Inside_Event(sf::RenderWindow& window, sf::Event& event, sf::View& view)
{
	input_flowtime_field->InputEvent(window, event, input_hide, btn_hide, input_texts, enter_pressed);
	if (enter_pressed)
	{
		std::cout << "Enter pressed" << std::endl;
		enter_pressed = false;
	}
}

void FlowTime::Run_Outside_Event(sf::RenderWindow& window, sf::Event& event, bool& run_main_window, bool& run_app)
{
	if (window.hasFocus())
	{
		add_flowtime_btn->BtnEvents(window, event, add_rect, btn_hide);
	}
}

void FlowTime::Render_In_Main_Window(sf::RenderWindow& window)
{
	window.draw(this->background);
	if (!btn_hide)
	{
		add_flowtime_btn->DrawTo(window);
	}
	if (!input_hide)
	{
		input_flowtime_field->DrawTo(window);
	}
}

void FlowTime::Render_In_View(sf::RenderWindow& window)
{
}
