#include "../includes/Server.hpp"


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

void Server::command_JOIN(std::vector<std::string> parameters, Client *client) {
	std::vector<std::string>		channels_string;
	std::vector<std::string>		keys;
	std::vector<Channel>::iterator	it;

	if (parameters.size() < 1) {
		ft_print_numerics(461);
		return ;
	}
	channels_string = parse_comma(parameters[0]);
	if (parameters.size() > 1)
		keys = parse_comma(parameters[1]);
	for (size_t i = 0; i < channels_string.size(); i++) {
		for (it = _channels.begin(); it != _channels.end(); it++)
			if ((*it).get_name() ==  channels_string[i])
				break;
		if (it == _channels.end()) {
			_channels.push_back(Channel(channels_string[i]));
			it = _channels.begin();
			for (; it != _channels.end(); it++) {
				if ((*it).get_name() == channels_string[i])
					break;
			}
		}
		if (keys.size() - 1 > i) // A check
			(*it).set_user(client);
		else
			(*it).set_user(client, keys[i]);
	}
}

void Server::command_PART(std::vector<std::string> parameters, Client *client) {
	std::vector<std::string>		channels_string;
	std::vector<Channel>::iterator	it;

	if (parameters.size() < 1) {
		ft_print_numerics(461);
		return ;
	}
	channels_string = parse_comma(parameters[0]);
	for (size_t i = 0; i < channels_string.size(); i++) {
		for (it = _channels.begin(); it != _channels.end(); it++)
			if ((*it).get_name() ==  channels_string[i])
				break;
		if (it == _channels.end()) {
			ft_print_numerics(403);
			continue ;
		}
		(*it).remove_user(client, &_channels);
	}
}

void Server::command_TOPIC(std::vector<std::string> parameters, Client *client) {
	std::vector<Channel>::iterator	it;
	std::map<Client*, std::string>::iterator it2;

	if (parameters.size() < 1 || parameters.size() > 2) {
		ft_print_numerics(461);
		return ;
	}
	for (it = _channels.begin(); it != _channels.end(); it++)
		if ((*it).get_name() ==  parameters[0])
			break;	
	if (it == _channels.end()) {
		ft_print_numerics(403);
		return ;
	}
	it2 = (*it).get_users().find(client);
	if (it2 == (*it).get_users().end()) {
		ft_print_numerics(442);
		return ;
	}
	if (parameters.size() == 2)
		(*it).set_topic(parameters[1]);
	else
		std::cout << (*it).get_topic();
		// ft_print_numerics(332); // RPL_TOPIC (332) 
}

void Server::command_NAMES(std::vector<std::string> parameters) {
	std::vector<std::string>		channels_string;
	std::vector<Channel>::iterator	it;

	if (parameters.size() < 1) {
		for (it = _channels.begin(); it != _channels.end(); it++) {
			ft_print_numerics(353); //RPL_NAMREPLY (353) 
		}
	} else {
		channels_string = parse_comma(parameters[0]);
		for (size_t i = 0; i < channels_string.size(); i++) {
			for (it = _channels.begin(); it != _channels.end(); it++)
				if ((*it).get_name() ==  channels_string[i])
					break;
			if (it == _channels.end())
				continue ;
			ft_print_numerics(353); //RPL_NAMREPLY (353) 
		}
	}
	ft_print_numerics(366); // RPL_ENDOFNAMES (366) 
}

void Server::command_LIST(std::vector<std::string> parameters) {
	std::vector<std::string>		channels_string;
	std::vector<Channel>::iterator	it;

	if (parameters.size() < 1) {
		for (it = _channels.begin(); it != _channels.end(); it++) {
			ft_print_numerics(353); //RPL_NAMREPLY (353) 
		}
	} else {
		channels_string = parse_comma(parameters[0]);
		for (size_t i = 0; i < channels_string.size(); i++) {
			for (it = _channels.begin(); it != _channels.end(); it++)
				if ((*it).get_name() ==  channels_string[i])
					break;
			if (it == _channels.end())
				continue ;
			ft_print_numerics(353); //RPL_NAMREPLY (353) 
		}
	}
	ft_print_numerics(366); // RPL_ENDOFNAMES (366) 
}

void Server::command_INVITE(Client *sender, std::vector<std::string> parameters) {
	std::vector<Channel>::iterator	channel_it;
	std::vector<Client>::iterator	client_it;

	if (parameters.size() != 2) {
		ft_print_numerics(461);
	} else {
		for (client_it = _clients.begin(); client_it != _clients.end(); client_it++)
			if ((*client_it).get_nickname() ==  parameters[0])
				break;
		// Check ce qu'il faut faire si le nickname correspond a aucun Client
		for (channel_it = _channels.begin(); channel_it != _channels.end(); channel_it++)
			if ((*channel_it).get_name() ==  parameters[1])
				break;
		if (channel_it == _channels.end())
			ft_print_numerics(403);
		if ((*channel_it).get_users().find(sender)->second.find("o") == std::string::npos) {
			ft_print_numerics(482);  // ERR_CHANOPRIVSNEEDED (482)
		} else {
			(*channel_it).add_invite(&(*client_it));
			ft_print_numerics(341); //RPL_NAMREPLY (353) 
		}
	}
	ft_print_numerics(366); // RPL_ENDOFNAMES (366) 
}

// void Server::command_KICK(Client *sender, std::vector<std::string> parameters) {

// }