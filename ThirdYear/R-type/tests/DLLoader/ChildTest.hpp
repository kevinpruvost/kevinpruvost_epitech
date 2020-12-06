/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** ChildTest
*/

#pragma once

#include "TestClass.hpp"
#include "DLLoader/export.h"

class ChildTest : virtual public TestClass{
    public:
        ChildTest();
        ~ChildTest();

        int sayHello() override;

    protected:
    private:
};

EXPORT_FUNCTION RType::Common::Engine::Entity * getChildClass();
