#pragma once

#include "commands/Commands.hpp"
#include "app/App.hpp"
#include "file/Files.hpp"

namespace Milho {
    
    struct Cmd_MOTD : public Command {
        inline int executeCommand(std::string& cmd, std::vector<std::string>& args) override {
            std::stringstream ss;
            for (int i = 0; i < args.size(); i++) {
                ss << args.at(i) << " ";
            }
            GET_APP_INSTANCE.setMOTD(ss.str());
            save();
            std::cout << "MOTD alterada!" << std::endl;
            return 0;
        }

    };

    struct Cmd_Goodbye : public Command {
        inline int executeCommand(std::string& cmd, std::vector<std::string>& args) override {
            std::stringstream ss;
            for (int i = 0; i < args.size(); i++) {
                ss << args.at(i) << " ";
            }
            GET_APP_INSTANCE.setGoodbye(ss.str());
            save();
            std::cout << "Mensagem de adeus alterada!" << std::endl;
            return 0;
        }

    };

    struct Cmd_Exit : public Command {
        inline int executeCommand(std::string& cmd, std::vector<std::string>& args) override {
            return -1;
        }

    };

}