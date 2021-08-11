#include <stdc++.h>
#include "SFML/Graphics.hpp"
#define WIDTH 594.f
#define HEIGHT 594.f
#define bW 64.f;
#define bH 64.f;
#define ZERO 0
class Box
{
public:
	sf::RectangleShape shape;
	sf::Text text;
	bool fixed = false;
	bool wrong = false;
	Box(sf::Font* font, float width, float height)
	{
		this->shape.setSize(sf::Vector2f(width, height));
		this->shape.setFillColor(sf::Color(250, 250, 250));
		this->text.setFont(*font);
		this->text.setCharacterSize(38);
		this->text.setFillColor(sf::Color(52, 72, 97));
	}
	void setTextSize(size_t size)
	{
		this->text.setCharacterSize(size);
	}
};

class Bar
{
public:
	sf::RectangleShape shape;
	Bar(int xPos, int yPos, float w, float h)
	{
		this->shape.setSize(sf::Vector2f(w, h));
		this->shape.setPosition(sf::Vector2f(100.f + xPos * 66.f, 150.f + yPos * 66.f));
		this->shape.setFillColor(sf::Color(52, 72, 97));
	}
};

void sameCellUpdate(std::vector<std::vector<Box>>& Boxes, std::string item)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if ((std::string)Boxes[i][j].text.getString() == item)
			{
				Boxes[i][j].shape.setFillColor(sf::Color(250, 250, 250));
				Boxes[i][j].text.setStyle(sf::Text::Regular);
			}
		}
	}
}

void clearBoxColor(std::vector<std::vector<Box>>& Boxes)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Boxes[i][j].shape.setFillColor(sf::Color(250, 250, 250));
		}
	}
}

bool gameOver(std::vector<std::vector<std::string>> checkBoxes, std::vector<std::vector<std::string>> solved)
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (checkBoxes[i][j] != solved[i][j])
				return false;
	return true;
}

bool safeToAssign(std::vector<std::vector<int>> graph, int i, int j, int num)
{
	int a = (i / 3) * 3, b = (j / 3) * 3;
	int Ix, Iy;
	for (int cI = 0; cI < 3; cI++)
	{
		for (int cJ = 0; cJ < 3; cJ++)
		{
			if (graph[a + cI][b + cJ] == num)
				return false;
		}
	}
	for (int k = 0; k < 9; k++)
	{
		if (graph[i][k] == num)
			return false;
	}
	for (int k = 0; k < 9; k++)
	{
		if (graph[k][j] == num)
			return false;
	}
	return true;
}
bool findZero(std::vector<std::vector<int>> graph, int& r, int& c)
{
	for (r = 0; r < 9; r++)
		for (c = 0; c < 9; c++)
			if (graph[r][c] == ZERO)
				return true;
	return false;
}
bool solveSoduko(std::vector<std::vector<int>>& graph)
{
	int row, column;

	if (!findZero(graph, row, column))
		return true;

	for (int num = 1; num <= 9; num++)
	{
		if (safeToAssign(graph, row, column, num)) // main base case
		{
			graph[row][column] = num;
			if (solveSoduko(graph))
			{
				return true;
			}
			graph[row][column] = ZERO;
		}
	}
	return false;
}
void findRandPos(std::vector<std::vector<int>> graph, int& r, int& c)
{
	do
	{
		r = rand() % 9;
		c = rand() % 9;
	} while (graph[r][c] == 0);
}
bool compare(std::vector<std::vector<int>> test1, std::vector<std::vector<int>> test2)
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (test1[i] != test2[i])
				return false;
	return true;
}

void colorBoxesOnSelect(std::vector<std::vector<Box>>& Boxes, int i, int j, bool clear);
bool clickDetect(sf::Vector2f, sf::Vector2f, sf::Vector2f);


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1200, 894), "Sudoku", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	// Canvas 
	sf::RectangleShape rect(sf::Vector2f(WIDTH, HEIGHT));
	rect.setPosition(sf::Vector2f(100.f, 150.f));
	rect.setFillColor(sf::Color(211, 216, 226));
	rect.setOutlineThickness(3.f);
	rect.setOutlineColor(sf::Color(52, 72, 97));

	// middle Bars
	Bar b1(3, 0, 3.f, HEIGHT), b2(6, 0, 3.f, HEIGHT), b3(0, 3, WIDTH, 3.f), b4(0, 6, WIDTH, 3.f);
	std::vector<Bar> Bars;
	Bars.push_back(b1);
	Bars.push_back(b2);
	Bars.push_back(b3);
	Bars.push_back(b4);

	sf::Font font;
	font.loadFromFile("Font/Roboto-Light.ttf");


	//std::vector<std::vector<int>> sudoku
	//{
	//	{5,0,3,1,2,0,0,8,0},
	//	{6,0,1,3,0,9,0,0,0},
	//	{0,8,0,0,5,0,0,0,0},
	//	{0,2,0,5,3,0,6,0,7},
	//	{0,5,0,0,0,0,0,2,8},
	//	{0,0,8,0,6,0,0,0,1},
	//	{2,0,0,0,7,0,0,0,0},
	//	{0,0,0,6,0,5,8,0,0},
	//	{0,0,7,0,0,2,5,1,0},
	//};
	//std::vector<std::vector<std::string>> solved 
	//{
	//	{"5", "4", "3", "1", "2", "6", "7", "8", "9"},
	//	{"6", "7", "1", "3", "8", "9", "2", "4", "5"},
	//	{"9", "8", "2", "4", "5", "7", "1", "3", "6"},
	//	{"1", "2", "4", "5", "3", "8", "6", "9", "7"},
	//	{"3", "5", "6", "7", "9", "1", "4", "2", "8"},
	//	{"7", "9", "8", "2", "6", "4", "3", "5", "1"},
	//	{"2", "1", "5", "8", "7", "3", "9", "6", "4"},
	//	{"4", "3", "9", "6", "1", "5", "8", "7", "2"},
	//	{"8", "6", "7", "9", "4", "2", "5", "1", "3"}
	//};

	// the sudoku generator
	std::vector<std::vector<int>> sudoku(9, std::vector<int>(9, 0));
	std::vector<int> rem;
	int randomInt;
	srand(time(NULL));
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			do
			{
				randomInt = rand() % 9 + 1;
			} while (std::find(rem.begin(), rem.end(), randomInt) != rem.end());
			rem.push_back(randomInt);
			sudoku[i][j] = randomInt;
		}
	}
	std::cout.setf(std::ios::boolalpha);
	std::cout << solveSoduko(sudoku) << std::endl;
	std::vector<std::vector<int>> copySoduko;
	std::vector<std::vector<int>> copyVec(sudoku);
	int r, c, backUp, anBackUp;
	int xT, yT;
	int test;

	for (int i = 0; i < 25; i++)
	{
		copySoduko = sudoku;
		findRandPos(copySoduko, r, c);
		findRandPos(copySoduko, xT, yT);
		copySoduko[r][c] = 0;
		copySoduko[xT][yT] = 0;
		backUp = copySoduko[r][c];
		anBackUp = copySoduko[xT][yT];

		if (solveSoduko(copySoduko))
		{
			if (compare(copyVec, copySoduko))
			{
				sudoku[r][c] = 0;
				sudoku[xT][yT] = 0;
			}
		}
	}

	// the result part
	for (int i = 0; i < 9; i++)
	{
		std::cout << "{";
		for (int j = 0; j < 9; j++)
			std::cout << copySoduko[i][j] << ',';
		std::cout << "},";
		std::cout << std::endl;
	}

	std::cout << "\n\nTheFinalOne: " << std::endl;
	for (int i = 0; i < 9; i++)
	{
		std::cout << "{";
		for (int j = 0; j < 9; j++)
			std::cout << sudoku[i][j] << ',';
		std::cout << "},";
		std::cout << std::endl;
	}
	std::vector<std::vector<std::string>> solved(9, std::vector<std::string>(9, ""));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			solved[i][j] = std::to_string(copySoduko[i][j]);
		}
	}

	std::vector<std::vector<Box>> Boxes(9, std::vector<Box>(9, Box(&font, 64.f, 64.f)));
	std::vector<std::vector<std::string>> boxCheck(9, std::vector<std::string>(9, ""));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Boxes[i][j].shape.setPosition(sf::Vector2f(101.f + 66.f * i, 151.f + 66.f * j));
			Boxes[i][j].text.setPosition(sf::Vector2f(Boxes[i][j].shape.getPosition().x + 22.f, Boxes[i][j].shape.getPosition().y + 8.f));
			if (sudoku[i][j] != 0)
			{
				Boxes[i][j].text.setString(std::to_string(sudoku[i][j]));
				Boxes[i][j].fixed = true;
				boxCheck[i][j] = std::to_string(sudoku[i][j]);
			}
			else
			{
				boxCheck[i][j] = "";
				Boxes[i][j].text.setFillColor(sf::Color(0, 114, 227));
			}

		}
	}

	int _bPosX = -1, _bPosY = -1;
	int _nmPadX = -1, _nmPadY = -1;
	std::string boxContent, prevContent;
	sf::Vector2i cellPos;
	bool selected = false;


	// Numpad Tiles
	std::vector<std::vector<Box>> NumPad(3, std::vector<Box>(3, Box(&font, 80.f, 110.f)));
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			NumPad[i][j].shape.setPosition(sf::Vector2f(830.f + 85.f * i, 280.f + 115.f * j));
			NumPad[i][j].setTextSize(48);
			NumPad[i][j].text.setStyle(sf::Text::Bold);
			NumPad[i][j].text.setPosition(sf::Vector2f(NumPad[i][j].shape.getPosition().x + 25.f, NumPad[i][j].shape.getPosition().y + 22.f));
			NumPad[i][j].text.setString(std::to_string(j * 3 + i + 1));
			NumPad[i][j].text.setFillColor(sf::Color(0, 114, 227));
		}
	}
	// variables related to NumPad
	std::string _pstNP, _prevNP;
	bool valInsertedInCell = false;
	int x = -1, y = -1;

	// the remove button
	Box remove(&font, 100.f, 50.f);
	remove.shape.setPosition(sf::Vector2f(830.f, 220.f));
	remove.text.setPosition(sf::Vector2f(838.f, 230.f));
	remove.text.setCharacterSize(24);
	remove.text.setString("Remove");
	remove.text.setFillColor(sf::Color(0, 114, 227));



	srand(time(NULL));
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				window.close();
			}
		}


		// Updating 
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mPos = (sf::Vector2f)sf::Mouse::getPosition(window); // current mouse position

				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						sf::Vector2f bPos = Boxes[i][j].shape.getPosition();
						if (clickDetect(mPos, bPos, sf::Vector2f(64.f, 64.f)))
						{
							prevContent = boxContent;
							if (Boxes[i][j].text.getString() != "")
								boxContent = Boxes[i][j].text.getString();

							cellPos = sf::Vector2i(i, j);
							selected = true;

							if (_bPosX != -1) colorBoxesOnSelect(Boxes, _bPosX, _bPosY, true);
							colorBoxesOnSelect(Boxes, i, j, false);
							_bPosX = i;
							_bPosY = j;
							break;
						}
					}
				}
				if (selected)
				{
					Boxes[cellPos.x][cellPos.y].shape.setFillColor(sf::Color(187, 222, 251));
				}

				// the present NumPad selected digit
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						sf::Vector2f npPos = NumPad[i][j].shape.getPosition();
						if (clickDetect(mPos, npPos, sf::Vector2f(80.f, 110.f)))
						{
							_prevNP = _pstNP;
							_pstNP = NumPad[i][j].text.getString();
							if (_pstNP != _prevNP)
								std::cout << _pstNP << std::endl;

							if (_nmPadX != -1)
							{
								NumPad[_nmPadX][_nmPadY].shape.setFillColor(sf::Color(250, 250, 250));
							}
							NumPad[i][j].shape.setFillColor(sf::Color(226, 235, 243));

							_nmPadX = i;
							_nmPadY = j;

							if (selected && !Boxes[cellPos.x][cellPos.y].fixed)
							{
								Boxes[cellPos.x][cellPos.y].text.setString(_pstNP);
								valInsertedInCell = true;
							}
							break;
						}
					}
				}
			}
		}


		// checking for the change in Boxes Cell values
		if (valInsertedInCell)
		{
			valInsertedInCell = false;
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (boxCheck[i][j] != Boxes[i][j].text.getString())
					{
						if (x != -1 && x == i && y == j)
						{
							sameCellUpdate(Boxes, boxCheck[i][j]);
						}
						//colorBoxesOnSelect(Boxes, i, j, false);
						boxCheck[i][j] = Boxes[i][j].text.getString();
						colorBoxesOnSelect(Boxes, i, j, false);
						x = i;
						y = j;
					}

				}
			}
		}

		// remove operation
		if (remove.shape.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (Boxes[cellPos.x][cellPos.y].text.getString() != "" && !Boxes[cellPos.x][cellPos.y].fixed)
			{
				sameCellUpdate(Boxes, Boxes[cellPos.x][cellPos.y].text.getString());
				clearBoxColor(Boxes);
				Boxes[cellPos.x][cellPos.y].text.setString(sf::String(""));
				boxCheck[cellPos, x][cellPos.y] = "";
			}
		}

		// Loop for marking the red box for the wrong selection
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if ((std::string)Boxes[i][j].text.getString() != solved[i][j] && (std::string)Boxes[i][j].text.getString() != "")
				{
					Boxes[i][j].wrong = true;
				}
				else
				{
					Boxes[i][j].wrong = false;
				}


				if (Boxes[i][j].wrong)
				{
					Boxes[i][j].shape.setFillColor(sf::Color(247, 207, 214));
				}
			}
		}

		// Game over logic
		if (gameOver(boxCheck, solved))
			window.close();

		/* ===========================DRAW=========================== */
		window.clear(sf::Color(220, 220, 220));
		window.draw(rect);

		for (auto box : Boxes)
		{
			for (auto item : box)
			{
				window.draw(item.shape);
				window.draw(item.text);
			}
		}
		for (auto bar : Bars)
		{
			window.draw(bar.shape);
		}

		for (auto nums : NumPad)
		{
			for (auto item : nums)
			{
				window.draw(item.shape);
				window.draw(item.text);
			}
		}
		window.draw(remove.shape);
		window.draw(remove.text);
		window.display();
	}
}

void colorBoxesOnSelect(std::vector<std::vector<Box>>& Boxes, int i, int j, bool clear)
{
	int a = (i / 3) * 3, b = (j / 3) * 3;
	int Ix, Iy;
	sf::Color c;
	clear ? c = sf::Color(250, 250, 250) : c = sf::Color(226, 235, 243);


	std::string numStr = Boxes[i][j].text.getString();
	if (numStr != "")
	{

		// Highlighting the other than selected number in the BOX
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (Boxes[i][j].text.getString() == numStr && !clear)
				{
					Boxes[i][j].shape.setFillColor(sf::Color(195, 215, 234));
					Boxes[i][j].text.setStyle(sf::Text::Bold);
				}
				else if (Boxes[i][j].text.getString() == numStr && clear)
				{
					Boxes[i][j].shape.setFillColor(sf::Color(250, 250, 250));
					Boxes[i][j].text.setStyle(sf::Text::Regular);
				}
			}
		}
	}

	// For the 3x3 matrix extracted from the supplied ith and jth index
	for (int cI = 0; cI < 3; cI++)
	{
		for (int cJ = 0; cJ < 3; cJ++)
		{
			Ix = a + cI;
			Iy = b + cJ;
			Boxes[Ix][Iy].shape.setFillColor(c);
		}
	}

	// the row/column along the index supplied
	for (int k = 0; k < 9; k++)
	{
		Boxes[i][k].shape.setFillColor(c);
	}

	// the row/column along the index supplied 
	for (int k = 0; k < 9; k++)
	{
		Boxes[k][j].shape.setFillColor(c);
	}
}

bool clickDetect(sf::Vector2f mClick, sf::Vector2f entityClick, sf::Vector2f DMNS)
{
	return (mClick.x >= entityClick.x && mClick.x <= entityClick.x + DMNS.x && mClick.y >= entityClick.y && mClick.y <= entityClick.y + DMNS.y);
}