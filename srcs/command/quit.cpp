#include "../../includes/Server.hpp"

void Server::command_QUIT(Client &sender, Message &msg)
{
    std::string quit_msg;
    std::string quit_channel;
    Message tmp = msg;
    tmp.get_tab_parameter().clear();
    int nb_chan = 0;

    if (msg.get_nb_parameter() < 1)
        quit_msg = "";
    else
        quit_msg = msg.get_parameter();
    for (size_t i = 0; i < get_clients().size(); i++)
    {
        if (msg.get_nb_parameter() > 0)
            send_message(*get_clients()[i], ":" + sender.get_fullidentity() + " ERROR :" + sender.get_nickname() + " is exiting the network with the message: \"QUIT: " + quit_msg + "\"");
        else
            send_message(*get_clients()[i], ":" + sender.get_fullidentity() + " ERROR :" + sender.get_nickname() + " is exiting the network");
    }
    for (size_t i = 0; i < sender.get_channel().size(); i++)
    {
        if (i + 1 != sender.get_channel().size())
            quit_channel = quit_channel + (&sender)->get_channel()[i]->get_name() +  ",";
        else
            quit_channel = quit_channel + (&sender)->get_channel()[i]->get_name();
        nb_chan++;
    }
    if (sender.get_channel().size() > 0)
    {
        tmp.set_parameter(quit_channel);
        ft_split_parameter(tmp);
        command_PART(&sender, tmp);
    }
}

void Server::command_QUIT(Client &sender)
{
    std::string quit_msg;
    std::string quit_channel;
    std::string quit = "QUIT";
    int nb_chan = 0;
    Message tmp;

    for (size_t i = 0; i < get_clients().size(); i++)
    {
        send_message(*get_clients()[i], ":" + sender.get_fullidentity() + " ERROR :" + sender.get_nickname() + " is exiting the network with the message: \"BIG CRASH NOOB\"");
    }
    for (size_t i = 0; i < sender.get_channel().size(); i++)
    {
        if (i + 1 != sender.get_channel().size())
            quit_channel = quit_channel + (&sender)->get_channel()[i]->get_name() +  ",";
        else
            quit_channel = quit_channel + (&sender)->get_channel()[i]->get_name();
        nb_chan++;
    }
    if (sender.get_channel().size() > 0)
    {
        tmp.set_command(quit);
        tmp.set_parameter(quit_channel);
        ft_split_parameter(tmp);
        command_PART(&sender, tmp);
    }
}