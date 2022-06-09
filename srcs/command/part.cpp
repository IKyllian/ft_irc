#include "../../includes/ft_irc.hpp"

std::string build_part_message(std::string client, std::string channel) {
	std::string str;

	str += ":";
	str += client;
	str += " PART #";
	str += channel;
	return str;
}
// void Server::command_PART(Client *client, std::vector<std::string> parameters) {
// 	std::vector<std::string>		channels_string;
// 	std::vector<Channel>::iterator	channel_it;

// 	if (parameters.size() < 1) {
// 		ft_print_numerics(461);
// 		return ;
// 	}
// 	channels_string = parse_comma(parameters[0]);
// 	for (size_t i = 0; i < channels_string.size(); i++) {
// 		channel_it = get_channel(channels_string[i]);
// 		if (channel_it == _channels.end()) {
// 			ft_print_numerics(403);
// 			continue ;
// 		}
// 		(*channel_it).remove_user(client, &_channels);
// 		std::cout << ":" << client->get_nickname() << " PART " << (*channel_it).get_name() << std::endl;

// 	}
// }

void Server::command_PART(Client *client, Message &message) {
	std::vector<std::string>		channels_string;
	std::vector<Channel>::iterator	channel_it;

	if (message.get_tab_parameter().size() < 1) {
		send_message(*client, ft_print_numerics(461));
		return ;
	}
	channels_string = parse_comma(message.get_tab_parameter()[0]);
	for (size_t i = 0; i < channels_string.size(); i++) {
		channel_it = get_channel(channels_string[i]);
		if (channel_it == _channels.end()) {
			send_message(*client, ft_print_numerics(403));
			continue ;
		}
		(*channel_it).remove_user(client, &_channels);
		send_message(*client, build_part_message(client->get_nickname(), (*channel_it).get_name()));
	}
}