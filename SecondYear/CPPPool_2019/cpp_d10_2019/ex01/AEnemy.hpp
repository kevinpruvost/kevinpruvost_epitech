/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef AENEMY_HPP
#define AENEMY_HPP

// C++ includes
#include <string>

class AEnemy
{
public:
    AEnemy(int hp, const std::string & type);
    virtual ~AEnemy();

public:
    virtual void takeDamage(int damage);

    const std::string & getType() const;
    int getHP() const;

    void setHP(int hp);

private:
    int _hp;
    const std::string _type;
};

#endif // AENEMY_HPP
