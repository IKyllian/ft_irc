#include "../../includes/ft_irc.hpp"

void Server::command_INVITE(Client *sender, Message &message) {
	std::vector<Channel*>::iterator	channel_it;
	std::vector<Client*>::iterator	client_it;

	if (message.get_tab_parameter().size() < 2 || message.get_tab_parameter().size() > 2) {
		send_message(*sender, print_numerics(461, message.get_sender(), message.get_receiver(), NULL, &message));
	} else {
		if (message.get_tab_parameter()[1].size() > 0 && message.get_tab_parameter()[1][0] != '#' && message.get_tab_parameter()[1][0] != '&')
			return ;
		channel_it = get_channel(message.get_tab_parameter()[1]);
		if (channel_it == _channels.end()) {
			send_message(*sender, print_numerics(403, message.get_sender(), message.get_receiver(), NULL, &message));
			return ;
		}
		if ((*channel_it)->get_users().find(sender)->second.find("o") == std::string::npos) {
			send_message(*sender, print_numerics(482, message.get_sender(), message.get_receiver(), *channel_it, &message));  // ERR_CHANOPRIVSNEEDED (482)
		} else {
			client_it = get_client(message.get_tab_parameter()[0]);
			if (client_it != _clients.end() && (*channel_it)->get_users().find(*client_it) != (*channel_it)->get_users().end())
				return ;
			(*channel_it)->add_invite(message.get_tab_parameter()[0]);
			//A revoir
			for (std::map<Client*, std::string>::iterator it2 = (*channel_it)->get_users().begin(); it2 != (*channel_it)->get_users().end(); it2++)
				send_message(*(it2->first), print_numerics(336, message.get_sender(), message.get_receiver(), (*channel_it), &message));
			send_message(*sender, print_numerics(337, message.get_sender(), message.get_receiver(), (*channel_it), &message));
			send_message(*sender, build_command_message(sender->get_nickname(), message.get_tab_parameter()[0], (*channel_it)->get_name(), "INVITE"));
			if (client_it != _clients.end())
				send_message(*(*client_it), build_command_message(sender->get_nickname(), (*client_it)->get_nickname(), (*channel_it)->get_name(), "INVITE"));
		}
	}
}