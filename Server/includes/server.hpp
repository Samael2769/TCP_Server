/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/uio.h>

#include <vector>
#include <map>
#include <thread>

#define MAX_CLIENT 30
#define NAME "SM_server"

class server {
    public:
        server(int port, void (*handler)(int socket, void * data));
        ~server();
        int server_create(int port);
        int server_run();
        int server_cli_handling();
        int server_activity();
        int server_check_talking();
        int send_msg(int fd, std::string buffer);
        int receive_msg(int fd, std::string *buffer);

        typedef struct client_s {
            int socket;
            std::string buffer;
            int valread;
        } client_t;

    protected:
    private:
        int port;
        int sock;
        socklen_t address_len;
        struct sockaddr_in address;
        std::vector<client_t> clients;
        int max_clients;
        std::string name;
        int talk_sock;
        int nb_clients;
        std::map<std::string, void (server::*)(int, std::vector<std::string>)> commands;
        std::vector<std::pair<client_t, client_t>> gamers;
        fd_set readfds;
        void (*_handler)(int socket, void * data);
};

#endif /* !SERVER_HPP_ */
