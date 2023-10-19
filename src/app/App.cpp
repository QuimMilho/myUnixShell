#include "pch.hpp"

#include "app/App.hpp"
#include "file/Files.hpp"
#include "commands/Commands.hpp"

namespace Milho {

    App::App() {
        App::instance = this;
    }

    void App::start() {
        int res = 0;
        load();

        Command::registerCommands();

        printMOTD();

        while (res >= 0) {
            std::string cmd;
            std::vector<std::string> args;
            
            printArrow();

            Command::read(cmd, args);

            printLines();

            res = Command::execute(cmd, args);

            if (res == -1)
                break;
        }

        printGoodbye();
        printLines();
    }

    void App::setGoodbye(std::string goodbye) {
        this->goodbye = goodbye;
    }

    void App::setMOTD(std::string motd) {
        this->motd = motd;
    }

    void App::printArrow() {
        std::cout << "\n\n\n        -->";
        std::cout.flush();
    }

    void App::printMOTD() {
        std::cout << "\n\n\n\n\n\n\n\n\n\n    " << this->motd << std::endl;
    }

    void App::printLines() {
        std::cout << "\n\n\n";
    }

    void App::printGoodbye() {
        std::cout << "    " << this->goodbye << std::endl;
    }

}