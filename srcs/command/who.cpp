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

	std::cout << "enter check wildcard" << std::endl;
	std::cout << "channel name. = " << channel.get_name() << std::endl;
	if (channel.get_name() == msg.get_tab_parameter()[0])
		return (true);
	else if ((wildcard_pos = msg.get_tab_parameter()[0].find("*")) != std::string::npos)
	{
		std::cout << "wildcard = " << wildcard_pos << std::endl << "Size tab = " << msg.get_tab_parameter()[0].size() << std::endl;
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
	bool same_channel = false;
	bool channel_found = false;
	bool send_user = false;

	std::cout << "nb parameter = " << msg.get_nb_parameter() << std::endl;
	std::cout << "nb client = " << this->_clients.size() << std::endl;
	if (msg.get_nb_parameter() == 0 || (msg.get_nb_parameter() == 1 && (msg.get_tab_parameter()[0] == "0" || msg.get_tab_parameter()[0] == "*")))
	{
		for (size_t i = 0; i < this->_clients.size(); i++)
		{
			if (this->_clients[i].get_user_modes().find("i") == std::string::npos)
			{
				for (size_t j = 0; j < sender.get_channel().size(); j++)
				{
					for (size_t k = 0; k < this->_clients[i].get_channel().size(); k++)
					{
						if (sender.get_channel()[j] == this->_clients[i].get_channel()[k])
						{
							same_channel = true;
							break;
						}
					}
					if (same_channel == true)
						break;
				}
				if (same_channel == false)
				{
					send_message(sender, print_numerics(352, _clients[i], sender, NULL, &msg));
					send_user = true;
				}
			}
		}
		if (send_user == true)
			send_message(sender, print_numerics(315, sender, sender, NULL, &msg));
	}
	else
	{
		std::cout << "nb parameter = " << msg.get_nb_parameter() << std::endl;
		std::cout << "nb channels = " << this->get_channels().size() << std::endl;
		for (size_t i = 0; i < this->get_channels().size(); i++)
		{
			if (check_wildcards(this->get_channels()[i], msg)) //Check possible wildcards
			{
				std::cout << "found channel" << std::endl;
				std::map<Client*, std::string>::iterator it = this->get_channels()[i].get_users().begin();
				for(; it != this->get_channels()[i].get_users().end(); it++)
				{
					if (msg.get_nb_parameter() > 1 && msg.get_tab_parameter()[1] == "o")
					{
						if ((*it).first->get_user_modes().find("o"))
						{
							send_message(sender, print_numerics(352, *(it->first), sender, &get_channels()[i], &msg));
							send_user = true;
						}
					}
					else
					{
						send_message(sender, print_numerics(352, *(it->first), sender, &get_channels()[i], &msg));
						send_user = true;	
					}
				}
				channel_found = true;
			}
		}
		if (channel_found == true)
		{
			if (send_user == true)
				send_message(sender, print_numerics(315, sender, sender, NULL, &msg));
			return ;
		}
		std::cout << "no Channel found" << std::endl;
		for (size_t i = 0; i < this->_clients.size(); i++)
		{
			if (this->_clients[i].get_user_modes().find("i") == std::string::npos)
			{
				//  Potentiellement d'autres truc (users' host, server, realname and nickname)
				if (check_wildcards(this->_clients[i], msg))               //Check possible wildcards
				{
					send_message(sender, print_numerics(352, this->_clients[i], sender, NULL, &msg));
					send_user = true;
				}
			}
		}
		if (send_user == true)
			send_message(sender, print_numerics(315, sender, sender, NULL, &msg));
	}
}