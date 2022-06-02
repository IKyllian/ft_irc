#include "../../includes/Server.hpp"
#include "../../includes/ft_irc.hpp"

void    Server::command_WHO(Client &sender, Message &msg)
{
    (void)sender;
    std::cout << "nb parameter WHO = " << msg.get_nb_parameter() << std::endl;
    if (msg.get_nb_parameter() != 1)
    {
        
    }
}