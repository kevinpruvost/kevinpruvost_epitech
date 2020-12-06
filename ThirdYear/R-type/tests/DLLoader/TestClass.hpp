/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TestClass
*/

#pragma once

#include "Entity.hpp"
#include "DLLoader/export.h"

class TestClass : virtual public RType::Common::Engine::Entity
{
public:
    TestClass();
    ~TestClass();

    void Update() override;
    void Start() override;
};

EXPORT_FUNCTION TestClass * getClass()
{
    return new TestClass;
}