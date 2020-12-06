/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef EXAM_HPP
#define EXAM_HPP

class Exam
{
public:
    Exam(bool * cheat = nullptr);

public:
    void start(int nb);
    bool isCheating();

public:
    void (Exam::*kobayashiMaru)(int) = nullptr;
    static bool cheat;

private:
    bool * adress;
};


//static bool Exam::cheat = false;

#endif // EXAM_HPP
