#include "../../includes/ft_irc.hpp"

// void Server::command_JOIN(Client *client, std::vector<std::string> parameters) {
// 	std::vector<std::string>		channels_string;
// 	std::vector<std::string>		keys;
// 	std::vector<Channel>::iterator	channel_it;

// 	if (parameters.size() < 1) {
// 		ft_print_numerics(461);
// 		return ;
// 	}
// 	channels_string = parse_comma(parameters[0]);
// 	if (parameters.size() > 1)
// 		keys = parse_comma(parameters[1]);
// 	for (size_t i = 0; i < channels_string.size(); i++) {
// 		channel_it = get_channel(channels_string[i]);
// 		if (channel_it == _channels.end()) {
// 			_channels.push_back(Channel(channels_string[i]));
// 			channel_it = get_channel(channels_string[i]);
// 		}
// 		if (keys.size() - 1 > i) // A check
// 			(*channel_it).set_user(client);
// 		else
// 			(*channel_it).set_user(client, keys[i]);
// 	}
// }

void Server::command_JOIN(Client *client, Message &message, Server &server) {
	std::vector<std::string>		channels_string;
	std::vector<std::string>		keys;
	std::vector<Channel>::iterator	channel_it;

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
			_channels.push_back(Channel(channels_string[i], &server));
			channel_it = get_channel(channels_string[i]);
		}
		if (keys.size() - 1 > i) // A check
			(*channel_it).set_user(client, message);
		else
			(*channel_it).set_user(client, message, keys[i]);
	}
}