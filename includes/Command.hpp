#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "ft_irc.hpp"

class Command
{
    
    public:
        Command();
        Command(std::string cname, std::string cinfo);
        ~Command();

        std::string get_command_name() const;
        std::string get_command_info() const;

        void set_command_name(std::string val);
        void set_command_info(std::string val);

    private:
        std::string _command_name;
        std::string _command_info;
    
};

#endif