/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** server
*/

#include "server.hpp"

int server::server_create(int port)
{
    this->port = port;

    if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        exit(84);
    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = INADDR_ANY;
    this->address.sin_port = htons(port);
    this->address_len = sizeof(this->address);
    if (bind(this->sock, (struct sockaddr *)&this->address, this->address_len) < 0)
        exit(84);
    if (listen(this->sock, 3) < 0)
        exit(84);
    this->nb_clients = 0;
    this->max_clients = MAX_CLIENT;
    this->name = NAME;
    return 0;
}

int server::server_check_talking()
{
    for (int i = 0; i < clients.size(); ++i) {
        if (clients[i].socket > 0)
            FD_SET(clients[i].socket, &this->readfds);
        if (clients[i].socket > this->talk_sock)
            this->talk_sock = clients[i].socket;
    }
    return 0;
}

std::vector<std::string> split_string(std::string str, char c = ' ')
{
    std::vector<std::string> words;
    std::string word = "";

    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == c) {
            words.push_back(word);
            word = "";
        } else
            word += str[i];
    }
    words.push_back(word);
    return words;
}

int server::server_cli_handling()
{
    for (int i = 0; i < clients.size(); ++i) {
        if (FD_ISSET(clients[i].socket, &this->readfds)) {
            clients[i].valread = receive_msg(clients[i].socket, &clients[i].buffer);
            switch (clients[i].valread) {
                case -1:
                    return -1;
                case 0:
                    close(clients[i].socket);
                    clients[i].socket = -1;
                    break;
                default:
                    clients[i].buffer = clients[i].buffer.substr(0, clients[i].buffer.size() - 1);
                    std::cout << "client: " << clients[i].socket << " = " << clients[i].buffer << std::endl;
                    _handler(clients[i].socket, &clients[i].buffer);
                    break;
            }
            clients[i].buffer = "";
        }
    }
    return 0;
}

int server::server_activity()
{
    int entering_socket = -1;

    if (FD_ISSET(this->sock, &this->readfds)) {
        if ((entering_socket = accept(this->sock, (struct sockaddr *)&this->address, &this->address_len)) < 0)
            return -1;
        client_t client;
        client.socket = entering_socket;
        client.buffer = "";
        client.valread = 0;
        clients.push_back(client);
        this->nb_clients++;
        send_msg(entering_socket, "Welcome to the server\n");
    }
    if (server_cli_handling() != 0)
        return -1;
    return 0;
}

int server::server_run()
{
    int activity = 0;

    std::cout << "Server running " << this->name << " on port: " << this->port << std::endl;
    while(1) {
        FD_ZERO(&this->readfds);
        FD_SET(this->sock, &this->readfds);
        this->talk_sock = this->sock;
        if (server_check_talking() != 0)
            return -1;
        if ((activity = select(this->talk_sock + 1, &this->readfds, NULL, NULL, NULL)) < 0 && errno != EINTR)
            return -1;
        if (server_activity() != 0)
            return -1;
    }
    return 0;
}

server::server(int port, void (*handler)(int socket, void * data))
{
    server_create(port);
    _handler = handler;
    std::cout << "Server created " << this->name << std::endl;
    if (server_run() != 0)
        throw std::runtime_error("Server run failed");
}

int server::send_msg(int sock, std::string buffer)
{
    int valread = 0;
    if ((valread = write(sock, buffer.c_str(), strlen(buffer.c_str())) < 0))
        return -1;
    return valread;
}

int server::receive_msg(int sock, std::string * buffer)
{
    int valread = 0;
    char buffers[1024] = {0};

    if ((valread = read(sock, buffers, 1024)) < 0)
        return -1;
    *buffer = buffers;
    return valread;
}