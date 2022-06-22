#include "../includes/Message.hpp"
#include "../includes/ft_irc.hpp"

std::vector<std::string> ft_split_message(std::string str)
{
    std::vector<std::string> msg_list;
    size_t old_position;
    size_t position = 0;
    size_t startpoint = 0;
    std::string tmp;

    while (position != std::string::npos)
    {
        old_position = position;
        position = str.find("\r\n", position);
        if (position - startpoint > 0)
        {
            tmp = str.substr(startpoint, position);
            std::string tmp = str.substr(startpoint, position);
            if (position == std::string::npos)
            {
                if (str.substr(startpoint, position).size() <= 0)
                    break;
                msg_list.push_back(str.substr(startpoint, position));
                break;
            }
            msg_list.push_back(str.substr(startpoint, position - startpoint));
        }
        if (position != std::string::npos)
        {
            position += 2;
            startpoint = position;
        }
    }
    return (msg_list);
}

void ft_split_parameter(Message &msg)
{
    size_t position = 0;
    size_t startpoint = 0;
    int nb = 0;

    while (position != std::string::npos)
    {
        position = msg.get_parameter().find(" ", position);
        if (position - startpoint > 0)
        {
            msg.get_tab_parameter().push_back(msg.get_parameter().substr(startpoint, position - startpoint));
            nb++;
        }
        if (position != std::string::npos)
        {
            position++;
            startpoint = position;
        }
    }
    msg.set_nb_parameter(nb);
    return ;
}

Message *ft_create_message(std::string str)
{
    Message *msg = new Message;
    std::string delimiter = " ";
    std::string str_to_pass;
    size_t position = 0;
    size_t startpoint = 0;
    
    if (str[0] == ':')
    {
        position = str.find(' ', position);
        str_to_pass = str.substr(startpoint, position - startpoint);
        msg->set_prefix(str_to_pass);
        position++;
        startpoint = position;
    }
    position = str.find(' ', position);
    str_to_pass = str.substr(startpoint, position - startpoint);
    msg->set_command(str_to_pass);
    msg->set_nb_parameter(0);
    if (position != std::string::npos)
    {
        position++;
        startpoint = position;
        position = str.length();
        str_to_pass = str.substr(startpoint, position - startpoint);
        msg->set_parameter(str_to_pass);
        position++;
        startpoint = position;
        ft_split_parameter(*msg);
    }
    return (msg);
}

std::string build_command_message(std::string sender, std::string receiver, std::string target, std::string command, std::vector<std::string> message, std::string params) {
    std::string answer;

	answer += ":";
	answer += sender;
    answer += " ";
	answer += command;
    answer += " ";
    if (command == "INVITE") {
	    answer += receiver;
        answer += " ";
    }
	answer += target;
    if (command == "PRIVMSG" || command == "NOTICE") {
        answer += " ";
        for (size_t i = 1; i < message.size(); i++) {
            answer += message[i];
            if (i + 1 < message.size())
                answer += " ";
        }
    } else if (command == "MODE") {
        answer += " ";
        answer += receiver; //receiver = mode
        answer += " ";
        answer += params;
    } else if (command == "KICK") {
        answer += " ";
        answer += receiver;
    }
    return answer;
}