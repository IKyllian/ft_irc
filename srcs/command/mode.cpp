#include "../../includes/ft_irc.hpp"

// void Server::command_MODE_CHAN(Client *sender, std::vector<std::string> parameters) {
// 	std::vector<Channel>::iterator	channel_it;
// 	std::map<Client*, std::string>::iterator client_it;

// 	if (parameters.size() > 0) {
// 		channel_it = get_channel(parameters[0]);	
// 		if (channel_it == _channels.end()) {
// 			ft_print_numerics(403);
// 			return ;
// 		}
// 		if (parameters.size() == 1) {
// 			ft_print_numerics(324); // Renvoie les modes actuels
// 			return ;
// 		}
// 		client_it = (*channel_it).get_users().find(sender);
// 		if (client_it == (*channel_it).get_users().end()) {
// 			ft_print_numerics(442);
// 			return ;
// 		}
// 		if ((*channel_it).get_users().find(sender)->second.find("o") == std::string::npos) {
// 			ft_print_numerics(482);
// 			return ;
// 		}
// 		(*channel_it).set_channel_modes(parameters);
// 	} else 
// 		ft_print_numerics(461);
// }

void Server::command_MODE_CHAN(Client *sender, Message &message) {
	std::vector<Channel>::iterator	channel_it;
	std::map<Client*, std::string>::iterator client_it;

	if (message.get_tab_parameter().size() > 0) {
		channel_it = get_channel(message.get_tab_parameter()[0]);	
		if (channel_it == _channels.end()) {
			ft_print_numerics(403);
			return ;
		}
		if (message.get_tab_parameter().size() == 1) {
			ft_print_numerics(324); // Renvoie les modes actuels
			return ;
		}
		client_it = (*channel_it).get_users().find(sender);
		if (client_it == (*channel_it).get_users().end()) {
			ft_print_numerics(442);
			return ;
		}
		if ((*channel_it).get_users().find(sender)->second.find("o") == std::string::npos) {
			ft_print_numerics(482);
			return ;
		}
		(*channel_it).set_channel_modes(message.get_tab_parameter());
	} else 
		ft_print_numerics(461);
}

// void Server::command_MODE_USER(Client *sender, std::vector<std::string> parameters) {
// 	std::vector<Client>::iterator	client_it;

// 	if (parameters.size() == 1) {
// 		ft_print_numerics(221); // Send current mode of the target user
// 	} else if (parameters.size() > 1) {
// 		client_it = get_client(parameters[0]);
// 		if (client_it == _clients.end()) {
// 			ft_print_numerics(401);
// 			return ;
// 		} else if (sender->get_nickname() != (*client_it).get_nickname()) {
// 			ft_print_numerics(502);
// 			return ;
// 		} else {
// 			(*client_it).set_user_modes(parameters[1]);
// 		}
// 	}
// }

void Server::command_MODE_USER(Client *sender, Message &message) {
	std::vector<Client>::iterator	client_it;

	if (message.get_tab_parameter().size() == 1) {
		ft_print_numerics(221); // Send current mode of the target user
	} else if (message.get_tab_parameter().size() > 1) {
		client_it = get_client(message.get_tab_parameter()[0]);
		if (client_it == _clients.end()) {
			ft_print_numerics(401);
			return ;
		} else if (sender->get_nickname() != (*client_it).get_nickname()) {
			ft_print_numerics(502);
			return ;
		} else {
			(*client_it).set_user_modes(message.get_tab_parameter()[1]);
		}
	}
}