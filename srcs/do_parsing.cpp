#include "../includes/ft_irc.hpp"

void do_parsing(Server &server, Client& expediteur, std::string message)
{
    std::vector<Message*> msg;
    std::vector<std::string> msg_list;

    msg_list = ft_split_message(message);
    for (size_t i = 0; i < msg_list.size(); i++)
        msg.push_back(ft_create_message(msg_list[i]));
    for (size_t i = 0; i < msg.size(); i++)
    {
        std::map<std::string, >;
    }

    for (size_t i = 0; i < msg_list.size(); i++)
        delete msg[i];
    return;
}