/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** client
*/

#include "client.hpp"

client::client(std::string ip, int port, int type)
{
    client_init(ip, port, type);
    fprintf(stderr, "client connected\n");
    if (client_run() != 0)
        throw std::runtime_error("client run error");
    close(this->sock);
}

void client::client_init(std::string ip, int port, int type)
{
    this->type = type;
    this->ip = ip;
    this->port = port;

    if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        exit(84);
    this->address.sin_family = AF_INET;
    this->address.sin_port = htons(this->port);
    this->address_len = sizeof(this->address);
    if (connect(this->sock, (struct sockaddr *)&this->address, this->address_len) < 0)
        exit(84);
    this->server_buffer = "";
    this->server_valread = 0;
    this->client_buffer = "";
    this->client_valread = 0;
}

int client::read_user()
{
    if (FD_ISSET(STDIN_FILENO, &this->readfds)) {
        this->client_valread = receive_msg(STDIN_FILENO, &this->client_buffer);
        switch (this->client_valread) {
            case -1:
                return -1;
            default:
                if (send_msg(this->sock, this->client_buffer) == -1)
                    return -1;
                break;
        }
        this->client_buffer = "";
    }
    return 0;
}

int client::read_server()
{
    if (FD_ISSET(this->sock, &this->readfds)) {
        if ((this->server_valread = receive_msg(this->sock, &this->server_buffer)) < 0)
            return -1;
        std::cout << this->server_buffer << std::endl;
        this->server_buffer = "";
    }
    return 0;
}

int client::client_run()
{
    int activity = 0;

    while (1) {
        FD_ZERO(&this->readfds);
        FD_SET(STDIN_FILENO, &this->readfds);
        FD_SET(this->sock, &this->readfds);
        if ((activity = select(this->sock + 1, &this->readfds, NULL, NULL, NULL)) < 0)
            return -1;
        if (read_server() == -1)
            return -1;
        if (this->type == 0)
            if (read_user() == -1)
                return -1;
    }
    return 0;
}

int client::receive_msg(int socket, std::string *buffer)
{
    int valread = 0;
    char buffers[1024] = {0};

    if ((valread = read(socket, buffers, 1024)) < 0)
        return -1;
    *buffer = buffers;
    return valread;
}

int client::send_msg(int socket, std::string buffer)
{
    int valread = 0;
    if ((valread = write(socket, buffer.c_str(), strlen(buffer.c_str())) < 0))
        return -1;
    return valread;
}