#include "Sudoku.h"

/*
	Default Constructor for the class BOX
*/
Box::Box()
{
	this->fixed = false;
	this->wrong = false;
}

/*
	Parameterized Constructor for the class BOX
	\param font Pointer to the referenced font to be used in its text
	\param width Width of the shape
	\param height height of the shape
*/
Box::Box(sf::Font* font, float width, float height)
{
	this->text.setFont(*font);
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(sf::Color(250, 250, 250));
	this->text.setCharacterSize(24);
	this->text.setFillColor(sf::Color(52, 72, 97));
	this->fixed = false;
	this->wrong = false;
}

/*
	Member function for setting the size of the text
	\param size Size of the character
*/
void Box::Set_Text_Size(int size)
{
	this->text.setCharacterSize(size);
}

/*
	Default Constructor	
*/
Bar::Bar()
{
}

/*
	Parameterized Constructor
	Its object creates the vertical and horizontal line in the canvas
	\param x_count X-position adjustment offset
	\param y-count Y-position adjustment offset
	\param w Width of the line
	\param h Height of the line
*/
Bar::Bar(int x_count, int y_count, float w, float h)
{
	float x_line_pos =  0.f;
	float y_line_pos = 0.f;

	if (x_count != 0)
	{
		if (x_count == 3)
		{
			x_line_pos = x_count * 55.f - 1.f;
		}
		else if (x_count == 6)
		{
			x_line_pos = x_count * 55.f;
		}
	}
	else
	{
		x_line_pos = float(x_count);
	}

	if (y_count != 0)
	{
		if (y_count == 3)
		{
			y_line_pos = y_count * 55.f - 1.f;
		}
		else if (y_count == 6)
		{
			y_line_pos = y_count * 55.f;
		}
	}
	else
	{
		y_line_pos = float(y_count);
	}
	
	this->line_shape.setSize(sf::Vector2f(w, h));
	this->line_shape.setPosition(sf::Vector2f(30.f + x_line_pos, 145.f + y_line_pos));
	this->line_shape.setFillColor(sf::Color(52, 72, 97));
}

/*
	Class for instanciating SUDOKU APP
	Non-Parameterized Constructor
*/
Sudoku::Sudoku()
{
	this->canvas.setSize({ CANVAS_W, CANVAS_H });
	this->canvas.setPosition({30.f, 145.f});
	this->canvas.setFillColor(sf::Color(211, 216, 226));
	this->canvas.setOutlineThickness(2.f);
	this->canvas.setOutlineColor(sf::Color(52, 72, 97));

	this->Load_Font();
	this->Load_All_Functions();

	this->remove_btn = new Btn("Remove", { 634.f, 245.f }, 16, this->roboto_font);
	this->remove_btn->SetTextColor(sf::Color(142, 50, 179));

	this->remove_btn_func = [&]()
	{
		if (selected_cell_pos.x != -1)
		{
			if (Boxes[selected_cell_pos.x][selected_cell_pos.y].text.getString() != "" && !Boxes[selected_cell_pos.x][selected_cell_pos.y].fixed)
			{
				Boxes[selected_cell_pos.x][selected_cell_pos.y].text.setString(sf::String(""));
				check_box[selected_cell_pos.y][selected_cell_pos.x] = "";
				Color_Boxes_On_Select(selected_cell_pos.x, selected_cell_pos.y, false);
				if (this->assists)
				{
					Check_Wrong_Inputs();
				}
				Boxes[selected_cell_pos.x][selected_cell_pos.y].shape.setFillColor(sf::Color(187, 222, 251));
			}
		}
	};

	if (!this->background_tex.loadFromFile("Texture/sudoku_background.png"))
		throw "Something that doesn't  matter";

	this->background.setTexture(this->background_tex);
	this->background.setPosition({ 0.f, 0.f });

	this->home_back_btn_clicked = false;
	this->home_back_btn = new Btn("Home", { 55.f, 30.f }, 14, this->roboto_font);
	this->home_back_btn->SetFillColor(sf::Color(157, 92, 183));
	this->home_back_btn->SetTextColor(sf::Color::White);
	this->home_back_btn_func = [&]()
	{
		this->home_back_btn_clicked = true;
	};

	this->animation_pattern =
	{
		{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0},
		{8, 1}, {8, 2}, {8, 3}, {8, 4}, {8, 5}, {8, 6}, {8, 7}, {8, 8},
		{7, 8}, {6, 8}, {5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 8},
		{0, 7}, {0, 6}, {0, 5}, {0, 4}, {0, 3}, {0, 2}, {0, 1},
		{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1},
		{7, 2}, {7, 3}, {7, 4}, {7, 5}, {7, 6}, {7, 7},
		{6, 7}, {5, 7}, {4, 7}, {3, 7}, {2, 7}, {1, 7},
		{1, 6}, {1, 5}, {1, 4}, {1, 3}, {1, 2},
		{2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2},
		{6, 3}, {6, 4}, {6, 5}, {6, 6},
		{5, 6}, {4, 6}, {3, 6}, {2, 6},
		{2, 5}, {2, 4}, {2, 3}, 
		{3, 3}, {4, 3}, {5, 3},
		{5, 4}, {5, 5}, 
		{4, 5}, {3, 5}, 
		{3, 4},
		{4, 4}
	};

	this->overlay.setSize({CANVAS_W, CANVAS_H});
	this->overlay.setPosition({30.f, 145.f});
	this->overlay.setFillColor(sf::Color(20, 20, 20, 30));
	
	this->new_game_btn = new Btn("New Game", { 278.f, 393.f }, 16, this->roboto_font);
	this->new_game_btn->SetTextColor(sf::Color(142, 50, 179));
	this->new_game_btn_func = [&]()
	{
		this->Load_All_Functions();
		this->stop_watch.restart();
	};
}

/*
	Identifiers Initializers 
	Made for the purpose of starting new game
*/
void Sudoku::Load_All_Functions()
{
	this->Generate_Sudoku();
	this->Load_UI_Components();
	this->Load_Boxes();

	this->mouse_held = false;
	this->prev_NP_x = -1;
	this->prev_NP_y = -1;
	this->prev_box_x = -1;
	this->prev_box_y = -1;
	this->selected_cell_pos = { -1, -1 };
	this->selected = false;
	this->value_inserted_in_cell = false;
	this->x = -1;
	this->y = -1;

	this->assists = false;
	this->toggler_held = false;
	this->is_game_over = false;
	this->key_held = false;
	this->text_held = false;
	this->check_completion = true;
	this->animation_counter = ANIMATION_TIMER;
	this->animation_x_pos = 0;
	this->animation_y_pos = 0;
	this->pattern_pos = 0;
	this->end_game = false;

	this->timer_text.setFont(this->roboto_font);
	this->timer_text.setCharacterSize(18);
	this->timer_text.setFillColor(sf::Color::Black);
	this->timer_text.setPosition({ 421.f, 105.f });
	this->timer_text.setString("00:00");

	this->time_taken = sf::Text("Time Taken : ", this->roboto_font, 28);
	this->time_taken.setFillColor(sf::Color::White);
	this->seconds = 0;
	this->start_stop_watch = false;
}

/*
	Default Destructor
*/
Sudoku::~Sudoku()
{
}

/*
	Initializes the required UI components to the Window
*/
void Sudoku::Load_UI_Components()
{
	Bars.push_back(Bar(3, 0, 2.f, CANVAS_H));
	Bars.push_back(Bar(6, 0, 2.f, CANVAS_H));
	Bars.push_back(Bar(0, 3, CANVAS_W, 2.f));
	Bars.push_back(Bar(0, 6, CANVAS_W, 2.f));

	this->Load_Toggler();

	this->assist_text = sf::Text("Auto-Check for Mistakes: ", this->roboto_font, 18);
	this->assist_text.setPosition({ 30.f, 105.f });
	this->assist_text.setFillColor(sf::Color::Black);
}

/*
	Loads 9x9 2D boxes to the app
	Also loads Num Pads to the app
*/
void Sudoku::Load_Boxes()
{
	Boxes = std::vector<std::vector<Box>>(9, std::vector<Box>(9, Box(&roboto_font,54.f, 54.f)));
	float x_pos = 0.f;
	float y_pos = 0.f;

	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			if (i < 3)
			{
				x_pos = 30.f + 55.f * i;
			}
			else if (i < 6)
			{
				x_pos = 31.f + 55.f * i;
			}
			else if (i < 9)
			{
				x_pos = 32.f + 55.f * i;
			}

			if (j < 3)
			{
				y_pos = 145.f + 55.f * j;
			}
			else if (j < 6)
			{
				y_pos = 146.f + 55.f * j;
			}
			else if (j < 9)
			{
				y_pos = 147.f + 55.f * j;
			}

			Boxes[i][j].shape.setPosition({ x_pos, y_pos });
			Boxes[i][j].text.setPosition({ Boxes[i][j].shape.getPosition().x + 20.f , Boxes[i][j].shape.getPosition().y + 12.f });

			if (sudoku[j][i] != 0)
			{
				Boxes[i][j].text.setString(std::to_string(sudoku[j][i]));
				Boxes[i][j].fixed = true;
				check_box[j][i] = std::to_string(sudoku[j][i]);
			}
			else
			{
				Boxes[i][j].text.setFillColor(sf::Color(0, 114, 227));
				Boxes[i][j].fixed = false;
				check_box[j][i] = "";
			}
		}
	}

	Num_Pads = std::vector<std::vector<NumPad>>(3, std::vector<NumPad>(3, NumPad(&roboto_font, 30.f)));
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Num_Pads[i][j].shape.setPosition({ 540.f + 67.f * i, 300.f + 67.f * j });
			Num_Pads[i][j].Set_Text_Size(24);
			Num_Pads[i][j].text.setStyle(sf::Text::Bold);
			Num_Pads[i][j].text.setPosition({ Num_Pads[i][j].shape.getPosition().x + 23.f, Num_Pads[i][j].shape.getPosition().y + 14.f });
			Num_Pads[i][j].text.setString(std::to_string(j * 3 + i + 1));
			Num_Pads[i][j].text.setFillColor(sf::Color(157, 92, 183));
			Num_Pads[i][j].shape.setOutlineThickness(2.f);
			Num_Pads[i][j].shape.setOutlineColor(sf::Color(44, 62, 82));
		}
	}
}

/*
	Loads the font from the directory
*/
void Sudoku::Load_Font()
{
	if (!roboto_font.loadFromFile("Fonts/Roboto-Light.ttf"))
		throw "Error in loading 'Roboto-Medium.ttf'";
	if (!kaushan_font.loadFromFile("Fonts/KaushanScript-Regular.ttf"))
		throw "Error in loading the 'KaushanScipt font'";
	if (!roboto_medium.loadFromFile("Fonts/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium.ttf'";
}

/*
	Renders all the components of the sudoko app to the window
	\param &window Reference main window where the components are rendered
*/
void Sudoku::Render_To_Main_Window(sf::RenderWindow& window)
{
	window.draw(this->background);
	window.draw(this->canvas);
	window.draw(this->timer_text);

	for (auto bar : Bars)
	{
		window.draw(bar.line_shape);
	}

	for (auto box : Boxes)
	{
		for (auto item : box)
		{
			window.draw(item.shape);
			window.draw(item.text);
		}
	}

	for (auto nums : Num_Pads)
	{
		for (auto pads : nums)
		{
			window.draw(pads.shape);
			window.draw(pads.text);
		}
	}

	remove_btn->DrawTo(window);
	window.draw(this->main_rect);
	window.draw(this->c_left);
	window.draw(this->c_right);
	window.draw(this->rect_circle);
	window.draw(this->assist_text);
	home_back_btn->DrawTo(window);

	if (end_game)
	{
		window.draw(this->overlay);
		this->new_game_btn->DrawTo(window);
		window.draw(this->time_taken);
	}
}

/*
	Run all the events / updates in the app
	\param &window Main window where the components are rendered
	\param even All the event related to the window
	\param &run_main_window Bool referenced to the the Main Window Running
	\param &run_app Bool referenced to the SUDOKU APP
*/
void Sudoku::Run_Events(sf::RenderWindow& window, sf::Event event, bool& run_main_window, bool& run_app)
{
	if (!end_game && !is_game_over)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
				if (!mouse_held)
				{
					this->Run_Box_Events(window, event);
					this->Run_Num_Pads_Events(window, event);
					this->Run_Other_Events(event);
					if (this->assists)
					{
						this->Check_Wrong_Inputs();
					}
					this->Run_Toggler_Event(event);
					mouse_held = true;
				}
			}
		}
		else
		{
			mouse_held = false;
		}

		remove_btn->BtnEvents(window, event, this->remove_btn_func);
		
		if (event.type == sf::Event::KeyPressed)
		{
			if (!key_held)
			{
				if (event.key.code == sf::Keyboard::Delete)
				{
					this->remove_btn_func();
					key_held = true;
				}

				if (selected)
				{
					if (event.key.code == sf::Keyboard::Right && selected_cell_pos.x < 8)
					{
						selected_cell_pos.x += 1;
					}

					if (event.key.code == sf::Keyboard::Up && selected_cell_pos.y > 0)
					{
						selected_cell_pos.y -= 1;
					}

					if (event.key.code == sf::Keyboard::Left && selected_cell_pos.x > 0)
					{
						selected_cell_pos.x -= 1;
					}

					if (event.key.code == sf::Keyboard::Down && selected_cell_pos.y < 8)
					{
						selected_cell_pos.y += 1;
					}

					key_held = true;
					
					if (prev_box_x != -1)
					{
						Color_Boxes_On_Select(prev_box_x, prev_box_y, true);
					}

					selected_box_string = Boxes[selected_cell_pos.x][selected_cell_pos.y].text.getString();
					Color_Boxes_On_Select(selected_cell_pos.x, selected_cell_pos.y, false);
					prev_box_x = selected_cell_pos.x;
					prev_box_y = selected_cell_pos.y;
					Boxes[selected_cell_pos.x][selected_cell_pos.y].shape.setFillColor(sf::Color(187, 222, 251));
					if (this->assists)
					{
						this->Check_Wrong_Inputs();
					}
				}
			}
		}
		else
		{
			key_held = false;
		}

		if (event.type == sf::Event::TextEntered && selected)
		{
			if (!text_held)
			{
				if (event.text.unicode < 128)
				{
					if (event.text.unicode > 48 && event.text.unicode < 58)
					{
						selected_num_pad = static_cast<char>(event.text.unicode);
						if (selected_num_pad != Boxes[selected_cell_pos.x][selected_cell_pos.y].text.getString())
						{
							if (selected && !Boxes[selected_cell_pos.x][selected_cell_pos.y].fixed)
							{
								if (static_cast<std::string>(Boxes[selected_cell_pos.x][selected_cell_pos.y].text.getString()) != "")
								{
									Color_Boxes_On_Select(selected_cell_pos.x, selected_cell_pos.y, true);
								}

								Boxes[selected_cell_pos.x][selected_cell_pos.y].text.setString(selected_num_pad);
								value_inserted_in_cell = true;
								this->Run_Other_Events(event);

								if (this->assists)
								{
									this->Check_Wrong_Inputs();
								}

								int x = 0;
								int y = 0;
								int temp = 0;
								temp = event.text.unicode - 49;
								x = temp / 3;
								y = temp % 3;

								if (prev_NP_x != -1)
								{
									Num_Pads[prev_NP_x][prev_NP_y].shape.setFillColor(sf::Color(250, 250, 250));
								}

								prev_NP_x = y;
								prev_NP_y = x;
								Num_Pads[y][x].shape.setFillColor(sf::Color(187, 222, 251));
							}
						}
					}
				}
				text_held = true;
			}
		}
		else
		{
			text_held = false;
		}

		if (check_completion)
		{
			Check_For_Completion();
		}

		if (this->selected && !this->start_stop_watch)
		{
			this->start_stop_watch = true;
			this->stop_watch.restart();
		}

		if (this->stop_watch.getElapsedTime().asSeconds() >= 1 && this->start_stop_watch)
		{
			this->seconds++;
			this->timer_string = std::to_string(seconds / 60).size() == 2 ? std::to_string(seconds / 60) : "0" + std::to_string(seconds / 60);
			this->timer_string += ":";
			this->timer_string += std::to_string(seconds % 60).size() == 2 ? std::to_string(seconds % 60) : "0" + std::to_string(seconds % 60);
			this->timer_text.setString(this->timer_string);
			this->stop_watch.restart();
		}
	}

	home_back_btn->BtnEvents(window, event, this->home_back_btn_func);

	if (home_back_btn_clicked)
	{
		home_back_btn_clicked = false;
		run_main_window = true;
		run_app = false;
	}

	if (is_game_over)
	{
		if (animation_counter < ANIMATION_TIMER)
		{
			animation_counter++;
		}
		else if (animation_counter >= ANIMATION_TIMER)
		{
			animation_x_pos = animation_pattern[pattern_pos][0];
			animation_y_pos = animation_pattern[pattern_pos][1];
			pattern_pos++;

			Boxes[animation_x_pos][animation_y_pos].shape.setFillColor(sf::Color(197, 163, 211));
			animation_counter = 0;
			if (pattern_pos >= animation_pattern.size())
			{
				is_game_over = false;
				end_game = true;
			}
		}
	}

	if (end_game)
	{
		this->new_game_btn->BtnEvents(window, event, this->new_game_btn_func);
		this->time_taken.setString("Time Taken: " + this->timer_string);
		this->time_taken.setPosition({ 30.f + 248.f - this->time_taken.getGlobalBounds().width / 2.f, 300.f });
	}
}

/*
	Run the events of the NUMBER PADS
	\param &window Main window for the components to be rendered
	\param event Events related to the main window
*/
void Sudoku::Run_Num_Pads_Events(sf::RenderWindow& window, sf::Event event)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			selected_num_pad_pos = Num_Pads[i][j].shape.getPosition();
			if (Detect_Click(mouse_pos, selected_num_pad_pos, { 50.f, 70.f }))
			{
				selected_num_pad = Num_Pads[i][j].text.getString();
				if (selected)
				{
					if (selected_num_pad != Boxes[selected_cell_pos.x][selected_cell_pos.y].text.getString())
					{
						if (selected && !Boxes[selected_cell_pos.x][selected_cell_pos.y].fixed)
						{
							if (static_cast<std::string>(Boxes[selected_cell_pos.x][selected_cell_pos.y].text.getString()) != "")
							{
								Color_Boxes_On_Select(selected_cell_pos.x, selected_cell_pos.y, true);
							}
							Boxes[selected_cell_pos.x][selected_cell_pos.y].text.setString(selected_num_pad);
							if (prev_NP_x != -1)
							{
								Num_Pads[prev_NP_x][prev_NP_y].shape.setFillColor(sf::Color(250, 250, 250));
							}
							prev_NP_x = i;
							prev_NP_y = j;
							Num_Pads[i][j].shape.setFillColor(sf::Color(187, 222, 251));
							value_inserted_in_cell = true;
						}
						break;
					}
				}
			}
		}
	}
}

/*
	Runs the events related with the BOXES / CANVAS
	\param &window Main window for the components to be rendered
	\prram event Events related to the main window
*/
void Sudoku::Run_Box_Events(sf::RenderWindow& window, sf::Event event)
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			selected_bos_pos = Boxes[i][j].shape.getPosition();
			if (Detect_Click(mouse_pos, selected_bos_pos, { 54.f, 54.f }))
			{
				selected_box_string = Boxes[i][j].text.getString();

				if (prev_box_x != -1)
				{
					Color_Boxes_On_Select(prev_box_x, prev_box_y, true);
				}
				
				Color_Boxes_On_Select(i, j, false);
				selected_cell_pos = { i, j };
				prev_box_x = i;
				prev_box_y = j;
				Boxes[i][j].shape.setFillColor(sf::Color(187, 222, 251));
				selected = true;
				break;
			}
		}
	}
}

/*
	Run other related Events / Updaters
	\param event Events related to the main window
*/
void Sudoku::Run_Other_Events(sf::Event event)
{
	if (value_inserted_in_cell)
	{
		value_inserted_in_cell = false;
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				if (check_box[i][j] != Boxes[j][i].text.getString())
				{
					if (x != -1 && x == i && y == j)
					{
						Same_Cell_Update(check_box[i][j]);
					}
					check_box[i][j] = Boxes[j][i].text.getString();
					Color_Boxes_On_Select(j, i, false);
					Boxes[selected_cell_pos.x][selected_cell_pos.y].shape.setFillColor(sf::Color(187, 222, 251));
					x = i;
					y = j;
				}
			}
		}
	}
}

/*
	Updates the cell previously highlighted for a particular cell value to the regular style
	\param item The cell data passed
*/
void Sudoku::Same_Cell_Update(std::string item)
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			if (static_cast<std::string>(Boxes[i][j].text.getString()) == item)
			{
				Boxes[i][j].shape.setFillColor(sf::Color(250, 250, 250));
				Boxes[i][j].text.setStyle(sf::Text::Regular);
			}
		}
	}
}

/*
	Loads the assist toggler
*/
void Sudoku::Load_Toggler()
{
	this->main_rect.setSize({ TOGGLER_WIDTH, 20.f });
	this->main_rect.setOrigin({ TOGGLER_WIDTH / 2.f, this->main_rect.getSize().y / 2.f });
	this->main_rect.setPosition({ 260.f, 118.f });
	this->main_rect.setFillColor(sf::Color(250, 250, 250));

	this->rect_circle.setRadius(TOGGLER_C_R);
	this->rect_circle.setOrigin({ TOGGLER_C_R, TOGGLER_C_R });

	this->c_left .setRadius(10.f);
	this->c_right.setRadius(10.f);
	this->c_left.setOrigin({ 10.f, 10.f });
	this->c_right.setOrigin({ 10.f, 10.f });
	this->c_left.setPosition({ this->main_rect.getPosition().x - TOGGLER_WIDTH / 2.f, this->main_rect.getPosition().y });
	this->c_right.setPosition({ this->main_rect.getPosition().x + TOGGLER_WIDTH / 2.f, this->main_rect.getPosition().y });

	this->c_left.setFillColor(sf::Color(250, 250, 250));
	this->c_right.setFillColor(sf::Color(250, 250, 250));
	
	this->rect_circle.setPosition({ this->main_rect.getPosition().x - TOGGLER_WIDTH / 2.f, this->main_rect.getPosition().y });
	this->rect_circle.setFillColor(sf::Color(157, 92, 183));
}

/*
	Clears all the boxes colors
*/
void Sudoku::Clear_Box_Color()
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			Boxes[i][j].shape.setFillColor(sf::Color(250, 250, 250));
		}
	}
}

/*
	Check for the possible wrong input comparing with the solved container
	Highlights the wrong cell with the definitive color
*/
void Sudoku::Check_Wrong_Inputs()
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			if(static_cast<std::string>(Boxes[j][i].text.getString()) != solved[i][j]
				&& static_cast<std::string>(Boxes[j][i].text.getString()) != "")
			{
				Boxes[j][i].wrong = true;
			}
			else
			{
				Boxes[j][i].wrong = false;
			}

			if (Boxes[j][i].wrong)
			{
				Boxes[j][i].shape.setFillColor(sf::Color(247, 207, 214));
			}
		}
	}
}

/*
	Runs the events related to the assist toggler
	\param event Events related to the main window
*/
void Sudoku::Run_Toggler_Event(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (this->rect_circle.getGlobalBounds().contains(this->mouse_pos))
			{
				if (!this->assists)
				{
					this->rect_circle.setPosition({ this->main_rect.getPosition().x + TOGGLER_WIDTH / 2.f, this->main_rect.getPosition().y });
					this->assists = true;
					this->Check_Wrong_Inputs();
				}
				else
				{
					this->rect_circle.setPosition({ this->main_rect.getPosition().x - TOGGLER_WIDTH / 2.f, this->main_rect.getPosition().y });
					this->assists = false;
					
					if (selected_cell_pos.x != -1)
					{
						this->Undo_Wrong_Highlight();
						this->Color_Boxes_On_Select(selected_cell_pos.x, selected_cell_pos.y, false);
						Boxes[selected_cell_pos.x][selected_cell_pos.y].shape.setFillColor(sf::Color(187, 222, 251));
					}
				}
			}
		}
	}
}

/*
	Undo all the cell previously highlighted for the wrong input
*/
void Sudoku::Undo_Wrong_Highlight()
{
	for (int i = 0; i < 9; ++i)
	{
		for(int j = 0; j < 9; ++j)
		{
			if (Boxes[j][i].wrong)
			{
				Boxes[j][i].shape.setFillColor(sf::Color(250,250,250));
			}
		}
	}
}

/*
	Detects the click of the mouse within the entity passed
	\param m_click A float vector for the position of the mouse
	\param entity_click A 2D float vector for the entity clicked position
	\param DMNS Dimension of the entity
*/
bool Sudoku::Detect_Click(sf::Vector2f m_click, sf::Vector2f entity_click, sf::Vector2f DMNS)
{
	return (m_click.x >= entity_click.x && m_click.x <= entity_click.x + DMNS.x &&
		m_click.y >= entity_click.y && m_click.y <= entity_click.y + DMNS.y);
}

/*
	Colors the row, column and the related nearby 3x3 Matrix for the selected cell
	\param i Rowth of the cell selected
	\param j Columnth of the cell selected
	\param clear Boolean that decides if the action is to clear the previous select or highlight the new select
*/
void Sudoku::Color_Boxes_On_Select(int i, int j, bool clear)
{
	int a = (i / 3) * 3, b = (j / 3) * 3;
	int Ix, Iy;
	sf::Color c;
	clear ? c = sf::Color(250, 250, 250) : c = sf::Color(226, 235, 243);
	std::string numStr = Boxes[i][j].text.getString();
	if (numStr != "")
	{
		// Highlighting other than selected number in the BOX
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
	else
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				
				Boxes[i][j].shape.setFillColor(sf::Color(250, 250, 250));
				Boxes[i][j].text.setStyle(sf::Text::Regular);
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

/*
	Main Generating algorithm for the SUDOKU
	ALGORITHM:
	- First randomly select any super 3x3 matrix from the 9x9 matrix
	- Randomly fill the selected super matrix from 1 - 9
	- Then feed this 9x9 grid to the sudoku solving algorithm
*/
void Sudoku::Generate_Sudoku()
{
	sudoku = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
	rem.clear();

	// Randomly filling the selected supermatrix from 1-9
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			do
			{
				random_int = rand() % 9 + 1;
			} while (std::find(rem.begin(), rem.end(), random_int) != rem.end());
			rem.push_back(random_int);
			sudoku[i][j] = random_int;
		}
	}

	// Solving the partially filled 9x9 grid
	Solve_Sudoku(sudoku);
	copy_vec = sudoku;

	int r, c, back_up, another_backup;
	int xT, yT;
	
	/*
		This specific loop here is a compromised algorithm.
		This loop randomly selects any two cell values and 
		checks for the validity of the solved sudoku grid on 
		the removal of those seleccted values for each loop.
		The idea is that the sudoku grid at any point shouldn't 
		have more than one solution i.e. it's solution should be unique.
	*/
	for (int i = 0; i < 25; i++)
	{
		copy_sudoku = sudoku;
		Find_Random_Pos(copy_sudoku, r, c);
		Find_Random_Pos(copy_sudoku, xT, yT);
		copy_sudoku[r][c] = 0;
		copy_sudoku[xT][yT] = 0;
		back_up = copy_sudoku[r][c];
		another_backup = copy_sudoku[xT][yT];
		
		if (Solve_Sudoku(copy_sudoku))
		{
			if (Compare(copy_vec, copy_sudoku))
			{
				sudoku[r][c] = 0;
				sudoku[xT][yT] = 0;
			}
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] != 0)
			{
				if (sudoku[i][j] != copy_sudoku[i][j])
				{
					std::cout << "BUG FOUND" << std::endl;
					sudoku[i][j] = 0;
				}
			}
		}
	}

	solved = std::vector<std::vector<std::string>>(9, std::vector<std::string>(9, ""));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			solved[i][j] = std::to_string(copy_sudoku[i][j]);
		}
	}

	this->check_box = std::vector<std::vector<std::string>>(9, std::vector<std::string>(9, ""));
}

/*
	Recursive funtion that takes an unsolved 9x9 GRID and 
	solves recursively.
	ALGORITHM (BACKTRACKING)
	- First find any position void of value
	- Assign values looping from 1 - 9
	- Recursively fill the 9x9 GRID checking for the completion
	- If at any instant the algorithm fails to assign the value the 
	  recursion tree break and back tracks for other value from the loop
	  hence the name 'BACKTRACKING'
*/
bool Sudoku::Solve_Sudoku(std::vector<std::vector<int>>& graph)
{
	int row, column;
	if (!Find_Zero(graph, row, column))
	{
		return true;
	}

	for (int num = 1; num <= 9; num++)
	{
		if (Safe_To_Assign(graph, row, column, num))
		{
			graph[row][column] = num;
			if (Solve_Sudoku(graph))
			{
				return true;
			}
			graph[row][column] = 0;
		}
	}
	return false;
}

/*
	Find any zero value cell in the GRID
	\param graph 9x9 GRID
	\param &r Row position referenced
	\param &c Column position referenced
*/
bool Sudoku::Find_Zero(std::vector<std::vector<int>> graph, int& r, int& c)
{
	for (r = 0; r < 9; r++)
		for (c = 0; c < 9; c++)
			if (graph[r][c] == 0)
				return true;
	return false;
}

/*
	Provides boolean whether the provided cell in the GRID is safe to assign or not
	\param graph 9x9 GRID
	\param i X-Position in the GRID
	\param j Y-Position in the GRID
	\param num Number to be assigned
*/
bool Sudoku::Safe_To_Assign(std::vector<std::vector<int>> graph, int i, int j, int num)
{
	int a = (i / 3) * 3, b = (j / 3) * 3;
	int Ix = 0;
	int Iy = 0;
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

/*
	Compares two GRIDS - Solved and the Preparing Sudoku GRID for the uniqueness
*/
bool Sudoku::Compare(std::vector<std::vector<int>> test1, std::vector<std::vector<int>> test2)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (test1[i][j] != test2[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

/*
	Find random cell with non-zero value in the 9x9 GRID
*/
void Sudoku::Find_Random_Pos(std::vector<std::vector<int>> graph, int& r, int& c)
{
	do
	{
		r = rand() % 9;
		c = rand() % 9;
	} while (graph[r][c] == 0);
}

/*
	Checks for the completion of the sudoku
*/
void Sudoku::Check_For_Completion()
{
	bool flag = false;
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			if (this->check_box[i][j] != this->solved[i][j])
			{
				flag = true;
				break;
			}
		}
	}

	if (!flag)
	{
		this->is_game_over = true;
		this->check_completion = false;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				Boxes[i][j].shape.setFillColor(sf::Color(250,250,250));
				Boxes[i][j].text.setStyle(sf::Text::Regular);
			}
		}
	}
}

/*
	Default Constructor
*/
NumPad::NumPad()
{
}

/*
	Parameterized Constructor
	\param font Pointer to the referenced font
	\prarm radius Radius of the shape for the Number Pad
*/
NumPad::NumPad(sf::Font* font, float radius)
{
	this->text.setFont(*font);
	this->shape.setRadius(radius);
	this->shape.setFillColor(sf::Color(250, 250, 250));
	this->text.setCharacterSize(24);
	this->text.setFillColor(sf::Color(52, 72, 97));
}

/*
	Member Function
	\param size Character size
*/
void NumPad::Set_Text_Size(int size)
{
	this->text.setCharacterSize(size);
}