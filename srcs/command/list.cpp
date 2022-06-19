#include "../../includes/ft_irc.hpp"

void Server::command_LIST(Message &message) {
	std::vector<std::string>		channels_string;
	std::vector<Channel*>::iterator	channel_it;

	send_message(message.get_sender(), print_numerics(321, message.get_sender(), message.get_receiver(), NULL, &message));	// RPL_LISTSTART (Pas sûr de devoir l'envoyer)
	if (message.get_tab_parameter().size() < 1) {
		for (channel_it = _channels.begin(); channel_it != _channels.end(); channel_it++) {
			if ((*channel_it)->get_channel_modes().find('s') != std::string::npos)
				continue ;
			// } else if ((*channel_it)->get_channel_modes().find('m') != std::string::npos) {
			// 	send_message(message.get_sender(), print_numerics(322, message.get_sender(), message.get_receiver(), (*channel_it), &message)); //Print without Topic
			// } else
				send_message(message.get_sender(), print_numerics(322, message.get_sender(), message.get_receiver(), (*channel_it), &message));
		}
	} else {
		channels_string = parse_comma(message.get_tab_parameter()[0]);
		for (size_t i = 0; i < channels_string.size(); i++) {
			if (channels_string[i].size() > 0 && channels_string[i][0] != '#' && channels_string[i][0] != '&')
				continue ;
			channel_it = get_channel(channels_string[i]);
			if (channel_it == _channels.end())
				send_message(message.get_sender(), print_numerics(402, message.get_sender(), message.get_receiver(), NULL, &message));
			if ((*channel_it)->get_channel_modes().find('s') != std::string::npos)
				continue ;
			// } else if ((*channel_it)->get_channel_modes().find('m') != std::string::npos) {
			// 	send_message(message.get_sender(), print_numerics(322, message.get_sender(), message.get_receiver(), (*channel_it), &message)); //Print without Topic
			// } else
				send_message(message.get_sender(), print_numerics(322, message.get_sender(), message.get_receiver(), (*channel_it), &message));
		}
	}
	send_message(message.get_sender(), print_numerics(323, message.get_sender(), message.get_receiver(), NULL, &message));	// RPL_LISTEND (Ce que l'on envoie a la fin de la commande LIST)
}