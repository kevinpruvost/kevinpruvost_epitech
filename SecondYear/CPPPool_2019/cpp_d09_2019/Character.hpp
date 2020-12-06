/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/23
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

// C++ includes
#include <string>

class Character
{
public:
    enum AttackRange {
        CLOSE = 0,
        RANGE = 1
    };

public:
    Character(const std::string & name = "Kreog", int level = 1,
              const std::string classs = "Warrior",
              const std::string race = "Dwarf",
              int pv = 100, int power = 100, int strength = 5,
              int stamina = 5, int intelligence = 5, int spirit = 5,
              int agility = 5, AttackRange range = CLOSE);

public:
    const std::string & getName() const;
    int getLvl() const;
    int getPv() const;
    int getPower() const;
    int getStrength() const;
    int getStamina() const;
    int getIntelligence() const;
    int getSpirit() const;
    int getAgility() const;
    std::string getClass() const;
    std::string getRace() const;

    void setLvl(int lvl);
    void setPv(int pv);
    void setPower(int power);
    void setStrength(int strength);
    void setStamina(int stamina);
    void setIntelligence(int intel);
    void setSpirit(int spirit);
    void setAgility(int agi);

public:
    int CloseAttack();
    int RangeAttack();
    void Heal();
    void RestorePower();
    void TakeDamage(int damage);

    void say(const std::string str) const;

public:
    bool checkAndUsePower(const int cost);

public:
    AttackRange Range;

private:
    int _lvl;
    int _pv;
    int _power;
    const std::string _name;
    const std::string _class;
    const std::string _race;

protected:
    int _strength;
    int _stamina;
    int _intelligence;
    int _spirit;
    int _agility;
};

std::ostream & operator<<(std::ostream & os, const Character & oof);

#endif // CHARACTER_HPP
