#include "Session_Tracker.h"

/// <summary>
/// db_session_list_data -> a 2d vector to contain the data from fetched from the database
/// new_input_texts -> tracks new session added to the view
/// </summary>
std::vector<std::string> db_session_list_data;
std::vector<std::string> db_total_time_string;
std::vector<std::string> new_input_texts;
std::vector<std::vector<std::string>> db_total_time_list;

/// <summary>
/// Parameterized constructor for SESSION_TRACKER 
/// </summary>
/// <param name="window">Window to render to</param>
Session_Tracker::Session_Tracker(sf::RenderWindow& window)
{
	this->win_size = window.getSize();
	this->win_sizeF = static_cast<sf::Vector2f>(win_size);
	this->Init_Variables();
	this->Init_Background();
	this->Init_UI_Components();
	delete_db_data = false;
	this->session = new Session(window, "Productivity Companion");
	this->Get_DB_Data();
}

/// <summary>
/// To destruct the pointer buttons
/// </summary>
Session_Tracker::~Session_Tracker()
{
	delete this->add_session_btn;
	delete this->input_session_field;
}

/// <summary>
/// Updates the SESSION_TAB_VIEW with the fetched session from the database
/// </summary>
void Session_Tracker::Update_Rects_After_DB()
{
	if (this->session_tab_vec.size() < 12)
	{
		this->Alter_Session_Tab_View();
	}
}

void Session_Tracker::Alter_Session_Tab_View()
{
	for (size_t i = 0; i < this->input_texts.size(); ++i)
	{
		if (this->session_tab_vec.empty())
		{
			this->initial_pos = { 132.f, 225.125f };
		}
		else if (this->session_tab_vec.size() <= 2)
		{
			this->initial_pos.x += 248.f;
		}
		else if (this->session_tab_vec.size() > 2 && this->session_tab_vec.size() <= 5)
		{
			if (this->session_tab_vec.size() == 3)
			{
				this->initial_pos.x = 132.f;
				this->initial_pos.y += 126.25f;
			}
			else
			{
				this->initial_pos.x += 248.f;
			}
		}
		else if (this->session_tab_vec.size() > 5 && this->session_tab_vec.size() <= 8)
		{
			if (this->session_tab_vec.size() == 6)
			{
				this->initial_pos.x = 132.f;
				this->initial_pos.y += 126.25f;
			}
			else
			{
				this->initial_pos.x += 248.f;
			}
		}
		else if (this->session_tab_vec.size() > 8 && this->session_tab_vec.size() <= 11)
		{
			if (this->session_tab_vec.size() == 9)
			{
				this->initial_pos.x = 132.f;
				this->initial_pos.y += 126.25f;
			}
			else
			{
				this->initial_pos.x += 248.f;
			}
		}
		this->session_tab = Session_Tab(this->input_texts[i], this->initial_pos, this->session_tab_size, roboto_font);
		this->session_tab_vec.push_back(Session_Tab(session_tab));
	}
}

/// <summary>
/// Fetch the data from the database
/// </summary>
void Session_Tracker::Get_DB_Data()
{
	session_tracker::select_data(dir);
	this->input_texts = db_session_list_data;

	for (auto str : db_session_list_data)
	{
		session_tracker::fetch_total_time_list(dir, str);
	}
	this->Update_Rects_After_DB();
	this->Set_DB_Total_Time_List();
}

/// <summary>
/// Update the data to the database
/// </summary>
void Session_Tracker::Update_DB_Data()
{
	if (!new_input_texts.empty())
	{
		session_tracker::insert_data(dir);
	}
}

void Session_Tracker::Set_DB_Total_Time_List()
{
	for (size_t i = 0; i < session_tab_vec.size(); ++i)
	{
		for (size_t j = 0; j < db_total_time_list.size(); ++j)
		{
			if (session_tab_vec[i].session_btn->text.getString() == db_total_time_list[j][0])
			{
				session_tab_vec[i].Set_Total_Time_Text(db_total_time_list[j][1]);
				break;
			}
		}
	}
}

void Session_Tracker::Set_DB_Data_To_View()
{
	db_total_time_list.clear();

	for (auto str : db_session_list_data)
	{
		session_tracker::fetch_total_time_list(dir, str);
	}
	Set_DB_Total_Time_List();
}

/// <summary>
/// Initializes required components of the app
/// </summary>
void Session_Tracker::Init_Variables()
{
	this->rect.setPosition({ 0.f, 0.f });
	this->rect.setSize({ 740.f, 30.f });
	this->rect.setFillColor(sf::Color(240, 240, 240));
	this->btn_hide = false;
	this->input_hide = true;
	this->enter_pressed = false;
	this->session_tab_size = { 202.f, 80.25f };
	this->btn_show = true;
	this->show_session = false;
	this->show_session_tab = true;
	this->dir = "Session.db";
	this->update_total_time_list = false;
	this->btn_event_func = [&]()
	{
		this->show_session = true;
		this->show_session_tab = false;
		this->session->Run_Functions(selected_session_name);
	};

	this->delete_event_func = [&]()
	{
		show_blur_overlay = true;
		show_pop_up = true;
		pop_up->Set_Session_Name(selected_session_name);
		pop_up->Set_Text_Font();
	};

	this->blur_overlay.setSize({ 760.f, 675.f });
	this->blur_overlay.setFillColor(sf::Color(5,10,48,130));
	this->blur_overlay.setPosition({ 0.f, 0.f });
	this->show_blur_overlay = false;

	this->pop_up = new Pop_Up_Message("Something", this->roboto_font);
	show_pop_up = false;
}

/// <summary>
/// Loads the background images and sets the texture
/// </summary>
void Session_Tracker::Init_Background()
{
	if (!this->texture.loadFromFile("Images/BBG.png"))
		throw "Error in loading the 'BG_Title.png'";
	this->background.setTexture(texture);
	this->background.setPosition({ 0.f, 0.f });
}

/// <summary>
/// Loads the fonts : Kaushan Script and Roboto Medium
/// </summary>
void Session_Tracker::Init_UI_Font()
{
	if (!kaushan_font.loadFromFile("Font/KaushanScript-Regular.ttf"))
		throw "Error in loading the 'KaushanScript-Regular.ttf'";
	if (!roboto_font.loadFromFile("Font/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium.ttf'";
}

/// <summary>
/// Initializes the BUTTON and the INPUTFIELD
/// </summary>
void Session_Tracker::Init_UI_Components()
{
	Init_UI_Font();
	this->add_session_btn = new Btn("+ Add new session", { win_sizeF.x / 2, 110.f }, static_cast<uint8_t>(16), roboto_font);
	this->add_session_btn->SetFillColor(sf::Color(BLUE_THEMED_C));
	this->add_session_btn->text.setFillColor(sf::Color::White);
	this->add_rect = [&]()
	{
		btn_hide = true;
		input_hide = false;
	};
	this->input_session_field = new InputField({ win_sizeF.x / 2, 110.f }, roboto_font);
}

/// <summary>
/// Updates the SESSION_TAB_VIEW
/// </summary>
void Session_Tracker::Update_Rects()
{
	if (input_texts.back() != "" )
	{
		if (session_tab_vec.size() < 12)
		{
			if (session_tab_vec.empty())
			{
				initial_pos = { 132.f, 225.125f };
			}
			else if (session_tab_vec.size() <= 2)
			{
				initial_pos.x += 248.f;
			}
			else if (session_tab_vec.size() > 2 && session_tab_vec.size() <= 5)
			{
				if (session_tab_vec.size() == 3)
				{
					initial_pos.x = 132.f;
					initial_pos.y += 126.25f;
				}
				else
				{
					initial_pos.x += 248.f;
				}
			}
			else if (session_tab_vec.size() > 5 && session_tab_vec.size() <= 8)
			{
				if (session_tab_vec.size() == 6)
				{
					initial_pos.x = 132.f;
					initial_pos.y += 126.25f;
				}
				else
				{
					initial_pos.x += 248.f;
				}
			}
			else if (session_tab_vec.size() > 8 && session_tab_vec.size() <= 11)
			{
				if (session_tab_vec.size() == 9)
				{
					initial_pos.x = 132.f;
					initial_pos.y += 126.25f;
				}
				else
				{
					initial_pos.x += 248.f;
				}
			}
			session_tab = Session_Tab(input_texts.back(), initial_pos, session_tab_size, roboto_font);
			session_tab_vec.push_back(Session_Tab(session_tab));
			session_tracker::insert_new_session(dir, input_texts.back());
			db_session_list_data.push_back(input_texts.back());
		}
	}
	else
	{
		input_texts.pop_back();
	}
}

/// <summary>
/// Renders the components in the main window
/// </summary>
/// <param name="window">Main window to render to</param>
void Session_Tracker::Render_In_Main_Window(sf::RenderWindow& window)
{
	if (show_session_tab)
	{
		window.draw(this->background);
		
		if (!btn_hide)
		{
			add_session_btn->DrawTo(window);
		}
		if (!input_hide)
		{
			input_session_field->DrawTo(window);
		}
		if (!session_tab_vec.empty() and btn_show)
		{
			for (auto& session_tab : session_tab_vec)
			{
				session_tab.Draw_To(window);
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
	if (show_session)
	{
		session->Draw_To_Main_Window(window);
	}
}


/// <summary>
/// Events to be handeled inside the poll event loop
/// </summary>
/// <param name="window">Window to render to</param>
/// <param name="event">Evens to handeled</param>
/// <param name="scroll_view">View to render to</param>
void Session_Tracker::Run_Inside_Event(sf::RenderWindow& window, sf::Event& event, sf::View& scroll_view)
{
	if (show_session_tab)
	{
		input_session_field->InputEvent(window, event, input_hide, btn_hide, input_texts, enter_pressed);
		if (enter_pressed)
		{
			Update_Rects();
			enter_pressed = false;
		}
	}

	if (show_session)
	{
		session->View_Scroll_Event(event, scroll_view);
	}

	if (show_pop_up)
	{
		pop_up->Run_Inside_Event(window, event);
	}
}

/// <summary>
/// Render the components in the Specified view
/// </summary>
/// <param name="window">Window to render to</param>
void Session_Tracker::Render_In_View(sf::RenderWindow& window)
{
	if (show_session)
	{
		session->Draw_To_View(window);
	}
}

/// <summary>
/// Run events outside the poll event poll
/// </summary>
/// <param name="window"></param>
/// <param name="event"></param>
void Session_Tracker::Run_Outside_Event(sf::RenderWindow& window, sf::Event& event)
{
	if (show_session_tab)
	{
		if (!show_pop_up)
		{
			add_session_btn->BtnEvents(window, event, add_rect, btn_hide);
			for (size_t i = 0; i < session_tab_vec.size(); ++i)
			{
				session_tab_vec[i].session_btn->BtnEvents(window, event, btn_event_func, input_texts[i], selected_session_name);
				session_tab_vec[i].delete_btn->BtnEvents(window, event, delete_event_func, input_texts[i], selected_session_name);
			}
		}
	}
	if (show_session)
	{
		session->Run_Events(window, event, show_session, show_session_tab, update_total_time_list);
	}
	if (update_total_time_list)
	{
		update_total_time_list = false;
		Set_DB_Data_To_View();
	}
	if (show_pop_up)
	{
		pop_up->Run_Outside_Event(window, event, show_blur_overlay, show_pop_up, delete_db_data);
	}
	if (delete_db_data)
	{
		delete_db_data = false;
		session_tracker::delete_session_tab(dir, selected_session_name);
		db_session_list_data.clear();
		db_total_time_list.clear();
		db_total_time_string.clear();
		session_tab_vec.clear();
		Get_DB_Data();

	}
}

/// <summary>
/// Default Constructor for the session_tab
/// </summary>
Session_Tab::Session_Tab()
{
}

/// <summary>
/// Parameterized Constructor for the session_tab
/// </summary>
/// <param name="name">Session Name</param>
/// <param name="pos">Position of the session_tab</param>
/// <param name="size">Dimension of the session_tab</param>
/// <param name="font">Font for the session_tab</param>
Session_Tab::Session_Tab(std::string name, sf::Vector2f pos, sf::Vector2f size, sf::Font& font)
{
	session_name = name;
	rect_pos = pos;
	rect_size = size;
	roboto_font = font;
	total_time_info.setFont(font);
	Set_Components();
	Set_Dimension();
	Set_Button();
}

/// <summary>
/// Default destructor for the session_tab
/// </summary>
Session_Tab::~Session_Tab()
{
}

/// <summary>
/// Initialize the components for the session_tab
/// </summary>
void Session_Tab::Set_Components()
{
	circle_radius = BORDER_RADIUS;
	background_color = sf::Color(BLUE_THEMED_C);
	total_time_info.setCharacterSize(14);
	total_time_info.setString("00:00:0.00");
	total_time_info.setOrigin({ total_time_info.getGlobalBounds().width / 2, 0.f });
}

/// <summary>
/// Set dimension to the UI components of the session_tab
/// </summary>
void Session_Tab::Set_Dimension()
{
	main_rect.setSize(rect_size);
	up_rect.setSize({ rect_size.x, circle_radius });
	left_rect.setSize({ circle_radius, rect_size.y });
	right_rect.setSize({ circle_radius, rect_size.y});
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

	total_time_info.setPosition({ main_rect_pos.x-30.f, main_rect_pos.y+20.f});
}

/// <summary>
/// Initialize the session_btn for the session_tab
/// </summary>
void Session_Tab::Set_Button()
{
	session_btn = new Btn(session_name, {main_rect_pos.x, main_rect_pos.y - 20.f}, 15, roboto_font);
	delete_btn = new Btn("Delete", { main_rect_pos.x + 70.f, main_rect_pos.y + 28.f }, 10, roboto_font);
	delete_btn->SetFillColor(sf::Color(209,265,42));
	delete_btn->text.setFillColor(sf::Color::White);
}

/// <summary>
/// Render all the UI components of the sesion_tab
/// </summary>
/// <param name="window">Window to render to</param>
void Session_Tab::Draw_To(sf::RenderWindow& window)
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
	window.draw(total_time_info);
	session_btn->DrawTo(window);
	delete_btn->DrawTo(window);
}

void Session_Tab::Set_Total_Time_Text(std::string total_time_string)
{
	total_time_info.setString(total_time_string);
}

/// <summary>
/// Callback function to set every row data from the database
/// to the local container
/// </summary>
/// <param name="NotUsed">A placeholder</param>
/// <param name="argc">Number of arguments</param>
/// <param name="argv">2D array to the row data</param>
/// <param name="azColName">2D array to the column data</param>
/// <returns>Returns success/failure</returns>
static int session_tracker::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	db_session_list_data.push_back(argv[1]);
	return 0;
}

/// <summary>
/// Fetches the data from the database
/// </summary>
/// <param name="s">Directory Location</param>
/// <returns>Returns success/failure</returns>
static int session_tracker::select_data(const char* s)
{
	sqlite3* DB;
	char* messageError;
	std::string sql = "SELECT * FROM SESSION;";
	int exit = sqlite3_open(s, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), session_tracker::callback, NULL, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in selectData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records selected Successfully!" << std::endl;
	return 0;
}

/// <summary>
/// Updates the data to the database
/// </summary>
/// <param name="s">Directory Location</param>
/// <returns>Returns success/failure</returns>
static int session_tracker::insert_data(const char* s)
{
	sqlite3* DB;
	char* messageError;
	int exit = sqlite3_open(s, &DB);
	std::string sql;
	if (!new_input_texts.empty())
	{
		std::string tester = "";
		for (size_t i = 0; i < new_input_texts.size(); ++i)
		{
			tester += "('" + new_input_texts[i] + "'),";
		}
		tester.erase(tester.size() - 1, 1);
		sql = "INSERT INTO SESSION (session_name) VALUES" + tester + ";";
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

int session_tracker::fetch_total_time_list(const char* s, std::string session_name)
{
	sqlite3* DB;
	char* messageError;
	std::string sql = "SELECT total_time FROM SESSION_LIST where session_id_name = '" + session_name + "' ORDER BY id DESC LIMIT 1;";
	int exit = sqlite3_open(s, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), session_tracker::call_back_total_time_list, &session_name, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in selectData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records selected Successfully!" << std::endl;
	return 0;
}

int session_tracker::call_back_total_time_list(void* something, int argc, char** argv, char** azColName)
{
	db_total_time_string.clear();
	db_total_time_string.push_back(*reinterpret_cast<std::string*>(something));
	db_total_time_string.push_back(argv[0]);
	db_total_time_list.push_back(db_total_time_string);
	return 0;
}

int session_tracker::delete_session_tab(const char* s, std::string name)
{
	sqlite3* DB;
	char* messageError;
	std::string sql = "DELETE FROM SESSION WHERE session_name = '" + name + "';"
					  "DELETE FROM SESSION_LIST WHERE session_id_name = '" + name + "';";

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

int session_tracker::insert_new_session(const char* s, std::string session_name)
{
	sqlite3* DB;
	char* messageError;
	int exit = sqlite3_open(s, &DB);
	std::string sql;
	sql = "INSERT INTO SESSION (session_name) VALUES('" + session_name + "');";
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in insertData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records inserted Successfully!" << std::endl;
	return 0;
}