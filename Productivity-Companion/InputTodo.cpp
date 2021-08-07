#include "InputTodo.h"
#include "Database.h"

extern bool run_todo_list;
//default constructor
udh::inputField::inputField()
{
	this->font.loadFromFile("Fonts/Roboto-Medium.ttf");
	this->textdata.setFont(font);
	this->textdata.setFillColor(sf::Color(0,0,0));
	this->textdata.setString("");
	this->textdata.setCharacterSize(16);
	
	// Icon loading and setting
	this->loadIconTexture();

	//assigning day when task was created
	std::time_t current;
	std::time (&current);
	struct tm* timecreated;
	timecreated = std::localtime(&current);
	this->creationDay = timecreated->tm_year * 365 + timecreated->tm_mon * 30 + timecreated->tm_mday;
}

void udh::inputField::loadIconTexture()
{
	if (!del_tex.loadFromFile("Texture/dust-bin1.png"))
		throw "Error in loading the 'dust_bin.png'";
	if (!edit_tex.loadFromFile("Texture/pencil.png"))
		throw "Error in loading the 'pencil.png'";
	del_icon = Icon(del_tex);
	edit_icon = Icon(edit_tex);

}

void udh::inputField::setdata(std::string str)
{
	text = str;
	textdata.setString(text);
}

void udh::inputField::drawtext(sf::RenderWindow* window)
{
	window->draw(textdata);
}

std::string udh::inputField::getdata()
{
	return this->text;
}

sf::Text udh::inputField::gettext()
{
	return textdata;
}

void udh::inputField::setposition(sf::Vector2f position)
{
	textdata.setPosition(position);
}

sf::Font udh::inputField::getfont()
{
	return font;
}

void udh::inputField::setdone()
{
	this->completed = true;
}

bool udh::inputField::getstatus()
{
	return this->completed;
}
int udh::inputField::getDay()
{
	return this->creationDay;
}

void udh::inputField::setday(int a)
{
	this->creationDay = a;
}
void udh::inputField::setCreationTime()
{
	time_t current;
	time(&current);
	struct tm* timecreated = localtime(&current);
	char timebuffer[40];
	strftime(timebuffer, 40, "%a %b %d %Y\n",timecreated);
}

std::string udh::inputField::SanitizedData()
{
	size_t pos = 0;
	std::string data=this->getdata();
	while ((pos = data.find('\'', pos)) != std::string::npos) {
		data.replace(pos, 1, "''");
		pos += 2;
	}
	return data;
}


void udh::drawlist(std::vector<udh::inputField>& textlist, sf::RenderWindow* window)
{
	if (!textlist.empty())
	{
		float i = 0;
		for (std::vector<udh::inputField>::iterator itr = textlist.begin(); itr < textlist.end(); itr++)
		{
			sf::CircleShape cL(15.f), cR(15.f);
			sf::RectangleShape Rect;
			Rect.setSize({700.f, 30.f});
			Rect.setPosition({ 20.f,i });
			cL.setPosition(5.f, i);
			cR.setPosition(705.f, i);
			Rect.setFillColor(sf::Color(200, 200, 200));
			cL.setFillColor(sf::Color(200, 200, 200));
			cR.setFillColor(sf::Color(200, 200, 200));

			itr->setposition(sf::Vector2f(50.f, i+5));

			//setting up mark done button
			itr->done.setBtnPosition(sf::Vector2f(20.f, i + 9));
			itr->done.setBtnSize(sf::Vector2f(12.f, 12.f));
			itr->done.setbtnRect(sf::FloatRect(20.f, i + 5, 18.f, 18.f));
			itr->done.setoutline(sf::Color(150, 150, 150), 2);

			itr->del_icon.Set_Icon_Pos({630.f, i+15});
			

			window->draw(Rect);
			window->draw(cL);
			window->draw(cR);

			itr->done.drawTo(*window);
			itr->del_icon.Draw_To(*window);
			if (!itr->completed)
			{
				itr->edit_icon.Set_Icon_Pos({ 680.f, i + 15 });
				itr->edit_icon.Draw_To(*window);

			}
			itr->drawtext(window);

			if (itr->completed == true)
			{
				itr->done.setbtncolor(sf::Color(40, 40, 40));
				itr->crossline.setPosition(sf::Vector2f(50, i + 14));
				itr->crossline.setFillColor(sf::Color(40, 40, 40));
				itr->crossline.setSize({ itr->gettext().getGlobalBounds().width+1, 3});
				itr->textdata.setFillColor(sf::Color(100, 100, 100));
				window->draw(itr->crossline);
			}
			else
			{
				itr->done.setbtncolor(sf::Color(235, 235, 235));
				itr->textdata.setFillColor(sf::Color::Black);
			}
			i += 40;
		}
	}
}

void udh::checkAction(sf::Event event, std::vector<udh::inputField>& textlist, sf::RenderWindow* window,
	std::vector<udh::inputField>::iterator& itredit, udh::inputField& sample, udh::Button& textarea)
{
	for (std::vector<udh::inputField>::iterator itr = textlist.begin(); itr < textlist.end(); itr++)
	{
		if (itr->done.ispressed(event, *window))
		{
			if (itr->completed == false)
				itr->completed = true;
			else
				itr->completed = false;
		}

		else if (itr->del_icon.Run_Outside_Event(*window, event))
		{
			udh::DeleteTask(itr);
			textlist.erase(itr);
			break;
		}

		
		else if (itr->edit_icon.Run_Outside_Event(*window, event) && !itr->completed)
		{
			itredit = itr;
			itr->edit.setbtncolor(sf::Color(150, 140, 220));
			sample.setdata(itr->getdata());
			textarea.setEditing();
			textarea.setbtntext("");
			textarea.setpressed();
		}
	}
}

void udh::editTask(udh::inputField& sampletext, std::string& a, sf::Event event, std::vector<udh::inputField>::iterator& edititr,
	udh::Button& textarea)
{
	unsigned char b;
	a = sampletext.getdata();
	a.pop_back();
	a.push_back('_');
	sampletext.setdata(a);
	if (event.type == sf::Event::TextEntered)
	{
		//take unicode and store into unsigned char
		b = event.text.unicode;
		if (event.type == sf::Event::TextEntered)
		{
			//take unicode and store into unsigned char
			b = event.text.unicode;
			if (b == 8)
			{
				if (!a.empty())
				{
					a.pop_back();
					if (!a.empty())
						a.pop_back();
					a.push_back('_');
					sampletext.setdata(a);
				}
			}
			else if (b == 13)
			{
				if (a.length() > 1)
				{
					a.pop_back();
					a.push_back('\n');
					sampletext.setdata(a);
					udh::updateTask(edititr);
					edititr->setdata(a);
					edititr->edit.setbtncolor(sf::Color(235, 235, 235));
					sampletext.setdata("");
					a.erase();
					textarea.unsetEditing();
					textarea.releasePressed();
					edititr->edit_icon.Set_Unheld();
				}
			}
			else if (a.length() <= 65)
			{
				a.pop_back();
				a.push_back(b);
				a.push_back('_');
				sampletext.setdata(a);
			}
		}
	}
}

void udh::addTask(udh::inputField& sampletext, std::string& a, sf::Event event, std::vector<udh::inputField>& textlist, udh::Button textarea)
{
	unsigned char b;
	if (sampletext.getdata().empty() && textarea.getstate())
	{
		if (a.empty())
			a.push_back('_');
		sampletext.setdata(a);
	}
	if (event.type == sf::Event::TextEntered)
	{
		//take unicode and store into unsigned char
		b = event.text.unicode;
		if (event.type == sf::Event::TextEntered)
		{
			//take unicode and store into unsigned char
			b = event.text.unicode;
			if (b == 8)
			{
				if (!a.empty())
				{
					a.pop_back();
					if (!a.empty())
						a.pop_back();
					a.push_back('_');
					sampletext.setdata(a);
				}
			}
			else if (b == 13)
			{
				if (a.length() > 1)
				{
					a.pop_back();
					a.push_back('\n');
					sampletext.setdata(a);
					sampletext.setCreationTime();
					textlist.push_back(sampletext);
					//if (run_todo_list)
					//{
					//}
					udh::AddTask(sampletext);
					sampletext.setdata("");
					a = "";
				}
			}
			else if (a.length() <= 65 && !a.empty())
			{
				a.pop_back();
				a.push_back(b);
				a.push_back('_');
				sampletext.setdata(a);
			}
		}
	}
}