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
	if (message.get_tab_parameter().size() == 2) {
		if (message.get_tab_parameter()[1].size() == 1 && message.get_tab_parameter()[1][0] == ':')
			(*channel_it).set_topic("");
		else
			(*channel_it).set_topic(message.get_tab_parameter()[1]);
		for (std::map<Client*, std::string>::iterator it2 = (*channel_it).get_users().begin(); it2 != (*channel_it).get_users().end(); it2++) {
			if ((*channel_it).get_topic() == "")
				send_message(*(it2->first), print_numerics(331, message.get_sender(), message.get_receiver(), &(*channel_it), &message)); // RPL_NOTOPIC (332)
			else
				send_message(*(it2->first), print_numerics(332, message.get_sender(), message.get_receiver(), &(*channel_it), &message)); // RPL_TOPIC (332)
		}
			// send_message(*(it2->first), print_numerics(336, message.get_sender(), message.get_receiver(), &(*channel_it), &message));
	}
	// else {
	// 	if ((*channel_it).get_topic() == "")
	// 		send_message(*client, print_numerics(331, message.get_sender(), message.get_receiver(), NULL, &message)); // RPL_NOTOPIC (332)
	// 	else
	// 		send_message(*client, print_numerics(332, message.get_sender(), message.get_receiver(), NULL, &message)); // RPL_TOPIC (332)
	// }
}