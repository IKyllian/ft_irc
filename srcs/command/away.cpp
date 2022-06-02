#include "../../includes/Server.hpp"
#include "../../includes/ft_irc.hpp"

void    Server::command_AWAY(Client &sender, Message &msg)
{
    if (msg.get_nb_parameter() == 0)
    {
        send_message(*this, sender, ft_print_numerics(305), 305);
        sender.set_away(false);
    }
    else
    {
        send_message(*this, sender, ft_print_numerics(306), 306);
        sender.set_away(true);
        sender.set_away_msg(msg.get_parameter());
    }
}