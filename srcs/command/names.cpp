#include "../../includes/ft_irc.hpp"

// void Server::command_NAMES(std::vector<std::string> parameters) {
// 	std::vector<std::string>		channels_string;
// 	std::vector<Channel>::iterator	channel_it;

// 	if (parameters.size() < 1) {
// 		for (channel_it = _channels.begin(); channel_it != _channels.end(); channel_it++) {
// 			ft_print_numerics(353); //RPL_NAMREPLY (353) 
// 		}
// 	} else {
// 		channels_string = parse_comma(parameters[0]);
// 		for (size_t i = 0; i < channels_string.size(); i++) {
// 			channel_it = get_channel(channels_string[i]);
// 			if (channel_it == _channels.end())
// 				continue ;
// 			ft_print_numerics(353); //RPL_NAMREPLY (353) 
// 		}
// 	}
// 	ft_print_numerics(366); // RPL_ENDOFNAMES (366) 
// }

void Server::command_NAMES(Message &message) {
	std::vector<std::string>		channels_string;
	std::vector<Channel>::iterator	channel_it;

	if (message.get_tab_parameter().size() < 1) {
		for (channel_it = _channels.begin(); channel_it != _channels.end(); channel_it++) {
			send_message(message.get_sender(), ft_print_numerics(353)); //RPL_NAMREPLY (353) 
		}
	} else {
		channels_string = parse_comma(message.get_tab_parameter()[0]);
		for (size_t i = 0; i < channels_string.size(); i++) {
			channel_it = get_channel(channels_string[i]);
			if (channel_it == _channels.end())
				continue ;
			send_message(message.get_sender(), ft_print_numerics(353)); //RPL_NAMREPLY (353) 
		}
	}
	send_message(message.get_sender(), ft_print_numerics(366)); // RPL_ENDOFNAMES (366) 
}