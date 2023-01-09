/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** project
*/

#include "project.hpp"
#include <iostream>
#include "Object.hpp"

project::project()
{

}

project::~project()
{
    
}

void hello()
{
    std::cout << "Hello World" << std::endl;
}

void count()
{
    for (int i = 0; i < 1000000; i++)
        std::cout << i << std::endl;
}

void project::createThread()
{
    Object b;
    t = std::thread(&Object::addValue, &b, 10);
    t.join();
    b.printValue();
}