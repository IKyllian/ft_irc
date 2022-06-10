#include "../includes/Command.hpp"

Command::Command() {}
Command::Command(std::string cname, std::string cinfo): _command_name(cname), _command_info(cinfo) {}
Command::~Command() {}

std::string Command::get_command_name() const { return (_command_name); };
std::string Command::get_command_info() const { return (_command_info); };

void Command::set_command_name(std::string val)
{
    _command_name = val;
}

void Command::set_command_info(std::string val)
{
    _command_info = val;
}