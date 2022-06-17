#include "../../includes/Server.hpp"
#include "../../includes/ft_irc.hpp"

void Server::command_WHOIS(Client &sender, Message &msg)
{
    if (msg.get_nb_parameter() < 1)
    {
        send_message(sender, build_response(401, sender, sender, NULL, &msg));
        return ;
    }
    else
    {
        std::cout << "_clients.size() = " << _clients.size() << std::endl; 
        for (size_t i = 0; i < _clients.size(); i++)
        {
            if (_clients[i]->get_nickname() == msg.get_tab_parameter()[0])
            {
                send_message(sender, build_response(311, *_clients[i], sender, NULL, &msg));
                for (size_t j = 0; j < _clients[i]->get_channel().size(); j++)
                {
                    if (_clients[i]->get_channel()[j]->get_channel_modes().find("s") == std::string::npos && _clients[i]->get_user_modes().find("i") == std::string::npos)
                        send_message(sender, build_response(301, *_clients[i], sender, _clients[i]->get_channel()[j], &msg));
                }
                if (_clients[i]->get_user_modes().find("o") != std::string::npos)
                    send_message(sender, build_response(313, *_clients[i], sender, NULL, &msg));
                if (_clients[i]->get_away() == true)
                    send_message(sender, build_response(301, *_clients[i], sender, NULL, &msg));
                send_message(sender, build_response(318, sender, sender, NULL, &msg));
                return ;
            }
        }
        //send_message(*this, msg, "", build_response(431, sender, sender, NULL, &msg), "431");
        send_message(sender, build_response(431, sender, sender, NULL, &msg));
    }
}