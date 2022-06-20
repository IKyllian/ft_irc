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
		client_it = get_client(message.get_tab_parameter()[0]);
		if (client_it == _clients.end()) {
			send_message(*sender, build_message2(401, *sender, message.get_tab_parameter()[0], NULL));
			return ;
		} else if (sender->get_nickname() != (*client_it)->get_nickname()) {
			send_message(*sender, build_response(502, *sender, *sender, NULL, &message));
			return ;
		} else {
			(*client_it)->set_user_modes(message.get_tab_parameter()[1], server);
		}
	}
}