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
            // for (unsigned int i = 0; i < tmp.length(); i++)
            // {
                // std::cout << "i: " << i << " : " << tmp[i] << " : " << (int) tmp[i] << std::endl; 
            // }
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

static void ft_split_parameter(Message &msg)
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
    // std::cout << "Split function " << msg.get_nb_parameter() << std::endl;

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
    if (position != std::string::npos)
    {
        position++;
        startpoint = position;
        position = str.length();
        str_to_pass = str.substr(startpoint, position - startpoint);
        std::cout << str_to_pass << std::endl;
        msg->set_parameter(str_to_pass);
        position++;
        startpoint = position;
        ft_split_parameter(*msg);
    }
    return (msg);
}