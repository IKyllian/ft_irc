#include "../../includes/ft_irc.hpp"

void Server::command_JOIN(Client *client, Message &message, Server &server) {
	std::vector<std::string>		channels_string;
	std::vector<std::string>		keys;
	std::vector<Channel*>::iterator	channel_it;

	if (message.get_tab_parameter().size() < 1) {
		send_message(*client, print_numerics(461, *client, *client, NULL, &message));
		return ;
	}
	channels_string = parse_comma(message.get_tab_parameter()[0]);
	if (message.get_tab_parameter().size() > 1)
		keys = parse_comma(message.get_tab_parameter()[1]);
	for (size_t i = 0; i < channels_string.size(); i++) {
		if (channels_string[i].size() > 0 && channels_string[i][0] != '#' && channels_string[i][0] != '&')
			continue ;
		channel_it = get_channel(channels_string[i]);
		if (channel_it == _channels.end()) {
			_channels.push_back(new Channel(channels_string[i], &server));
			channel_it = get_channel(channels_string[i]);
		}
		if (keys.size() - 1 > i) // A check
			(*channel_it)->set_user(client, message);
		else
			(*channel_it)->set_user(client, message, keys[i]);
	}
}