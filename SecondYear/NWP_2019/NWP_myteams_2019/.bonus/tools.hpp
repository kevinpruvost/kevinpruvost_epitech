/*
** A Kevin Pruvost's project, May 2020
** tools.cpp
** File description:
** tools
*/

#include "KVector.hpp"

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

KVector<std::string> splitString(const std::string & str, const std::string & delim = " ");