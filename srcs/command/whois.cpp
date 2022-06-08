#include "../../includes/Server.hpp"
#include "../../includes/ft_irc.hpp"

void Server::command_WHOIS(Client &sender, Message &msg)
{
    if (msg.set_nb_parameter < 1)
    {
        send_message(sender, ft_print_numerics(/*sender, */ 401) + "\n");
        return ;
    }
    else
    {
        for (size_t i = 0; i < this->_clients.size(); i++)
        {
            if (this->_client[i].get_nickname() == msg.get_tab_parameter()[0])
            {
                send_message(sender, ft_print_numerics(/*this->_clients[i], */ 311) + "\n");
                for (size_t j = 0; j < this->_client[i].get_channels().size(); j++)
                {
                    if (this->_client[i].get_channels()[j].get_channel_modes().find("s") == std::string::npos && this->_client[i].get_user_modes().find("i") == std::string::npos)
                        send_message(sender, ft_print_numerics(/*this->_client[i].get_channels()[j]*/ 319) + "\n");
                }
                if (this->_client[i].get_user_modes().find("o") != std::string::npos)
                    send_message(sender, ft_print_numerics(/*this->_clients[i]]*/ 313) + "\n");
                if (this->_client[i].get_away() == true)
                    send_message(sender, ft_print_numerics(/*this->_clients[i]*/ 301) + "\n");
                send_message(sender, ft_print_numerics(/*sender*/ 318) + "\n");
                return ;
            }
        }
        send_message(sender, ft_print_numerics(/*sender, */ 431) + "\n");
    }
    send_message(sender, ft_print_numerics(315) + "\n");
}