/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TestClass
*/

#include "TestClass.hpp"
#include "REngine.hpp"

TestClass::~TestClass()
{
}

TestClass::TestClass()
    : Entity ()
{
    std::cout << "hello" << std::endl;
}

void TestClass::Update()
{
    std::cout << "Say update from TestClass" << std::endl;
}

void TestClass::Start()
{
    std::cout << "Say hello from TestClass" << std::endl;
}