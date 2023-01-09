/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** main
*/

#include <iostream>
#include "server.hpp"

void handler(int socket, void * data)
{
    std::cout << "Handler called with socket " << socket;
    std::string str = *(std::string *)data;
    std::cout << " Data is " << str << std::endl;
}

int main(int ac, char **av)
{
    server *s = new server(atoi(av[1]), &handler);
    return 0;
}