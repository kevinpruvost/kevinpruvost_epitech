/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/30
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef DOMESTICKOALA_HPP
#define DOMESTICKOALA_HPP

#include <map>
#include <vector>
#include <string>

#include "KoalaAction.hpp"

using  methodPointer_t = void (KoalaAction::*)(const std::string & str);

class DomesticKoala
{
public:
    DomesticKoala(KoalaAction & action);
    ~DomesticKoala ();
    DomesticKoala(const  DomesticKoala  &);
    DomesticKoala &operator =(const  DomesticKoala &);

    //  Retrieves a vector  containing  all  the  member  function  pointers
    const  std::vector <methodPointer_t > *getActions () const;

    // Sets a member  function  pointer , linking  the  character (the  command) to the
    //  pointer (the  action).
    void  learnAction(unsigned  char  command , methodPointer_t  action);

    //  Deletes  the  command.
    void  unlearnAction(unsigned  char  command);

    //  Executes  the  action  linked  to the  given  command. The  string  is
    // the  parameter given  to the  member  function.
    void  doAction(unsigned  char  command , const  std:: string &param);

    //  Affects a new  KoalaAction  class to the  domestic  Koala.
    // This  erases  the  pointers  table.
    void  setKoalaAction(KoalaAction  &);

public:
    std::map<unsigned char, methodPointer_t> _map;
    KoalaAction & _koala;
};


#endif // DOMESTICKOALA_HPP
