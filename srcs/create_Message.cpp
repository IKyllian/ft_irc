#include "../includes/Message.hpp"
#include "../includes/ft_irc.hpp"

Message ft_create_message(std::string str)
{
    std::string delimiter = " ";
    std::string str_to_pass;
    int position = 0;
    int startpoint = 0;

    Message msg;

    if (str[0] == ':')
    {
        position = str.find(' ', position);
        str_to_pass = str.substr(startpoint, position - startpoint);
        msg.set_prefix(str_to_pass);
        position++;
        startpoint = position;
    }
    position = str.find(' ', position);
    str_to_pass = str.substr(startpoint, position - startpoint);
    msg.set_command(str_to_pass);
    position++;
    startpoint = position;

    position = str.length();
    str_to_pass = str.substr(startpoint, position - startpoint);
    msg.set_parameter(str_to_pass);
    position++;
    startpoint = position;    

    return (msg);
}