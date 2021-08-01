#include "Session.h"

/// <summary>
///  Default constructor for the RECORD
/// </summary>
Record::Record()
{
}

/// <summary>
/// Parameterized constructor for the RECORD
/// </summary>
/// <param name="f">Font referenced</param>
/// <param name="is_date">A bool to confirm if the RECORD is of type date or the detail.</param>
Record::Record(sf::Font& f, bool is_date)
{
	this->font = f;
	this->time_stamp_text.setFont(f);
	this->time_duration_text.setFont(f);
	this->date_text.setFont(f);
	this->time_stamp_text.setCharacterSize(TEXT_CHAR_SIZE);
	this->time_duration_text.setCharacterSize(TEXT_CHAR_SIZE);
	this->date_text.setCharacterSize(TEXT_CHAR_SIZE);
	this->rect_h = RECT_H;
	this->circle_radius = CIRCLE_R;
	this->date_bar = is_date;
	!is_date ? this->rect_w = DETAIL_BAR_WIDTH : this->rect_w = DATE_BAR_WIDTH;
	this->rect.setOrigin({ 0.f, this->rect_h / 2 });
	this->rect.setSize({ this->rect_w, this->rect_h });
	this->c_left.setRadius(this->circle_radius);
	this->c_right.setRadius(this->circle_radius);
	this->c_left.setOrigin({ CIRCLE_R, CIRCLE_R });
	this->c_right.setOrigin({ CIRCLE_R, CIRCLE_R });
}

/// <summary>
/// Set the text to the session detail
/// </summary>
/// <param name="data">A 2D vector of string to supply the data as session detail.</param>
void Record::Set_Text(std::vector<std::string> data)
{
	this->record_data = data;
	this->time_stamp_text.setString(this->record_data[0]);
	this->time_duration_text.setString(this->record_data[1]);
	this->time_stamp_text.setFillColor(sf::Color::Black);
	this->time_duration_text.setFillColor(sf::Color::Black);
	this->rect.setFillColor(sf::Color(DETAIL_BAR_C));
	this->c_left.setFillColor(sf::Color(DETAIL_BAR_C));
	this->c_right.setFillColor(sf::Color(DETAIL_BAR_C));
	this->time_stamp_text.setOrigin({ 0.f, this->time_stamp_text.getGlobalBounds().height / 2 });
	this->time_duration_text.setOrigin({ 0.f, this->time_duration_text.getGlobalBounds().height / 2 });
	this->time_stamp_text.setPosition({ TIME_STAMP_POSX, this->rect_pos.y - this->time_stamp_text.getGlobalBounds().height / 6 });
	this->time_duration_text.setPosition({ TIME_DURATION_POSX, this->rect_pos.y - this->time_stamp_text.getGlobalBounds().height / 3 });
}

/// <summary>
/// Set the text/date to the Date Bar
/// </summary>
/// <param name="data">String as the date.</param>
void Record::Set_Text(std::string data)
{
	this->is_bar = true;
	this->date_text.setString(data);
	this->date_text.setFillColor(sf::Color::White);

	this->rect.setFillColor(sf::Color(DATE_BAR_C));
	this->c_left.setFillColor(sf::Color(DATE_BAR_C));
	this->c_right.setFillColor(sf::Color(DATE_BAR_C));

	this->date_text.setOrigin({ this->date_text.getGlobalBounds().width / 2, this->date_text.getGlobalBounds().height / 2 });
	this->date_text.setPosition({ DATE_TEXT_POSX, this->rect_pos.y - this->time_stamp_text.getGlobalBounds().height / 3 - DATE_TEXT_POSY_OFFSET });
}

/// <summary>
/// Set the position of the RECORD
/// </summary>
/// <param name="pos">2D vector of float for the position of the RECORD</param>
void Record::Set_Rect_Position(sf::Vector2f pos)
{
	this->rect.setPosition(pos);
	this->rect_bounds = this->rect.getGlobalBounds();
	this->rect_pos = this->rect.getPosition();
	this->c_left.setPosition({ this->rect_bounds.left, this->rect_bounds.top + this->rect_bounds.height / 2 });
	this->c_right.setPosition({ this->rect_bounds.left + this->rect_bounds.width, this->rect_bounds.top + this->rect_bounds.height / 2 });
}

/// <summary>
/// Render the UI components to the window
/// </summary>
/// <param name="window">The window to render to</param>
void Record::Draw_To(sf::RenderWindow& window)
{
	window.draw(this->rect);
	window.draw(this->c_left);
	window.draw(this->c_right);
	window.draw(this->time_stamp_text);
	window.draw(this->time_duration_text);
	window.draw(this->date_text);
}

// 2D vector of string to contain the data fetched from the database
std::vector<std::vector<std::string>> result_vec;
// 2D vector of string to track the newly added data
std::vector<std::vector<std::string>> new_data_added_vec;
// The index used for the WHERE clause
std::string db_search_index;
// Total time holder
std::string total_time;

/// <summary>
/// Default Constructor
/// </summary>
Session::Session()
{
}

/// <summary>
/// Parameterized constructor for the SESSION app
/// </summary>
/// <param name="window">Window to render to</param>
/// <param name="name">The name of the sesion</param>
Session::Session(sf::RenderWindow& window, std::string name)
{
	this->win_size = window.getSize();
	this->win_sizeF = static_cast<sf::Vector2f>(this->win_size);
	this->win_center = sf::Vector2f({ this->win_sizeF.x / 2, this->win_sizeF.y / 2 });
	this->session_name = name;
	db_search_index = 1;
	this->Load_Tex_Font();
	this->Today_Date();
	this->Init_Variables();
	this->Run_Functions(name);
}

/// <summary>
/// A modifier function that loads the components to the SESSION for the session clicked
/// </summary>
/// <param name="name">The name of the sesison</param>
void Session::Run_Functions(std::string name)
{
	this->session_name = name;
	show_scroll_bar = false;
	this->reset_view = true;
	db_search_index = name;
	result_vec.clear();
	new_data_added_vec.clear();
	this->data_to_map.clear();
	this->records_table.clear();
	this->Set_Bg_Images_Pos();
	this->load_session_name();
	this->Init_UI_Components();
	total_time.clear();
	this->Get_DB_Data();
	this->Load_Clock_Components();
	this->time_data = { "", "" };
}

/// <summary>
/// Initializes the UI components
/// </summary>
void Session::Init_Variables()
{
	this->Btn_Trigger = [&]()
	{
		if (!btn_color_toggle)
		{
			toggle_btn->SetFillColor(sf::Color(STOP_BTN_COLOR));
			toggle_btn->text.setString("Stop Session");
			clock.restart();
			timer_on = true;
			bg_stop_image.setPosition({ 0.f, 0.f });
			bg_image.setPosition({ 0.f, -200.f });

			toggle_btn->SetBtnPosition({ win_center.x, bg_stop_image.getGlobalBounds().height });
			show_timer = true;
			std::time_t t = std::time(NULL);
			std::tm* tm = std::localtime(&t);
			start_time.clear();
			start_time = std::to_string(tm->tm_hour) + ":";
			tm->tm_min < 10 ? start_time += "0" + std::to_string(tm->tm_min) : start_time += std::to_string(tm->tm_min);
			tm->tm_hour > 12 ? start_time += " pm" : start_time += " am";
			start_timer = time_to_str;
		}
		else
		{
			toggle_btn->SetFillColor(sf::Color(START_BTN_COLOR));
			toggle_btn->text.setString("Start Session");
			timer_on = false;
			bg_image.setPosition({ 0.f, 0.f });
			bg_stop_image.setPosition({ 0.f, -200.f });
			toggle_btn->SetBtnPosition({ win_center.x, bg_image.getGlobalBounds().height });
			show_timer = false;

			std::time_t t = std::time(NULL);
			std::tm* tm = std::localtime(&t);
			end_time.clear();
			end_time = std::to_string(tm->tm_hour) + ":";
			tm->tm_min < 10 ? end_time += "0" + std::to_string(tm->tm_min) : end_time += std::to_string(tm->tm_min);
			tm->tm_hour > 12 ? end_time += " pm" : end_time += " am";
			time_data[0] = "Time Stamp: " + start_time + " - " + end_time;
			mili_sec = int(t2 / 10);
			ms = int(t2 / 10);
			end_timer = time_to_str;
			std::vector<int> start_vec, end_vec;
			std::string temp;
			start_vec = this->Convert_Data(start_timer);
			end_vec = this->Convert_Data(end_timer);

			duration = Timer_Duration(start_vec, end_vec);
			duration = "Duration: " + duration;
			time_data[1] = duration;
			data_to_map[date_string].push_back(time_data);
			records_table.clear();
			Map_To_Records_Vec();
			new_data_added_vec.push_back({ date_string, time_data[0], time_data[1] });
			added_vectors = new_data_added_vec;
			timer_string = time_to_str;
		}
		btn_color_toggle = !btn_color_toggle;
	};
	this->Home_Btn_Trigger = [&]()
	{
		home_btn_clicked = true;
		Update_DB_Data();
	};
	this->show_scroll_bar = false;
	this->scroll_bar.setFillColor(sf::Color(DATE_BAR_C));
	this->scroll_bar.setPosition({ 741.f, 0.f });
	this->scroll_bar.setSize({ 18.f, 207025 / ((records_table.size() + 1) * 35.f) });
	this->dir = "C:\\Users\\Progosta\\Desktop\\Tori Laure\\Session Tracker\\Session Tracker\\Session.db";
}

/// <summary>
/// Loads the background images and the UI fonts
/// </summary>
void Session::Load_Tex_Font()
{
	if(!this->bg_image_tex.loadFromFile("Texture/bgImageText1.png"))
		throw "Error in loading the 'bgImageText1'";
	if (!this->bg_stop_tex.loadFromFile("Texture/stopTimer1.png"))
		throw "Error in loading the 'stopTimer1.png'";
	if (!this->kaushan_font.loadFromFile("Font/KaushanScript-Regular.ttf"))
		throw "Error in loading 'Roboto-Medium.ttf";
	if (!this->roboto_font.loadFromFile("Font/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium.ttf'";
	this->bg_image.setTexture(this->bg_image_tex);
	this->bg_stop_image.setTexture(this->bg_stop_tex);
}

/// <summary>
/// Sets the position of the background image
/// </summary>
void Session::Set_Bg_Images_Pos()
{
	this->bg_image.setPosition({ 0.f, 0.f });
	this->bg_stop_image.setPosition({ 0.f, -200.f });
}

/// <summary>
/// Loads the session name and other related components.
/// </summary>
void Session::load_session_name()
{
	this->session_text = sf::Text(this->session_name, this->kaushan_font, 30);
	this->session_text.setPosition({ this->win_center.x - this->session_text.getGlobalBounds().width / 2, 35.f });
	this->session_text.setFillColor(sf::Color::White);
	this->circle.setRadius(BG_NAME_CIRCLE_R);
	this->circle.setOrigin({ BG_NAME_CIRCLE_R, BG_NAME_CIRCLE_R });
	this->circle.setFillColor(sf::Color(BG_CIRCLE_FILL_C));
	this->circle.setPosition({ this->session_text.getGlobalBounds().left - circle.getRadius() * 2, this->session_text.getGlobalBounds().top + session_text.getGlobalBounds().height / 2 });
}

/// <summary>
/// Creates the UI components: buttons 
/// </summary>
void Session::Init_UI_Components()
{
	this->Create_Toggle_Btn();
	this->Create_Home_Btn();
}

/// <summary>
/// Instanciates the toggle button
/// </summary>
void Session::Create_Toggle_Btn()
{
	this->toggle_btn = new Btn("Start Session", { this->win_center.x, this->bg_image.getGlobalBounds().height }, 16, this->roboto_font);
	this->toggle_btn->SetFillColor(sf::Color(START_BTN_COLOR));
	this->toggle_btn->text.setFillColor(sf::Color::White);
	this->btn_color_toggle = false;
}

/// <summary>
/// Loads all the clock components
/// </summary>
void Session::Load_Clock_Components()
{
	std::cout << total_time << std::endl;
	std::vector<int> total_time_int_vec;
	std::string temp;
	if (!total_time.empty())
	{
		total_time_int_vec = this->Convert_Data(total_time);
		seconds = total_time_int_vec[0] * 3600 + total_time_int_vec[1] * 60 + total_time_int_vec[2];
		mili_sec = total_time_int_vec[3];
		ms = total_time_int_vec[3];
		time_to_str = total_time;
	}
	else
	{
		seconds = 0;
		mili_sec = 0;
		ms = 0;
		time_to_str = "00:00:0.00";
	}

	t2 = 0;
	timer_on = false;
	
	timer_text.setFont(roboto_font);
	timer_text.setFillColor(sf::Color::White);
	timer_text.setPosition({ win_sizeF.x - 150.f, 120.f });
	timer_text.setCharacterSize(24);
	
	designate_time_text = sf::Text("HRS        MIN        SEC", roboto_font, 10);
	designate_time_text.setFillColor(sf::Color::White);
	designate_time_text.setPosition({ timer_text.getGlobalBounds().left + 8.f, 150.f });

	tracker_text = sf::Text("Tracking", roboto_font, 20);
	tracker_text.setPosition({ win_center.x - tracker_text.getGlobalBounds().width / 2, 110.f });
	tracking_shape.setRadius(TRACKER_CIRCLE_R);
	tracking_shape.setOrigin({ TRACKER_CIRCLE_R, TRACKER_CIRCLE_R });
	tracking_shape.setPosition({ tracker_text.getGlobalBounds().left + tracker_text.getGlobalBounds().width + tracking_shape.getRadius() * 2,
							tracker_text.getGlobalBounds().top });
	tracking_shape.setFillColor(sf::Color(STOP_BTN_COLOR));
	show_timer = false;
}

/// <summary>
/// Fetches the present date
/// </summary>
void Session::Today_Date()
{
	std::time_t t = std::time(NULL);
	std::tm* tm = std::localtime(&t);
	ss << std::put_time(tm, "%e %b %Y");
	date_string = ss.str();
}

/// <summary>
/// Create the home/back button
/// </summary>
void Session::Create_Home_Btn()
{
	home_btn = new Btn("Home", { 55.f, 30.f }, 14, roboto_font);
	home_btn->SetFillColor(sf::Color(DATE_BAR_C));
	home_btn->text.setFillColor(sf::Color::White);
	home_btn_clicked = false;
}

/// <summary>
/// Fetch the data from the db
/// </summary>
void Session::Get_DB_Data()
{
	std::vector<std::vector<std::string>> date_vec;
	session_detail::select_data(dir, session_name);
	date_vec = result_vec;

	std::vector<std::string> vec_data;
	for (size_t i = 0; i < date_vec.size(); ++i)
	{
		vec_data = { date_vec[i][1], date_vec[i][2] };
		data_to_map[date_vec[i][0]].push_back(vec_data);
	}
	Map_To_Records_Vec();
}

/// <summary>
/// Updates the data to the db
/// </summary>
void Session::Update_DB_Data()
{
	std::cout << time_to_str << std::endl;
	if (!new_data_added_vec.empty())
	{
		session_detail::insert_data(dir, time_to_str);
	}
}

/// <summary>
/// Converts the map data to the RECORDS
/// </summary>
void Session::Map_To_Records_Vec()
{
	Record date_record(roboto_font, true);
	Record detail_record(roboto_font);
	for (it = data_to_map.begin(); it != data_to_map.end(); it++)
	{
		if (it == data_to_map.begin())
		{
			date_record.Set_Rect_Position({ 20.f, 15.f });
		}
		else
		{
			sf::Vector2f lastRecordPos = records_table[records_table.size() - 1].rect.getPosition();
			date_record.Set_Rect_Position({ lastRecordPos.x, lastRecordPos.y + 35.f });
		}
		date_record.Set_Text(it->first);
		records_table.push_back(Record(date_record));
		for (size_t i = 0; i < it->second.size(); ++i)
		{
			sf::Vector2f lastRecordPos = records_table[records_table.size() - 1].rect.getPosition();
			detail_record.Set_Rect_Position({ lastRecordPos.x, lastRecordPos.y + 35.f });
			detail_record.Set_Text(it->second[i]);
			records_table.push_back(Record(detail_record));
		}
	}
}

/// <summary>
/// Converts the initial and final date vectors to the duration string
/// </summary>
/// <param name="start">The inital start time</param>
/// <param name="end">The ending stop time</param>
/// <returns>Duration in string</returns>
std::string Session::Timer_Duration(std::vector<int> start, std::vector<int> end)
{
	std::vector<std::string> dura_vec;
	for (int i = end.size() - 1; i >= 0; --i)
	{
		if (end[i] < start[i])
		{
			if (i == end.size() - 1)
			{
				end[i] += 100;
				end[int(i - 1)]--;
			}
			else
			{
				end[i] += 60;
				end[int(i - 1)]--;
			}
		}
		dura_vec.insert(dura_vec.begin(), std::to_string(end[i] - start[i]));
	}
	for (int i = 0; i < 2; i++)
	{
		if (dura_vec[i].size() == 1)
		{
			dura_vec[i].resize(2, '0');
			std::reverse(dura_vec[i].begin(), dura_vec[i].end());
		}
	}
	return dura_vec[0] + ":" + dura_vec[1] + ":" + dura_vec[2] + "." + dura_vec[3];
}

std::vector<int> Session::Convert_Data(std::string data_time)
{
	std::vector<int> result;
	std::string temp = "";
	for (auto str : data_time)
	{
		if (str != ':' and str != '.')
		{
			temp += str;
		}
		else
		{
			result.push_back(stoi(temp));
			temp = "";
		}
	}
	result.push_back(stoi(temp));
	return result;
}

/// <summary>
/// Events to run outside the window pollevent loop
/// </summary>
/// <param name="window">Window to render to</param>
/// <param name="event">Events from the main window</param>
/// <param name="show_session">Boolean to control the display.</param>
/// <param name="show_button">Boolean to control the display.</param>
//void Session::Run_Events(sf::RenderWindow& window, sf::Event& event, bool &show_session, bool &show_button)
//{
//	toggle_btn->BtnEvents(window, event, Btn_Trigger);
//	home_btn->BtnEvents(window, event, Home_Btn_Trigger);
//	Timer_Run_Event();
//	if (home_btn_clicked)
//	{
//		show_session = false;
//		show_button = true;
//		home_btn_clicked = false;
//	}
//}

void Session::Run_Events(sf::RenderWindow& window, sf::Event& event, bool& show_session, bool& show_button, bool& update_total_time_list)
{
	toggle_btn->BtnEvents(window, event, Btn_Trigger);
	home_btn->BtnEvents(window, event, Home_Btn_Trigger);
	Timer_Run_Event();
	if (home_btn_clicked)
	{
		show_session = false;
		show_button = true;
		home_btn_clicked = false;
		update_total_time_list = true;
	}
}

/// <summary>
/// The timer manipulation and mechanism function
/// </summary>
void Session::Timer_Run_Event()
{
	if (timer_on)
	{
		t1 = clock.getElapsedTime().asSeconds();
		t2 = clock.getElapsedTime().asMilliseconds();

		if (mili_sec > 0)
		{
			if (t2 / 10 >= 1)
			{
				if (ms < 99)
				{
					ms++;
				}
				else
				{
					mili_sec = 0;
					seconds++;
					ms = 0;
				}
				clock.restart();
			}
		}
		else if (t2 / 10 >= 99)
		{
			seconds += 1;
			clock.restart();
		}

		hours = std::to_string(seconds / 3600);
		minutes = std::to_string((seconds / 60) % 60);

		if (hours.size() == 1)
		{
			hours.resize(2, '0');
			std::reverse(hours.begin(), hours.end());
		}
		if (minutes.size() == 1)
		{
			minutes.resize(2, '0');
			std::reverse(minutes.begin(), minutes.end());
		}

		mili_sec == 0 ? mS = std::to_string(t2 / 10) : mS = std::to_string(ms);
		time_to_str = hours + ":" + minutes + ":" + std::to_string(seconds % 60) + "." + mS;
		timer_text.setString(time_to_str);
	}
}

/// <summary>
/// Event section for the scroll and the scroll bar in the view
/// </summary>
/// <param name="event">Event related to the main window</param>
/// <param name="scroll_view">View to display the RECORDS/SESSION_DETAIL to</param>
void Session::View_Scroll_Event(sf::Event& event, sf::View& scroll_view)
{
	if (reset_view)
	{
		Reset_Scroll_Bar_And_View(scroll_view);
		reset_view = false;
	}
	if (records_table.size() > 13)
	{

		show_scroll_bar = true;
		scroll_bar.setSize({ 18.f, 207025 / ((records_table.size() + 1) * 35.f) });
		float estimated_height = (records_table.size() - 12) * 35.f + 337.5;
		float scroll_bar_move = (((records_table.size() - 12) * 35.f + 455.f) - scroll_bar.getSize().y) / (records_table.size() - 12);
		if (event.type == sf::Event::MouseWheelMoved)
		{
			if (scroll_view.getCenter().y != 337.5)
			{
				if (event.mouseWheel.delta >= 1)
				{
					scroll_view.move(0.f, -35.f);
					scroll_bar.move(0.f, -scroll_bar_move);
				}
			}

			if (scroll_view.getCenter().y != estimated_height)
			{
				if (event.mouseWheel.delta <= -1)
				{
					scroll_view.move(0.f, 35.f);
					scroll_bar.move(0.f, scroll_bar_move);
				}
			}
		}
	}
}

void Session::Reset_Scroll_Bar_And_View(sf::View& scroll_view)
{
	scroll_view.reset(sf::FloatRect(0.f, 0.f, 760.f, 675.f));
	scroll_bar.setPosition({ scroll_bar.getPosition().x, 0.f });
}


/// <summary>
/// Render components in the view section
/// </summary>
/// <param name="window">Window to render to</param>
void Session::Draw_To_View(sf::RenderWindow& window)
{
	if (show_scroll_bar)
	{
		window.draw(scroll_bar);
	}
	for (auto& record : records_table)
	{
		if (record.date_text.getString() == date_string)
		{
			record.date_text.setString("Today");
		}
		record.Draw_To(window);
	}
}

/// <summary>
/// Render components in the  main window section
/// </summary>
/// <param name="window">Window to render to</param>
void Session::Draw_To_Main_Window(sf::RenderWindow& window)
{
	window.draw(bg_image);
	window.draw(bg_stop_image);
	window.draw(session_text);
	if (show_timer)
	{
		window.draw(tracker_text);
		window.draw(designate_time_text);
		window.draw(timer_text);
		window.draw(tracking_shape);
	}
	window.draw(circle);
	toggle_btn->DrawTo(window);
	home_btn->DrawTo(window);
}



/// <summary>
/// The comparator class supplied to the map for sorting the w.r.t. the key
/// </summary>
/// <param name="first">The first date string</param>
/// <param name="second">The consecutive second date string</param>
/// <returns>Boolean whether the sorting should be acending or decending</returns>
bool Comparator_Func::operator()(const std::string& first, const std::string& second) const
{
	std::vector<int> date_first = Convert_Date_To_Vec(first);
	std::vector<int> date_second = Convert_Date_To_Vec(second);
	return date_first[2] > date_second[2] or date_first[1] > date_second[1] or date_first[0] > date_second[0];
}

/// <summary>
/// A map for mapping months and the and the index
/// </summary>
std::map<std::string, int> month_map ={
	{ "Jan", 1},
	{ "Feb", 2 },
	{ "Mar", 3 },
	{ "Apr", 4 },
	{ "May", 5 },
	{ "Jun", 6 },
	{ "Jul", 7 },
	{ "Aug", 8 },
	{ "Sep", 9 },
	{ "Oct", 10 },
	{ "Nov", 11 },
	{ "Dec", 12 }
};

/// <summary>
/// Convert the date to vector of integer
/// </summary>
/// <param name="date_string">Date in string</param>
/// <returns>Vector of integer for hours:minutes:seconds</returns>
std::vector<int> Convert_Date_To_Vec(std::string date_string)
{
	std::vector<std::string> separate_string;
	std::string temp_str;
	std::istringstream ss(date_string);
	while (ss >> temp_str)
	{
		separate_string.push_back(temp_str);
	}
	return {
		stoi(separate_string[0]), month_map[separate_string[1]], stoi(separate_string[2])
	};
}

/// <summary>
/// Tokenizer to convert string delimited by '_' to vector of strings.
/// </summary>
/// <param name="row">String with the delimited included.</param>
/// <returns>Separated strings in a vector container.</returns>
std::vector<std::string> string_to_2dVec_parser(char* row)
{
	std::vector<std::string> result;
	std::string temp = "";
	std::string row_data = row;

	for (char str : row_data)
	{
		if (str != '_')
		{
			temp += str;
		}
		else
		{
			result.push_back(temp);
			temp = "";
		}
	}
	result.push_back(temp);
	return result;
}

/// <summary>
/// Call back function that run for every row data extracted from the database.
/// </summary>
/// <param name="NotUsed">An unused part of the program.</param>
/// <param name="argc">Count of the arguments.</param>
/// <param name="argv">Data of a row in an 2d array.</param>
/// <param name="azColName">Data of a column in an 2d array.</param>
/// <returns>Confirms the execution</returns>
static int session_detail::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	result_vec.push_back(string_to_2dVec_parser(argv[1]));
	total_time = argv[3];
	return 0;
}

/// <summary>
/// Fetches the data from the database
/// </summary>
/// <param name="s">Database location</param>
/// <param name="selected_data">Session name passed for the data to be selected according</param>
/// <returns>Confirms the execution</returns>
static int session_detail::select_data(const char* s, std::string selected_data = "")
{
	sqlite3* DB;
	char* messageError;
	std::string sql = "SELECT * FROM SESSION_LIST WHERE session_id_name = '" + selected_data + "';";

	int exit = sqlite3_open(s, &DB);
	
	exit = sqlite3_exec(DB, sql.c_str(), session_detail::callback, NULL, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in selectData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records selected Successfully!" << std::endl;
	return 0;
}

/// <summary>
/// Updates the data into the database.
/// </summary>
/// <param name="s">Database location.</param>
/// <returns>Confirms the execution.</returns>
static int session_detail::insert_data(const char* s, std::string total_time)
{
	sqlite3* DB;
	char* messageError;
	int exit = sqlite3_open(s, &DB);
	std::string sql;

	if (!new_data_added_vec.empty())
	{
		std::string tester = "";
		for (size_t i = 0; i < new_data_added_vec.size(); ++i)
		{
			tester += "('" + new_data_added_vec[i][0] + "_" + new_data_added_vec[i][1] + "_" + new_data_added_vec[i][2] +"','" + db_search_index + "','"+ total_time+ "'),";
		}
		tester.erase(tester.size() - 1, 1);
		sql = "INSERT INTO SESSION_LIST (session_detail, session_id_name, total_time) VALUES" + tester + ";";
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