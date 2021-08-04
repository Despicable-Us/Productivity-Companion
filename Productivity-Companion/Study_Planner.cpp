#include "Study_Planner.h"

std::vector<std::string> db_planner_list_data;
std::vector<std::string> new_input_data;

Planner_Tab::Planner_Tab()
{
}

Planner_Tab::Planner_Tab(std::string name, sf::Vector2f pos, sf::Vector2f size, sf::Font& font)
{
	this->plan_sheet_name = name;
	this->rect_pos = pos;
	this->rect_size = size;
	this->roboto_font = font;
	Set_Components();
	Set_Dimension();
	Set_Button();
}

Planner_Tab::~Planner_Tab()
{
}

void Planner_Tab::Set_Components()
{
	circle_radius = BORDER_RADIUS_S;
	background_color = sf::Color(APP_THEME_COLOR);
}

void Planner_Tab::Set_Dimension()
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

void Planner_Tab::Set_Button()
{
	planner_btn = new Btn(plan_sheet_name, { main_rect_pos.x, main_rect_pos.y - 20.f }, 15, roboto_font);
	delete_btn = new Btn("Delete", { main_rect_pos.x , main_rect_pos.y + 28.f }, 10, roboto_font);
	delete_btn->SetFillColor(sf::Color(209, 265, 42));
	delete_btn->text.setFillColor(sf::Color::White);
}

void Planner_Tab::Draw_To(sf::RenderWindow& window)
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
	planner_btn->DrawTo(window);
	delete_btn->DrawTo(window);
}

Study_Planner::Study_Planner()
{
}

Study_Planner::Study_Planner(sf::RenderWindow& window)
{
	this->win_size = window.getSize();
	this->win_sizeF = static_cast<sf::Vector2f>(win_size);
	this->Init_Variables();
	this->Init_Background();
	this->Init_UI_Components();
	delete_db_data = false;
	this->plan_sheet = new TodoList("Productivity Companion");
	this->Get_DB_Data();
}

Study_Planner::~Study_Planner()
{
	delete this->add_planner_btn;
	delete this->input_planner_field;
}

void Study_Planner::Init_Variables()
{
	this->rect.setPosition({ 0.f, 0.f });
	this->rect.setSize({ 740.f, 30.f });
	this->rect.setFillColor(sf::Color(240, 240, 240));
	this->btn_hide = false;
	this->input_hide = true;
	this->enter_pressed = false;
	this->planner_tab_size = { 202.f, 80.25f };
	this->btn_show = true;
	this->show_planner_list = false;
	this->show_planner_tab = true;
	this->dir = "Productivity_companion.db";

	this->btn_event_func = [&]()
	{
		this->show_planner_list = true;
		this->show_planner_tab = false;
		this->plan_sheet->Reset_Functions(selected_planner_sheet_name);
	};

	this->delete_event_func = [&]()
	{
		show_blur_overlay = true;
		show_pop_up = true;
		pop_up->Set_Session_Name(selected_planner_sheet_name);
		pop_up->Set_Text_Font();
	};

	this->blur_overlay.setSize({ 760.f, 675.f });
	this->blur_overlay.setFillColor(sf::Color(5, 10, 48, 130));
	this->blur_overlay.setPosition({ 0.f, 0.f });
	this->show_blur_overlay = false;

	this->pop_up = new Pop_Up_Message("Something", this->roboto_font);
	show_pop_up = false;

}

void Study_Planner::Init_Background()
{
	if (!this->texture.loadFromFile("Texture/study_planner_background.PNG"))
		throw "Error in loading the 'study_planner_back1.png'";
	this->background.setTexture(texture);
	this->background.setPosition({ 0.f, 0.f });
}

void Study_Planner::Init_UI_Font()
{
	if (!kaushan_font.loadFromFile("Font/KaushanScript-Regular.ttf"))
		throw "Error in loading the 'KaushanScript-Regular.ttf'";
	if (!roboto_font.loadFromFile("Font/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium.ttf'";
}

void Study_Planner::Init_UI_Components()
{
	Init_UI_Font();
	this->add_planner_btn = new Btn("+ Add New Plan Sheet", { win_sizeF.x / 2, 110.f }, static_cast<uint8_t>(16), roboto_font);
	this->add_planner_btn->SetFillColor(sf::Color(ADD_COLOR));
	this->add_planner_btn->text.setFillColor(sf::Color::White);
	this->add_rect = [&]()
	{
		btn_hide = true;
		input_hide = false;
	};
	this->input_planner_field = new InputField({ win_sizeF.x / 2, 110.f }, roboto_font);

	this->home_back_button = new Btn("Home", { 55.f, 30.f }, 14, this->roboto_font);
	this->home_back_button_clicked = false;
	this->home_back_button_func = [&]()
	{
		this->home_back_button_clicked = true;
	};
}

void Study_Planner::Update_Rects()
{
	if (input_texts.back() != "")
	{
		if (planner_tab_vec.size() < 12)
		{
			if (planner_tab_vec.empty())
			{
				initial_pos = { 132.f, 225.125f };
			}
			else if (planner_tab_vec.size() <= 2)
			{
				initial_pos.x += 248.f;
			}
			else if (planner_tab_vec.size() > 2 && planner_tab_vec.size() <= 5)
			{
				if (planner_tab_vec.size() == 3)
				{
					initial_pos.x = 132.f;
					initial_pos.y += 126.25f;
				}
				else
				{
					initial_pos.x += 248.f;
				}
			}
			else if (planner_tab_vec.size() > 5 && planner_tab_vec.size() <= 8)
			{
				if (planner_tab_vec.size() == 6)
				{
					initial_pos.x = 132.f;
					initial_pos.y += 126.25f;
				}
				else
				{
					initial_pos.x += 248.f;
				}
			}
			else if (planner_tab_vec.size() > 8 && planner_tab_vec.size() <= 11)
			{
				if (planner_tab_vec.size() == 9)
				{
					initial_pos.x = 132.f;
					initial_pos.y += 126.25f;
				}
				else
				{
					initial_pos.x += 248.f;
				}
			}
			planner_tab = Planner_Tab(input_texts.back(), initial_pos, planner_tab_size, roboto_font);
			planner_tab_vec.push_back(Planner_Tab(planner_tab));
			study_planner::insert_new_plan_sheet(dir, input_texts.back());
			db_planner_list_data.push_back(input_texts.back());
		}
	}
	else
	{
		input_texts.pop_back();
	}
}

void Study_Planner::Update_Rects_After_DB()
{
	if (this->planner_tab_vec.size() < 12)
	{
		this->Alter_Planner_Tab_View();
	}
}

void Study_Planner::Alter_Planner_Tab_View()
{
	for (size_t i = 0; i < this->input_texts.size(); ++i)
	{
		if (this->planner_tab_vec.empty())
		{
			this->initial_pos = { 132.f, 225.125f };
		}
		else if (this->planner_tab_vec.size() <= 2)
		{
			this->initial_pos.x += 248.f;
		}
		else if (this->planner_tab_vec.size() > 2 && this->planner_tab_vec.size() <= 5)
		{
			if (this->planner_tab_vec.size() == 3)
			{
				this->initial_pos.x = 132.f;
				this->initial_pos.y += 126.25f;
			}
			else
			{
				this->initial_pos.x += 248.f;
			}
		}
		else if (this->planner_tab_vec.size() > 5 && this->planner_tab_vec.size() <= 8)
		{
			if (this->planner_tab_vec.size() == 6)
			{
				this->initial_pos.x = 132.f;
				this->initial_pos.y += 126.25f;
			}
			else
			{
				this->initial_pos.x += 248.f;
			}
		}
		else if (this->planner_tab_vec.size() > 8 && this->planner_tab_vec.size() <= 11)
		{
			if (this->planner_tab_vec.size() == 9)
			{
				this->initial_pos.x = 132.f;
				this->initial_pos.y += 126.25f;
			}
			else
			{
				this->initial_pos.x += 248.f;
			}
		}
		this->planner_tab = Planner_Tab(this->input_texts[i], this->initial_pos, this->planner_tab_size, roboto_font);
		this->planner_tab_vec.push_back(Planner_Tab(planner_tab));
	}
}

void Study_Planner::Run_Inside_Event(sf::RenderWindow& window, sf::Event& event, sf::View& view)
{
	if (show_planner_tab)
	{
		input_planner_field->InputEvent(window, event, input_hide, btn_hide, input_texts, enter_pressed);
		if (enter_pressed)
		{
			Update_Rects();
			enter_pressed = false;
		}
	}

	if (show_planner_list)
	{
		this->plan_sheet->RunTodo(window, event, view, show_planner_tab, show_planner_list);
	}

	if (show_pop_up)
	{
		pop_up->Run_Inside_Event(window, event);
	}
}

void Study_Planner::Run_Outside_Event(sf::RenderWindow& window, sf::Event& event, bool& run_main_window, bool& run_app)
{
	if (show_planner_tab)
	{
		if (!show_pop_up)
		{
			add_planner_btn->BtnEvents(window, event, add_rect, btn_hide);
			for (size_t i = 0; i < planner_tab_vec.size(); ++i)
			{
				planner_tab_vec[i].planner_btn->BtnEvents(window, event, btn_event_func, input_texts[i], selected_planner_sheet_name);
				planner_tab_vec[i].delete_btn->BtnEvents(window, event, delete_event_func, input_texts[i], selected_planner_sheet_name);
			}
			if (home_back_button_clicked)
			{
				this->home_back_button_clicked = true;
				run_main_window = true;
				run_app = false;
			}
		}
	}

	if (show_pop_up)
	{
		pop_up->Run_Outside_Event(window, event, show_blur_overlay, show_pop_up, delete_db_data);
	}
	if (delete_db_data)
	{
		delete_db_data = false;
		study_planner::delete_planner_tab(dir, selected_planner_sheet_name);
		db_planner_list_data.clear();
		planner_tab_vec.clear();
		Get_DB_Data();
	}


}

void Study_Planner::Render_In_Main_Window(sf::RenderWindow& window)
{
	if (show_planner_tab)
	{
		window.draw(this->background);
		this->home_back_button->DrawTo(window);
		if (!btn_hide)
		{
			add_planner_btn->DrawTo(window);
		}
		if (!input_hide)
		{
			input_planner_field->DrawTo(window);
		}
		if (!planner_tab_vec.empty() and btn_show)
		{
			for (auto& planner_tab : planner_tab_vec)
			{
				planner_tab.Draw_To(window);
			}
		}
		if (show_blur_overlay)
		{
			window.draw(this->blur_overlay);
		}
		if (show_pop_up)
		{
			pop_up->Draw_To(window);
		}
		
	}
	if (show_planner_list)
	{
		this->plan_sheet->DrawTodoMainWindow(window);
	}
	
}

void Study_Planner::Render_In_View(sf::RenderWindow& window)
{
	if (show_planner_list)
	{
		this->plan_sheet->DrawTodoView(window);
	}
}

void Study_Planner::Get_DB_Data()
{
	study_planner::select_data(dir);
	this->input_texts = db_planner_list_data;
	this->Update_Rects_After_DB();
}

void Study_Planner::Update_DB_Data()
{
	if (!new_input_data.empty())
	{
		study_planner::insert_data(dir);
	}
}


int study_planner::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	db_planner_list_data.push_back(argv[1]);
	return 0;
}

int study_planner::select_data(const char* s)
{
	sqlite3* DB;
	char* messageError;
	std::string sql = "SELECT * FROM PLANNER;";
	int exit = sqlite3_open(s, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), study_planner::callback, NULL, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in selectData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records selected Successfully!" << std::endl;
	return 0;
}

int study_planner::insert_data(const char* s)
{
	sqlite3* DB;
	char* messageError;
	int exit = sqlite3_open(s, &DB);
	std::string sql;
	if (!new_input_data.empty())
	{
		std::string tester = "";
		for (size_t i = 0; i < new_input_data.size(); ++i)
		{
			tester += "('" + new_input_data[i] + "'),";
		}
		tester.erase(tester.size() - 1, 1);
		sql = "INSERT INTO PLANNER (plan_sheet_name) VALUES" + tester + ";";
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			std::cerr << "Error in insertData function." << std::endl;
			sqlite3_free(messageError);
		}
		else
			std::cout << "Records inserted Successfully!" << std::endl;
	}
	return 0;
}

int study_planner::delete_planner_tab(const char* s, std::string name)
{
	sqlite3* DB;
	char* messageError;
	std::cout << name << std::endl;
	std::string sql = "DELETE FROM PLANNER WHERE plan_sheet_name = '" + name + "';"

					"DELETE FROM PLANNER_LIST WHERE plan_sheet_name = '" + name + "';";

	int exit = sqlite3_open(s, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in deleteData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records deleted Successfully!" << std::endl;

	return 0;
}

int study_planner::insert_new_plan_sheet(const char* s, std::string planner_name)
{
	sqlite3* DB;
	char* messageError;
	int exit = sqlite3_open(s, &DB);
	std::string sql;
	sql = "INSERT INTO PLANNER (plan_sheet_name) VALUES('" + planner_name + "');";
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in insertData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records inserted Successfully!" << std::endl;
	return 0;
}