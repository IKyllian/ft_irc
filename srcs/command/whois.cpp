#include "../../includes/Server.hpp"
#include "../../includes/ft_irc.hpp"

void Server::command_WHOIS(Client &sender, Message &msg)
{
    if (msg.get_nb_parameter() < 1)
    {
        send_message(sender, ft_print_numerics(/*sender, */ 401) + "\n");
        return ;
    }
    else
    {
        for (size_t i = 0; i < _clients.size(); i++)
        {
            if (_clients[i].get_nickname() == msg.get_tab_parameter()[0])
            {
                send_message(sender, print_numerics(311, _clients[i], sender, NULL, &msg) + "\n");
                for (size_t j = 0; j < _clients[i].get_channel().size(); j++)
                {
                    if (_clients[i].get_channel()[j]->get_channel_modes().find("s") == std::string::npos && _clients[i].get_user_modes().find("i") == std::string::npos)
                        send_message(sender, print_numerics(301, _clients[i], sender, _clients[i].get_channel()[j], &msg) + "\n");
                }
                if (_clients[i].get_user_modes().find("o") != std::string::npos)
                    send_message(sender, print_numerics(313, _clients[i], sender, NULL, &msg) + "\n");
                if (_clients[i].get_away() == true)
                    send_message(sender, print_numerics(301, _clients[i], sender, NULL, &msg) + "\n");
                send_message(sender, print_numerics(318, sender, sender, NULL, &msg) + "\n");
                return ;
            }
        }
        //send_message(*this, msg, "", print_numerics(431, sender, sender, NULL, &msg) + "\n", "431");
        send_message(sender, print_numerics(431, sender, sender, NULL, &msg) + "\n");
    }
}