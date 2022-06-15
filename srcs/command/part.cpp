#include "../../includes/ft_irc.hpp"

void Server::command_PART(Client *client, Message &message) {
	std::vector<std::string>		channels_string;
	std::vector<Channel>::iterator	channel_it;
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
			send_message(*client, print_numerics(403, *client, *client, NULL, &message)); // Probleme avec channel sur print numerics
			continue ;
		}
		ret = (*channel_it).remove_user(client, &_channels);
		if (ret < 0)
			send_message(*client, print_numerics(442, *client, *client, &(*channel_it), &message));
		else
			send_message(*client, build_command_message(client->get_nickname(), "", (*channel_it).get_name(), "PART"));
	}
}