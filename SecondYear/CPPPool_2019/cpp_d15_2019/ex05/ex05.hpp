/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/29
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef EX05_HPP
#define EX05_HPP

#include <vector>
#include <exception>
#include <string>
#include <sstream>
#include <cstring>
#include <deque>

template<typename T>
class array
{
public:
    array() {}
    array(unsigned int size) { _array.resize(size); }

    array(const array & arr)
        : _array { arr.getArray() } {}

    array & operator=(const array & arr)
    {
        _array = arr.getArray();
        return *this;
    }

    template<typename U>
    array<U> convertTo(U (*func)(const T & nb))
    {
        array<U> arr(size());
        for (size_t i = 0; i < size(); ++i)
            arr[i] = func(_array[i]);
        return arr;
    }

    std::string display(const T & ite) const
    {
        std::ostringstream os;
        os << ite;
        return os.str();
    }

    void dump() const
    {
        std::cout << "[";
        for (auto ite = _array.begin(); ite != _array.end();)
        {
            std::cout << display(*ite);
            ++ite;
            if (ite != _array.end())
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

    T operator[](const unsigned int index) const
    {
        if (index >= _array.size())
            throw std::exception();
        return _array.at(index);
    }

    T & operator[](const unsigned int index)
    {
        if (index >= _array.size())
        {
            _array.resize(index + 1);
            return _array.at(index);
        }
        return _array.at(index);
    }

    size_t size() const { return _array.size(); }

    std::vector<T> getArray() const { return _array; }

public:
    std::vector<T> _array;
};


template<>
class array<bool>
{
public:
    array() {}
    array(unsigned int size) { _array.resize(size); }

    array(const array & arr)
        : _array { arr.getArray() } {}

    array & operator=(const array & arr)
    {
        _array = arr.getArray();
        return *this;
    }

    template<typename U>
    array<U> convertTo(U (*func)(const bool & nb))
    {
        array<U> arr(size());
        for (size_t i = 0; i < size(); ++i)
            arr[i] = func(_array[i]);
        return arr;
    }

    std::string display(const bool & ite) const
    {
        if (ite)
            return "true";
        return "false";
    }

    void dump() const
    {
        std::cout << "[";
        for (auto ite = _array.begin(); ite != _array.end();)
        {
            std::cout << display(*ite);
            ++ite;
            if (ite != _array.end())
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

    bool operator[](const unsigned int index) const
    {
        if (index >= _array.size())
            throw std::exception();
        return _array.at(index);
    }

    bool & operator[](const unsigned int index)
    {
        if (index >= _array.size())
        {
            _array.resize(index + 1);
            return _array.at(index);
        }
        return _array.at(index);
    }

    size_t size() const { return _array.size(); }

    std::deque<bool> getArray() const { return _array; }

public:
    std::deque<bool> _array;
};

#endif // EX05_HPP
