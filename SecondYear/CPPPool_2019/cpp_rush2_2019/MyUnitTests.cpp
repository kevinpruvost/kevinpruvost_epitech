/*
** EPITECH PROJECT, 2020
** MyUnitTests.cpp
** File description:
** unit tests for "Little LittlePony and teddy" (page 2 of the PDF)
*/

#include "MyUnitTests.hpp"

// Project includes
#include "Teddy.hpp"
#include "LittlePony.hpp"
#include "Box.hpp"
#include "GiftPaper.hpp"
#include "PapaXmasTable.hpp"
#include "PapaXmasConveyorBelt.hpp"
#include "PapaXmasConveyorBelt.hpp"
#include "PapaXmasElf.hpp"
#include "PapaXmasTable.hpp"

// C++ includes
#include <iostream>

Object ** MyUnitTests2()
{
    Object ** tab = new Object*[2];
    PapaXmasElf *elf = new PapaXmasElf;
    PapaXmasTable *table = new PapaXmasTable;
    PapaXmasConveyorBelt *belt = new PapaXmasConveyorBelt;
    Box *box = new Box;
    GiftPaper *gf = new GiftPaper;

    tab[0] = new Teddy("cuddles");
    tab[1] = new LittlePony("happy pony");

    //*gf << box << tab[0];
    
    belt->put(tab[0]); // cuddles sur conveyor
    elf->take(belt); // Elfe prend cuddles
    elf->put(table); // pose sur la table
    std::cout << "First test :\n " << elf->look(table) << std::endl;
    belt->put(box); // box sur conveyor
    belt->put(tab[1]); // essaie de mettre happy pony sur la belt
    elf->take(belt);    // prend la box
    elf->put(table); // pose la box
    std::cout << "deuxieme tests :\n " << elf->look(table) << std::endl;
    belt->put(gf);   // met le papier sur la belt
    elf->take(belt); // prends le papier
    belt->put(tab[1]); // met happy pony sur la belt
    elf->take(belt); // essaie de prendre happy pony
    elf->put(table); // met le papier sur la table
    std::cout << "troisieme tests :\n ";
    std::cout << elf->look(table) << std::endl;
    elf->take(2, table); // prends papier sr la table
    elf->put(belt); // met sur la table
    elf->pressOut(belt->getButton()); // press out

    elf->setConveyor(belt);
    elf->setTable(table);

    Object ** tabs = new Object*[6];
    
    tabs[0] = new LittlePony("gift2");
    tabs[1] = new LittlePony("gift1");
    table->put(tabs[0]);
    elf->put(table);
    table->put(tabs[1]);
    elf->put(table);

    elf->packAGift();
    return tab;
}

Object ** MyUnitTests()
{
    Object ** tab = new Object*[2];

    tab[0] = new Teddy("cuddles");
    tab[1] = new LittlePony("happy pony");

    return tab;
}

Object * MyUnitTests(Object ** objects)
{
    Teddy * ted = (Teddy*)objects[0];
    Box *box = (Box*)objects[1];
    GiftPaper *goofy = (GiftPaper*)objects[2];

    box->wrapMeThat(ted);
    goofy->wrapMeThat(box);

    box->isTaken();

    return goofy;
}

IConveyorBelt * createConveyorBelt()
{
    return new PapaXmasConveyorBelt;
}

ITable * createTable()
{
    return new PapaXmasTable;
}