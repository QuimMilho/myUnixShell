#pragma once

#include "pch.hpp"

#include "myshell.hpp"

#define GET_APP_INSTANCE Milho::App::getInstance()

namespace Milho {
    
    struct App {
        App();

        void start();

        inline static App& getInstance() {
            return *instance;
        }

        void setMOTD(std::string motd);

        void setGoodbye(std::string goodbye);

        inline std::string getMOTD() {
            return motd;
        }

        inline std::string getGoodbye() {
            return goodbye;
        }
        
    private:
        inline static App* instance = nullptr;
        std::string motd, goodbye;

        void printMOTD();
        void printGoodbye();
        void printArrow();
        void printLines();

    };

}