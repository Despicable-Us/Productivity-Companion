#include "InputField.h"


udh::inputField::inputField()
{
	font.loadFromFile("Fonts/ArialCE.ttf");
	textdata.setFont(font);
	textdata.setCharacterSize(23);
	textdata.setFillColor(sf::Color::Magenta);

	del.setBtnTextFont(font);
	del.setTextColor(sf::Color::Magenta);
	del.setTextSize(20);
	del.setbtntext("delete");
	del.setBtnSize(sf::Vector2f(60.f, 20.f));

	edit.setTextSize(20);
	edit.setBtnTextFont(font);
	edit.setTextColor(sf::Color::Magenta);
	edit.setBtnSize(sf::Vector2f(50.f, 20.f));

}
void udh::inputField::setdata(std::string a)
{
	text = a;
	textdata.setString(text);
}
void udh::inputField::drawtext(sf::RenderWindow* window)
{
	window->draw(textdata);
}
std::string udh::inputField::getdata()
{
	return text;
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
void udh::inputField::changecolor(sf::RenderWindow* window)
{
	textdata.setFillColor(sf::Color::Red);
}
void udh::inputField::setdone()
{
	this->completed = true;
}

void udh::drawlist(std::vector<udh::inputField>& textlist, sf::RenderWindow* window)
{
	if (!textlist.empty())
	{
		float i = 50;
		for (std::vector<udh::inputField>::iterator itr = textlist.begin(); itr < textlist.end(); itr++)
		{
			itr->setposition(sf::Vector2f(50.f, i));
			//setting up mark done button
			itr->done.setBtnPosition(sf::Vector2f(20.f, i + 5));
			itr->done.setBtnSize(sf::Vector2f(20.f, 20.f));
			itr->done.setbtnRect(sf::FloatRect(20.f, i + 5, 20.f, 20.f));

			//setting up delete button
			itr->del.setBtnPosition(sf::Vector2f(600.f, i + 5));
			itr->del.setbtnRect(sf::FloatRect(600.f, i + 5, 50.f, 20.f));
			itr->del.setTextPos();

			//seting up edit button
			itr->edit.setbtntext("edit");
			itr->edit.setBtnPosition({ 670.f, i + 5 });
			itr->edit.setbtnRect({ 670.f,i + 5,50.f,20.f });
			itr->edit.setTextPos();

			itr->edit.drawTo(*window);
			itr->del.drawTo(*window);
			itr->done.drawTo(*window);
			itr->drawtext(window);
			if (itr->completed == true)
			{
				itr->done.setbtncolor(sf::Color::Green);
				itr->crossline.setPosition(sf::Vector2f(50, i + 15));
				itr->crossline.setFillColor(sf::Color::Green);
				itr->crossline.setSize({ itr->gettext().getGlobalBounds().width, 2 });
				window->draw(itr->crossline);
			}
			else
			{
				itr->done.setbtncolor(sf::Color::White);
			}
			i += 50;
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
			std::cout << itr->completed;
		}
		else if (itr->del.ispressed(event, *window))
		{
			std::cout << "deleted\n";
			textlist.erase(itr);
			break;
		}
		else if (itr->edit.ispressed(event, *window))
		{
			itredit = itr;
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
					edititr->setdata(a);
					sampletext.setdata("");
					a.erase();
					textarea.unsetEditing();
					textarea.releasePressed();
				}
			}
			else if (a.length() <= 40)
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
					textlist.push_back(sampletext);
					sampletext.setdata("");
					a = "";
				}
			}
			else if (a.length() <= 40 && !a.empty())
			{
				a.pop_back();
				a.push_back(b);
				a.push_back('_');
				sampletext.setdata(a);
			}
		}
	}
}
