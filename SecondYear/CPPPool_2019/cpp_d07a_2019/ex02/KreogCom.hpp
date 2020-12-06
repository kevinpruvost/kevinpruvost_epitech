/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef KREOGCOM_HPP
#define KREOGCOM_HPP

// C++ includes
#include <vector>

class KreogCom
{
public:
    KreogCom(int x, int y, int serial);
    ~KreogCom();

    void addCom(int x, int y, int serial);
    void removeCom();
    KreogCom * getCom();

    void ping();
    void locateSquad();
    void setCom(KreogCom * com);

private:
    const int m_serial;
    int _x;
    int _y;

    KreogCom * _com = nullptr;
};

#endif // KREOGCOM_HPP
