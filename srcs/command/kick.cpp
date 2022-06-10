#include "../../includes/ft_irc.hpp"

// void Server::command_KICK(Client *sender, std::vector<std::string> parameters) {
// 	std::vector<Channel>::iterator	channel_it;
// 	std::vector<std::string>		clients_string;
// 	std::vector<Client>::iterator	client_it;

// 	if (parameters.size() < 2) {
// 		ft_print_numerics(461);
// 	} else {
// 		clients_string = parse_comma(parameters[1]);
// 		channel_it = get_channel(parameters[0]);
// 		if (channel_it == _channels.end()) {
// 			ft_print_numerics(403);
// 			return ;
// 		}
// 		if ((*channel_it).get_users().find(sender)->second.find("o") == std::string::npos) {
// 			ft_print_numerics(482);  // ERR_CHANOPRIVSNEEDED (482)
// 		} else {	
// 			for (size_t i = 0; i < clients_string.size(); i++) {
// 				client_it = get_client(clients_string[i]);
// 				if (client_it == _clients.end()) {
// 					ft_print_numerics(441);
// 					continue; 
// 				}
// 				(*channel_it).remove_user(&(*client_it), &_channels);
// 				std::cout << ":" << sender->get_nickname() << " KICK #" << (*channel_it).get_name() << " " << (*client_it).get_nickname() << std::endl;
// 			}
// 		}
// 	}
// }

void Server::command_KICK(Client *sender, Message &message) {
	std::vector<Channel>::iterator	channel_it;
	std::vector<std::string>		clients_string;
	std::vector<Client>::iterator	client_it;

	if (message.get_tab_parameter().size() < 2) {
		send_message(*sender, ft_print_numerics(461));
	} else {
		clients_string = parse_comma(message.get_tab_parameter()[1]);
		channel_it = get_channel(message.get_tab_parameter()[0]);
		if (channel_it == _channels.end()) {
			send_message(*sender, ft_print_numerics(403));
			return ;
		}
		if ((*channel_it).get_users().find(sender)->second.find("o") == std::string::npos) {
			send_message(*sender, ft_print_numerics(482));;  // ERR_CHANOPRIVSNEEDED (482)
		} else {	
			for (size_t i = 0; i < clients_string.size(); i++) {
				client_it = get_client(clients_string[i]);
				if (client_it == _clients.end()) {
					send_message(*sender, ft_print_numerics(441));
					continue; 
				}
				(*channel_it).remove_user(&(*client_it), &_channels);
			send_message(*sender, build_command_message(sender->get_nickname(), (*client_it).get_nickname(), (*channel_it).get_name(), "KICK"));
			}
		}
	}
}