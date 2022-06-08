#include "../../includes/ft_irc.hpp"

// void Server::command_INVITE(Client *sender, std::vector<std::string> parameters) {
// 	std::vector<Channel>::iterator	channel_it;
// 	std::vector<Client>::iterator	client_it;

// 	if (parameters.size() < 2 || parameters.size() > 2) {
// 		ft_print_numerics(461);
// 	} else {
// 		client_it = get_client(parameters[0]);
// 		if (client_it == _clients.end()) {
// 			ft_print_numerics(401);
// 			return ;
// 		}
// 		channel_it = get_channel(parameters[1]);
// 		if (channel_it == _channels.end()) {
// 			ft_print_numerics(403);
// 			return ;
// 		}
// 		if ((*channel_it).get_users().find(sender)->second.find("o") == std::string::npos) {
// 			ft_print_numerics(482);  // ERR_CHANOPRIVSNEEDED (482)
// 		} else {
// 			(*channel_it).add_invite(&(*client_it));
// 			ft_print_numerics(341); //RPL_NAMREPLY (353) 
// 		}
// 	}
// 	ft_print_numerics(366); // RPL_ENDOFNAMES (366) 
// }

void Server::command_INVITE(Client *sender, Message &message) {
	std::vector<Channel>::iterator	channel_it;
	std::vector<Client>::iterator	client_it;

	if (message.get_tab_parameter().size() < 2 || message.get_tab_parameter().size() > 2) {
		send_message(*sender, ft_print_numerics(461));
	} else {
		client_it = get_client(message.get_tab_parameter()[0]);
		if (client_it == _clients.end()) {
			send_message(*sender, ft_print_numerics(401));
			return ;
		}
		channel_it = get_channel(message.get_tab_parameter()[1]);
		if (channel_it == _channels.end()) {
			send_message(*sender, ft_print_numerics(403));
			return ;
		}
		if ((*channel_it).get_users().find(sender)->second.find("o") == std::string::npos) {
			send_message(*sender, ft_print_numerics(482));  // ERR_CHANOPRIVSNEEDED (482)
		} else {
			(*channel_it).add_invite(&(*client_it));
			send_message(*sender, ft_print_numerics(341)); //RPL_NAMREPLY (353) 
		}
	}
	send_message(*sender, ft_print_numerics(366)); // RPL_ENDOFNAMES (366) 
}