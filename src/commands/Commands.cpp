#include "pch.hpp"

#include "commands/Commands.hpp"
#include "commands/CommandList.hpp"

namespace Milho {
    
    void Command::registerCommand(const char* name) {
        this->commands.insert(std::pair<std::string, std::shared_ptr<Command>>(name, this));
    }

    void Command::registerCommands() {
        (new Cmd_Goodbye)->registerCommand("goodbye");
        (new Cmd_MOTD)->registerCommand("motd");
        (new Cmd_Exit)->registerCommand("exit");
    }

    void Command::read(std::string& cmd, std::vector<std::string>& args) {
        std::string line, word;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        ss >> cmd;
        while (ss >> word) {
            args.push_back(word);
        }
    }

    int Command::execute(std::string& cmd, std::vector<std::string>& args) {
        try {
            std::shared_ptr<Command> command = commands.at(cmd);
            return command->executeCommand(cmd, args);
        } catch (std::exception& e) {
            Command::executeDefault(cmd, args);
            return 0;
        }
    }

    int Command::executeDefault(std::string& cmd, std::vector<std::string>& args) {
        return 0;
    }

}