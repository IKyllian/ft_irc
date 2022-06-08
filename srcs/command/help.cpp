#include "../../includes/Server.hpp"
#include "../../includes/ft_irc.hpp"

void Server::command_HELP(Client &sender, Message &msg)
{
    if (msg.set_nb_parameter < 1)
    {
        for (size_t i = 0; i < this->_commands.size(); i++)
        {
            //  Modification possible selon le call de ft_print_numerics (Le help est que sur une ligne pour l'instant)
            send_message(sender, ft_print_numerics(/*this->_client[i].get_channels()[j]*/ 704) + "\n");
            send_message(sender, ft_print_numerics(/*this->_client[i].get_channels()[j]*/ 706) + "\n");

        }
        return;
    }
    else
    {
        for (size_t i = 0; i < this->_commands.size(); i++)
        {
            if (i < this->_commands[i].get_command_name() == msg.get_tab_parameter()[0])
            {
                //  Modification possible selon le call de ft_print_numerics (Le help est que sur une ligne pour l'instant)
                send_message(sender, ft_print_numerics(/*this->_client[i].get_channels()[j]*/ 704) + "\n");
                send_message(sender, ft_print_numerics(/*this->_client[i].get_channels()[j]*/ 706) + "\n");
                return ;
            }
        }
        send_message(sender, ft_print_numerics(/*sender, */ 524) + "\n");
    }
}