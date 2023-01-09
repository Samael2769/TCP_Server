/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Object
*/

#include "Object.hpp"

Object::Object()
{
    entier = 10;
}

Object::~Object()
{
}

void Object::printValue()
{
    std::cout << entier << std::endl;
}

void Object::addValue(int val)
{
    entier += val;
}