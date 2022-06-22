#include "../../includes/ft_irc.hpp"

void Server::command_MODE_CHAN(Client *sender, Message &message) {
	std::vector<Channel*>::iterator	channel_it;
	std::map<Client*, std::string>::iterator client_it;

	if (message.get_tab_parameter().size() > 0) {
		channel_it = get_channel(message.get_tab_parameter()[0]);	
		if (channel_it == _channels.end()) {
			send_message(*sender, build_response(403, *sender, *sender, (*channel_it), &message));
			return ;
		}
		if (message.get_tab_parameter().size() == 1) {
			send_message(*sender, build_response(324, *sender, *sender, (*channel_it), &message)); // Renvoie les modes actuels
			return ;
		}
		client_it = (*channel_it)->get_users().find(sender);
		if (client_it == (*channel_it)->get_users().end()) {
			send_message(*sender, build_response(442, *sender, *sender, (*channel_it), &message));
			return ;
		}
		if ((*channel_it)->get_users().find(sender)->second.find("o") == std::string::npos) {
			send_message(*sender, build_response(482, *sender, *sender, (*channel_it), &message));
			return ;
		}
		(*channel_it)->set_channel_modes(sender, message.get_tab_parameter());
	} else 
		send_message(*sender, build_response(461, *sender, *sender, (*channel_it), &message));
}

void Server::command_MODE_USER(Client *sender, Message &message, Server &server) {
	std::vector<Client*>::iterator	client_it;

	if (message.get_tab_parameter().size() == 1) {
		send_message(*sender, build_response(221, *sender, *sender, NULL, &message));
	} else if (message.get_tab_parameter().size() > 1) {
		if (sender->get_nickname() != message.get_tab_parameter()[0])
			send_message(*sender, build_response(502, *sender, *sender, NULL, &message));
		else
			sender->set_user_modes(message.get_tab_parameter()[1], server);
	}
}