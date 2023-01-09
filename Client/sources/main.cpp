/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** main
*/

#include <iostream>
#include "client.hpp"

int main(int ac, char **av)
{
    client *c = new client(av[1], atoi(av[2]), atoi(av[3]));
    return 0;
}