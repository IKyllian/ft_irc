#include "../../includes/ft_irc.hpp"

void Server::command_KICK(Client *sender, Message &message) {
	std::vector<Channel>::iterator	channel_it;
	std::vector<std::string>		clients_string;
	std::vector<Client>::iterator	client_it;

	if (message.get_tab_parameter().size() < 2) {
		send_message(*sender, print_numerics(461, message.get_sender(), message.get_receiver(), NULL, &message));
	} else {
		clients_string = parse_comma(message.get_tab_parameter()[1]);
		if (message.get_tab_parameter()[0].size() > 0 && message.get_tab_parameter()[0][0] != '#' && message.get_tab_parameter()[0][0] != '&')
			return ;
		channel_it = get_channel(message.get_tab_parameter()[0]);
		if (channel_it == _channels.end()) {
			send_message(*sender, print_numerics(403, message.get_sender(), message.get_receiver(), NULL, &message));
			return ;
		}
		if ((*channel_it).get_users().find(sender)->second.find("o") == std::string::npos) {
			send_message(*sender, print_numerics(482, message.get_sender(), message.get_receiver(), &(*channel_it), &message));  // ERR_CHANOPRIVSNEEDED (482)
		} else {	
			for (size_t i = 0; i < clients_string.size(); i++) {
				client_it = get_client(clients_string[i]);
				if (client_it == _clients.end()) {
					send_message(*sender, print_numerics(441, message.get_sender(), message.get_receiver(), &(*channel_it), &message));
					continue; 
				}
				for (std::map<Client*, std::string>::iterator it2 = (*channel_it).get_users().begin(); it2 != (*channel_it).get_users().end(); it2++)
					send_message(*(it2->first), build_command_message(sender->get_nickname(), (*client_it).get_nickname(), (*channel_it).get_name(), "KICK"));
				(*channel_it).remove_user(&(*client_it), &_channels);
			}
		}
	}
}