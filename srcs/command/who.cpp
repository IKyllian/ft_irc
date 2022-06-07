#include "../../includes/Server.hpp"
#include "../../includes/ft_irc.hpp"

bool    check_wildcards(Client &client, Message &msg)
{
    size_t  wildcard_pos;

    std::cout << "enter check wildcard" << std::endl;
    if (client.get_nickname() == msg.get_tab_parameter()[0] || client.get_realname() == msg.get_tab_parameter()[0])
        return (true);
    else if ((wildcard_pos = msg.get_tab_parameter()[0].find("*")) != std::string::npos)
    {
        std::cout << "wildcard = " << wildcard_pos << std::endl << "Size tab = " << msg.get_tab_parameter()[0].size() << std::endl;
        if (wildcard_pos == 0)
        {
            if (client.get_nickname().substr(client.get_nickname().size() - (msg.get_tab_parameter()[0].size()  - 1)) == msg.get_tab_parameter()[0].substr(1))
            {
                return (true);
            }
        }
        else if (wildcard_pos == msg.get_tab_parameter()[0].size() - 1)
        {
            if (client.get_nickname().substr(0, wildcard_pos) == msg.get_tab_parameter()[0].substr(0, wildcard_pos))
            {
                return (true);
            }
        }
        else
        {
            std::cout << "1: " <<  client.get_nickname().substr(0, wildcard_pos) << " = " << msg.get_tab_parameter()[0].substr(0, wildcard_pos) << std::endl << "2: " << client.get_nickname().substr(client.get_nickname().size() - (msg.get_tab_parameter()[0].size() - (wildcard_pos + 1))) << " = " << msg.get_tab_parameter()[0].substr(wildcard_pos + 1) << std::endl;
            if (client.get_nickname().substr(0, wildcard_pos) == msg.get_tab_parameter()[0].substr(0, wildcard_pos) && client.get_nickname().substr(client.get_nickname().size() - (msg.get_tab_parameter()[0].size() - (wildcard_pos + 1))) == msg.get_tab_parameter()[0].substr(wildcard_pos + 1))
            {
                return (true);
            }
        }
    }
    return (false);
}

void    Server::command_WHO(Client &sender, Message &msg)
{
    bool same_channel = false;

    std::cout << "nb parameter = " << msg.get_nb_parameter() << std::endl;
    std::cout << "nb client = " << this->_clients.size() << std::endl;
    if (msg.get_nb_parameter() == 0 || (msg.get_nb_parameter() == 1 && (msg.get_tab_parameter()[0] == "0" || msg.get_tab_parameter()[0] == "*")))
    {
        for (size_t i = 0; i < this->_clients.size(); i++)
        {
            if (this->_clients[i].get_user_modes().find("i") == std::string::npos)
            {
                for (size_t j = 0; j < sender.get_channel().size(); j++)
                {
                    for (size_t k = 0; k < this->_clients[i].get_channel().size(); k++)
                    {
                        if (sender.get_channel()[j] == this->_clients[i].get_channel()[k])
                        {
                            same_channel = true;
                            break;
                        }
                    }
                    if (same_channel == true)
                        break;
                }
                if (same_channel == false)
                    send_message(sender, ft_print_numerics(/*this->_clients[i], */352) + "\n");
            }
        }
        send_message(sender, ft_print_numerics(315) + "\n");
    }
    else
    {
        std::cout << "nb parameter = " << msg.get_nb_parameter() << std::endl;
        for (size_t i = 0; i < this->get_channels().size(); i++)
        {
            if (this->get_channels()[i].get_name() == msg.get_tab_parameter()[0]) //Check possible wildcards
            {
                std::map<Client*, std::string>::iterator it = this->get_channels()[i].get_users().begin();
                for(; it != this->get_channels()[i].get_users().end(); it++)
                {
                    if (msg.get_nb_parameter() > 1 && msg.get_tab_parameter()[1] == "o")
                    {
                        if ((*it).first->get_user_modes().find("o"))
                            send_message(sender, ft_print_numerics(/*(*it).first), */352) + "\n");
                    }
                    else
                        send_message(sender, ft_print_numerics(/*(*it).first), */352) + "\n");
                }
                send_message(sender, ft_print_numerics(315) + "\n");
                return ;
            }
        }
        std::cout << "no Channel found" << std::endl;
        for (size_t i = 0; i < this->_clients.size(); i++)
        {
            if (this->_clients[i].get_user_modes().find("i") == std::string::npos)
            {
                //  Potentiellement d'autres truc (users' host, server, realname and nickname)
                if (check_wildcards(this->_clients[i], msg))               //Check possible wildcards
                    send_message(sender, ft_print_numerics(/*this->_clients[i], */352) + "\n");
            }
        }
        send_message(sender, ft_print_numerics(315) + "\n");
    }
}