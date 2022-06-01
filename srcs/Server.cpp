#include "../includes/Server.hpp"
#include "../includes/Message.hpp"
#include "../includes/ft_irc.hpp"

Server::Server() {}

Server::Server(const Server &server):
	_network_name(server._network_name),
	_hostname(server._hostname),
	_port(server._port),
	_infoServer(server._infoServer),
	_servername(server._servername),
	_locationServer(server._locationServer), 
	_hostInfo (server._hostInfo),
	_hostMail(server._hostMail),
	_version (server._version),
	_token(server._token),
	_connexion(server._connexion),
	_nb_user (server._nb_user),
	_nb_clients (server._nb_clients),
	_nb_operator (server._nb_operator),
	_invisible_user (server._invisible_user),
	_server_connected(server._server_connected),
	_nb_channel(server._nb_channel),
	_datetime (server._datetime)
{
}

Server::~Server() {}




std::string Server::get_network_name() const { return (_network_name); }
std::string Server::get_hostname() const { return (_hostname); }
std::string Server::get_port() const { return (_port); }
std::string Server::get_infoServer() const { return (_infoServer); }
std::string Server::get_servername() const { return (_servername); }
std::string Server::get_locationServer() const { return (_locationServer); }
std::string Server::get_hostInfo() const { return (_hostInfo); }
std::string Server::get_hostMail() const { return (_hostMail); }
std::string Server::get_version() const { return (_version); }
std::string Server::get_token() const { return (_token); }
std::string Server::get_connexion() const { return (_connexion); }
std::string Server::get_nb_user() const { return (_nb_user); }
std::string Server::get_nb_clients() const { return (_nb_clients); }
std::string Server::get_nb_operator() const { return (_nb_operator); }
std::string Server::get_invisible_user() const { return (_invisible_user); }
std::string Server::get_server_connected() const { return (_server_connected); }
std::string Server::get_nb_channel() const { return (_nb_channel); }
std::string Server::get_datetime() const { return (_datetime); }

std::vector<Client>	&Server::get_clients() { return (_clients); }
std::vector<Channel> &Server::get_channels() { return (_channels); }
std::vector<struct pollfd> &Server::get_fds() { return (_fds); };
std::string Server::get_password() const { return (_password); }
bool Server::get_using_password() const { return (_using_password); }
int Server::get_server_fd() const { return (_fds[0].fd); }

std::vector<Client>::iterator Server::get_client(std::string to_search){
	std::vector<Client>::iterator	client_it;

	for (client_it = _clients.begin(); client_it != _clients.end(); client_it++)
		if ((*client_it).get_nickname() == to_search)
			break;
	return (client_it);
}

std::vector<Channel>::iterator Server::get_channel(std::string to_search){
	std::vector<Channel>::iterator	channel_it;

	for (channel_it = _channels.begin(); channel_it != _channels.end(); channel_it++)
			if ((*channel_it).get_name() == to_search)
				break;
	return (channel_it);
}

void Server::set_network_name(std::string &val) {
	_network_name = val;
}

void Server::set_hostname(std::string &val) {
	_hostname = val;
}

void Server::set_port(std::string &val) {
	_port = val;
}

void Server::set_infoServer(std::string &val) {
	_infoServer = val;
}

void Server::set_servername(std::string &val) {
	_servername = val;
}

void Server::set_locationServer(std::string &val) {
	_locationServer = val;
}

void Server::set_hostInfo(std::string &val) {
	_hostInfo = val;
}

void Server::set_hostMail(std::string &val) {
	_hostMail = val;
}

void Server::set_version(std::string &val) {
	_version = val;
}

void Server::set_token(std::string &val) {
	_token = val;
}

void Server::set_connexion(std::string &val) {
	_connexion = val;
}

void Server::set_nb_user(std::string &val) {
	_nb_user = val;
}

void Server::set_nb_clients(std::string &val) {
	_nb_clients = val;
}

void Server::set_nb_operator(std::string &val) {
	_nb_operator = val;
}

void Server::set_invisible_user(std::string &val) {
	_invisible_user = val;
}

void Server::set_server_connected(std::string &val) {
	_server_connected = val;
}

void Server::set_nb_channel(std::string &val) {
	_nb_channel = val;
}

void Server::set_datetime(std::string &val) {
	_datetime = val;
}

void Server::set_password(std::string val) {
	_password = val;
}

void Server::set_using_password(bool val) {
	_using_password = val;
}


void Server::set_user(Client client) {
	std::vector<Client>::iterator it = get_client(client.get_nickname());
	if (it == _clients.end()) {
		_clients.push_back(client);
	}
}

void Server::command_JOIN(Client *client, std::vector<std::string> parameters) {
	std::vector<std::string>		channels_string;
	std::vector<std::string>		keys;
	std::vector<Channel>::iterator	channel_it;

	if (parameters.size() < 1) {
		ft_print_numerics(461);
		return ;
	}
	channels_string = parse_comma(parameters[0]);
	if (parameters.size() > 1)
		keys = parse_comma(parameters[1]);
	for (size_t i = 0; i < channels_string.size(); i++) {
		channel_it = get_channel(channels_string[i]);
		if (channel_it == _channels.end()) {
			_channels.push_back(Channel(channels_string[i]));
			channel_it = get_channel(channels_string[i]);
		}
		if (keys.size() - 1 > i) // A check
			(*channel_it).set_user(client);
		else
			(*channel_it).set_user(client, keys[i]);
	}
}

void Server::command_PART(Client *client, std::vector<std::string> parameters) {
	std::vector<std::string>		channels_string;
	std::vector<Channel>::iterator	channel_it;

	if (parameters.size() < 1) {
		ft_print_numerics(461);
		return ;
	}
	channels_string = parse_comma(parameters[0]);
	for (size_t i = 0; i < channels_string.size(); i++) {
		channel_it = get_channel(channels_string[i]);
		if (channel_it == _channels.end()) {
			ft_print_numerics(403);
			continue ;
		}
		(*channel_it).remove_user(client, &_channels);
		std::cout << ":" << client->get_nickname() << " PART " << (*channel_it).get_name() << std::endl;

	}
}

void Server::command_TOPIC(Client *client, std::vector<std::string> parameters) {
	std::vector<Channel>::iterator	channel_it;
	std::map<Client*, std::string>::iterator client_it;

	if (parameters.size() < 1 || parameters.size() > 2) {
		ft_print_numerics(461);
		return ;
	}
	channel_it = get_channel(parameters[0]);	
	if (channel_it == _channels.end()) {
		ft_print_numerics(403);
		return ;
	}
	client_it = (*channel_it).get_users().find(client);
	if (client_it == (*channel_it).get_users().end()) {
		ft_print_numerics(442);
		return ;
	}
	if ((*channel_it).get_channel_modes().find("t") != std::string::npos) {
		if ((*channel_it).get_users().find(client)->second.find("o") == std::string::npos) {
			ft_print_numerics(482);
			return ;
		}
	}
	if (parameters.size() == 2)
		(*channel_it).set_topic(parameters[1]);
	else
		std::cout << (*channel_it).get_topic() << std::endl;
		// ft_print_numerics(332); // RPL_TOPIC (332) 
}

void Server::command_NAMES(std::vector<std::string> parameters) {
	std::vector<std::string>		channels_string;
	std::vector<Channel>::iterator	channel_it;

	if (parameters.size() < 1) {
		for (channel_it = _channels.begin(); channel_it != _channels.end(); channel_it++) {
			ft_print_numerics(353); //RPL_NAMREPLY (353) 
		}
	} else {
		channels_string = parse_comma(parameters[0]);
		for (size_t i = 0; i < channels_string.size(); i++) {
			channel_it = get_channel(channels_string[i]);
			if (channel_it == _channels.end())
				continue ;
			ft_print_numerics(353); //RPL_NAMREPLY (353) 
		}
	}
	ft_print_numerics(366); // RPL_ENDOFNAMES (366) 
}

void Server::command_LIST(std::vector<std::string> parameters) {
	std::vector<std::string>		channels_string;
	std::vector<Channel>::iterator	channel_it;

	ft_print_numerics(321);	// RPL_LISTSTART (Pas sûr de devoir l'envoyer)
	if (parameters.size() < 1) {
		for (channel_it = _channels.begin(); channel_it != _channels.end(); channel_it++) {
			if ((*channel_it).get_channel_modes().find('s') != std::string::npos) {
				continue ;
			} else if ((*channel_it).get_channel_modes().find('m') != std::string::npos) {
				ft_print_numerics(322); //Print without Topic
			} else
				ft_print_numerics(322);
		}
	} else {
		channels_string = parse_comma(parameters[0]);
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

void Server::command_INVITE(Client *sender, std::vector<std::string> parameters) {
	std::vector<Channel>::iterator	channel_it;
	std::vector<Client>::iterator	client_it;

	if (parameters.size() < 2 || parameters.size() > 2) {
		ft_print_numerics(461);
	} else {
		client_it = get_client(parameters[0]);
		if (client_it == _clients.end()) {
			ft_print_numerics(401);
			return ;
		}
		channel_it = get_channel(parameters[1]);
		if (channel_it == _channels.end()) {
			ft_print_numerics(403);
			return ;
		}
		if ((*channel_it).get_users().find(sender)->second.find("o") == std::string::npos) {
			ft_print_numerics(482);  // ERR_CHANOPRIVSNEEDED (482)
		} else {
			(*channel_it).add_invite(&(*client_it));
			ft_print_numerics(341); //RPL_NAMREPLY (353) 
		}
	}
	ft_print_numerics(366); // RPL_ENDOFNAMES (366) 
}

void Server::command_KICK(Client *sender, std::vector<std::string> parameters) {
	std::vector<Channel>::iterator	channel_it;
	std::vector<std::string>		clients_string;
	std::vector<Client>::iterator	client_it;

	if (parameters.size() < 2) {
		ft_print_numerics(461);
	} else {
		clients_string = parse_comma(parameters[1]);
		channel_it = get_channel(parameters[0]);
		if (channel_it == _channels.end()) {
			ft_print_numerics(403);
			return ;
		}
		if ((*channel_it).get_users().find(sender)->second.find("o") == std::string::npos) {
			ft_print_numerics(482);  // ERR_CHANOPRIVSNEEDED (482)
		} else {	
			for (size_t i = 0; i < clients_string.size(); i++) {
				client_it = get_client(clients_string[i]);
				if (client_it == _clients.end()) {
					ft_print_numerics(441);
					continue; 
				}
				(*channel_it).remove_user(&(*client_it), &_channels);
				std::cout << ":" << sender->get_nickname() << " KICK #" << (*channel_it).get_name() << " " << (*client_it).get_nickname() << std::endl;
			}
		}
	}
}

void Server::command_MODE_CHAN(Client *sender, std::vector<std::string> parameters) {
	std::vector<Channel>::iterator	channel_it;
	std::map<Client*, std::string>::iterator client_it;

	if (parameters.size() > 0) {
		channel_it = get_channel(parameters[0]);	
		if (channel_it == _channels.end()) {
			ft_print_numerics(403);
			return ;
		}
		if (parameters.size() == 1) {
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
		(*channel_it).set_channel_modes(parameters);
	} else 
		ft_print_numerics(461);
}

bool Server::_nick_available(std::string nick) const {
	for (unsigned long i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].get_nickname() == nick)
			return false;
	}
	return true;
}

bool Server::_nick_isvalid(std::string nick) const {
	std::string valid = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789`|^_-{}[]\\";

	if (nick.find_first_not_of(valid) != std::string::npos)
		return false;
	return true;

}

void Server::command_NICK(Client &client, Message &message) {
	std::string new_nick = message.get_tab_parameter()[0];

	if (message.get_tab_parameter().size() == 0)
	{
	    //    431    ERR_NONICKNAMEGIVEN
        //       ":No nickname given"
        //  - Returned when a nickname parameter expected for a
        //    command and isn't found.

		// send_message(*this, client, /* print numerics demander a Romain */, 431);

	}
	else if (!_nick_available(new_nick))
	{
		//    433    ERR_NICKNAMEINUSE
		//           "<nick> :Nickname is already in use"
		//      - Returned when a NICK message is processed that results
		//        in an attempt to change to a currently existing
		//        nickname.

		// send_message(*this, client, /* print numerics demander a Romain */, 433);

	}
	else if (!_nick_isvalid(new_nick))
	{
		//        432    ERR_ERRONEUSNICKNAME
        //       "<nick> :Erroneous nickname"
        //  - Returned after receiving a NICK message which contains
        //    characters which do not fall in the defined set.  See
        //    section 2.3.1 for details on valid nicknames.

		// send_message(*this, client, /* print numerics demander a Romain */, 432);
	}
	//else if (/* is restricted, demander a Kyllian pour les user modes*/)
	//{
		//    484    ERR_RESTRICTED
		//           ":Your connection is restricted!"
		//      - Sent by the server to a user upon connection to indicate
		//        the restricted nature of the connection (user mode "+r").
		// send_message(*this, client, /* print numerics demander a Romain */, 484);
	//}
	else 
	{
		//set nickname
		client.set_nickname(new_nick);

		//send_message(); //for valid nick change
		//response
	}

	    //    437    ERR_UNAVAILRESOURCE
        //       "<nick/channel> :Nick/channel is temporarily unavailable"
        //  - Returned by a server to a user trying to join a channel
        //    currently blocked by the channel delay mechanism.
        //  - Returned by a server to a user trying to change nickname
        //    when the desired nickname is blocked by the nick delay
        //    mechanism.

		//        436    ERR_NICKCOLLISION
        //       "<nick> :Nickname collision KILL from <user>@<host>"
        //  - Returned by a server to a client when it detects a
        //    nickname collision (registered of a NICK that
        //    already exists by another server).

}