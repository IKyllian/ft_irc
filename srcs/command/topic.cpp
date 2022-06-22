#include "../../includes/ft_irc.hpp"

void Server::command_TOPIC(Client *client, Message &message) {
	std::vector<Channel*>::iterator	channel_it;
	std::map<Client*, std::string>::iterator client_it;
	std::string topic;

	if (message.get_tab_parameter().size() < 1) {
		send_message(*client, print_numerics(461, message.get_sender(), message.get_receiver(), NULL, &message));
		return ;
	}
	if (message.get_tab_parameter()[0].size() > 0 && message.get_tab_parameter()[0][0] != '#' && message.get_tab_parameter()[0][0] != '&')
			return ;
	channel_it = get_channel(message.get_tab_parameter()[0]);	
	if (channel_it == _channels.end()) {
		send_message(*client, build_message2(403, *client, message.get_tab_parameter()[0], NULL));
		return ;
	}
	client_it = (*channel_it)->get_users().find(client);
	if (client_it == (*channel_it)->get_users().end()) {
		send_message(*client, print_numerics(442, message.get_sender(), message.get_receiver(), (*channel_it), &message));
		return ;
	}
	if ((*channel_it)->get_channel_modes().find("t") != std::string::npos) {
		if ((*channel_it)->get_users().find(client)->second.find("o") == std::string::npos) {
			send_message(*client, print_numerics(482, message.get_sender(), message.get_receiver(), (*channel_it), &message));
			return ;
		}
	}
	if (message.get_tab_parameter().size() > 1) {
		if (message.get_tab_parameter()[1].size() == 1 && message.get_tab_parameter()[1][0] == ':')
			(*channel_it)->set_topic("");
		else {
			for (size_t i = 1; i < message.get_tab_parameter().size(); i++) {
				topic += message.get_tab_parameter()[i];
				if (i + 1 < message.get_tab_parameter().size())
					topic += " ";
			}
			(*channel_it)->set_topic(topic);
		}
		for (std::map<Client*, std::string>::iterator it2 = (*channel_it)->get_users().begin(); it2 != (*channel_it)->get_users().end(); it2++) {
			if ((*channel_it)->get_topic() == "")
				send_message(*(it2->first), print_numerics(331, message.get_sender(), message.get_receiver(), (*channel_it), &message)); // RPL_NOTOPIC (332)
			else
				send_message(*(it2->first), print_numerics(332, message.get_sender(), message.get_receiver(), (*channel_it), &message)); // RPL_TOPIC (332)
		}
	}
	else {
		for (std::map<Client*, std::string>::iterator it2 = (*channel_it)->get_users().begin(); it2 != (*channel_it)->get_users().end(); it2++) {
			if ((*channel_it)->get_topic() == "")
				send_message(*(it2->first), print_numerics(331, message.get_sender(), message.get_receiver(), (*channel_it), &message)); // RPL_NOTOPIC (332)
			else
				send_message(*(it2->first), print_numerics(332, message.get_sender(), message.get_receiver(), (*channel_it), &message)); // RPL_TOPIC (332)
		}
	}
}