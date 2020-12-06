/*
** EPITECH PROJECT, 2020
** MyUnitTests.hpp
** File description:
** ex00
*/

#pragma once

#include "Object.hpp"
#include "IConveyorBelt.hpp"
#include "ITable.hpp"
#include "Display.hpp"

Object ** MyUnitTests();
Object * MyUnitTests(Object **objects);
Object ** MyUnitTests2();


IConveyorBelt * createConveyorBelt();
ITable * createTable();