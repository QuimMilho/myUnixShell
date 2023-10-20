#pragma once
#include "pch.hpp"

namespace Milho {

    struct Command {
        static int execute(std::string& cmd, std::vector<std::string>& args);
        static void registerCommands();
        static void read(std::string& cmd, std::vector<std::string>& args);

    protected:
        Command() = default;

        virtual int executeCommand(std::string& cmd, std::vector<std::string>& args) = 0;
        
    private:
        inline static std::unordered_map<std::string, std::shared_ptr<Command>> commands = {};

        static int executeDefault(std::string& cmd, std::vector<std::string>& args);
        static void processArgs(std::string& cmd, std::vector<std::string>& args, std::vector<char *>& argv);

        void registerCommand(const char* name);
        
    };

}