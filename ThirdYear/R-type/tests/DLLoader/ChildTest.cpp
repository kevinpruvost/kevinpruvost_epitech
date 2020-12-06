/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** ChildTest
*/

#include "ChildTest.hpp"

ChildTest::ChildTest()
    : TestClass()
{
}

ChildTest::~ChildTest()
{
}

int ChildTest::sayHello()
{
    std::cout << "Goodbye Child" << std::endl;
    return 1;
}

RType::Common::Engine::Entity * getChildClass()
{
    return new ChildTest();
}
