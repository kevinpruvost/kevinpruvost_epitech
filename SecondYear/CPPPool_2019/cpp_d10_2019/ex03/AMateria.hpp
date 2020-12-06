/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <string>

#include "ICharacter.hpp"

class AMateria
{
public:
    AMateria(const std:: string & type);
    virtual ~AMateria();

public:
    const std::string & getType() const; // Returns  the  materia  type
    unsigned int getXP() const; // Returns  the  Materia's XP

    void setXP(unsigned int xp);

    virtual AMateria * clone() const = 0;
    virtual void use(ICharacter & target);

private:
    unsigned int xp_ = 0;
    const std::string type_;
};

#endif // AMATERIA_HPP
