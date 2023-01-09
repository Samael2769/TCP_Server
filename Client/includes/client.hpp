/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

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

class client {
    public:
        client(std::string ip, int port, int type);
        ~client();
        void client_init(std::string ip, int port, int type);
        int read_user();
        int read_server();
        int client_run();
        int receive_msg(int fd, std::string *buffer);
        int send_msg(int fd, std::string buffer);
    protected:
    private:
        int type;
        int sock;
        std::string ip;
        int port;
        struct sockaddr_in address;
        socklen_t address_len;
        std::string server_buffer;
        int server_valread;
        std::string client_buffer;
        int client_valread;
        fd_set readfds;
        fd_set writefds;
        fd_set exceptfds;
        struct timeval timeout;
};

#endif /* !CLIENT_HPP_ */
