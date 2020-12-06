/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SpaceInvader
*/

#include "SpaceInvader.hpp"

SpaceInvader::SpaceInvader(ArcadeContent &arcadeContent)
    : AGameModule(arcadeContent, "resources/resourcesSpaceInvader"), _player{nullptr}, _scorePath{"games/space_invader/scores"}, _levelPath{"games/space_invader/map/level1"}, _namePanelCursorString{"a"}, _cursor{0, 0}
{
    _nbLife = 3;
    _level = 0;
    readBestScore();
    restart(_levelPath);
}

SpaceInvader::~SpaceInvader()
{
    saveScore();
}

void SpaceInvader::drawScore()
{
    writeCenteredStringOnMap(39, 2, "player");
    writeCenteredStringOnMap(39, 4, _playerName);

    writeCenteredStringOnMap(39, 8, "life");
    writeCenteredStringOnMap(39, 10, std::to_string(_nbLife));

    writeCenteredStringOnMap(39, 14, "level");
    writeCenteredStringOnMap(39, 16, std::to_string(_level));

    writeCenteredStringOnMap(39, 20, "score");
    writeCenteredStringOnMap(39, 22, std::to_string(_score));

    if (_bestScore != 0)
    {
        writeCenteredStringOnMap(39, 26, "highest score");
        writeCenteredStringOnMap(39, 28, "by " + _bestPlayerName);
        writeCenteredStringOnMap(39, 29, std::to_string(_bestScore));
    }
}

void SpaceInvader::changePage(SpaceInvader::PageId page)
{
    _pageId = page;
    if (_pageId == MENU)
        _startMenu = std::chrono::system_clock::now();
}

bool SpaceInvader::animate()
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

void SpaceInvader::writeLineOnMap(int x, int y, std::string str)
{
    for (const auto &c : str) {
        map()[++x][y] = c;
    }
}

/* Display score user when the game is finish */
void SpaceInvader::updateScorePage() {
    clearMap();
    std::string sentenceScore = "your score: ";
    std::string score = std::to_string(this->_score);
    std::string quit = "quit";
    static int yMenu = 0;

    if (yMenu == 0 && !SpaceInvader::animate())
        quit = "    ";
    SpaceInvader::writeLineOnMap((MAP_WIDTH - (int)sentenceScore.size() + (int)score.size()) / 2, MAP_HEIGHT / 2,
        sentenceScore + score);
    SpaceInvader::writeLineOnMap((MAP_WIDTH - (int)quit.size()) / 2, MAP_HEIGHT / 2 + 2, quit);
    if (event().getKeyValue() == ArcadeEvent::KeyValue::ENTER) {
        if (yMenu == 0)
            setKey(ArcadeEvent::KeyValue::MAINMENU);
    }
}

void SpaceInvader::update()
{
    static const std::vector<void (SpaceInvader::*)()> funcs =
            {&SpaceInvader::updateMenu, &SpaceInvader::updateInGame, &SpaceInvader::updateName
            , &SpaceInvader::updateScorePage};

    (this->*funcs[_pageId])();
}

std::vector<std::pair<int, int>> SpaceInvader::findInMapVector(const char c)
{
    std::vector<std::pair<int, int>> pos;

    for (int i = 0; i < (int)_invaderMap.size(); ++i)
    {
        for (int j = 0; j < (int)_invaderMap[i].size(); ++j)
        {
            if (_invaderMap[i][j] == c)
                pos.push_back(std::pair<int, int>{i, j});
        }
    }
    return pos;
}

void SpaceInvader::readBestScore()
{
    std::ifstream scoreFile(_scorePath);

    if (scoreFile.is_open())
    {
        std::string buffer;
        std::getline(scoreFile, buffer);
        _bestPlayerName = buffer.substr(0, buffer.find(' '));
        buffer = buffer.substr(buffer.find(' ') + 1);
        try
        {
            _bestScore = std::stoi(buffer);
        }
        catch (std::exception &)
        {
            _bestPlayerName.clear();
        }
    }
}

bool SpaceInvader::checkWin()
{
    for (int i = 0; i < (int)this->_ennemy.size(); ++i)
    {
        if (this->_ennemy[i].getIsDead() == false)
        {
            return false;
        }
    }
    return true;
}

std::pair<int, int> SpaceInvader::findInMap(const char c)
{
    std::pair<int, int> pos;

    for (int i = 0; i < (int)_invaderMap.size(); ++i)
    {
        for (int j = 0; j < (int)_invaderMap[i].size(); ++j)
        {
            if (_invaderMap[i][j] == c)
            {
                pos.first = i;
                pos.second = j;
                return pos;
            }
        }
    }
    pos.first = -1;
    pos.second = -1;
    return pos;
}

void SpaceInvader::loadMap(const std::string &fileName)
{
    clearMap();

    std::ifstream f1(fileName);
    std::string s;

    if (!f1.is_open())
    {
        throw EXCEPTION("Map file " + fileName + " cannot be opened.");
        return;
    }

    std::vector<std::string> lines;

    while (std::getline(f1, s, '\n'))
        lines.push_back(s);
    f1.close();

    if (lines.empty() || lines.size() > 30)
    {
        throw EXCEPTION("Map file " + fileName + " is not well formated.");
        return;
    }

    int y = 0;

    _invaderMap.clear();
    _invaderMap.resize(lines[0].length());

    for (int i = 0; i < (int)lines[0].length(); ++i)
        _invaderMap[i].resize(lines.size());

    for (const auto &line : lines)
    {
        if (line.length() > 30 || line.length() != lines[0].length())
        {
            throw EXCEPTION("Map file " + fileName + " is not well formated.");
            return;
        }
        int x = 0;
        for (const auto &c : line)
        {
            _invaderMap[x][y] = c;
            ++x;
        }
        ++y;
    }
}

void SpaceInvader::drawMap()
{
    for (int i = 0; i < (int)_invaderMap.size(); ++i)
        for (int j = 0; j < (int)_invaderMap[i].size(); ++j)
        {
            map()[i][j] = _invaderMap[i][j];
        }
}

bool SpaceInvader::restart(const std::string &fileName)
{
    loadMap(fileName);

    auto playerPos = findInMap('P');
    auto enemyPos = findInMapVector('M');
    auto bridgePos = findInMapVector('"');

    try
    {
        _player.reset(new Spaceinvader::Player(playerPos, _invaderMap));

        _ennemy.clear();
        for (auto &i : enemyPos)
            _ennemy.push_back(Spaceinvader::Ennemy(i, _invaderMap));
        _bridge.clear();
        for (auto &i : bridgePos)
            _bridge.push_back(Spaceinvader::Bridge(i, _invaderMap));
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
    drawMap();
    _startEnemy = std::chrono::system_clock::now();
    _shootEnemy = std::chrono::system_clock::now();
    _shootPlayer = std::chrono::system_clock::now();
    _startPlayer = std::chrono::system_clock::now();
    return true;
}

/* Take INVADERLEFT ou INVADERRIGHT in parameter,
and return pair who contain x y corresponding AI position */
std::pair<int, int> SpaceInvader::findExtremAI(int status)
{
    int x = -1;
    int y = -1;

    for (int i = 0; i < (int)this->_ennemy.size(); ++i)
    {
        if (this->_ennemy[i].getIsDead() == false && x == -1) {
            y = this->_ennemy[i].getPos().second;
            x = this->_ennemy[i].getPos().first;
        }
        else if (status == INVADERLEFT && this->_ennemy[i].getPos().first < x &&
                this->_ennemy[i].getIsDead() == false)
        {
            y = this->_ennemy[i].getPos().second;
            x = this->_ennemy[i].getPos().first;
        }
        else if (status == INVADERRIGHT && this->_ennemy[i].getPos().first > x &&
                this->_ennemy[i].getIsDead() == false)
        {
            y = this->_ennemy[i].getPos().second;
            x = this->_ennemy[i].getPos().first;
        }
    }
    if (x == -1) {
        if (status == INVADERLEFT)
            return _ennemy[0].getPos();
        return _ennemy.back().getPos();
    }
    return std::pair<int, int>(x, y);
}

void SpaceInvader::downAI()
{
    for (int i = (int)_ennemy.size() - 1; i >= 0; --i)
    {
        std::pair<int, int> oldPos{_ennemy[i].getPos()};
        _ennemy[i].reduceHeight(_invaderMap);
        if (!_ennemy[i].getIsDead()) {
            map()[_ennemy[i].getPos().first][_ennemy[i].getPos().second] = 'M';
            map()[oldPos.first][oldPos.second] = ' ';
        }
    }
}

void SpaceInvader::enemy()
{
    std::pair<int, int> oldPos;
    static int direction = INVADERLEFT;
    static bool down = false;
    auto end = std::chrono::system_clock::now();
    int ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - _startEnemy).count();

    if (ms <= 900 - 10 * _level)
        return;

    if (map()[findExtremAI(INVADERRIGHT).first + 1][findExtremAI(INVADERRIGHT).second] == '#')
    {
        direction = INVADERLEFT;
        down = (down) ? (false) : (true);
    }
    else if (map()[findExtremAI(INVADERLEFT).first - 1][findExtremAI(INVADERLEFT).second] == '#')
    {
        direction = INVADERRIGHT;
        down = (down) ? (false) : (true);
    }

    if (down)
        downAI();
	else
		for (auto &i : _ennemy)
		{
		    std::pair<int, int> oldPos = i.getPos();
		    i.update(_invaderMap, direction);
		    if (!i.getIsDead()) {
		        map()[oldPos.first][oldPos.second] = ' ';
		        map()[i.getPos().first][i.getPos().second] = 'M';
		    }
		}
    _startEnemy = std::chrono::system_clock::now();
}

/* Take pair who contain x y in parameter,
if position is found inside ennemy list, return its index */
int SpaceInvader::FindEnemy(std::pair<int, int> pos)
{
    for (int i = 0; i < (int)this->_ennemy.size(); ++i)
    {
        if (this->_ennemy[i].getPos() == pos)
        {
            return i;
        }
    }
    return 0;
}

/* Take pair who contain x y in parameter,
if position is found inside bridge list, return its index */
int SpaceInvader::FindBridge(std::pair<int, int> pos)
{
    for (int i = 0; i < (int)this->_ennemy.size(); ++i)
    {
        if (_bridge[i].getPos() == pos)
        {
            return i;
        }
    }
    return 0;
}

void SpaceInvader::player()
{
    std::pair<int, int> oldPos{_player->getPos()};
    auto end = std::chrono::system_clock::now();
    int ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - _startPlayer).count();

    if (KEY_VALUE == ArcadeEvent::KeyValue::LEFT)
        _player->setLeft();
    else if (KEY_VALUE == ArcadeEvent::KeyValue::RIGHT)
        _player->setRight();
    if (KEY_VALUE == ArcadeEvent::KeyValue::ENTER)
        _player->getWantToShoot() = true;

    if (ms <= 300 - 10 * _level)
        return;

    int ret = _player->moveForward(map());
    if (ret >= 0)
    {
        map()[oldPos.first][oldPos.second] = ' ';
        map()[_player->getPos().first][_player->getPos().second] = 'P';
        return;
    }
}

void SpaceInvader::shootEnemy()
{
    auto end = std::chrono::system_clock::now();
    int msshhot = std::chrono::duration_cast<std::chrono::milliseconds>(end - _shootEnemy).count();

    if (msshhot >= 200 - 10 * _level) {
        for (auto & i : _ennemy) {
            if (!i.getIsDead()) {
                std::pair<int, int> oldPosShoot = i.getShootPos();
                int res = i.shoot(map());
                if (res == 1) {
                    _player->getIsDead() = true;
                    i.getIsShooting() = false;
                    map()[i.getShootPos().first][i.getShootPos().second] = ' ';
                } else if (res == 2) {
                    _bridge[FindBridge({i.getShootPos().first, i.getShootPos().second - 1})].getIsDead() = true;
                    i.getIsShooting() = false;
                    map()[i.getShootPos().first][i.getShootPos().second] = ' ';
                    map()[i.getShootPos().first][i.getShootPos().second + 1] = ' ';
                } else if (res == 3) {
                    i.getIsShooting() = false;
                    map()[i.getShootPos().first][i.getShootPos().second] = ' ';
                } else if (res == 0) {
                    (oldPosShoot != std::pair<int, int>{-1, -1}) ? map()[oldPosShoot.first][oldPosShoot.second] = ' ' : 0;
                    i.getShootPos().second += 1;
                    map()[i.getShootPos().first][i.getShootPos().second] = '|';
                }
            }
        }
    }
    if (msshhot >= 200 - 10 * _level)
        _shootEnemy = std::chrono::system_clock::now();
}

void SpaceInvader::shootPlayerAndEnemy()
{
    auto end = std::chrono::system_clock::now();
    int msshot = std::chrono::duration_cast<std::chrono::milliseconds>(end - _shootPlayer).count();
    int ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - _startPlayer).count();

    if (_player->getWantToShoot() || (_player->isPlayerShooting() && msshot >= 50))
    {
        _player->getWantToShoot() = false;
        std::pair<int, int> oldPosShoot{_player->getShootPos()};
        int res = _player->shoot(map());
        if (res == 1)
        {
            int enemy = FindEnemy({_player->getShootPos().first, _player->getShootPos().second - 1});
            _ennemy[enemy].getIsDead() = true;
            std::pair<int, int> posMissile = _ennemy[enemy].getShootPos();
            (posMissile != std::pair<int, int>{-1, -1}) ? map()[posMissile.first][posMissile.second] = ' ' : 0;
            _player->isPlayerShooting() = false;
            map()[_player->getShootPos().first][_player->getShootPos().second] = ' ';
            map()[_player->getShootPos().first][_player->getShootPos().second - 1] = ' ';
            _score += 10;
        }
        else if (res == 2)
        {
            _bridge[FindBridge({_player->getShootPos().first, _player->getShootPos().second - 1})].getIsDead() = true;
            _player->isPlayerShooting() = false;
            map()[_player->getShootPos().first][_player->getShootPos().second] = ' ';
            map()[_player->getShootPos().first][_player->getShootPos().second - 1] = ' ';
        }
        else if (res == 3)
        {
            _player->isPlayerShooting() = false;
            map()[_player->getShootPos().first][_player->getShootPos().second] = ' ';
        }
        else if (res == 0)
        {
            (oldPosShoot != std::pair<int, int>{-1, -1}) ? map()[oldPosShoot.first][oldPosShoot.second] = ' ' : 0;
            _player->getShootPos().second -= 1;
            map()[_player->getShootPos().first][_player->getShootPos().second] = '|';
        }
    }
    if (msshot >= 50)
        _shootPlayer = std::chrono::system_clock::now();
    if (ms >= 300 - 10 * _level)
        _startPlayer = std::chrono::system_clock::now();
    shootEnemy();
}

void SpaceInvader::updateInGame()
{
    if (this->_nbLife == 0)
        changePage(SpaceInvader::PageId::SCORE);
    if (checkWin())
    {
        restart(_levelPath);
        ++_level;
    }
    clearMap();
    drawMap();
    if (_player->getIsDead()) {
        _nbLife -= 1;
        if (_nbLife > 0)
            _player->getIsDead() = false;
    }
    player();
    shootPlayerAndEnemy();
	enemy();
    drawScore();

    for (int i = 0; i < (int)_invaderMap.size(); ++i)
        for (int j = 0; j < (int)_invaderMap[0].size(); ++j)
            _invaderMap[i][j] = map()[i][j];

    if (KEY_VALUE == ArcadeEvent::KeyValue::ESCAPE)
        changePage(SpaceInvader::PageId::MENU);
}

void SpaceInvader::saveScore()
{
    std::ofstream outFile;

    _bestScore = _score;
    _bestPlayerName = _playerName;

    outFile.open(_scorePath);
    if (_score > _bestScore)
    {
        outFile << _playerName << " " << _score << std::endl;
    }
}

extern "C"
{
    IGameModule *getGameModule(ArcadeContent &arcadeContent)
    {
        return new SpaceInvader(arcadeContent);
    }
}