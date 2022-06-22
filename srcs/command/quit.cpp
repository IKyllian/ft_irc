#include "../../includes/Server.hpp"
#include "../../includes/ft_irc.hpp"

void Server::command_QUIT(Client &sender, Message &msg)
{
    std::string quit_msg;
    std::string quit_channel;
    Message tmp = msg;
    tmp.get_tab_parameter().clear();

    if (msg.get_nb_parameter() < 1)
        quit_msg = "";
    else
        quit_msg = msg.get_parameter();
    for (size_t i = 0; i < get_clients().size(); i++)
        send_message(*get_clients()[i], ":" + sender.get_fullidentity() + " QUIT: " + quit_msg);
    std::cout << "channel size = " << sender.get_channel().size() << std::endl;
    for (size_t i = 0; i < sender.get_channel().size(); i++)
    {
        // std::cout << "channel names = " << sender.get_channel()[i]->get_name() << std::endl;
        if (i + 1 != sender.get_channel().size())
            quit_channel = quit_channel + (&sender)->get_channel()[i]->get_name() +  ",";
        else
            quit_channel = quit_channel + (&sender)->get_channel()[i]->get_name();
    }
    std::cout << "quit_channel = " << quit_channel << std::endl;
    tmp.set_parameter(quit_channel);
    ft_split_parameter(tmp);
    std::cout << "tmp = " << tmp.get_tab_parameter()[0] << std::endl;
    command_PART(&sender, tmp);
}