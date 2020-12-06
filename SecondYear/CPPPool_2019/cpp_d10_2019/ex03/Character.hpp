/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "ICharacter.hpp"
#include "AMateria.hpp"

#include <vector>

class Character : virtual public ICharacter
{
public:
    Character(const std::string & name);
    Character(Character & other);
    ~Character() override;

public:
    const std::string & getName() const override;
    void equip(AMateria * m) override;
    void unequip(int idx) override;
    void use(int idx, ICharacter& target) override;
    AMateria * getMateria(int idx) const;

    Character & operator=(Character & other);

private:
    AMateria * _materias[4] = {nullptr, nullptr, nullptr, nullptr};
    static const size_t MaxMateriasSize = 4;
    std::string _name;
};



#endif // CHARACTER_HPP
