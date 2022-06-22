#include "../../includes/Server.hpp"

void Server::command_NAMES(Message &message) {
	std::vector<std::string>		channels_string;
	std::vector<Channel*>::iterator	channel_it;

	if (message.get_tab_parameter().size() < 1) {
		for (channel_it = _channels.begin(); channel_it != _channels.end(); channel_it++) {
			for (std::map<Client*, std::string>::iterator it = (*channel_it)->get_users().begin(); it != (*channel_it)->get_users().end(); it++)
				send_message(message.get_sender(), build_message2(353, message.get_sender(), "", (*channel_it))); //RPL_NAMREPLY (353) 
		}
	} else {
		channels_string = parse_comma(message.get_tab_parameter()[0]);
		for (size_t i = 0; i < channels_string.size(); i++) {
			if (channels_string[i].size() > 0 && channels_string[i][0] != '#' && channels_string[i][0] != '&')
				continue ;
			channel_it = get_channel(channels_string[i]);
			if (channel_it == _channels.end())
				continue ;
			send_message(message.get_sender(), build_message2(353, message.get_sender(), "", (*channel_it))); //RPL_NAMREPLY (353) 
			send_message(message.get_sender(), build_response(366, message.get_sender(), message.get_receiver(), (*channel_it), &message));
		}
	}
}