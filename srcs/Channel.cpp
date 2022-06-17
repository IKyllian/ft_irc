#include "../includes/Channel.hpp"

Channel::Channel(){}
Channel::Channel(std::string &name, Server *server) : _name(name), _user_limit(0), _server(server) {}
Channel::Channel(const Channel &channel) : _name(channel._name) {
	_users.clear();
	_users = channel._users;
	// users.insert(channel.users.begin(), channel.users.end());
	_channel_modes = channel._channel_modes;
	_server = channel._server;
}

Channel::~Channel() {
	_users.clear();
}

bool Channel::operator==(const Channel &channel) { return (get_name() == channel.get_name()); };

std::vector<Client*>::iterator Channel::search_user_invite(Client *client) {
	std::vector<Client*>::iterator it = _invite_list.begin();
	for (; it != _invite_list.end(); it++)
		if ((*it)->get_nickname() == client->get_nickname())
			return (it);
	return (it);
}

std::vector<Client*>::iterator Channel::search_user_ban(Client *client) {
	std::vector<Client*>::iterator it = _users_ban.begin();
	for (; it != _users_ban.end(); it++)
		if (*it == client)
			return (it);
	return (it);
}

std::string									Channel::get_name() const { return (_name); }
std::map<Client*, std::string>				&Channel::get_users()  { return (_users); }
std::vector<Client*>						&Channel::get_users_ban() { return (_users_ban); };
std::vector<Client*>						&Channel::get_invite_list() { return (_invite_list); };
std::map<Client*, std::string>::iterator	Channel::get_user(Client* client) { return (_users.find(client)); }
std::string									Channel::get_channel_modes() const { return (_channel_modes); }
std::string 								Channel::get_password() const { return (_password); }
std::string 								Channel::get_topic() const { return (topic); };
int 										Channel::get_user_limit() const { return (_user_limit); }
Server 										&Channel::get_server() const { return (*_server); }

void Channel::set_name(std::string val) {
	_name = val;
}


void Channel::set_server(Server *server) {
	_server = server;
}

void Channel::set_password(std::string password) {
	this->_password = password;
}

void Channel::set_user_limit(int limit) {
	_user_limit = limit;
}

void Channel::set_topic(std::string new_topic) {
		topic = new_topic;
}

void Channel::set_user(Client* client, Message &message, std::string key) { // Fonction qui sert a add un user au channel
	std::map<Client*, std::string>::iterator user_it = get_user(client);
	std::vector<Client*>::iterator user_ban_it;
	std::vector<Client*>::iterator user_invite_it;

	if (user_it == _users.end()) {
		user_ban_it = search_user_ban(client);
		if ((_channel_modes.find('l') == std::string::npos) || (_channel_modes.find('l') != std::string::npos && _users.size() < _user_limit)) {
			if (_users_ban.end() == user_ban_it) {
				if (_channel_modes.find('k') != std::string::npos) {
					if (key != _password) {
						send_message(*client, _server->print_numerics(475, *client, *client, NULL, &message));
						return ;
					}
				}
				if (_channel_modes.find('i') != std::string::npos) {
					user_invite_it = search_user_invite(client);
					if (user_invite_it != _invite_list.end()) { // Check si le user a recu une invitation
						_users.insert(std::pair<Client*, std::string>(client, ""));
						client->get_channel().push_back(this);
						_invite_list.erase(user_invite_it);
						send_message(*client, build_command_message(client->get_nickname(), "", get_name(), "JOIN"));
						if (topic.size() > 0)
							send_message(*client, _server->build_response(332, *client, *client, this, &message));
						for (std::map<Client*, std::string>::iterator it2 = get_users().begin(); it2 != get_users().end(); it2++)
							send_message(*(it2->first), build_message2(353, message.get_sender(), "", this));
							// send_message(message.get_sender(), build_message2(353, message.get_sender(), "", this));
						// send_message(_server->build_response(366, *client, *client, this, &message));
						send_message(*client, _server->build_response(366, *client, *client, this, &message));
					} else
						// send_message(_server->build_response(473, *client, *client, this, &message));
						send_message(*client, _server->build_response(473, *client, *client, this, &message));
				} else {
					if (_users.size() == 0)
						_users.insert(std::pair<Client*, std::string>(client, "o"));
					else
						_users.insert(std::pair<Client*, std::string>(client, ""));
					client->get_channel().push_back(this);
					send_message(*client, build_command_message(client->get_nickname(), "", get_name(), "JOIN"));
					if (topic.size() > 0)
						send_message(*client, _server->build_response(332, *client, *client, this, &message));
					for (std::map<Client*, std::string>::iterator it2 = get_users().begin(); it2 != get_users().end(); it2++)
						send_message(*(it2->first), build_message2(353, message.get_sender(), "", this));
					// send_message(_server->build_response(366, *client, *client, this, &message));
					send_message(*client, _server->build_response(366, *client, *client, this, &message));
				}
			} else
				send_message(*client, _server->print_numerics(474, *client, *client, NULL, &message));
				// send_message(*client, ft_print_numerics(474));
		} else
			send_message(*client, _server->print_numerics(471, *client, *client, NULL, &message));
			// send_message(*client, ft_print_numerics(471));
	} else
		send_message(*client, _server->print_numerics(443, *client, *client, this, &message));
}

void Channel::set_mode(Client *sender, char mode, std::string parameter) {
	size_t nb;

	if (mode == 'o') {
		if (parameter == "")
			send_message(*sender, build_message2(461, *sender, "MODE", this));
		else {
			set_user_mode(sender, mode, parameter);
			_channel_modes.push_back(mode);
		}
	} else if (mode == 'p')
		_channel_modes.push_back(mode);
	else if (mode == 's')
		_channel_modes.push_back(mode);
	else if (mode == 'i') {
		// for (std::map<Client*, std::string>::iterator it = get_users().begin(); it != get_users().end(); it++)
		// 	send_message(*(it->first), print_numerics(336, *sender, *sender, this));
		// send_message(*sender, print_numerics(337, *sender, *sender, this));

		//check RPL_INVEXLIST (346)
		// RPL_INVITELIST (336)
		// RPL_ENDOFINVITELIST (337)
		_channel_modes.push_back(mode);
	}
	else if (mode == 't')
		_channel_modes.push_back(mode);
	else if (mode == 'n')
		_channel_modes.push_back(mode);
	else if (mode == 'm')
		_channel_modes.push_back(mode);
	else if (mode == 'l') {
		if (parameter == "")
			send_message(*sender, build_message2(461, *sender, "MODE", this));
		for (size_t i = 0; i < parameter.size(); i++) {
			if ((parameter[i] < 48 || parameter[i] > 57) && parameter[i] != ' ') {
				std::cout << "Mode l : Parse Error" << std::endl;
				return ;
			}
		}
		std::istringstream(parameter) >> nb;
		if (nb > SIZE_MAX)
			send_message(*sender, build_message2(461, *sender, "MODE", this));
		else {
			_channel_modes.push_back(mode);
			set_user_limit(nb);
		}
	} else if (mode == 'b') {
		std::map<Client*, std::string>::iterator it = _users.begin();
		for (; it != _users.end(); it++)
			if ((*it).first->get_nickname() == parameter)
				break;
		if (it == _users.end())
			ft_print_numerics(401);
		else {
			ban_user((*it).first);
			// for (std::map<Client*, std::string>::iterator it = get_users().begin(); it != get_users().end(); it++)
			// 	send_message(*(it->first), print_numerics(367, *sender, *sender, this));
			// send_message(*(it->first), print_numerics(368, *sender, *sender, this));
			// ft_print_numerics(367); // RPL_BANLIST
			// ft_print_numerics(368); // RPL_ENDOFBANLIST
		}
	} else if (mode == 'v') {
		if (parameter == "")
			send_message(*sender, build_message2(461, *sender, "MODE", this));
		else
			set_user_mode(sender, mode, parameter);
	} else if (mode == 'k') {
		if (parameter == "")
			send_message(*sender, build_message2(461, *sender, "MODE", this));
		else {
			set_password(parameter);
			_channel_modes.push_back(mode);
		}
	}
	else
		ft_print_numerics(472);
}

void Channel::unset_mode(Client *sender, char mode, std::string parameter) {
	if (mode == 'o') {
		if (parameter == "")
			ft_print_numerics(461);
		else {
			unset_user_mode(sender, mode, parameter);
			_channel_modes.erase(_channel_modes.find(mode), 1);
		}
	} else if (mode == 'p')
		_channel_modes.erase(_channel_modes.find(mode), 1);
	else if (mode == 's')
		_channel_modes.erase(_channel_modes.find(mode), 1);
	else if (mode == 'i')
		_channel_modes.erase(_channel_modes.find(mode), 1);
	else if (mode == 't')
		_channel_modes.erase(_channel_modes.find(mode), 1);
	else if (mode == 'n')
		_channel_modes.erase(_channel_modes.find(mode), 1);
	else if (mode == 'm')
		_channel_modes.erase(_channel_modes.find(mode), 1);
	else if (mode == 'l') {
		_channel_modes.erase(_channel_modes.find(mode), 1);
		set_user_limit(0);
	} else if (mode == 'b') {
		std::map<Client*, std::string>::iterator it = _users.begin();
		for (; it != _users.end(); it++)
		if ((*it).first->get_nickname() == parameter)
			break; 
		if (it == _users.end())
			ft_print_numerics(401);
		else
			unban_user((*it).first);
	} else if (mode == 'v') {
		if (parameter == "")
			ft_print_numerics(461);
		else
			unset_user_mode(sender, mode, parameter);
	} else if (mode == 'k') {
		if (parameter == "")
			ft_print_numerics(461);
		else {
			set_password();
			_channel_modes.erase(_channel_modes.find(mode), 1);
		}
	}
}

void Channel::set_channel_modes(Client *sender, std::vector<std::string> parameters) {
	const std::string modes = "opsitnmlbvk";
	std::string mode = parameters[1];
	std::vector<std::string> params;
	std::string string_mode;
	char symbol;

	if (parameters.size() > 2)
		params = parse_comma(parameters[2]);
	if (mode.size() > 1) {
		if (mode[0] != '+' && mode[0] != '-')
			std::cout << "Mode : error syntax" << std::endl;
		else {
			for (size_t i = 0; i < mode.size(); i++) {
				if (mode[i] == '+' || mode[i] == '-') {
					symbol = mode[i];
					continue ;
				}
				if (symbol == '+') {
					if (modes.find(mode[i]) != std::string::npos) {
						if (_channel_modes.find(mode[i]) != std::string::npos) {
							send_message(*sender, _server->print_numerics(501, *sender, *sender, NULL, NULL));
							// send_message(*sender, build_message2(501, "", "", this));
							continue;
						} else {
							if (params.size() > 0 && i - 1 < params.size())
								set_mode(sender, mode[i], params[i - 1]);
							else
								set_mode(sender, mode[i]);
							send_message(*sender, build_command_message(sender->get_nickname(), "", get_name(), "MODE", parameters, params));
							// ft_print_numerics(324); // RPL_CHANNELMODEIS
						}
					} else {
						string_mode += mode[i];
						send_message(*sender, build_message2(472, *sender, string_mode, this));
						string_mode = "";
					}
				} else if (symbol == '-') {
					if (modes.find(mode[i]) != std::string::npos) {
						if (_channel_modes.find(mode[i]) == std::string::npos) {
							send_message(*sender, _server->print_numerics(501, *sender, *sender, NULL, NULL));
							// send_message(*sender, build_message2(501, "", "", this));
							continue;
						} else {
							if (params.size() > 0 && i - 1 < params.size())
								unset_mode(sender, mode[i], params[i - 1]);
							else
								unset_mode(sender, mode[i]);
							send_message(*sender, build_command_message(sender->get_nickname(), "", get_name(), "MODE", parameters, params));
						}
					}
				}
			}
		}
	} else
		send_message(*sender, _server->print_numerics(324, *sender, *sender, this, NULL));
		// ft_print_numerics(324); // RPL_CHANNELMODEIS (Si aucun mode n'est donné, renvoie juste les modes actuels) ==> check aussi RPL_CREATIONTIME(329)
}

void Channel::set_user_mode(Client *sender, char mode, std::string parameter) {
	std::map<Client*, std::string>::iterator it = _users.begin();
	for (; it != _users.end(); it++)
		if ((*it).first->get_nickname() == parameter)
			break;
	if (it == _users.end())
		send_message(*sender, build_message2(401, *sender, parameter, this));
	else {
		if (it->second.find(mode) == std::string::npos)
			it->second.push_back(mode);
	}
}

void Channel::unset_user_mode(Client *sender, char mode, std::string parameter) {
	std::map<Client*, std::string>::iterator it = _users.begin();
	for (; it != _users.end(); it++)
		if ((*it).first->get_nickname() == parameter)
			break;
	if (it == _users.end())
		send_message(*sender, build_message2(401, *sender, parameter, this));
	else {
		if (it->second.find(mode) != std::string::npos)
			it->second.erase(_channel_modes.find(mode), 1);
	}
}

int Channel::add_invite(Client *client) {
	std::vector<Client*>::iterator it = search_user_invite(client);
	std::vector<Client*>::iterator it2 = search_user_ban(client);
	std::map<Client*, std::string>::iterator it3;
	if (it2 == _users_ban.end()) {
		if (_users.find(client) != _users.end())
			return (443); 
		if (it == _invite_list.end())
			_invite_list.push_back(client);
	}
	return (0);
}

int Channel::remove_user(Client *client, std::vector<Channel> *channels) {
	std::map<Client*, std::string>::iterator it;
	std::vector<Channel>::iterator it2;
	for (it = _users.begin(); it != _users.end(); it++)
		if ((*it).first->get_nickname() == client->get_nickname())
			break ;
	_users.erase(it);
	client->get_channel().erase(client->get_channel_by_name(this->get_name()));
	remove_invite(client);
	if (_users.size() == 0) {
		for (it2 = channels->begin(); it2 != channels->end(); it2++)
			if (it2->get_name() == get_name())
				break ;			
		if (it2 != channels->end())
			channels->erase(it2);
	}
	return (0);
}

void Channel::remove_invite(Client *client) {
	std::vector<Client*>::iterator it = search_user_invite(client);
	if (_invite_list.end() != it)
		_invite_list.erase(it);
}

void Channel::ban_user(Client *client) {
	std::map<Client*, std::string>::iterator it = _users.find(client);
	std::vector<Client*>::iterator it2 = search_user_ban(client);
	
	if (_users.end() != it) {
		_users.erase(it);
		client->get_channel().erase(client->get_channel_by_name(this->get_name()));
	}
	if (_users_ban.end() == it2)
		_users_ban.push_back(client);
	remove_invite(client);
}


void Channel::unban_user(Client *client) {
	std::vector<Client*>::iterator it = search_user_ban(client);
	if (_users_ban.end() != it)
		_users_ban.erase(it);
}

void Channel::print_users() {
	for (std::map<Client*, std::string>::iterator it = _users.begin(); it != _users.end(); it++)
		std::cout << it->first->get_nickname() << std::endl;
}

std::vector<std::string> parse_comma(std::string parameter) {
	std::vector<std::string> strings_parse;
	int idx = 0;
	size_t pos = parameter.find(",", idx);
	while (pos != std::string::npos) {
		strings_parse.push_back(parameter.substr(idx, pos - idx));
		idx = pos + 1;
		pos = parameter.find(",", idx);
	}
	strings_parse.push_back(parameter.substr(idx, parameter.size() - idx));
	return (strings_parse);
}