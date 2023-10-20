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
        int k = fork(), exitstatus;
        if (k == 0) {
            std::vector<char *> argv;
            processArgs(cmd, args, argv);
            execvp(cmd.c_str(), argv.data());
            exit(INT32_MAX);
        }
        wait(&exitstatus);
        if (WEXITSTATUS(exitstatus) == 255) {
            std::cout << "Esse comando nao existe!\n";
            return 1;
        }
        std::cout << "\n\n    Codigo de saida: " << WEXITSTATUS(exitstatus);
        return 0;
    }

    void Command::processArgs(std::string& cmd, std::vector<std::string>& args, std::vector<char *>& argv) {
        argv.push_back((char *) cmd.c_str());
        for (int i = 0; i < args.size(); i++) {
            argv.push_back((char *) args.at(i).c_str());
        }
        argv.push_back(nullptr);
    }

}