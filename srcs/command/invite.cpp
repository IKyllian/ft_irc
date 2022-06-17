#include "../../includes/ft_irc.hpp"

void Server::command_INVITE(Client *sender, Message &message) {
	std::vector<Channel*>::iterator	channel_it;
	std::vector<Client*>::iterator	client_it;
	int ret;

	if (message.get_tab_parameter().size() < 2 || message.get_tab_parameter().size() > 2) {
		send_message(*sender, print_numerics(461, message.get_sender(), message.get_receiver(), NULL, &message));
	} else {
		client_it = get_client(message.get_tab_parameter()[0]);
		if (client_it == _clients.end()) {
			send_message(*sender, print_numerics(401, message.get_sender(), message.get_receiver(), NULL, &message));
			return ;
		}
		if (message.get_tab_parameter()[1].size() > 0 && message.get_tab_parameter()[1][0] != '#' && message.get_tab_parameter()[1][0] != '&')
			return ;
		channel_it = get_channel(message.get_tab_parameter()[1]);
		if (channel_it == _channels.end()) {
			send_message(*sender, print_numerics(403, message.get_sender(), message.get_receiver(), NULL, &message));
			return ;
		}
		if ((*channel_it)->get_users().find(sender)->second.find("o") == std::string::npos) {
			send_message(*sender, print_numerics(482, message.get_sender(), message.get_receiver(), NULL, &message));  // ERR_CHANOPRIVSNEEDED (482)
		} else {
			ret = (*channel_it)->add_invite((*client_it));
			if (ret == 443)
				send_message(*sender, print_numerics(443, message.get_sender(), message.get_receiver(), (*channel_it), &message)); //ERR_USERONCHANNEL (443) 
			else {
				//A revoir
				for (std::map<Client*, std::string>::iterator it2 = (*channel_it)->get_users().begin(); it2 != (*channel_it)->get_users().end(); it2++)
					send_message(*(it2->first), print_numerics(336, message.get_sender(), message.get_receiver(), (*channel_it), &message));
				send_message(*sender, print_numerics(337, message.get_sender(), message.get_receiver(), (*channel_it), &message));
			} 
			send_message(*sender, build_command_message(sender->get_nickname(), (*client_it)->get_nickname(), (*channel_it)->get_name(), "INVITE"));
		}
	}
}