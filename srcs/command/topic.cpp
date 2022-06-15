#include "../../includes/ft_irc.hpp"

void Server::command_TOPIC(Client *client, Message &message) {
	std::vector<Channel>::iterator	channel_it;
	std::map<Client*, std::string>::iterator client_it;

	if (message.get_tab_parameter().size() < 1 || message.get_tab_parameter().size() > 2) {
		send_message(*client, print_numerics(461, message.get_sender(), message.get_receiver(), NULL, &message));
		return ;
	}
	if (message.get_tab_parameter()[0].size() > 0 && message.get_tab_parameter()[0][0] != '#' && message.get_tab_parameter()[0][0] != '&')
			return ;
	channel_it = get_channel(message.get_tab_parameter()[0]);	
	if (channel_it == _channels.end()) {
		send_message(*client, print_numerics(403, message.get_sender(), message.get_receiver(), NULL, &message));
		return ;
	}
	client_it = (*channel_it).get_users().find(client);
	if (client_it == (*channel_it).get_users().end()) {
		send_message(*client, print_numerics(442, message.get_sender(), message.get_receiver(), NULL, &message));
		return ;
	}
	if ((*channel_it).get_channel_modes().find("t") != std::string::npos) {
		if ((*channel_it).get_users().find(client)->second.find("o") == std::string::npos) {
			send_message(*client, print_numerics(482, message.get_sender(), message.get_receiver(), NULL, &message));
			return ;
		}
	}
	if (message.get_tab_parameter().size() == 2)
		(*channel_it).set_topic(message.get_tab_parameter()[1]);
	else {
		if ((*channel_it).get_topic() == "")
			send_message(*client, print_numerics(331, message.get_sender(), message.get_receiver(), NULL, &message)); // RPL_NOTOPIC (332)
		else
			send_message(*client, print_numerics(332, message.get_sender(), message.get_receiver(), NULL, &message)); // RPL_TOPIC (332)
	}
}