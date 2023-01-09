/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Object
*/

#pragma once
#include <iostream>

class Object {
    public:
        Object();
        ~Object();
        void printValue();
        void addValue(int val);

    protected:
    private:
        int entier;
};
