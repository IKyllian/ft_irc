#include "../../includes/Server.hpp"
#include "../../includes/ft_irc.hpp"

bool	check_wildcards(Client &client, Message &msg)
{
	size_t  wildcard_pos;

	std::cout << "enter check wildcard" << std::endl;
	if (client.get_nickname() == msg.get_tab_parameter()[0] || client.get_realname() == msg.get_tab_parameter()[0])
		return (true);
	else if ((wildcard_pos = msg.get_tab_parameter()[0].find("*")) != std::string::npos)
	{
		std::cout << "wildcard = " << wildcard_pos << std::endl << "Size tab = " << msg.get_tab_parameter()[0].size() << std::endl;
		if (wildcard_pos == 0)
		{
			if (client.get_nickname().substr(client.get_nickname().size() - (msg.get_tab_parameter()[0].size()  - 1)) == msg.get_tab_parameter()[0].substr(1))
			{
				return (true);
			}
		}
		else if (wildcard_pos == msg.get_tab_parameter()[0].size() - 1)
		{
			if (client.get_nickname().substr(0, wildcard_pos) == msg.get_tab_parameter()[0].substr(0, wildcard_pos))
			{
				return (true);
			}
		}
		else
		{
			std::cout << "1: " <<  client.get_nickname().substr(0, wildcard_pos) << " = " << msg.get_tab_parameter()[0].substr(0, wildcard_pos) << std::endl << "2: " << client.get_nickname().substr(client.get_nickname().size() - (msg.get_tab_parameter()[0].size() - (wildcard_pos + 1))) << " = " << msg.get_tab_parameter()[0].substr(wildcard_pos + 1) << std::endl;
			if (client.get_nickname().substr(0, wildcard_pos) == msg.get_tab_parameter()[0].substr(0, wildcard_pos) && client.get_nickname().substr(client.get_nickname().size() - (msg.get_tab_parameter()[0].size() - (wildcard_pos + 1))) == msg.get_tab_parameter()[0].substr(wildcard_pos + 1))
			{
				return (true);
			}
		}
	}
	return (false);
}

bool	check_wildcards(Channel &channel, Message &msg)
{
	size_t  wildcard_pos;

	if (channel.get_name() == msg.get_tab_parameter()[0])
		return (true);
	else if ((wildcard_pos = msg.get_tab_parameter()[0].find("*")) != std::string::npos)
	{
		if (wildcard_pos == 0)
		{
			if (channel.get_name().substr(channel.get_name().size() - (msg.get_tab_parameter()[0].size()  - 1)) == msg.get_tab_parameter()[0].substr(1))
			{
				return (true);
			}
		}
		else if (wildcard_pos == msg.get_tab_parameter()[0].size() - 1)
		{
			if (channel.get_name().substr(0, wildcard_pos) == msg.get_tab_parameter()[0].substr(0, wildcard_pos))
			{
				return (true);
			}
		}
		else
		{
			std::cout << "1: " <<  channel.get_name().substr(0, wildcard_pos) << " = " << msg.get_tab_parameter()[0].substr(0, wildcard_pos) << std::endl << "2: " << channel.get_name().substr(channel.get_name().size() - (msg.get_tab_parameter()[0].size() - (wildcard_pos + 1))) << " = " << msg.get_tab_parameter()[0].substr(wildcard_pos + 1) << std::endl;
			if (channel.get_name().substr(0, wildcard_pos) == msg.get_tab_parameter()[0].substr(0, wildcard_pos) && channel.get_name().substr(channel.get_name().size() - (msg.get_tab_parameter()[0].size() - (wildcard_pos + 1))) == msg.get_tab_parameter()[0].substr(wildcard_pos + 1))
			{
				return (true);
			}
		}
	}
	return (false);
}

void	Server::command_WHO(Client &sender, Message &msg)
{
	bool channel_found = false;

	if (msg.get_nb_parameter() == 0 || (msg.get_nb_parameter() == 1 && (msg.get_tab_parameter()[0] == "0" || msg.get_tab_parameter()[0] == "*")))
	{
		for (size_t i = 0; i < this->_clients.size(); i++)
		{
			send_message(sender,":" +  sender.get_fullidentity() + " " + print_numerics(352, *_clients[i], sender, NULL, &msg));
		}
		send_message(sender,build_response(315, sender, sender, NULL, &msg));
	}
	else
	{
		for (size_t i = 0; i < this->get_channels().size(); i++)
		{
			if (check_wildcards(*this->get_channels()[i], msg))
			{
				std::map<Client*, std::string>::iterator it = this->get_channels()[i]->get_users().begin();
				for(; it != this->get_channels()[i]->get_users().end(); it++)
				{
					if (msg.get_nb_parameter() > 1 && msg.get_tab_parameter()[1] == "o")
					{
						if ((*it).first->get_user_modes().find("o"))
						{
							send_message(sender,":" +  sender.get_fullidentity() + " " + print_numerics(352, *(it->first), sender, get_channels()[i], &msg));
						}
					}
					else
					{
						send_message(sender,":" +  sender.get_fullidentity() + " " + print_numerics(352, *(it->first), sender, get_channels()[i], &msg));
					}
				}
				channel_found = true;
				send_message(sender,":" +  sender.get_fullidentity() + " " + print_numerics(315, sender, sender, get_channels()[i], &msg));
				return ;
			}
		}
		for (size_t i = 0; i < this->_clients.size(); i++)
		{
			if (this->_clients[i]->get_user_modes().find("i") == std::string::npos)
			{
				if (check_wildcards(*this->_clients[i], msg))
				{
					if (sender.get_channel().size() > 0)
						send_message(sender,build_response(352, *this->_clients[i], sender, sender.get_channel()[0], &msg));
					else
						send_message(sender,build_response(352, *this->_clients[i], sender, NULL, &msg));
				}
			}
		}
		send_message(sender,":" +  sender.get_fullidentity() + " " + print_numerics(315, sender, sender, NULL, &msg));
	}
}