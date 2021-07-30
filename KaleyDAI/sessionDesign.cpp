#include "SFML/Graphics.hpp"
#include <stdc++.h>
#include "Btn.h"
#include <ctime>
#include <chrono>
#include <time.h>
#include <sstream>
#include <sqlite3.h>
#define SQLITE_OK 0

// Color Container
#define FADEW 230, 230, 230
#define DATEBARC 41, 41, 41

static int selectData(const char* s);
static int insertData(const char* s);
static int callback(void*, int, char**, char**);
std::vector<std::string> string_to_2dVec_parser(char* row);
std::vector<std::vector<std::string>> result_vec;



class Record
{
	public:
		sf::RectangleShape rect;
		sf::CircleShape Cleft, Cright;
		sf::Font font;
		sf::Text timeT;
		sf::Text durationT;
		sf::Text dayT;
		std::vector<std::string> recordData;
		sf::Vector2f rectPos;
		sf::FloatRect rectBounds;
		sf::FloatRect timeTBounds;
		sf::FloatRect durationTBounds;

		float rectW, rectH, circleRadius;

		bool isBar = false;
		bool date_bar;
		
		Record(sf::Font& f, bool isDate = 0)
		{
			this->font = f;
			this->timeT.setFont(f);
			this->timeT.setCharacterSize(16);
			this->durationT.setCharacterSize(16);
			this->durationT.setFont(f);
			this->dayT.setFont(f);
			this->dayT.setCharacterSize(16);
			rectH = 30.f;
			circleRadius = 15.f;
			date_bar = isDate;
			if (!isDate)
			{
				rectW = 700.f;
				this->rect.setOrigin({ 0.f, rectH / 2 });
			}
			else
			{
				rectW = 300.f;
				this->rect.setOrigin({ 0.f, rectH / 2 });
			}


			this->rect.setSize({ rectW, rectH  });
			
			this->Cleft.setRadius(circleRadius);
			this->Cright.setRadius(circleRadius);
			this->Cleft.setOrigin({ circleRadius, circleRadius });
			this->Cright.setOrigin({ circleRadius, circleRadius });

		}

		void SetText(std::vector<std::string> data)
		{

			this->recordData = data;
			this->timeT.setString(this->recordData[0]);
			this->durationT.setString(this->recordData[1]);
			this->timeT.setFillColor(sf::Color::Black);
			this->durationT.setFillColor(sf::Color::Black);

			this->rect.setFillColor(sf::Color(FADEW));
			this->Cleft.setFillColor(sf::Color(FADEW));
			this->Cright.setFillColor(sf::Color(FADEW));

			this->timeT.setOrigin({ 0.f, this->timeT.getGlobalBounds().height / 2 });
			this->durationT.setOrigin({ 0.f, this->durationT.getGlobalBounds().height / 2 });

			this->timeT.setPosition({ 30.f, this->rectPos.y - this->timeT.getGlobalBounds().height / 6 });
			this->durationT.setPosition({ 510.f, this->rectPos.y - this->timeT.getGlobalBounds().height / 3 });
			
		}

		// Overloaded
		void SetText(std::string data)
		{
			this->isBar = true;
			this->dayT.setString(data);
			this->dayT.setFillColor(sf::Color::White);

			this->rect.setFillColor(sf::Color(DATEBARC));
			this->Cleft.setFillColor(sf::Color(DATEBARC));
			this->Cright.setFillColor(sf::Color(DATEBARC));

			this->dayT.setOrigin({ this->dayT.getGlobalBounds().width / 2, this->dayT.getGlobalBounds().height / 2 });
			this->dayT.setPosition({ 70.f, this->rectPos.y - this->timeT.getGlobalBounds().height / 3 - 3.f });
		}
		

		void SetRectPosition(sf::Vector2f pos)
		{
			this->rect.setPosition(pos);
			this->rectBounds = this->rect.getGlobalBounds();
			this->rectPos = this->rect.getPosition();
	
			this->Cleft.setPosition({rectBounds.left, rectBounds.top + rectBounds.height/2});
			this->Cright.setPosition({ rectBounds.left + rectBounds.width, rectBounds.top + rectBounds.height / 2 });

		}
		
		void DrawTo(sf::RenderWindow& window)
		{
			window.draw(this->rect);
			window.draw(this->Cleft);
			window.draw(this->Cright);
			window.draw(this->timeT);
			window.draw(this->durationT);
			window.draw(this->dayT);
		}
};


std::string timerDuration(std::vector<int> start, std::vector<int> end)
{
	std::vector<std::string> duraVec;
	for (int i = end.size() - 1; i >= 0; --i)
	{
		if (end[i] < start[i])
		{
			if (i == end.size() - 1)
			{
				end[i] += 100;
				end[int(i-1)]--;
			}
			else
			{
				end[i] += 60;
				end[int(i-1)]--;
			}
		}

		duraVec.insert(duraVec.begin(), std::to_string(end[i] - start[i]));
	}
	for (int i = 0; i < 2; i++)
	{
		if (duraVec[i].size() == 1)
		{
			duraVec[i].resize(2, '0');
			std::reverse(duraVec[i].begin(), duraVec[i].end());
		}
	}
	return duraVec[0] + ":" + duraVec[1] + ":" + duraVec[2] + "." + duraVec[3];
}

std::map<std::string, int> month_map =
{
	{"Jan", 1},
	{"Feb", 2},
	{"Mar", 3},
	{"Apr", 4},
	{"May", 5},
	{"Jun", 6},
	{"Jul", 7},
	{"Aug", 8},
	{"Sep", 9},
	{"Oct", 10},
	{"Nov", 11},
	{"Dec", 12}
};

std::vector<int> ConvertDateToVec(std::string date_string)
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

class com
{
public:
	bool operator()(const std::string &first,  const std::string &second) const
	{
		std::vector<int> date_first = ConvertDateToVec(first);
		std::vector<int> date_second = ConvertDateToVec(second);
		return date_first[2] > date_second[2] or date_first[1] > date_second[1] or date_first[0] > date_second[0];
	}
};

//auto com = [&](const std::string& first, const std::string& second)
//{
//	std::vector<int> date_first = ConvertDateToVec(first);
//	std::vector<int> date_second = ConvertDateToVec(second);
//	return date_first[2] > date_second[2] or date_first[1] > date_second[1] or date_first[0] > date_second[0];
//};




std::map<std::string, std::vector<std::vector<std::string>>, com> data_to_map;
std::map<std::string, std::vector<std::vector<std::string>>>::iterator it;


void map_to_records_vec(std::vector<Record> &recordsTable, sf::Font &robotoFont)
{
	Record tableDate(robotoFont, true);
	Record record(robotoFont);
	for (it = data_to_map.begin(); it != data_to_map.end(); it++)
	{
		if (it == data_to_map.begin())
		{
			tableDate.SetRectPosition({ 20.f, 15.f });
			tableDate.SetText(it->first);
			recordsTable.push_back(Record(tableDate));
		}
		else
		{
			sf::Vector2f lastRecordPos = recordsTable[recordsTable.size() - 1].rect.getPosition();
			tableDate.SetRectPosition({ lastRecordPos.x, lastRecordPos.y + 35.f });
			tableDate.SetText(it->first);
			recordsTable.push_back(Record(tableDate));
		}
		for (size_t i = 0; i < it->second.size(); ++i)
		{
			sf::Vector2f lastRecordPos = recordsTable[recordsTable.size() - 1].rect.getPosition();
			record.SetRectPosition({ lastRecordPos.x, lastRecordPos.y + 35.f });
			record.SetText(it->second[i]);
			recordsTable.push_back(Record(record));
		}
	}
	for (it = data_to_map.begin(); it != data_to_map.end(); ++it)
	{
		std::cout << it->first << std::endl;
		for (size_t i = 0; i < it->second.size(); ++i)
		{
			for (size_t j = 0; j < it->second[i].size(); ++j)
			{
				std::cout << it->second[i][j] << '\t';
			}
			std::cout << std::endl;
		}
	}
}


// global section for the database component
std::vector < std::vector < std::string>> new_data_added_vec;


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(760, 675), "Session", sf::Style::Default, settings);
	sf::Event event;

	// Window component
	sf::Vector2u winSize = window.getSize();
	sf::Vector2f winSizeF = static_cast<sf::Vector2f>(winSize);
	sf::Vector2f winCenter({ winSizeF.x / 2, winSizeF.y / 2 });

	//Background thingy
	sf::Texture bgImageTex, bgStopTex;
	if (!bgImageTex.loadFromFile("Texture/bgImageText1.png"))
		throw "Error in loading the 'bgImageText1'";

	if (!bgStopTex.loadFromFile("Texture/stopTimer1.png"))
		throw "Error in loading the 'stopTimer1.png'";

	sf::Sprite bgImage, bgStopImage;
	bgImage.setTexture(bgImageTex);
	bgImage.setPosition({ 0.f, 0.f });
	bgStopImage.setTexture(bgStopTex);
	bgStopImage.setPosition({ 0.f, -200.f });

	//UI font 
	sf::Font font;
	if (!font.loadFromFile("Font/KaushanScript-Regular.ttf"))
		throw "Error in loading 'Roboto-Medium.ttf";
	sf::Text uiText("Engineering", font, 30);

	// The SESSION NAME
	uiText.setPosition({ winCenter.x - uiText.getGlobalBounds().width / 2, 35.f });
	uiText.setFillColor(sf::Color::White);

	// Design Circle 
	sf::CircleShape circle(6.f);
	circle.setOrigin({ 6.f, 6.f });
	circle.setFillColor(sf::Color(8, 218, 145));
	circle.setPosition({ uiText.getGlobalBounds().left - circle.getRadius() * 2, uiText.getGlobalBounds().top + uiText.getGlobalBounds().height / 2 });

	// Button component
	sf::Font robotoFont;
	if (!robotoFont.loadFromFile("Font/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium.ttf'";

	sf::Color startColor(24, 171, 14);
	sf::Color stopColor(247, 12, 55);

	// Start session and Stop session interactive button
	Btn* startBtn = new Btn("Start Session", { winCenter.x, bgImage.getGlobalBounds().height }, 16, robotoFont);
	startBtn->SetFillColor(startColor);
	startBtn->text.setFillColor(sf::Color::White);
	bool btnColorToggle = false;

	// all about the timer
	sf::Clock clock;
	float t1;
	sf::Int32 t2 = 0;
	int seconds = 0;
	int miliSec = 0;
	int ms = 0;
	bool timerOn = false; // timer thingy


	sf::Text time, trackerText("Tracking", robotoFont, 20), designateTime("HRS        MIN        SEC", robotoFont, 10);

	// Time display
	time.setFont(robotoFont);
	time.setFillColor(sf::Color::White);
	time.setPosition({ winSizeF.x - 150.f, 120.f });
	time.setCharacterSize(24);
	std::string timeToStr ="00:00:0.00"; // time parsed string

	// HRS MIN SEC below the timer
	designateTime.setFillColor(sf::Color::White);
	designateTime.setPosition({time.getGlobalBounds().left+8.f, 150.f});
	
	// 'Tracking' TEXT display
	trackerText.setPosition({ winCenter.x - trackerText.getGlobalBounds().width / 2, 110.f });
	sf::CircleShape trackingShape(5.f);
	trackingShape.setOrigin({ 5.f, 5.f });
	trackingShape.setPosition({trackerText.getGlobalBounds().left+trackerText.getGlobalBounds().width+trackingShape.getRadius()*2, 
								trackerText.getGlobalBounds().top});
	trackingShape.setFillColor(stopColor);
	bool showTimer = false;


	// dummy data just to show
	std::vector<std::string> data = {"Time Stamp: 12:56 am - 3:02pm", "Duration: 02:06:56.98"};
	// record object creation
	Record record(robotoFont);
	std::vector<Record> recordsTable;
	std::string date_string;
	std::ostringstream ss;
	
	
	// testing the theory of working with the data base
/*	std::vector<std::vector<std::string>> date_vec =
	{
		{"20 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:01:56.98"},
		{"20 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:02:56.98"},
		{"20 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:03:56.98"},
		{"19 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:04:56.98"},
		{"19 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:05:56.98"},
		{"19 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:06:56.98"},
		{"18 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:07:56.98"},
		{"18 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:08:56.98"},
		{"18 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:09:56.98"},
		{"17 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:10:56.98"},
		{"17 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:11:56.98"},
		{"17 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:12:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:13:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:14:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:15:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:16:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:17:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:18:56.98"},
		{"19 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:06:56.98"},
		{"18 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:07:56.98"},
		{"18 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:08:56.98"},
		{"18 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:09:56.98"},
		{"17 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:10:56.98"},
		{"17 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:11:56.98"},
		{"17 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:12:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:13:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:14:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:15:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:16:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:17:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:18:56.98"},
		{"19 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:06:56.98"},
		{"18 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:07:56.98"},
		{"18 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:08:56.98"},
		{"18 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:09:56.98"},
		{"17 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:10:56.98"},
		{"17 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:11:56.98"},
		{"17 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:12:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:13:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:14:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:15:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:16:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:17:56.98"},
		{"16 Jul 2021", "Time Stamp: 12:00 am - 12:00 pm", "Duration: 00:18:56.98"},
	}; */                  

	//working with the database
	std::vector<std::vector<std::string>> date_vec;
	const char* dir = "C:\\Users\\Progosta\\Desktop\\Tori Laure\\Session Tracker\\Session Tracker\\Session.db";
	selectData(dir);
	date_vec = result_vec;

	std::vector<std::string> vecData;

	for (size_t i = 0; i < date_vec.size(); i++)
	{
		vecData = { date_vec[i][1], date_vec[i][2] };
		data_to_map[date_vec[i][0]].push_back(vecData);
	}

	Record tableDate(robotoFont, true);
	map_to_records_vec(recordsTable, robotoFont);


	// to capture the time interval
	std::time_t t;
	std::tm* tm;
	char* dt;
	std::string startTime;
	std::string endTime;

	std::string mS;
	std::string hour;
	std::string minutes;

	std::string duration;
	std::string startTimer;
	std::string endTimer;


	// Today date
	t = std::time(NULL);
	tm = std::localtime(&t);
	ss << std::put_time(tm, "%e %b %Y");
	date_string = ss.str();
	std::cout << "Date_String: " << date_string << std::endl;


	// Inserting the view thingy
	sf::View scroll_view;
	scroll_view.reset(sf::FloatRect(0.f, 0.f, 760.f, 675.f));
	scroll_view.setViewport(sf::FloatRect(0.f, 0.326f, 1.f, 1.f));

	// add the scroll bar 
	sf::RectangleShape scroll_bar({18.f, 120.f});
	bool show_scroll_bar = false;
	scroll_bar.setFillColor(sf::Color::Black);
	scroll_bar.setPosition({741.f, 0.f});
	scroll_bar.setSize({18.f, 207025 / ((recordsTable.size() + 1) * 35.f)});


	auto testFunc = [&]()
	{
		if (!btnColorToggle)
		{
			startBtn->SetFillColor(stopColor);
			startBtn->text.setString("Stop Session");
			clock.restart();
			timerOn = true;
			bgStopImage.setPosition({0.f, 0.f});
			bgImage.setPosition({ 0.f, -200.f });
			startBtn->SetBtnPosition({ winCenter.x, bgStopImage.getGlobalBounds().height });
			showTimer = true;

			// handling the start time of the time interval
			t = std::time(NULL);
			tm = std::localtime(&t);

			startTime.clear();
			startTime = std::to_string(tm->tm_hour) + ":";
			tm->tm_min < 10 ? startTime += "0" + std::to_string(tm->tm_min) : startTime += std::to_string(tm->tm_min);
			tm->tm_hour > 12 ? startTime += " pm" : startTime += " am";

			startTimer = timeToStr;
		}
		else
		{
			startBtn->SetFillColor(startColor);
			startBtn->text.setString("Start Session");
			timerOn = false;
			bgImage.setPosition({ 0.f, 0.f });
			bgStopImage.setPosition({ 0.f, -200.f });
			startBtn->SetBtnPosition({ winCenter.x, bgImage.getGlobalBounds().height });
			showTimer = false;

			// Working with the system time and all that thing
			t = std::time(NULL);
			tm = std::localtime(&t);

			endTime.clear();
			endTime = std::to_string(tm->tm_hour) + ":";
			tm->tm_min < 10 ? endTime += "0" + std::to_string(tm->tm_min) : endTime += std::to_string(tm->tm_min);
			tm->tm_hour > 12 ? endTime += " pm" : endTime += " am";
			
			data[0] = "Time Stamp: " + startTime + " - " + endTime;
			
			
			miliSec = int(t2 / 10);
			ms = int(t2 / 10);
			endTimer = timeToStr;

			// Finding the duration 
			std::vector<int> startVec, endVec;
			std::string temp;

			for (auto str : startTimer)
			{
				if (str != ':' && str != '.')
				{
					temp += str;
				}
				else
				{
					startVec.push_back(stoi(temp));
					temp = "";
				}
			}
			startVec.push_back(stoi(temp));
			temp = "";

			for (auto str : endTimer)
			{
				if (str != ':' && str != '.')
				{
					temp += str;
				}
				else
				{
					endVec.push_back(stoi(temp));
					temp = "";
				}
			}
			endVec.push_back(stoi(temp));
			

			duration = timerDuration(startVec, endVec);
			std::cout << duration << std::endl;
			
			duration = "Duration: " + duration;

			data[1] = duration;

			data_to_map[date_string].push_back(data);
			recordsTable.clear();
			map_to_records_vec(recordsTable, robotoFont);
			new_data_added_vec.push_back({ date_string, data[0], data[1] });
		}
		btnColorToggle = !btnColorToggle;
	};

	
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			// scroll bar thingy
			if (recordsTable.size() > 13)
			{
				show_scroll_bar = true;
				scroll_bar.setSize({ 18.f, 207025 / ((recordsTable.size() + 1) * 35.f) });
				float estimated_height = (recordsTable.size() - 12) * 35.f + 337.5;
				float scroll_bar_move = (((recordsTable.size() - 12) * 35.f + 455.f) - scroll_bar.getSize().y) / (recordsTable.size() - 12);
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
		startBtn->BtnEvents(window, event, testFunc);

		// the main timer logic

		if (timerOn)
		{
			t1 = clock.getElapsedTime().asSeconds();
			t2 = clock.getElapsedTime().asMilliseconds();

			if (miliSec > 0)
			{
				if (t2 / 10 >= 1)
				{
					if (ms < 99)
					{
						ms++;
					}
					else
					{
						miliSec = 0;
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

			hour = std::to_string(seconds / 3600);
			minutes = std::to_string((seconds / 60) % 60);

			if (hour.size() == 1)
			{
				hour.resize(2, '0');
				std::reverse(hour.begin(), hour.end());
			}
			if (minutes.size() == 1)
			{
				minutes.resize(2, '0');
				std::reverse(minutes.begin(), minutes.end());
			}

			miliSec == 0 ? mS = std::to_string(t2 / 10) : mS = std::to_string(ms);
			timeToStr = hour + ":" + minutes + ":" + std::to_string(seconds % 60) + "." + mS;
			time.setString(timeToStr);
		}


		window.clear(sf::Color::White);

		//scroll view shown here
		window.setView(scroll_view);
		if (show_scroll_bar)
		{
			window.draw(scroll_bar);
		}
		for (auto& record : recordsTable)
		{
			if (record.date_bar)
			{
				if (record.dayT.getString() == date_string)
				{
					record.dayT.setString("Today");
				}
			}
			record.DrawTo(window);
		}

		window.setView(window.getDefaultView());
		
		window.draw(bgImage);
		window.draw(bgStopImage);
		window.draw(uiText);
		if (showTimer)
		{
			window.draw(trackerText);
			window.draw(trackingShape);
			window.draw(time);
			window.draw(designateTime);
		}
		window.draw(circle);
		startBtn->DrawTo(window);
	
		window.display();
	}

	if (!new_data_added_vec.empty())
	{
		insertData(dir);
	}
}


static int selectData(const char* s)
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

static int insertData(const char* s)
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

static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	result_vec.push_back(string_to_2dVec_parser(argv[1]));

	return 0;
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