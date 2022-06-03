#include "../../includes/Server.hpp"
#include "../../includes/ft_irc.hpp"

void    Server::command_WHO(Client &sender, Message &msg)
{
    bool same_channel = false;

    std::cout << "nb parameter = " << msg.get_nb_parameter() << std::endl;
    std::cout << "nb client = " << this->_clients.size() << std::endl;
    if (msg.get_nb_parameter() == 0)
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
        for (size_t i = 0; i < this->_clients.size(); i++)
        {
            if (this->_clients[i].get_user_modes().find("i") == std::string::npos)
            {
                if (this->_clients[i].get_nickname().find(msg.get_tab_parameter()[0]) != std::string::npos)
                    send_message(sender, ft_print_numerics(/*this->_clients[i], */352) + "\n");
            }
        }
        send_message(sender, ft_print_numerics(315) + "\n");
    }
}