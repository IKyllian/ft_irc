#include "../../includes/ft_irc.hpp"

// void Server::command_TOPIC(Client *client, std::vector<std::string> parameters) {
// 	std::vector<Channel>::iterator	channel_it;
// 	std::map<Client*, std::string>::iterator client_it;

// 	if (parameters.size() < 1 || parameters.size() > 2) {
// 		ft_print_numerics(461);
// 		return ;
// 	}
// 	channel_it = get_channel(parameters[0]);	
// 	if (channel_it == _channels.end()) {
// 		ft_print_numerics(403);
// 		return ;
// 	}
// 	client_it = (*channel_it).get_users().find(client);
// 	if (client_it == (*channel_it).get_users().end()) {
// 		ft_print_numerics(442);
// 		return ;
// 	}
// 	if ((*channel_it).get_channel_modes().find("t") != std::string::npos) {
// 		if ((*channel_it).get_users().find(client)->second.find("o") == std::string::npos) {
// 			ft_print_numerics(482);
// 			return ;
// 		}
// 	}
// 	if (parameters.size() == 2)
// 		(*channel_it).set_topic(parameters[1]);
// 	else
// 		std::cout << (*channel_it).get_topic() << std::endl;
// 		// ft_print_numerics(332); // RPL_TOPIC (332) 
// }

void Server::command_TOPIC(Client *client, Message &message) {
	std::vector<Channel>::iterator	channel_it;
	std::map<Client*, std::string>::iterator client_it;

	if (message.get_tab_parameter().size() < 1 || message.get_tab_parameter().size() > 2) {
		send_message(*client, ft_print_numerics(461));
		return ;
	}
	if (message.get_tab_parameter()[0].size() > 0 && message.get_tab_parameter()[0][0] != '#' && message.get_tab_parameter()[0][0] != '&')
			return ;
	channel_it = get_channel(message.get_tab_parameter()[0]);	
	if (channel_it == _channels.end()) {
		send_message(*client, ft_print_numerics(403));
		return ;
	}
	client_it = (*channel_it).get_users().find(client);
	if (client_it == (*channel_it).get_users().end()) {
		send_message(*client, ft_print_numerics(442));
		return ;
	}
	if ((*channel_it).get_channel_modes().find("t") != std::string::npos) {
		if ((*channel_it).get_users().find(client)->second.find("o") == std::string::npos) {
			send_message(*client, ft_print_numerics(482));
			return ;
		}
	}
	if (message.get_tab_parameter().size() == 2)
		(*channel_it).set_topic(message.get_tab_parameter()[1]);
	else {
		if ((*channel_it).get_topic() == "")
			send_message(*client, ft_print_numerics(331)); // RPL_NOTOPIC (332)
		else
			send_message(*client, ft_print_numerics(332)); // RPL_TOPIC (332)
	}
}