#include "../includes/Message.hpp"
#include "../includes/ft_irc.hpp"

std::vector<std::string> ft_split_message(std::string str)
{
    std::vector<std::string> msg_list;
    size_t position = 0;
    size_t startpoint = 0;

    while (position != std::string::npos)
    {
        position = str.find("\r\n", position);
        std::cout << "position - startpoint = " << position - startpoint << std::endl;
        if (position - startpoint > 0)
            msg_list.push_back(str.substr(startpoint, position - startpoint));
        if (position != std::string::npos)
        {
            position += 2;
            startpoint = position;
        }
    }
    return (msg_list);
}

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