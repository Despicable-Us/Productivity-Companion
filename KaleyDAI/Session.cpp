#include "Session.h"

Record::Record(sf::Font& f, bool is_date)
{
	this->font = f;
	time_stamp_text.setFont(f);
	time_duration_text.setFont(f);
	date_text.setFont(f);
	time_stamp_text.setCharacterSize(TEXT_CHAR_SIZE);
	time_duration_text.setCharacterSize(TEXT_CHAR_SIZE);
	date_text.setCharacterSize(TEXT_CHAR_SIZE);

	rect_h = RECT_H;
	circle_radius = CIRCLE_R;
	date_bar = is_date;

	!is_date ? rect_w = DETAIL_BAR_WIDTH : rect_w = DATE_BAR_WIDTH;

	rect.setOrigin({ 0.f, rect_h / 2 });
	rect.setSize({ rect_w, rect_h });

	c_left.setRadius(circle_radius);
	c_right.setRadius(circle_radius);
	c_left.setOrigin({ CIRCLE_R, CIRCLE_R });
	c_right.setOrigin({ CIRCLE_R, CIRCLE_R });
}

void Record::Set_Text(std::vector<std::string> data)
{
	record_data = data;
	time_stamp_text.setString(this->record_data[0]);
	time_duration_text.setString(this->record_data[1]);
	time_stamp_text.setFillColor(sf::Color::Black);
	time_duration_text.setFillColor(sf::Color::Black);

	rect.setFillColor(sf::Color(DETAIL_BAR_C));
	c_left.setFillColor(sf::Color(DETAIL_BAR_C));
	c_right.setFillColor(sf::Color(DETAIL_BAR_C));

	time_stamp_text.setOrigin({ 0.f, time_stamp_text.getGlobalBounds().height / 2 });
	time_duration_text.setOrigin({ 0.f, time_duration_text.getGlobalBounds().height / 2 });

	time_stamp_text.setPosition({ TIME_STAMP_POSX, rect_pos.y - time_stamp_text.getGlobalBounds().height / 6 });
	time_duration_text.setPosition({ TIME_DURATION_POSX, rect_pos.y - time_stamp_text.getGlobalBounds().height / 3 });
}

void Record::Set_Text(std::string data)
{
	is_bar = true;
	date_text.setString(data);
	date_text.setFillColor(sf::Color::White);

	rect.setFillColor(sf::Color(DATE_BAR_C));
	c_left.setFillColor(sf::Color(DATE_BAR_C));
	c_right.setFillColor(sf::Color(DATE_BAR_C));

	date_text.setOrigin({ date_text.getGlobalBounds().width / 2, date_text.getGlobalBounds().height / 2 });
	date_text.setPosition({ DATE_TEXT_POSX, rect_pos.y - time_stamp_text.getGlobalBounds().height / 3 - DATE_TEXT_POSY_OFFSET });
}

void Record::Set_Rect_Position(sf::Vector2f pos)
{
	rect.setPosition(pos);
	rect_bounds = rect.getGlobalBounds();
	rect_pos = rect.getPosition();

	c_left.setPosition({ rect_bounds.left, rect_bounds.top + rect_bounds.height / 2 });
	c_right.setPosition({ rect_bounds.left + rect_bounds.width, rect_bounds.top + rect_bounds.height / 2 });

}

void Record::Draw_To(sf::RenderWindow& window)
{
	window.draw(rect);
	window.draw(c_left);
	window.draw(c_right);
	window.draw(time_stamp_text);
	window.draw(time_duration_text);
	window.draw(date_text);
}

std::vector<std::vector<std::string>> result_vec;
std::vector<std::vector<std::string>> new_data_added_vec;

// Session Members
Session::Session(sf::RenderWindow& window, std::string name)
{
	// setting window info
	win_size = window.getSize();
	win_sizeF = static_cast<sf::Vector2f>(win_size);
	win_center = sf::Vector2f({ win_sizeF.x / 2, win_sizeF.y / 2 });
	session_name = name;
	Load_Tex_Font();
	load_session_name();
	Init_UI_Components();
	Load_Clock_Components();
	Today_Date();
	Init_Variables();
	Get_DB_Data();
	
	time_data = { "", "" };
}


void Session::Init_Variables()
{
	Btn_Trigger = [&]()
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

			// handling the start time of the time interval
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

			// Working with the system time and all that thing
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

			// Finding the duration 
			std::vector<int> start_vec, end_vec;
			std::string temp;

			for (auto str : start_timer)
			{
				if (str != ':' && str != '.')
				{
					temp += str;
				}
				else
				{
					start_vec.push_back(stoi(temp));
					temp = "";
				}
			}
			start_vec.push_back(stoi(temp));
			temp = "";

			for (auto str : end_timer)
			{
				if (str != ':' && str != '.')
				{
					temp += str;
				}
				else
				{
					end_vec.push_back(stoi(temp));
					temp = "";
				}
			}
			end_vec.push_back(stoi(temp));

			duration = Timer_Duration(start_vec, end_vec);
			duration = "Duration: " + duration;

			time_data[1] = duration;

			data_to_map[date_string].push_back(time_data);
			records_table.clear();
			Map_To_Records_Vec();
			new_data_added_vec.push_back({ date_string, time_data[0], time_data[1] });
			added_vectors = new_data_added_vec;
			timer_string = time_to_str;
			std::cout << timer_string << std::endl;
		}
		btn_color_toggle = !btn_color_toggle;
	};

	Home_Btn_Trigger = [&]()
	{
		home_btn_clicked = true;
	};

	show_scroll_bar = false;
	scroll_bar.setFillColor(sf::Color(DATE_BAR_C));
	scroll_bar.setPosition({ 741.f, 0.f });
	scroll_bar.setSize({ 18.f, 207025 / ((records_table.size() + 1) * 35.f) });

	dir = "C:\\Users\\Progosta\\Desktop\\Tori Laure\\Session Tracker\\Session Tracker\\Session.db";
}

void Session::Load_Tex_Font()
{
	if(!bg_image_tex.loadFromFile("Texture/bgImageText1.png"))
		throw "Error in loading the 'bgImageText1'";

	if (!bg_stop_tex.loadFromFile("Texture/stopTimer1.png"))
		throw "Error in loading the 'stopTimer1.png'";

	if (!kaushan_font.loadFromFile("Font/KaushanScript-Regular.ttf"))
		throw "Error in loading 'Roboto-Medium.ttf";

	if (!roboto_font.loadFromFile("Font/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium.ttf'";

	bg_image.setTexture(bg_image_tex);
	bg_stop_image.setTexture(bg_stop_tex);
	bg_image.setPosition({ 0.f, 0.f });
	bg_stop_image.setPosition({ 0.f, -200.f });
}


void Session::load_session_name()
{
	std::cout << session_name << std::endl;
	session_text = sf::Text(session_name, kaushan_font, 30);
	session_text.setPosition({ win_center.x - session_text.getGlobalBounds().width / 2, 35.f });
	session_text.setFillColor(sf::Color::White);

	circle.setRadius(BG_NAME_CIRCLE_R);
	circle.setOrigin({ BG_NAME_CIRCLE_R, BG_NAME_CIRCLE_R });
	circle.setFillColor(sf::Color(BG_CIRCLE_FILL_C));
	circle.setPosition({ session_text.getGlobalBounds().left - circle.getRadius() * 2, session_text.getGlobalBounds().top + session_text.getGlobalBounds().height / 2 });
}

void Session::Init_UI_Components()
{
	Create_Toggle_Btn();
	Create_Home_Btn();
}

void Session::Create_Toggle_Btn()
{
	toggle_btn = new Btn("Start Session", { win_center.x, bg_image.getGlobalBounds().height }, 16, roboto_font);
	toggle_btn->SetFillColor(sf::Color(START_BTN_COLOR));
	toggle_btn->text.setFillColor(sf::Color::White);
	btn_color_toggle = false;
}

void Session::Load_Clock_Components()
{
	t2 = 0;
	seconds = 0;
	mili_sec = 0;
	ms = 0;
	timer_on = false;
	
	timer_text.setFont(roboto_font);
	timer_text.setFillColor(sf::Color::White);
	timer_text.setPosition({ win_sizeF.x - 150.f, 120.f });
	timer_text.setCharacterSize(24);
	time_to_str = "00:00:0.00";

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

void Session::Today_Date()
{
	std::time_t t = std::time(NULL);
	std::tm* tm = std::localtime(&t);
	ss << std::put_time(tm, "%e %b %Y");
	date_string = ss.str();
}

void Session::Create_Home_Btn()
{
	home_btn = new Btn("Home", { 55.f, 30.f }, 14, roboto_font);
	home_btn->SetFillColor(sf::Color(DATE_BAR_C));
	home_btn->text.setFillColor(sf::Color::White);
	home_btn_clicked = false;
}

void Session::Get_DB_Data()
{
	std::vector<std::vector<std::string>> date_vec;
	select_data(dir);
	date_vec = result_vec;

	std::vector<std::string> vec_data;
	for (size_t i = 0; i < date_vec.size(); ++i)
	{
		vec_data = { date_vec[i][1], date_vec[i][2] };
		data_to_map[date_vec[i][0]].push_back(vec_data);
	}
	Map_To_Records_Vec();
}

void Session::Update_DB_Data()
{
	if (!new_data_added_vec.empty())
	{
		insert_data(dir);
	}
}

void Session::Map_To_Records_Vec()
{
	Record date_record(roboto_font, true);
	Record detail_record(roboto_font);
	for (it = data_to_map.begin(); it != data_to_map.end(); it++)
	{
		if (it == data_to_map.begin())
		{
			date_record.Set_Rect_Position({ 20.f, 15.f });
			date_record.Set_Text(it->first);
			records_table.push_back(Record(date_record));
		}
		else
		{
			sf::Vector2f lastRecordPos = records_table[records_table.size() - 1].rect.getPosition();
			date_record.Set_Rect_Position({ lastRecordPos.x, lastRecordPos.y + 35.f });
			date_record.Set_Text(it->first);
			records_table.push_back(Record(date_record));
		}
		for (size_t i = 0; i < it->second.size(); ++i)
		{
			sf::Vector2f lastRecordPos = records_table[records_table.size() - 1].rect.getPosition();
			detail_record.Set_Rect_Position({ lastRecordPos.x, lastRecordPos.y + 35.f });
			detail_record.Set_Text(it->second[i]);
			records_table.push_back(Record(detail_record));
		}
	}
}

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

void Session::Run_Events(sf::RenderWindow& window, sf::Event& event, bool &show_session, bool &show_button)
{
	toggle_btn->BtnEvents(window, event, Btn_Trigger);
	home_btn->BtnEvents(window, event, Home_Btn_Trigger);
	Timer_Run_Event();
	if (home_btn_clicked)
	{
		show_session = false;
		show_button = true;
		home_btn_clicked = false;
	}
}

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

void Session::View_Scroll_Event(sf::Event& event, sf::View& scroll_view)
{
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


bool Comparator_Func::operator()(const std::string& first, const std::string& second) const
{
	std::vector<int> date_first = Convert_Date_To_Vec(first);
	std::vector<int> date_second = Convert_Date_To_Vec(second);
	return date_first[2] > date_second[2] or date_first[1] > date_second[1] or date_first[0] > date_second[0];
}

std::map<std::string, int> month_map =
{
	{"Jan", 1},
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

static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	result_vec.push_back(string_to_2dVec_parser(argv[1]));
	return 0;
}

static int select_data(const char* s)
{
	sqlite3* DB;
	char* messageError;

	std::string sql = "SELECT * FROM SESSION_LIST;";

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error in selectData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records selected Successfully!" << std::endl;

	return 0;
}

static int insert_data(const char* s)
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
			tester += "('" + new_data_added_vec[i][0] + "_" + new_data_added_vec[i][1] + "_" + new_data_added_vec[i][2] + "'),";
		}
		tester.erase(tester.size() - 1, 1);


		sql = "INSERT INTO SESSION_LIST (session_detail) VALUES" + tester + ";";
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
