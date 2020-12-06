/*
** EPITECH PROJECT, 2020
** Nibbler.cpp
** File description:
** nibbler
*/

#include "Nibbler.hpp"

#include "Exception.hpp"

Nibbler::Nibbler(ArcadeContent & arcadeContent)
    : AGameModule(arcadeContent, "resources/resourcesNibbler")
{
    Nibbler::nibblerMapClear();
}

Nibbler::~Nibbler()
{
}

//clear nibbler map
void Nibbler::nibblerMapClear()
{
    this->__nibblerMap.clear();
    this->__nibblerMap.resize(MAP_WIDTH);
    for (int i = 0; i < MAP_WIDTH; ++i)
        __nibblerMap[i].resize(MAP_HEIGHT, 0);
}

//pars line of the bestscore file
std::string Nibbler::parsLine(const std::string &buffer)
{
    bool space = false;
    std::string bestScore;

    for (int i = 0; i < (int)buffer.size(); ++i) {
        if (buffer.at(i) == ' ')
            space = true;
        else {
            if (space == true)
                bestScore += buffer.at(i);
            else
                this->__nameBestScore += buffer.at(i);
        }
    }
    return bestScore;
}

//Load bestScore
void Nibbler::loadBestScore()
{
    std::ifstream inFile(this->__pathScore);
    std::string buffer;
    std::string bestScore;

    this->__bestScore = 0;
    if (this->__nameBestScore.empty())
        this->__nameBestScore = "default";
    if (!inFile.is_open()) {
        return;
    }
    while (std::getline(inFile, buffer))
        bestScore = Nibbler::parsLine(buffer);
    if (!bestScore.empty())
        this->__bestScore = (unsigned int)std::stoi(bestScore);
}

//write currently score inside bestScore file
void Nibbler::setScore()
{
    std::ofstream outFile;

    outFile.open(this->__pathScore);
    if (this->__score > this->__bestScore) {
        outFile << this->__namePlayer1 <<  " " << this->__score << std::endl;
    }
}

//Load positions of each cunsomables
void Nibbler::chargeCunsomable()
{
    unsigned int i = 0;
    char tmp;
    this->__nbConsomable = 0;

    for (std::vector<char> str : this->__nibblerMap) {
        for (unsigned int j = 0; j < str.size(); ++j) {
            tmp = str.at(j);
            if (tmp == 'C')
                this->__nbConsomable++;
        }
        ++i;
    }
}

//Load each part's position of the snake inside an int array
void Nibbler::foundSnake()
{
    unsigned int i = 0;
    char tmp;

    for (std::vector<char> str : this->__nibblerMap) {
        for (unsigned int j = 0; j < str.size(); ++j) {
            tmp = str.at(j);
            if (tmp == 'H') {
                this->__headX = i;
                this->__headY = j;
            } else if (tmp == 'B') {
                __snakePosition.push_back(std::pair<unsigned int, unsigned int>(j, i));
            } else if (tmp == 'T') {
                this->__tailX = i;
                this->__tailY = j;
            }
        }
        ++i;
    }
}

//Centet map on vertical Axe
int Nibbler::centerVertcalMap(int level)
{
    std::ifstream inFile(this->__pathArray.at(level));
    std::string buffer;
    int nb_line = 0;
    int index = 0;

    if (inFile.is_open()) {
        for (nb_line = 0; std::getline(inFile, buffer); ++nb_line);
    } else
        setKey(ArcadeEvent::KeyValue::MAINMENU);
    index = (MAP_HEIGHT - nb_line) / 2;
    for (int i = 0; i < index; ++i)
        this->__nibblerMap[i][0] = '\n';
    return index;
}

//Centet map on horizontal Axe
int Nibbler::centerHorizontalMap(int level)
{
    std::ifstream inFile(this->__pathArray.at(level));
    std::string buffer;
    int lengthLine = 0;
    int index = 0;

    if (inFile.is_open()) {
        std::getline(inFile, buffer);
        lengthLine = (int)buffer.size(); 
    } else
        setKey(ArcadeEvent::KeyValue::MAINMENU);
    index = (MAP_WIDTH - 20 - lengthLine) / 2;
    for (int i = 0; i < index; ++i)
        this->__nibblerMap[i][0] = '\n';
    return index;
}

void Nibbler::displayMap()
{
    for (std::vector<char> str : this->__nibblerMap) {
        for (int i = 0; i < (int)str.size(); ++i)
            std::cout << str.at(i);
        std::cout << std::endl;
    }
}

//Charge next level of the game
void Nibbler::loadNextLevel(bool up)
{
    int level = this->__level;
    if (up == false)
        level -= 1;
    std::ifstream inFile(this->__pathArray.at(level));
    std::string buffer;
    int y = Nibbler::centerVertcalMap(level);
    int startX = Nibbler::centerHorizontalMap(level);
    Nibbler::nibblerMapClear();

    if (level == 0)
        Nibbler::loadBestScore();
    this->__snakePosition.clear();
    this->__nbConsomable = 0;
    if (inFile.is_open()) {
        for (; std::getline(inFile, buffer); ++y) {
            for (int x = 0, posX = startX; x < (int)buffer.size(); ++x, ++posX) {
                this->__nibblerMap[posX][y] = buffer.at(x);
            }
        }
    } else {
        throw EXCEPTION("No " + __pathArray[level] + " found.");
        setKey(ArcadeEvent::KeyValue::MAINMENU);
        return;
    }
    chargeCunsomable();
    foundSnake();
    if (up == true) {
        this->__level += 1;
    }
}

//Move all body
void Nibbler::moveBody(int oldX, int oldY)
{
    __nibblerMap[__tailX][__tailY] = ' ';
    __tailY = __snakePosition.front().first;
    __tailX = __snakePosition.front().second;
    auto it = __snakePosition.begin();
    __snakePosition.erase(it);
    __snakePosition.push_back(std::pair<unsigned int, unsigned int>{oldY, oldX});

    __nibblerMap[__tailX][__tailY] = 'T';
    __nibblerMap[__headX][__headY] = 'H';
    __nibblerMap[__snakePosition.back().second][__snakePosition.back().first] = 'B';
}

//Grow the length of the snake
void Nibbler::grow(int y, int x)
{
    __score += 10;
    __nibblerMap[__headX][__headY] = 'B';
    __snakePosition.push_back(std::pair<unsigned int, unsigned int>{__headY, __headX});
    __nibblerMap[x][y] = 'H';
    __headY = y;
    __headX = x;
    __snakeLength += 1;
    return;
}

int Nibbler::orientation()
{
    if (__headX < __snakePosition.back().second)
        return LEFTSNAKE;
    else if (__headX > __snakePosition.back().second)
        return RIGHTSNAKE;
    else if (__headY > __snakePosition.back().first)
        return DOWNSNAKE;
    else
        return UPSNAKE;
    return 0;
}

void Nibbler::moveSnakeUp()
{
    if (__headY - 1 < 0 || __nibblerMap[__headX][__headY-1] == '#' || __nibblerMap[__headX][__headY-1] == 'B' || __nibblerMap[__headX][__headY-1] == 'T')
        return;
    else if (__nibblerMap[__headX][__headY-1] == 'C') {
        grow(__headY - 1, __headX);
    } else if (orientation() != UPSNAKE){
        --__headY;
        moveBody(__headX, __headY + 1);
    }
    return;
}

void Nibbler::moveSnakeDown()
{
    if (__headY + 1 > __nibblerMap.size() || __nibblerMap[__headX][__headY+1] == '#' || __nibblerMap[__headX][__headY+1] == 'B' || __nibblerMap[__headX][__headY+1] == 'T')
        return;
    else if (__nibblerMap[__headX][__headY + 1] == 'C') {
        grow(__headY + 1, __headX);
    }
    else if (orientation() != DOWNSNAKE){
        ++__headY;
        moveBody(__headX, __headY - 1);
    }
    return;
}

void Nibbler::automoveUp()
{
    if (__nibblerMap[__headX][__headY-1] == 'C') {
        grow(__headY-1, __headX);
    } else if (__nibblerMap[__headX][__headY-1] == '#' || \
        __nibblerMap[__headX][__headY-1] == 'B' || \
        __nibblerMap[__headX][__headY-1] == 'T')
        return;
    else {
        --__headY;
        moveBody(__headX, __headY + 1);
    }
}

void Nibbler::automoveDown()
{
    if (__nibblerMap[__headX][__headY+1] == 'C') {
        grow(__headY+1, __headX);
    } else if (__nibblerMap[__headX][__headY+1] == '#' || \
        __nibblerMap[__headX][__headY+1] == 'B' || \
        __nibblerMap[__headX][__headY+1] == 'T')
        return;
    else {
        ++__headY;
        moveBody(__headX, __headY - 1);
    }
}

void Nibbler::automoveRight()
{
    if (__nibblerMap[__headX+1][__headY] == 'C') {
        grow(__headY, __headX + 1);
    } else if (__nibblerMap[__headX+1][__headY] == '#' || \
        __nibblerMap[__headX+1][__headY] == 'B' || \
        __nibblerMap[__headX+1][__headY] == 'T')
        return;
    else {
        ++__headX;
        moveBody(__headX - 1, __headY);
    }
}

void Nibbler::moveSnakeRight()
{
    int move = orientation();

    if (move == RIGHTSNAKE && (__nibblerMap[__headX][__headY + 1] != '#' && __nibblerMap[__headX][__headY + 1] != 'T' && __nibblerMap[__headX][__headY + 1] != 'B'))
        moveSnakeDown();
    else if (move == LEFTSNAKE && (__nibblerMap[__headX][__headY - 1] != '#' && __nibblerMap[__headX][__headY - 1] != 'T' && __nibblerMap[__headX][__headY - 1] != 'B'))
        moveSnakeUp();
    else if (__nibblerMap[__headX+1][__headY] == 'C')
        grow(__headY, __headX + 1);
    else if (move == UPSNAKE && (__nibblerMap[__headX+1][__headY] != '#' && \
        __nibblerMap[__headX+1][__headY] != 'B' && \
        __nibblerMap[__headX+1][__headY] != 'T')) {
        ++__headX;
        moveBody(__headX - 1, __headY);
    } else if (move == DOWNSNAKE && (__nibblerMap[__headX-1][__headY] != '#' && \
        __nibblerMap[__headX-1][__headY] != 'B' && \
        __nibblerMap[__headX-1][__headY] != 'T')) {
        --__headX;
        moveBody(__headX + 1, __headY);
    } else if (__nibblerMap[__headX+1][__headY] == '#' || \
        __nibblerMap[__headX+1][__headY] == 'B' || \
        __nibblerMap[__headX+1][__headY] == 'T')
        (orientation() == RIGHTSNAKE) ? moveSnakeDown() : moveSnakeUp();
}

void Nibbler::automoveLeft()
{
    if (__nibblerMap[__headX-1][__headY] == '#' || \
        __nibblerMap[__headX-1][__headY] == 'B' || \
        __nibblerMap[__headX-1][__headY] == 'T')
        return;
    else if (__nibblerMap[__headX-1][__headY] == 'C')
        grow(__headY, __headX - 1);
    else {
        --__headX;
        moveBody(__headX + 1, __headY);
    }
}


void Nibbler::moveSnakeLeft()
{
    int move = orientation();

    if (move == RIGHTSNAKE && (__nibblerMap[__headX][__headY - 1] != '#' && __nibblerMap[__headX][__headY - 1] != 'T' && __nibblerMap[__headX][__headY + 1] != 'B'))
        moveSnakeUp();
    else if (move == LEFTSNAKE && (__nibblerMap[__headX][__headY + 1] != '#' && __nibblerMap[__headX][__headY + 1] != 'T' && __nibblerMap[__headX][__headY + 1] != 'B'))
        moveSnakeDown();
    else if (move == UPSNAKE && (__nibblerMap[__headX-1][__headY] != '#' && \
        __nibblerMap[__headX-1][__headY] != 'B' && \
        __nibblerMap[__headX-1][__headY] != 'T')) {
        --__headX;
        moveBody(__headX + 1, __headY);
    } else if (move == DOWNSNAKE && __nibblerMap[__headX+1][__headY] != '#' && \
        __nibblerMap[__headX+1][__headY] != 'B' && \
        __nibblerMap[__headX+1][__headY] != 'T') {
        ++__headX;
        moveBody(__headX - 1, __headY);
    }
    else if (__nibblerMap[__headX-1][__headY] == 'C')
        grow(__headY, __headX - 1);
    else if (__nibblerMap[__headX-1][__headY] == '#' || \
        __nibblerMap[__headX-1][__headY] == 'B' || \
        __nibblerMap[__headX-1][__headY] == 'T')
        (move == RIGHTSNAKE) ? moveSnakeUp() : moveSnakeDown();
}

//Move snake inside the map
void Nibbler::moveSnake()
{
    int move = orientation();

    if (event().getKeyValue() == ArcadeEvent::KeyValue::LEFT) {
        moveSnakeLeft();
    } else if (event().getKeyValue() == ArcadeEvent::KeyValue::RIGHT) {
        moveSnakeRight();
    } else if (doMove()) {
        if (move == UPSNAKE || move == DOWNSNAKE)
            (__nibblerMap[__headX][__headY + 1] == '#' || __nibblerMap[__headX][__headY + 1] == 'B' || __nibblerMap[__headX][__headY + 1] == 'T') ? automoveUp() : automoveDown();
        else {
            (move == LEFTSNAKE) ? automoveLeft() : automoveRight();
        }
    }
}

void Nibbler::writeLineOnMap(int x, int y, std::string str)
{
    for (const auto &c : str) {
        this->__nibblerMap[++x][y] = c;
    }
}

void Nibbler::displayInformationGame()
{
    int refX = 30;

    Nibbler::writeLineOnMap(refX, 9, "player " + this->__namePlayer1);
    Nibbler::writeLineOnMap(refX, 11, "left " + std::to_string(this->__nbrLife));
    //Nibbler::writeLineOnMap(refX, 13, "time " + std::to_string(this->__time));
    if (__bestScore != 0)
    {
        Nibbler::writeLineOnMap(refX, 15, "highest score " + std::to_string(this->__bestScore));
        Nibbler::writeLineOnMap(refX, 17, "by " + this->__nameBestScore);
    }
    Nibbler::writeLineOnMap(refX, 19, "your score " + std::to_string(this->__score));
}

bool Nibbler::checkDead()
{
    if (__nibblerMap[__headX][__headY + 1] == '#' || \
        __nibblerMap[__headX][__headY + 1] == 'T' || \
        __nibblerMap[__headX][__headY + 1] == 'B' || \
        __nibblerMap[__headX][__headY + 1] == 'H')
        if (__nibblerMap[__headX][__headY - 1] == '#' || \
            __nibblerMap[__headX][__headY - 1] == 'T' || \
            __nibblerMap[__headX][__headY - 1] == 'B' || \
            __nibblerMap[__headX][__headY - 1] == 'H')
            if (__nibblerMap[__headX+1][__headY] == '#' || \
                __nibblerMap[__headX+1][__headY] == 'T' || \
                __nibblerMap[__headX+1][__headY] == 'B' || \
                __nibblerMap[__headX+1][__headY] == 'H')
                if (__nibblerMap[__headX-1][__headY] == '#' || \
                    __nibblerMap[__headX-1][__headY] == 'T' || \
                    __nibblerMap[__headX-1][__headY] == 'B' || \
                    __nibblerMap[__headX-1][__headY] == 'H')
                    return true;
    return false;
}

bool Nibbler::animate()
{
    static bool anim = false;
    static auto start = std::chrono::system_clock::now();

    auto end = std::chrono::system_clock::now();
    int elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();

    if (elapsed_ms >= 400)
    {
        start = std::chrono::system_clock::now();
        anim = !anim;
    }
    return anim;
}

void Nibbler::setName()
{
    std::string refAlphabetPart1 = "a b c d e f g h i j k l m";
    std::string refAlphabetPart2 = "n o p q r s t u v w x y z";
    std::string save = "save";
    std::string Delete = "delete";
    std::string alphabetPart1 = "a b c d e f g h i j k l m";
    std::string alphabetPart2 = "n o p q r s t u v w x y z";
    std::string message = "enter your name";
    static std::string name;

    if (this->__yMenu == 0 && !Nibbler::animate()) {
        alphabetPart1.at(this->__xMenu) = ' ';
    } else if (this->__yMenu == 1 && !Nibbler::animate()){
        alphabetPart2.at(this->__xMenu) = ' ';
    } else if (this->__yMenu == 2 && !Nibbler::animate()) {
        save = "    ";
    } else if (this->__yMenu == 3 && !Nibbler::animate()) {
        Delete = "      ";
    }

    Nibbler::writeLineOnMap((MAP_WIDTH - (int)alphabetPart1.size()) / 2, MAP_HEIGHT / 2 - 5, alphabetPart1);
    Nibbler::writeLineOnMap((MAP_WIDTH - (int)alphabetPart2.size()) / 2, MAP_HEIGHT / 2 - 3, alphabetPart2);
    Nibbler::writeLineOnMap((MAP_WIDTH - (int)message.size()) / 2, MAP_HEIGHT / 2 - 1, message);
    Nibbler::writeLineOnMap((MAP_WIDTH - (int)name.size()) / 2, MAP_HEIGHT / 2 + 3, name);
    Nibbler::writeLineOnMap((MAP_WIDTH - (int)save.size()) / 2, MAP_HEIGHT / 2 + 7, save);
    Nibbler::writeLineOnMap((MAP_WIDTH - (int)Delete.size()) / 2, MAP_HEIGHT / 2 + 9, Delete);
    if (event().getKeyValue() == ArcadeEvent::KeyValue::ENTER) {
        if (this->__yMenu == 0 && name.size() < 7)
            name += refAlphabetPart1.at(this->__xMenu);
        else if (this->__yMenu == 1  && name.size() < 7)
            name += refAlphabetPart2.at(this->__xMenu);
        else if (this->__yMenu == 2)
            this->__namePlayer1 = name;
        else if (name.size() != 0 && this->__yMenu == 3) {
            for (int a = 0; a < (int)name.size(); ++a)
                name.at(a) = ' ';
            Nibbler::writeLineOnMap((MAP_WIDTH - (int)name.size()) / 2, MAP_HEIGHT / 2 + 3, name);
            name.clear();
        }
    }
    if (event().getKeyValue() == ArcadeEvent::KeyValue::RIGHT && this->__xMenu < 24) {
        this->__xMenu += 2;
    }
    if (event().getKeyValue() == ArcadeEvent::KeyValue::LEFT && this->__xMenu > 0) {
        this->__xMenu -= 2;
    }
    if (event().getKeyValue() == ArcadeEvent::KeyValue::UP && this->__yMenu > 0) {
        this->__yMenu -= 1;
    }
    if (event().getKeyValue() == ArcadeEvent::KeyValue::DOWN && this->__yMenu <= 3) {
        this->__yMenu += 1;
    }
}

bool Nibbler::doMove()
{
    bool anim = false;
    static auto start = std::chrono::system_clock::now();

    auto end = std::chrono::system_clock::now();
    int elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();

    if (elapsed_ms >= 500) {
        start = std::chrono::system_clock::now();
        anim = !anim;
    }
    return anim;
}

void Nibbler::EscapeMenu()
{
    Nibbler::nibblerMapClear();
    std::string mainMenu = "main menu";
    std::string resume = "resume";
    std::string quit = "quit";

    if (this->__yMenu == 0 && !Nibbler::animate()) {
        resume = "      ";
    } else if (this->__yMenu == 1 && !Nibbler::animate()) {
        mainMenu = "         ";
    } else if (this->__yMenu == 2 && !Nibbler::animate()) {
        quit = "    ";
    }

    Nibbler::writeLineOnMap((MAP_WIDTH - (int)resume.size()) / 2, MAP_HEIGHT / 2 - 2, resume);
    Nibbler::writeLineOnMap((MAP_WIDTH - (int)mainMenu.size()) / 2, MAP_HEIGHT / 2, mainMenu);
    Nibbler::writeLineOnMap((MAP_WIDTH - (int)quit.size()) / 2, MAP_HEIGHT / 2 + 2, quit);
    if (event().getKeyValue() == ArcadeEvent::KeyValue::ENTER) {
        if (this->__yMenu == 0) {
            this->__EscapeMenuEnable = false;
            this->__nibblerMap = this->__saveNibblerMap;
        } else if (this->__yMenu == 1)
            setKey(ArcadeEvent::KeyValue::MAINMENU);
        else if (this->__yMenu == 2)
            setKey(ArcadeEvent::KeyValue::EXIT);
    }
    if (event().getKeyValue() == ArcadeEvent::KeyValue::UP && this->__yMenu > 0) {
        this->__yMenu -= 1;
    }
    if (event().getKeyValue() == ArcadeEvent::KeyValue::DOWN && this->__yMenu < 2) {
        this->__yMenu += 1;
    }
}

//main loop of the game
void Nibbler::update()
{
    clearMap();
    if (this->__namePlayer1.compare("default") == 0) {
        setName();
    } else {
        if (this->__EscapeMenuEnable == true)
            Nibbler::EscapeMenu();
        else {
            Nibbler::chargeCunsomable();
            if (event().getKeyValue() == ArcadeEvent::KeyValue::ESCAPE) {
                this->__EscapeMenuEnable = true;
                map() = this->__nibblerMap;
                this->__saveNibblerMap = this->__nibblerMap;
                return;
            }
            if (this->__nbrLife <= 0) {
                Nibbler::setScore();
                setKey(ArcadeEvent::KeyValue::MAINMENU);
            }
            if (this->__level == this->__max_level && this->__nbConsomable == 0) {
                Nibbler::setScore();
                return setKey(ArcadeEvent::KeyValue::MAINMENU);
            } if (Nibbler::checkDead() == true) {
                this->__nbrLife -= 1;
                loadNextLevel(false);
            } else if (this->__nbConsomable == 0) {
                loadNextLevel(true);
                if (this->__nbConsomable == 0 || this->__snakePosition.empty())
                    setKey(ArcadeEvent::KeyValue::MAINMENU);
            }
            Nibbler::moveSnake();
            Nibbler::displayInformationGame();
        }
    }
    map() = this->__nibblerMap;
}
