#include "../../includes/ft_irc.hpp"

// void Server::command_LIST(std::vector<std::string> parameters) {
// 	std::vector<std::string>		channels_string;
// 	std::vector<Channel>::iterator	channel_it;

// 	ft_print_numerics(321);	// RPL_LISTSTART (Pas sûr de devoir l'envoyer)
// 	if (parameters.size() < 1) {
// 		for (channel_it = _channels.begin(); channel_it != _channels.end(); channel_it++) {
// 			if ((*channel_it).get_channel_modes().find('s') != std::string::npos) {
// 				continue ;
// 			} else if ((*channel_it).get_channel_modes().find('m') != std::string::npos) {
// 				ft_print_numerics(322); //Print without Topic
// 			} else
// 				ft_print_numerics(322);
// 		}
// 	} else {
// 		channels_string = parse_comma(parameters[0]);
// 		for (size_t i = 0; i < channels_string.size(); i++) {
// 			channel_it = get_channel(channels_string[i]);
// 			if (channel_it == _channels.end())
// 				ft_print_numerics(402);
// 			if ((*channel_it).get_channel_modes().find('s') != std::string::npos) {
// 				continue ;
// 			} else if ((*channel_it).get_channel_modes().find('m') != std::string::npos) {
// 				ft_print_numerics(322); //Print without Topic
// 			} else
// 				ft_print_numerics(322);
// 		}
// 	}
// 	ft_print_numerics(323);	// RPL_LISTEND (Ce que l'on envoie a la fin de la commande LIST)
// }

void Server::command_LIST(Message &message) {
	std::vector<std::string>		channels_string;
	std::vector<Channel>::iterator	channel_it;

	ft_print_numerics(321);	// RPL_LISTSTART (Pas sûr de devoir l'envoyer)
	if (message.get_tab_parameter().size() < 1) {
		for (channel_it = _channels.begin(); channel_it != _channels.end(); channel_it++) {
			if ((*channel_it).get_channel_modes().find('s') != std::string::npos) {
				continue ;
			} else if ((*channel_it).get_channel_modes().find('m') != std::string::npos) {
				ft_print_numerics(322); //Print without Topic
			} else
				ft_print_numerics(322);
		}
	} else {
		channels_string = parse_comma(message.get_tab_parameter()[0]);
		for (size_t i = 0; i < channels_string.size(); i++) {
			channel_it = get_channel(channels_string[i]);
			if (channel_it == _channels.end())
				ft_print_numerics(402);
			if ((*channel_it).get_channel_modes().find('s') != std::string::npos) {
				continue ;
			} else if ((*channel_it).get_channel_modes().find('m') != std::string::npos) {
				ft_print_numerics(322); //Print without Topic
			} else
				ft_print_numerics(322);
		}
	}
	ft_print_numerics(323);	// RPL_LISTEND (Ce que l'on envoie a la fin de la commande LIST)
}