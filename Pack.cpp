#include <iostream>
#include <string>
#include <sstream>
#include "Pack.hpp"

Pack::Pack()
{
    first = 0;
    second = 0;
    third = 0;
}

Pack::Pack(int _first, int _second, int _third) 
{
    first = _first;
    second = _second;
    third = _third;
}
Pack::Pack(
    int _first, bool _first_negated, 
    int _second, bool _second_negated, 
    int _third, bool _third_negated
) {
    first = _first;
    second = _second;
    third = _third;
    first_isNegated = _first_negated;
    second_isNegated = _second_negated;
    third_isNegated = _third_negated;
}

Pack::~Pack() { }

std::string Pack::toString() 
{
    std::string fn = first_isNegated ? "-" : "";
    std::string sn = second_isNegated ? "-" : "";
    std::string tn = third_isNegated ? "-" : "";
    return "Pack: " + fn + std::to_string(first) + ", " + sn + std::to_string(second) + ", " + tn + std::to_string(third);
}

int Pack::getFirst()
{
    return first;
}


int Pack::getSecond()
{
    return second;
}


int Pack::getThird()
{
    return third;
}

bool Pack::first_getIsNegated()
{
    return first_isNegated;
}

bool Pack::second_getIsNegated()
{
    return second_isNegated;
}

bool Pack::third_getIsNegated()
{
    return third_isNegated;
}

void Pack::first_setIsNegated(bool _first)
{
    first_isNegated = _first;
}


void Pack::second_setIsNegated(bool _second)
{
    second_isNegated = _second;
}


void Pack::third_setIsNegated(bool _third)
{
    first_isNegated = _third;
}

void Pack::setFirst(int _first)
{
    first = _first;
}


void Pack::setSecond(int _second)
{
    second = _second;
}


void Pack::setThird(int _third)
{
    third = _third;
}
