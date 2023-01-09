/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** project
*/

#ifndef PROJECT_HPP_
#define PROJECT_HPP_

#include <thread>

class project {
    public:
        project();
        ~project();
        void createThread();
    protected:
    private:
        std::thread t;
};

#endif /* !PROJECT_HPP_ */
