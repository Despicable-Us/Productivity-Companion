#include "timeSetter.h"


dial::timeSetter::timeSetter(sf::RenderWindow& window): TOGGLE::ToggleMusic(window) // ----------------------------------------------------
{
    if(!this->timeFont.loadFromFile("Fonts/digital-7.ttf")) {
        throw "couldn't open the font file";
    }
    this->initialSetup(window, 0);
}

void dial::timeSetter::initialSetup(sf::RenderWindow& window,int a)
{
 //setting the music file
    if (!this->timeUpSound.openFromFile("Sounds/timeUP.ogg")) {
        throw "Timeup sound failed to load";
    }
    if (!this->pauseSound.openFromFile("Sounds/paused.ogg")) {
        throw "Paused sound failed to load";
    }
    this->timeUpSound.setVolume(50);
    this->pauseSound.setVolume(50);

    if (a == 1) { this->timeUpSound.play(); this->updatePoints(this->stopTime); }
    if (a == 2) { this->pauseSound.play(); this->updatePoints(-10.0f); }
    
    sf::Vector2f position = sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.50f); //------------>change Position here

    this->mainCircle.setRadius(150.f);
    this->mainCircle.setPosition(position);
    this->mainCircle.setFillColor(sf::Color(MAIN_CIRCLE_COLOR));
    this->mainCircle.setOrigin(150, 150);

    this->fillers.setRadius(8.f);
    this->fillers.setOrigin(8.f, 8.f);
    this->fillers.setFillColor(sf::Color(FILLER_COLOR));
    
    this->playButton.setRadius(this->mainCircle.getRadius() / 1.8f);
    float playBtnRad = this->playButton.getRadius();
    this->playButton.setPointCount(3);
    this->playButton.setPosition(this->mainCircle.getPosition());
    this->playButton.setOrigin(playBtnRad,playBtnRad-10);
    this->playButton.setFillColor(sf::Color(PLAY_AND_PAUSE_COLOR));
    this->playButton.setRotation(90.f);
    this->playButton.rotate(0.f);

    this->stopButton.setSize(sf::Vector2f(playBtnRad * 1.4, playBtnRad * 1.4));
    this->stopButton.setOrigin(playBtnRad * 1.4 / 2.0f, playBtnRad * 1.4 / 2.f);
    this->stopButton.setFillColor(sf::Color(PLAY_AND_PAUSE_COLOR));
    this->stopButton.setPosition(this->mainCircle.getPosition());

    this->knobCircle.setRadius(15.f);
    this->knobCircle.setOrigin(15.f, 15.f);
    this->knobCircle.setFillColor(sf::Color(KNOB_COLOR));
    this->knobCircle.setPosition(this->stop_pos);

    this->timeText.setFont(this->timeFont);
    this->timeText.setPosition(this->mainCircle.getPosition().x,
                               this->mainCircle.getPosition().y + this->mainCircle.getRadius()*1.2f);
    this->timeText.setCharacterSize(70);
    this->timeText.setOrigin(90, 0);
    this->timeText.setFillColor(sf::Color(TIMER_TEXT_COLOR));


    if (a == 0) {
        this->all_pos = this->findAllPos();
        this->eachMinPos = this->findEachMinpos();
        this->fiveMult_pos1 = this->find5MultPos();
    }
    this->stopTime = 25.0f;
    this->cursor_size = 0;
    this->stop_pos = this->posForTime(this->stopTime);


    this->stopSignDisp = 0;
    this->tickingFlag = 0;
    this->knobPressing = 0;
    this->stopPressed = 0;

    this->initiatePoints();     //Points class
    

}


//calculations
std::vector<sf::Vector2f> dial::timeSetter::findAllPos()
{
    float a = mainCircle.getPosition().x;
    float b = mainCircle.getPosition().y;
    float r = mainCircle.getRadius();
    std::vector<sf::Vector2f> all_pos;
    for (float y = b - r; y < b + r; y += 0.1f) {
        float x = sqrt((pow(r, 2) - (pow((y - b), 2)))) + a;
        all_pos.push_back(sf::Vector2f(x, y));
    }
    for (float y = b + r; y >= b - r; y -= 0.1f) {
        float x = sqrt((pow(r, 2) - (pow((y - b), 2)))) + a;
        all_pos.push_back(sf::Vector2f(-x + float(2 * a), y));
    }
    return all_pos;
}

std::vector<sf::Vector3f> dial::timeSetter::find5MultPos()
{
    float a = this->mainCircle.getPosition().x;
    float b = this->mainCircle.getPosition().y;
    float r = this->mainCircle.getRadius();

    std::vector<sf::Vector3f> five_pos1;
    for (float y = b - r; y < b + r; y += 0.1f) {
        float x = sqrt((pow(r, 2) - (pow((y - b), 2)))) + a;
        float time = timeInMinutes(sf::Vector2f(x, y));
        if (int(time) % 5 == 0) {
            five_pos1.push_back(sf::Vector3f(time, x, y));
            //if same time as previous appends then popping it
            if (five_pos1.size() > 1) {
                if (five_pos1[five_pos1.size() - 2].x == time) {
                    five_pos1.pop_back();
                }
            }
        }
    }
    for (float y = b + r; y >= b - r; y -= 0.1f) {
        float x = sqrt((pow(r, 2) - (pow((y - b), 2)))) + a;
        float time = timeInMinutes(sf::Vector2f(-x + float(2 * a), y));
        if (int(time) % 5 == 0) {
            five_pos1.push_back(sf::Vector3f(time, -x + float(2 * a), y));
            //if same time as previous appends then popping it
            if (five_pos1.size() > 1) {
                if (five_pos1[five_pos1.size() - 2].x == time) {
                    five_pos1.pop_back();
                }
            }
        }
    }

    return five_pos1;
}

std::vector<sf::Vector3f> dial::timeSetter::findEachMinpos()
{
    float a = this->mainCircle.getPosition().x;
    float b = this->mainCircle.getPosition().y;
    float r = this->mainCircle.getRadius();

    std::vector<sf::Vector3f> five_pos1;
    for (float y = b - r; y < b + r; y += 0.1f) {
        float x = pow(((pow(r, 2) - (pow((y - b), 2)))), 0.5) + a;
        float time = timeInMinutes(sf::Vector2f(x, y));
        
        five_pos1.push_back(sf::Vector3f(time, x, y));
        //if same time as previous appends then popping it
        if (five_pos1.size() > 1) {
            if (five_pos1[five_pos1.size() - 2].x == time) {
                five_pos1.pop_back();
            }
        }
        
    }
    for (float y = b + r; y >= b - r; y -= 0.1f) {
        float x = pow(((pow(r, 2) - (pow((y - b), 2)))), 0.5) + a;
        float time = timeInMinutes(sf::Vector2f(-x + float(2 * a), y));
        
        five_pos1.push_back(sf::Vector3f(time, -x + float(2 * a), y));
        //if same time as previous appends then popping it
        if (five_pos1.size() > 1) {
            if (five_pos1[five_pos1.size() - 2].x == time) {
                five_pos1.pop_back();
            }
        }
        
    }

    return five_pos1;
    
}


//time setters
float dial::timeSetter::timeInMinutes(sf::Vector2f pos)
{
    float rad = this->mainCircle.getRadius();
    float x1 = this->mainCircle.getPosition().x;
    float y1 = this->mainCircle.getPosition().y;
    float x2 = this->mainCircle.getPosition().x;
    float y2 = this->mainCircle.getPosition().y - this->mainCircle.getRadius();
    float x3 = pos.x;
    float y3 = pos.y;

    float area = (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2;
    float angle = asin(area * 2 / (rad * rad)) * (180 / 3.14);

    if (x3 > x1 && y3 > y1) {
        angle = 90 + (90 - angle);
    }
    if (x3 <= x1 && y3 > y1) {
        angle = 180 - angle;
    }
    if (x3 < x1 && y3 <= y1) {
        angle = 360 + angle;
    }
    float time = ceil(angle / 3);
    return time;
}

sf::Vector2f dial::timeSetter::posForTime(float time)
{
    int index = time / 5;
    sf::Vector2f pos = sf::Vector2f(this->fiveMult_pos1[index].y, this->fiveMult_pos1[index].z);
    return pos;
}

sf::String dial::timeSetter::timeOutString(float secs)
{
    sf::String returnStr;
    std::string minStr = std::to_string(int(secs) / 60);
    std::string secStr = std::to_string(int(secs) % 60);

    if (minStr.length() == 1) {
        minStr = "0" + minStr;
    }
    if (secStr.length() == 1) {
        secStr = "0" + secStr;
    }
    returnStr = minStr + " : " + secStr;
    return returnStr;
}

void dial::timeSetter::restartClock()
{
    this->clk.restart();
}

void dial::timeSetter::updateTimeText()
{
    float temp = (this->stopTime * 60) - this->clk.getElapsedTime().asSeconds();
    this->timeText.setString(this->timeOutString(temp));
}


//dialsetters
void dial::timeSetter::updateFillers(sf::Vector2f pos)
{
    this->cursorCurrentPos = pos;
    this->pointKnob();
    this->getCursorSize();
}

void dial::timeSetter::pointKnob()
{
    float r = this->mainCircle.getRadius();
    //centre
    float a = this->mainCircle.getPosition().x;
    float b = this->mainCircle.getPosition().y;
    //mouse position
    float a1 = this->cursorCurrentPos.x;
    float b1 = this->cursorCurrentPos.y;
    //coordinates of two possible points when a line and circle intersects
    float x1, y1, x2, y2;
    //in this condition slope becomes indefinite so adding 0.001 to resolve
    if (a == a1) {
        a1 += 0.001f;
    }
    float m = (b1 - b) / (a1 - a);
    float d = b - m * a;
    float del = (((r * r) * (1 + (m * m))) - ((b - (m * a) - d) * (b - (m * a) - d)));
    x1 = ((a + (b * m) - d * m + float(pow(del, 0.5))) / (1 + m * m));
    x2 = ((a + (b * m) - (d * m) - float(pow(del, 0.5))) / (1 + (m * m)));
    y1 = ((d + (a * m) + (b * m * m) + m * float(pow(del, 0.5))) / (1 + (m * m)));
    y2 = ((d + (a * m) + (b * m * m) - (m * float(pow(del, 0.5)))) / (1 + (m * m)));

    if (a1 > a) {
        this->knobCircle.setPosition(sf::Vector2f(x1, y1));
        //not letting user to set time below 25 mins
        if (this->timeInMinutes(sf::Vector2f(x1, y1)) < 25.0f) {
            sf::Vector2f pos = sf::Vector2f(fiveMult_pos1[5].y, fiveMult_pos1[5].z);
            this->knobCircle.setPosition(pos);
        }
        //not letting user to set time from 120 mins to 25 mins directly
        if (this->stopTime == 120.0f) {
            sf::Vector2f pos = sf::Vector2f(fiveMult_pos1[24].y, fiveMult_pos1[24].z);
            this->knobCircle.setPosition(pos);
        }
    }
    else {
        this->knobCircle.setPosition(sf::Vector2f(x2, y2));
    }

    //updating the last time in minutes DIVISIBLE BY FIVE
    int time = int(this->timeInMinutes(this->knobCircle.getPosition()));
    this->stopTime = time - float(time % 5);
    if (this->stopTime < 25.0f) {   //not letting user set time < 25 mins
        this->stopTime = 25.0f;
    }
    this->stop_pos = this->posForTime(this->stopTime);
}

void dial::timeSetter::getCursorSize()
{
    //center
    float a = this->mainCircle.getPosition().x;
    float b = this->mainCircle.getPosition().y;
    //radius
    float r = this->mainCircle.getRadius();
    if (this->knobCircle.getPosition().x > a) {
        for (float y = b - r; y <= this->knobCircle.getPosition().y; y += 0.1f) {
            this->cursor_size += 1;
        }
    }
    if (this->knobCircle.getPosition().x < a) {
        for (float y = b - r; y <= b + r; y += 0.1f) {
            this->cursor_size += 1;
        }
        for (float y = b + r; y >= this->knobCircle.getPosition().y; y -= 0.1f) {
            this->cursor_size += 1;
        }
    }

}


//hover
int dial::timeSetter::checkInKnob(sf::Vector2f pos)
{
    if (this->knobCircle.getGlobalBounds().contains(pos)) {
        return 1;
    }
    return 0;
}

int dial::timeSetter::checkInPlay(sf::Vector2f pos)
{
    if (this->playButton.getGlobalBounds().contains(pos)) {
        return 1;
    }
    return 0;
}

int dial::timeSetter::checkInStop(sf::Vector2f pos)
{
    if (this->stopButton.getGlobalBounds().contains(pos)) {
        return 1;
    }
    return 0;
}

void dial::timeSetter::increseScale(int a)
{
    switch (a){
    case 1:
        this->knobCircle.setScale(sf::Vector2f(1.08f, 1.08f));
        break;
    case 2:
        this->playButton.setScale(sf::Vector2f(1.08f, 1.08f));
        break;
    case 3:
        this->stopButton.setScale(sf::Vector2f(1.08f, 1.08f));
        break;
    }
}

void dial::timeSetter::resetScale()
{
    this->knobCircle.setScale(sf::Vector2f(1.0f, 1.0f));
    this->playButton.setScale(sf::Vector2f(1.0f, 1.0f));
    this->stopButton.setScale(sf::Vector2f(1.0f, 1.0f));

}



//display 

void dial::timeSetter::printPressing(sf::RenderWindow& window)
{
    this->displayPoints(window);
    window.draw(this->mainCircle);
    window.draw(this->playButton);

    //drawing fillers from all_pos
    size_t i = 0;
    for (i; i < this->cursor_size; i++) {
        fillers.setPosition(all_pos[i]);
        window.draw(fillers);
    }

    //drawing circle at the top of main circle
    this->knobCircle.setPosition(sf::Vector2f(this->mainCircle.getPosition().x
        , this->mainCircle.getPosition().y - this->mainCircle.getRadius()));
    window.draw(knobCircle);

    //drawing knobCicle at the tip of fillers
    this->knobCircle.setPosition(all_pos[0]);
    if (i > 0) {
        this->knobCircle.setPosition(all_pos[i - 1]);
    }
    window.draw(this->knobCircle);

    //updating timeText
    this->timeText.setString(this->timeOutString(stopTime * 60));
    window.draw(this->timeText);
    
    //fillers begin to fill from start again so...
    this->cursor_size = 0;
}

void dial::timeSetter::printReleased(sf::RenderWindow& window)
{
    this->displayPoints(window);
    window.draw(this->mainCircle);
    window.draw(this->playButton);

    this->stop_pos = this->posForTime(this->stopTime); //stopTime is updated by pointKnob

    //draws fillers top stop_pos
    for (auto it = all_pos.begin(); it != all_pos.end(); ++it) {
        fillers.setPosition(*it);
        window.draw(fillers);
        if (stop_pos == *it) {
            break;
        }
    }
    //drawing circle at the top of main circle
    this->knobCircle.setPosition(sf::Vector2f(this->mainCircle.getPosition().x
        , this->mainCircle.getPosition().y - this->mainCircle.getRadius()));
    window.draw(knobCircle);

    //drawing cicle at the tip
    this->knobCircle.setPosition(stop_pos);
    window.draw(this->knobCircle);

    this->timeText.setString(this->timeOutString(stopTime * 60));
    window.draw(this->timeText);

}

void dial::timeSetter::printTicking(sf::RenderWindow& window, int& tickingFlag, int& stopPressed)
{

    this->displayPoints(window);

    //if stop is not pressed
    if(stopPressed != 2) {
        this->stopSignDisp = 1;
        window.draw(this->mainCircle);
        window.draw(this->stopButton);

        float secRemaining = (this->stopTime * 60) - this->clk.getElapsedTime().asSeconds();
        float min = ceil(int(secRemaining) / 60.0f);

        //updating Time Text
        this->updateTimeText();
        window.draw(this->timeText);

        //getting stopPos for fillers from eachMinPos
        sf::Vector2f stopPos = sf::Vector2f(this->eachMinPos[min].y, this->eachMinPos[min].z);
        //updating fillers
        if (min) { //to not print the filler when time becomes zero
            for (auto it = all_pos.begin(); it != all_pos.end(); ++it) {
                fillers.setPosition(*it);
                window.draw(fillers);
                if (stopPos == *it) {
                    break;
                }
            }
        }

        //timer complete
        if (std::string(this->timeText.getString()) == "00 : 00") {
            tickingFlag = 0;
            this->initialSetup(window,1);
        }
    }
    else{                   //timer stopped
        tickingFlag = 0;
        stopPressed = 0;
        this->stopTime = 25;
        this->initialSetup(window, 2);
    }
    
}


//function that run on main 

void dial::timeSetter::dialPollEvents(sf::RenderWindow &window,sf::Event& event)
{
    sf::Vector2f currentPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.key.code == sf::Mouse::Left) {
            if (this->checkInKnob(currentPos) && !this->tickingFlag) {
                this->knobPressing = 1;
            }
            //play and pause button
            if (!this->knobPressing) {
                if (this->checkInStop(currentPos) && this->stopSignDisp) {
                    std::cout << "stop has been pressed" << std::endl;
                    this->stopPressed = 1;
                }
                if (this->checkInPlay(currentPos) && !this->stopSignDisp) {
                    this->tickingFlag = 1;
                }
            }
        }
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.key.code == sf::Mouse::Left) {
            if (this->knobPressing) {
                this->knobPressing = 0;
            }
            if (this->tickingFlag && this->checkInPlay(currentPos)) {
                this->restartClock();
                this->tickingFlag = 2;                                //two signifies mouse pressed and released within playButton
            }
            else {
                this->tickingFlag = 0;
            }

            if (this->checkInStop(currentPos) && this->stopPressed) {
                this->stopPressed = 2;                                //two signifies mouse pressed and released within stop button
            }
            else {
                this->stopPressed = 0;
            }
        }
    }
    this->togglePollEvent(window, event); //---------------------------------------------------------------------
}

void dial::timeSetter::dialUpdateFromEvents(sf::RenderWindow &window)
{
    this->toggleUpadteFromEvent();           //---------------------------------------------------------------------
    sf::Vector2f currentPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    //hover effect
    int shapeId = 0;
    if (this->checkInKnob(currentPos)) {
        shapeId = 1;
    }
    if (this->checkInPlay(currentPos)) {
        shapeId = 2;
    }
    if (this->checkInStop(currentPos)) {
        shapeId = 3;
    }

    if (!knobPressing) {
        if (shapeId) {
            this->increseScale(shapeId);
            shapeId = 0;
        }
        else {
            this->resetScale();
        }
    }
    if (knobPressing) {
        this->updateFillers(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    }
}

void dial::timeSetter::dialDrawComponents(sf::RenderWindow& window)
{
    this->toggledrawComponents(window); //-------------------------------
    if (this->knobPressing) {
        this->printPressing(window);
    }
    else {
        // if clock is not tiking
        if (this->tickingFlag != 2) {
            //if play button is showing
            if (this->stopSignDisp != 1) {
                this->printReleased(window);
            }
            else {
                this->printTicking(window, this->tickingFlag, this->stopPressed);
            }
        }
        else {
            this->printTicking(window, this->tickingFlag, this->stopPressed);
        }
    }
}
