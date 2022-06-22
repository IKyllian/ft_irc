#include "../../includes/ft_irc.hpp"

void Server::command_PART(Client *client, Message &message) {
	std::vector<std::string>		channels_string;
	std::vector<Channel*>::iterator	channel_it;
	std::map<Client*, std::string>::iterator it;
	int ret;

	if (message.get_tab_parameter().size() < 1) {
		send_message(*client, print_numerics(461, *client, *client, NULL, &message));
		return ;
	}
	channels_string = parse_comma(message.get_tab_parameter()[0]);
	for (size_t i = 0; i < channels_string.size(); i++) {
		if (channels_string[i].size() > 0 && channels_string[i][0] != '#' && channels_string[i][0] != '&')
			continue ;
		channel_it = get_channel(channels_string[i]);
		if (channel_it == _channels.end()) {
			send_message(*client, build_message2(403, *client, channels_string[i], NULL));
			continue ;
		}
		for (it = (*channel_it)->get_users().begin(); it != (*channel_it)->get_users().end(); it++) {
			if ((*it).first->get_nickname() == client->get_nickname())
			break ;
		}
		if ((*channel_it)->get_users().end() == it)
			send_message(*client, print_numerics(442, *client, *client, (*channel_it), &message));
		else {
			for (std::map<Client*, std::string>::iterator it2 = (*channel_it)->get_users().begin(); it2 != (*channel_it)->get_users().end(); it2++)
				send_message(*(it2->first), build_command_message(client->get_nickname(), "", (*channel_it)->get_name(), "PART"));
			ret = (*channel_it)->remove_user(client, &_channels);
		}
	}
}